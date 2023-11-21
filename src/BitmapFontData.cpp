///////////////////////////////////////////////////////////////////////////////
// BitmapFontData.cpp
// ==================
// draw bitmap text for GLFW app
// dependencies: GLAD, Matrix4, Vector2, Vector3, Tokenizer
//
//  AUTHOR: Song Ho Ahn (song.ahn@gmail.com)
// CREATED: 2009-04-15
// UPDATED: 2023-04-30
///////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <sstream>
#include <fstream>
#include "BitmapFontData.h"

// static member definition
float BitmapFontData::quadVertices[20];     // 4 of (x,y,z,s,t)

const char* BitmapFontData::vsSource =R"(
// GLSL version (OpenGL 3.3)
#version 330
// uniforms
uniform mat4 matrixModelViewProjection;
// vertex attribs (input)
layout(location=0) in vec3 vertexPosition;
layout(location=1) in vec2 vertexTexCoord;
// varyings (output)
out vec2 texCoord0;
void main()
{
    texCoord0 = vertexTexCoord;
    gl_Position = matrixModelViewProjection * vec4(vertexPosition, 1.0);
}
)";

const char* BitmapFontData::fsSource =R"(
// GLSL version (OpenGL 3.3)
#version 330
// uniforms
uniform vec4 materialDiffuse;           // material diffuse color
uniform sampler2D map0;                 // texture map #1
// varyings (input)
in vec2 texCoord0;
// output
out vec4 fragColor;
void main()
{
    fragColor = texture(map0, texCoord0) * materialDiffuse;
}
)";



///////////////////////////////////////////////////////////////////////////////
// ctor
///////////////////////////////////////////////////////////////////////////////
BitmapFontData::BitmapFontData() : size(0), base(0), bitmapWidth(0), bitmapHeight(0),
                                   bitmapWidthInv(1), bitmapHeightInv(1)
{
    vboId = vaoId = progId = 0;
    uniformMatrixModelViewProjection = uniformMaterialDiffuse = uniformMap0 = 0;

    color[0] = color[1] = color[2] = color[3] = 1.0f;
    scale.x = scale.y = 1.0f;
}



///////////////////////////////////////////////////////////////////////////////
// dtor
///////////////////////////////////////////////////////////////////////////////
BitmapFontData::~BitmapFontData()
{
    for(size_t i = 0; i < pages.size(); ++i)
    {
        glDeleteTextures(1, &pages[i]);
    }
    pages.clear();
    kernings.clear();
    characters.clear();

    glDeleteBuffers(1, &vboId);
    glDeleteVertexArrays(1, &vaoId);
    glDeleteProgram(progId);
    vboId = vaoId = progId = 0;
}



///////////////////////////////////////////////////////////////////////////////
// read font config & bitmap directly from data
///////////////////////////////////////////////////////////////////////////////
bool BitmapFontData::loadFont(const char* fontConfig, const unsigned char* fontBitmap)
{
    if(!fontConfig || !fontBitmap)
        return false;

    initShader();
    initVBO();

    // reset members
    for(size_t i = 0; i < pages.size(); ++i)
    {
        glDeleteTextures(1, &pages[i]);
    }
    pages.clear();
    kernings.clear();
    characters.clear();

    Tokenizer lines(fontConfig, "\n");
    Tokenizer fields;
    std::string line;
    std::string field;

    while((line = lines.next()) != "")
    {
        fields.set(line);
        field = fields.next();

        if(field == "info")
        {
        //    parseInfo(fields);
        }
        else if(field == "common")
        {
            parseCommon(fields);
        }
        else if(field == "page")
        {
            //parsePage(fields);
        }
        else if(field == "chars")
        {
            parseCharacterCount(fields);
        }
        else if(field == "char")
        {
            parseCharacter(fields);
        }
        else if(field == "kerning")
        {
            parseKerning(fields);
        }
    }

    // generate texture from data
    GLuint texId = generateTexture(fontBitmap);
    pages.push_back(texId);

    // set uvs per character
    initUVs();

    return true;
}



