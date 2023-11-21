///////////////////////////////////////////////////////////////////////////////
// BitmapFontData.h
// ================
// draw bitmap text for GLFW app
// dependencies: GLAD, Matrix4, Vector2, Vector3, Tokenizer
//
//  AUTHOR: Song Ho Ahn (song.ahn@gmail.com)
// CREATED: 2009-04-15
// UPDATED: 2023-04-30
///////////////////////////////////////////////////////////////////////////////

#ifndef BITMAP_FONT_DATA_H
#define BITMAP_FONT_DATA_H

#include <gl.h>

#include <string>
#include <vector>
#include <map>
#include <utility>
#include "Vectors.h"
#include "Matrices.h"
#include "Tokenizer.h"



///////////////////////////////////////////////////////////////////////////////
// character descriptor
struct BitmapCharacter
{
    short x;
    short y;
    short width;
    short height;
    short xOffset;
    short yOffset;
    short xAdvance;
    short page;
    Vector4 uvs;    // s1, t1, s2, t2

    BitmapCharacter() : x(0), y(0), width(0), height(0), xOffset(0), yOffset(0),
                        xAdvance(0), page(0) {};
};



///////////////////////////////////////////////////////////////////////////////
class BitmapFontData
{
public:
    BitmapFontData();
    ~BitmapFontData();

    bool loadFont(const char* fontConfig, const unsigned char* fontBitmap);
    int drawText(float x, float y, const char* str);
    int getTextWidth(const char* str);
    void setWindowSize(int w, int h);

    void setColor(float r, float g, float b, float a);
    void setColor(const float color[4]);
    void setColor(const Vector4& color);
    void setScale(float x, float y);
    void setScale(const Vector2& scale);
    void setAngle(float z);

    short getHeight() const                 { return size; }
    short getBaseline() const               { return base; }

protected:


private:
    void parseCommon(Tokenizer& str);
    void parseCharacterCount(Tokenizer& str);
    void parseCharacter(Tokenizer& str);
    void parseKerning(Tokenizer& str);
    void initUVs();

    bool initShader();
    void initVBO();
    GLuint generateTexture(const unsigned char* data);

    static void getFieldAndValue(const std::string& str, std::string& field, std::string& value);
    static void getFieldAndValue(const std::string& str, std::string& field, short& value);
    static void trimQuotes(std::string& str);

    //std::string name;
    short size;
    short base;
    short bitmapWidth;
    short bitmapHeight;
    float bitmapWidthInv;
    float bitmapHeightInv;
    short characterCount;

    //short pageCount;
    std::vector<GLuint> pages;
    std::map<short, BitmapCharacter> characters;
    std::map<std::pair<short, short>, short> kernings;
    std::string path;

    static float quadVertices[20];      // 5 * 4
    GLuint vboId;
    GLuint vaoId;
    GLuint progId;
    static const char* vsSource;
    static const char* fsSource;
    GLint uniformMatrixModelViewProjection; // uniform locations
    GLint uniformMaterialDiffuse;
    GLint uniformMap0;
    float color[4];
    Vector2 scale;
    Vector3 angle;
    Matrix4 matrixProjection;
};

#endif