///////////////////////////////////////////////////////////////////////////////
// print text and return width of the text
///////////////////////////////////////////////////////////////////////////////
int BitmapFontData::drawText(float x, float y, const char* str)
{
    if(!str)
        return 0;

    if(pages.size() < 1)
        return 0;   // do nothing if no texture

    char chr;
    char prevChr = 0;
    BitmapCharacter character;
    std::pair<short, short> kerning;

    // snap to pixel
    int shiftX = (int)(x + 0.5f);
    int shiftY = (int)(y + 0.5f);

    // OpenGL calls
    glUseProgram(progId);
    glActiveTexture(GL_TEXTURE0);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    Matrix4 matrixModel;
    matrixModel.rotate(angle.z, 0,0,1);
    matrixModel.scale(scale.x, scale.y, 1);
    matrixModel.translate(shiftX, shiftY, 0);
    Matrix4 matrixModelViewProjection = matrixProjection * matrixModel;
    glUniformMatrix4fv(uniformMatrixModelViewProjection, 1, false, matrixModelViewProjection.get());

    glUniform4fv(uniformMaterialDiffuse, 1, color);
    glUniform1i(uniformMap0, 0);

    glBindVertexArray(vaoId);

    int cursor = 0;
    while((chr = *str++) != '\0')
    {
        character = characters[(short)chr];

        // kerning
        kerning.first = prevChr;
        kerning.second = chr;
        cursor += kernings[kerning];

        // interleaved triangle strip (vertex and texCoords)
        quadVertices[0] = cursor + character.xOffset;           // v0.x
        quadVertices[1] = base - character.yOffset;             // v0.y
        quadVertices[2] = 0;                                    // v0.z
        quadVertices[3] = character.uvs[0];                     // v0.s
        quadVertices[4] = character.uvs[1];                     // v0.t

        quadVertices[5] = cursor + character.xOffset;           // v1.x
        quadVertices[6] = quadVertices[1] - character.height;   // v1.y
        quadVertices[7] = 0;                                    // v1.z
        quadVertices[8] = character.uvs[0];                     // v1.s
        quadVertices[9] = character.uvs[3];                     // v1.t

        quadVertices[10] = quadVertices[0] + character.width;   // v2.x
        quadVertices[11] = base - character.yOffset;            // v2.y
        quadVertices[12] = 0;                                   // v2.z
        quadVertices[13] = character.uvs[2];                    // v2.s
        quadVertices[14] = character.uvs[1];                    // v2.t

        quadVertices[15] = quadVertices[0] + character.width;   // v3.x
        quadVertices[16] = quadVertices[1] - character.height;  // v3.y
        quadVertices[17] = 0;                                   // v3.z
        quadVertices[18] = character.uvs[2];                    // v3.s
        quadVertices[19] = character.uvs[3];                    // v3.t

        // update VBO
        glBindBuffer(GL_ARRAY_BUFFER, vboId);
        glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 20, quadVertices, GL_DYNAMIC_DRAW);

        // draw a quad
        glBindTexture(GL_TEXTURE_2D, pages[character.page]);
        glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

        // next
        cursor += character.xAdvance;
        prevChr = chr;
    }

    glBindTexture(GL_TEXTURE_2D, 0);
    glBindVertexArray(0);
    glUseProgram(0);

    return (int)(cursor * scale.x + 0.5f);  // return width of the current string
}



///////////////////////////////////////////////////////////////////////////////
// compute the width of the text
///////////////////////////////////////////////////////////////////////////////
int BitmapFontData::getTextWidth(const char* str)
{
    if(!str)
        return 0;

    char chr;
    char prevChr = 0;
    std::pair<short, short> kerning;

    int cursor = 0;
    while((chr = *str++) != '\0')
    {
        // kerning
        kerning.first = prevChr;
        kerning.second = chr;
        cursor += kernings[kerning];

        // next
        cursor += characters[(short)chr].xAdvance;
        prevChr = chr;
    }
    return (int)(cursor * scale.x + 0.5f);
}



///////////////////////////////////////////////////////////////////////////////
// resize window dimension and projection matrix
// call it before drawText() to setup viewport and ortho projection matrix
///////////////////////////////////////////////////////////////////////////////
void BitmapFontData::setWindowSize(int width, int height)
{
    const float N = -1.0f;
    const float F = 1.0f;

    // construct ortho projection matrix
    matrixProjection.identity();
    matrixProjection[0]  =  2.0f / width;
    matrixProjection[5]  =  2.0f / height;
    matrixProjection[10] = -2.0f / (F - N);
    matrixProjection[12] = -1.0f;
    matrixProjection[13] = -1.0f;
    matrixProjection[14] = -(F + N) / (F - N);
}



///////////////////////////////////////////////////////////////////////////////
void BitmapFontData::parseCommon(Tokenizer& str)
{
    std::string subStr;
    std::string field;
    short value;

    while((subStr = str.next()) != "")
    {
        getFieldAndValue(subStr, field, value);
        if(field == "lineHeight")
        {
            this->size = value;
        }
        else if(field == "base")
        {
            this->base = value;
        }
        else if(field == "scaleW")
        {
            this->bitmapWidth = value;
            this->bitmapWidthInv = 1.0f / this->bitmapWidth;
        }
        else if(field == "scaleH")
        {
            this->bitmapHeight = value;
            this->bitmapHeightInv = 1.0f / this->bitmapHeight;
        }
        //else if(field == "pages")
        //{
        //    this->pageCount = value;
        //}
    }
}



///////////////////////////////////////////////////////////////////////////////
void BitmapFontData::parseCharacterCount(Tokenizer& str)
{
    std::string subStr;
    std::string field;
    short value;

    while((subStr = str.next()) != "")
    {
        getFieldAndValue(subStr, field, value);
        if(field == "count")
        {
            characterCount = value;
        }
    }
}



///////////////////////////////////////////////////////////////////////////////
void BitmapFontData::parseCharacter(Tokenizer& str)
{
    std::string subStr;
    std::string field;
    short value;
    short index = 0;

    while((subStr = str.next()) != "")
    {
        getFieldAndValue(subStr, field, value);
        if(field == "id")
        {
            index = value;
            BitmapCharacter character;
            characters[index] = character;
        }
        else if(field == "x")
        {
            characters[index].x = value;
        }
        else if(field == "y")
        {
            characters[index].y = value;
        }
        else if(field == "width")
        {
            characters[index].width = value;
        }
        else if(field == "height")
        {
            characters[index].height = value;
        }
        else if(field == "xoffset")
        {
            characters[index].xOffset = value;
        }
        else if(field == "yoffset")
        {
            characters[index].yOffset = value;
        }
        else if(field == "xadvance")
        {
            characters[index].xAdvance = value;
        }
        else if(field == "page")
        {
            characters[index].page = value;
        }
    }
}



///////////////////////////////////////////////////////////////////////////////
void BitmapFontData::parseKerning(Tokenizer& str)
{
    std::string subStr;
    std::string field;
    short value;
    std::pair <short, short> kerning;

    while((subStr = str.next()) != "")
    {
        getFieldAndValue(subStr, field, value);
        if(field == "first")
        {
            kerning.first = value;
        }
        else if(field == "second")
        {
            kerning.second = value;
        }
        else if(field == "amount")
        {
            kernings[kerning] = value;
        }
    }
}



///////////////////////////////////////////////////////////////////////////////
void BitmapFontData::getFieldAndValue(const std::string& str, std::string& field, std::string& value)
{
    Tokenizer tokenizer(str, "=");
    field = tokenizer.next();
    value = tokenizer.next();
}

void BitmapFontData::getFieldAndValue(const std::string& str, std::string& field, short& value)
{
    std::string valueStr;
    Tokenizer tokenizer(str, "=");
    field = tokenizer.next();
    valueStr = tokenizer.next();
    std::stringstream ss(valueStr);
    ss >> value;
}



///////////////////////////////////////////////////////////////////////////////
// trim leading and tailing quote char
///////////////////////////////////////////////////////////////////////////////
void BitmapFontData::trimQuotes(std::string& str)
{
    str = str.substr(1, str.size()-2);
}



///////////////////////////////////////////////////////////////////////////////
// set font colour
///////////////////////////////////////////////////////////////////////////////
void BitmapFontData::setColor(float r, float g, float b, float a)
{
    this->color[0] = r;
    this->color[1] = g;
    this->color[2] = b;
    this->color[3] = a;
}

void BitmapFontData::setColor(const float color[4])
{
    if(!color)
        return;

    setColor(color[0], color[1], color[2], color[3]);
}

void BitmapFontData::setColor(const Vector4& color)
{
    setColor(color[0], color[1], color[2], color[3]);
}



///////////////////////////////////////////////////////////////////////////////
// set scale
///////////////////////////////////////////////////////////////////////////////
void BitmapFontData::setScale(float x, float y)
{
    scale.x = x;
    scale.y = y;
}

void BitmapFontData::setScale(const Vector2& scale)
{
    this->scale = scale;
}



///////////////////////////////////////////////////////////////////////////////
// set angle
///////////////////////////////////////////////////////////////////////////////
void BitmapFontData::setAngle(float z)
{
    angle.z = z;
}



///////////////////////////////////////////////////////////////////////////////
// init GLSL shader
///////////////////////////////////////////////////////////////////////////////
bool BitmapFontData::initShader()
{
    if(progId)
        return true;

    const int MAX_LENGTH = 2048;
    char log[MAX_LENGTH];
    int logLength = 0;

    // create shader and program
    GLuint vsId = glCreateShader(GL_VERTEX_SHADER);
    GLuint fsId = glCreateShader(GL_FRAGMENT_SHADER);
    progId = glCreateProgram();

    // load shader sources
    glShaderSource(vsId, 1, &BitmapFontData::vsSource, NULL);
    glShaderSource(fsId, 1, &BitmapFontData::fsSource, NULL);

    // compile shader sources
    glCompileShader(vsId);
    glCompileShader(fsId);

    //@@ debug
    int vsStatus, fsStatus;
    glGetShaderiv(vsId, GL_COMPILE_STATUS, &vsStatus);
    if(vsStatus == GL_FALSE)
    {
        glGetShaderiv(vsId, GL_INFO_LOG_LENGTH, &logLength);
        glGetShaderInfoLog(vsId, MAX_LENGTH, &logLength, log);
        std::cout << "===== Vertex Shader Log =====\n" << log << std::endl;
    }
    glGetShaderiv(fsId, GL_COMPILE_STATUS, &fsStatus);
    if(fsStatus == GL_FALSE)
    {
        glGetShaderiv(fsId, GL_INFO_LOG_LENGTH, &logLength);
        glGetShaderInfoLog(fsId, MAX_LENGTH, &logLength, log);
        std::cout << "===== Fragment Shader Log =====\n" << log << std::endl;
    }

    // attach shaders to the program
    glAttachShader(progId, vsId);
    glAttachShader(progId, fsId);

    // link program
    glLinkProgram(progId);

    // get uniform/attrib locations
    glUseProgram(progId);
    uniformMatrixModelViewProjection = glGetUniformLocation(progId, "matrixModelViewProjection");
    uniformMaterialDiffuse           = glGetUniformLocation(progId, "materialDiffuse");
    uniformMap0                      = glGetUniformLocation(progId, "map0");

    // unbind GLSL
    glUseProgram(0);
    glDeleteShader(vsId);
    glDeleteShader(fsId);

    // check GLSL status
    int linkStatus;
    glGetProgramiv(progId, GL_LINK_STATUS, &linkStatus);
    if(linkStatus == GL_FALSE)
    {
        glGetProgramiv(progId, GL_INFO_LOG_LENGTH, &logLength);
        glGetProgramInfoLog(progId, MAX_LENGTH, &logLength, log);
        std::cout << "===== GLSL Program Log =====\n" << log << std::endl;
        return false;
    }
    else
    {
        return true;
    }
}



///////////////////////////////////////////////////////////////////////////////
// init VBO & VAO
///////////////////////////////////////////////////////////////////////////////
void BitmapFontData::initVBO()
{
    if(!vaoId)
        glGenVertexArrays(1, &vaoId);
    glBindVertexArray(vaoId);

    if(!vboId)
        glGenBuffers(1, &vboId);

    glBindBuffer(GL_ARRAY_BUFFER, vboId);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 20, quadVertices, GL_DYNAMIC_DRAW);

    // enable vertex array attributes for bound VAO
    // use explict attribute locations: vertex=0, texCoord=1
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    // store vertex array pointers to bound VAO
    int stride = sizeof(float) * 5;
    glVertexAttribPointer(0, 3, GL_FLOAT, false, stride, 0);
    glVertexAttribPointer(1, 2, GL_FLOAT, false, stride, (void*)(3 * sizeof(float)));

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}



///////////////////////////////////////////////////////////////////////////////
// create texture object from data
///////////////////////////////////////////////////////////////////////////////
GLuint BitmapFontData::generateTexture(const unsigned char* data)
{
    GLint format = GL_RED;  // single channel

    // copy the texture to OpenGL
    GLuint texture;
    glGenTextures(1, &texture);

    // set active texture and configure it
    glBindTexture(GL_TEXTURE_2D, texture);

    // select modulate to mix texture with color for shading
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

    // swizzle red channel to alpha and others are 1
    int swizzleMask[] = {GL_ONE, GL_ONE, GL_ONE, GL_RED};
    glTexParameteriv(GL_TEXTURE_2D, GL_TEXTURE_SWIZZLE_RGBA, swizzleMask);

    glTexImage2D(GL_TEXTURE_2D, 0, format, this->bitmapWidth, this->bitmapHeight, 0, format, GL_UNSIGNED_BYTE, data);

    glBindTexture(GL_TEXTURE_2D, 0);

    return texture;
}



///////////////////////////////////////////////////////////////////////////////
void BitmapFontData::initUVs()
{
    std::map<short, BitmapCharacter>::iterator iter = characters.begin();
    while(iter != characters.end())
    {
        iter->second.uvs[0] = iter->second.x * bitmapWidthInv;
        iter->second.uvs[1] = iter->second.y * bitmapHeightInv;
        iter->second.uvs[2] = (iter->second.x + iter->second.width) * bitmapWidthInv;
        iter->second.uvs[3] = (iter->second.y + iter->second.height) * bitmapHeightInv;

        ++iter;
    }
}
