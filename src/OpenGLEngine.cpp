// https://github.com/ocornut/imgui
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

// http://www.songho.ca/opengl/gl_sphere.html
#include "Sphere.h"
#include "Bmp.h"
#include "BitmapFontData.h"
#include "fontCourier20.h"
#include "Matrices.h"
#include "Timer.h"
#include "Vectors.h"

// https://www.glfw.org/
#include <gl.h>
#define GLFW_INCLUDE_NONE
#include <glfw3.h>
 
// https://github.com/datenwolf/linmath.h/blob/master/linmath.h
#include "linmath.h"

// https://github.com/g-truc/glm
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
 
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>

#include "OpenGLEngine.h"
#include "TLEReader.h"

// Constructor
OpenGLEngine::OpenGLEngine() {
    Sphere newSphere(1.0f, 128, 64, true, 2);

    earth = newSphere;
    sunAngle = new float(0.0f);
}

// Initialize OpenGL
void OpenGLEngine::init() {
    initSharedMem();

    if (!glfwInit())
        exit(EXIT_FAILURE);
 
    #ifdef __APPLE__
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    #endif
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
 
    window = glfwCreateWindow(1280, 720, "Space Debris Tracker", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }
 
    glfwMakeContextCurrent(window);
    gladLoadGL(glfwGetProcAddress);
    glfwSetWindowUserPointer(window, this);
 
    // glGenBuffers(1, &vertex_buffer);
    // glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
    // glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // Read TLE Data
    TLEReader tle;

    points = tle.ReadFile("2023_332.txt", numSats);

    cout << points[0] << points[1], points[2];

    initGL();
    initGLSL();
    initVBO();

    bmFont.loadFont(fontCourier20, bitmapCourier20);

    // init GLFW callbacks
    glfwSetFramebufferSizeCallback(window, framebufferSizeCallbackWrapper);
    glfwSetKeyCallback(window, keyCallbackWrapper);
    glfwSetMouseButtonCallback(window, mouseButtonCallbackWrapper);
    glfwSetCursorPosCallback(window, cursorPosCallbackWrapper);
    glfwSetErrorCallback(errorCallback);
    glfwSetScrollCallback(window, scrollCallbackWrapper);


    // load BMP image
    texId = loadTexture("earth10k.bmp", true);
    if(texId)
    {
        std::cout << "Loaded a texture: ID=" << texId << std::endl;
    }
    else
    {
        std::cout << "[ERROR] Failed to load a texture" << std::endl;
    }

    toPerspective();

    const GLubyte* renderer = glGetString(GL_RENDERER); // get renderer string
    const GLubyte* version = glGetString(GL_VERSION); // version as a string
    std::cout << "Renderer: " << renderer << std::endl;
    std::cout << "OpenGL version supported: " << version << std::endl;

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330");

    glfwSwapInterval(1);
}

void OpenGLEngine::shutdown() {
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
 
    glfwDestroyWindow(window);
 
    glfwTerminate();
}

void OpenGLEngine::mainEventLoop() {

    while (!glfwWindowShouldClose(window)) {
        // get frame time
        double currTime = glfwGetTime();
        double frameTime = currTime - runTime;
        runTime = currTime;

        // draw
        preFrame(frameTime);
        frame(frameTime);
        postFrame(frameTime);

        glfwPollEvents();
    }
    
}

bool OpenGLEngine::initSharedMem()
{
    windowWidth = fbWidth = WINDOW_WIDTH;
    windowHeight = fbHeight = WINDOW_HEIGHT;

    runTime = 0;

    mouseLeftDown = mouseRightDown = mouseMiddleDown = false;
    mouseX = mouseY = 0;

    cameraAngleX = cameraAngleY = 0.0f;
    cameraDistance = CAMERA_DISTANCE;

    drawMode = 0; // 0:fill, 1: wireframe, 2:points

    vao = 0;
    pointsVao = 0;
    vbo = 0;
    pointsVbo = 0;
    ibo = 0;
    texId = 0;

    // debug
    earth.printSelf();

    return true;
}

void OpenGLEngine::initGL()
{
    glPixelStorei(GL_UNPACK_ALIGNMENT, 4);      // 4-byte pixel alignment

    // enable /disable features
    //glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
    //glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
    glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glEnable(GL_LIGHTING);


    glClearColor(0, 0, 0, 0);                   // background color
    glClearStencil(0);                          // clear stencil buffer
    glClearDepth(1.0f);                         // 0 is near, 1 is far
    glDepthFunc(GL_LEQUAL);
}

///////////////////////////////////////////////////////////////////////////////
// create glsl programs
///////////////////////////////////////////////////////////////////////////////
bool OpenGLEngine::initGLSL()
{
    const int MAX_LENGTH = 2048;
    char log[MAX_LENGTH];
    int logLength = 0;

    // create shader and program
    GLuint vsId = glCreateShader(GL_VERTEX_SHADER);
    GLuint fsId = glCreateShader(GL_FRAGMENT_SHADER);
    progId = glCreateProgram();

    // load shader sources
    glShaderSource(vsId, 1, &vsSource, NULL);
    glShaderSource(fsId, 1, &fsSource, NULL);

    // compile shader sources
    glCompileShader(vsId);
    glCompileShader(fsId);

    //@@ debug
    int vsStatus, fsStatus, psStatus;
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

    uniformMatrixModelView           = glGetUniformLocation(progId, "matrixModelView");
    uniformMatrixModelViewProjection = glGetUniformLocation(progId, "matrixModelViewProjection");
    uniformMatrixNormal              = glGetUniformLocation(progId, "matrixNormal");
    // uniformLightPosition             = glGetUniformLocation(progId, "lightPosition");
    uniformLightAmbient              = glGetUniformLocation(progId, "lightAmbient");
    uniformLightDiffuse              = glGetUniformLocation(progId, "lightDiffuse");
    uniformLightSpecular             = glGetUniformLocation(progId, "lightSpecular");
    uniformMaterialAmbient           = glGetUniformLocation(progId, "materialAmbient");
    uniformMaterialDiffuse           = glGetUniformLocation(progId, "materialDiffuse");
    uniformMaterialSpecular          = glGetUniformLocation(progId, "materialSpecular");
    uniformMaterialShininess         = glGetUniformLocation(progId, "materialShininess");
    uniformMap0                      = glGetUniformLocation(progId, "map0");
    uniformTextureUsed               = glGetUniformLocation(progId, "textureUsed");
    attribVertexPosition = glGetAttribLocation(progId, "vertexPosition");
    attribVertexNormal   = glGetAttribLocation(progId, "vertexNormal");
    attribVertexTexCoord = glGetAttribLocation(progId, "vertexTexCoord");

    uniformLightDirection = glGetUniformLocation(progId, "lightDirection");

    // set uniform values
    //float lightPosition[] = {-2, 0, 1, 0};
    float lightDirection[] = {-1.0, 0.0, 1.0, 0.0};
    float lightAmbient[]  = {0.0f, 0.4f, 0.6f, 2};
    float lightDiffuse[]  = {0.7f, 0.7f, 0.7f, 1};
    float lightSpecular[] = {1.0f, 1.0f, 1.0f, 1};
    float materialAmbient[]  = {1.0f, 0.2f, 0.3f, 1};
    float materialDiffuse[]  = {1.7f, 1.7f, 1.7f, 1};
    float materialSpecular[] = {0.4f, 0.4f, 0.4f, 0};
    float materialShininess  = 16;

    // glUniform4fv(uniformLightPosition, 1, lightPosition);
    glUniform4fv(uniformLightDirection, 1, lightDirection);
    glUniform4fv(uniformLightAmbient, 1, lightAmbient);
    glUniform4fv(uniformLightDiffuse, 1, lightDiffuse);
    glUniform4fv(uniformLightSpecular, 1, lightSpecular);
    glUniform4fv(uniformMaterialAmbient, 1, materialAmbient);
    glUniform4fv(uniformMaterialDiffuse, 1, materialDiffuse);
    glUniform4fv(uniformMaterialSpecular, 1, materialSpecular);
    glUniform1f(uniformMaterialShininess, materialShininess);
    
    glUniform1i(uniformMap0, 0);
    glUniform1i(uniformTextureUsed, 1);

    // glUniform4fv(glGetUniformLocation(progId, "lightDirection"), 1, lightDir);

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
// copy vertex data to VBO and VA state to VAO
///////////////////////////////////////////////////////////////////////////////
void OpenGLEngine::initVBO()
{
    // Earth
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    glGenBuffers(1, &vbo);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, earth.getInterleavedVertexSize(), earth.getInterleavedVertices(), GL_STATIC_DRAW);

    // Index Array
    glGenBuffers(1, &ibo);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, earth.getIndexSize(), earth.getIndices(), GL_STATIC_DRAW);

    glEnableVertexAttribArray(attribVertexPosition);
    glEnableVertexAttribArray(attribVertexNormal);
    glEnableVertexAttribArray(attribVertexTexCoord);

    int stride = earth.getInterleavedStride();
    glVertexAttribPointer(attribVertexPosition, 3, GL_FLOAT, false, stride, 0);
    glVertexAttribPointer(attribVertexNormal, 3, GL_FLOAT, false, stride, (void*)(3 * sizeof(float)));
    glVertexAttribPointer(attribVertexTexCoord, 2, GL_FLOAT, false, stride, (void*)(6 * sizeof(float)));
    
    cout << "POINTS ARRAY: " << numSats << endl;
    // Points
    glGenBuffers(1, &pointsVbo);
    
    glBindBuffer(GL_ARRAY_BUFFER, pointsVbo);
    glBufferData(GL_ARRAY_BUFFER, numSats * 3 * sizeof(GLfloat), points, GL_STATIC_DRAW);

    glGenVertexArrays(1, &pointsVao);
    glBindVertexArray(pointsVao);


    glEnableVertexAttribArray(attribVertexPosition);
    glVertexAttribPointer(attribVertexPosition, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glBindVertexArray(0);

    // Unbind
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}


void OpenGLEngine::clearSharedMem()
{
    // Clean up Earth
    glDeleteBuffers(1, &vbo);
    glDeleteBuffers(1, &ibo);
    vbo = ibo = 0;
    glDeleteVertexArrays(1, &vao);
    vao = vao = 0;

    // Clean up points
    glDeleteBuffers(1, &pointsVbo);
    glDeleteVertexArrays(1, &pointsVao);

    // Clean up textures
    glDeleteTextures(1, &texId);
    texId = 0;

}



///////////////////////////////////////////////////////////////////////////////
// load raw image as a texture
///////////////////////////////////////////////////////////////////////////////
GLuint OpenGLEngine::loadTexture(const char* fileName, bool wrap)
{
    Image::Bmp bmp;
    if(!bmp.read(fileName))
        return 0;     // exit if failed load image

    // get bmp info
    int width = bmp.getWidth();
    int height = bmp.getHeight();
    const unsigned char* data = bmp.getDataRGB();
    GLenum type = GL_UNSIGNED_BYTE;    // only allow BMP with 8-bit per channel

    // We assume the image is 8-bit, 24-bit or 32-bit BMP
    GLenum format;
    int bpp = bmp.getBitCount();
    if(bpp == 8)
        format = GL_LUMINANCE;
    else if(bpp == 24)
        format = GL_RGB;
    else if(bpp == 32)
        format = GL_RGBA;
    else
        return 0;               // NOT supported, exit

    // gen texture ID
    GLuint texture;
    glGenTextures(1, &texture);

    // set active texture and configure it
    glBindTexture(GL_TEXTURE_2D, texture);

    // select modulate to mix texture with color for shading
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    //glTexParameteri(GL_TEXTURE_2D, GL_GENERATE_MIPMAP, GL_TRUE);

    // if wrap is true, the texture wraps over at the edges (repeat)
    //       ... false, the texture ends at the edges (clamp)
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrap ? GL_REPEAT : GL_CLAMP);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrap ? GL_REPEAT : GL_CLAMP);
    //glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    //glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    // copy texture data
    glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, type, data);
    glGenerateMipmap(GL_TEXTURE_2D);

    return texture;
}



///////////////////////////////////////////////////////////////////////////////
// display info messages
///////////////////////////////////////////////////////////////////////////////
void OpenGLEngine::showInfo()
{
    toOrtho();

    // call it once before drawing text to configure orthographic projection
    bmFont.setWindowSize(windowWidth, windowHeight);

    // std::stringstream ss;
    // ss << std::fixed << std::setprecision(3);

    // int x = 1;
    // int y = windowHeight - bmFont.getBaseline();
    // bmFont.setColor(1, 1, 1, 1);

    // ss << "Sphere Radius: " << earth.getRadius() << std::ends;
    // bmFont.drawText(x, y, ss.str().c_str());
    // ss.str("");
    // y -= bmFont.getHeight();

    // ss << "Sector Count: " << earth.getSectorCount() << std::ends;
    // bmFont.drawText(x, y, ss.str().c_str());
    // ss.str("");
    // y -= bmFont.getHeight();

    // ss << "Stack Count: " << earth.getStackCount() << std::ends;
    // bmFont.drawText(x, y, ss.str().c_str());
    // ss.str("");
    // y -= bmFont.getHeight();

    // ss << "Vertex Count: " << earth.getVertexCount() << std::ends;
    // bmFont.drawText(x, y, ss.str().c_str());
    // ss.str("");
    // y -= bmFont.getHeight();

    // ss << "Index Count: " << earth.getIndexCount() << std::ends;
    // bmFont.drawText(x, y, ss.str().c_str());
    // ss.str("");

    // // unset floating format
    // ss << std::resetiosflags(std::ios_base::fixed | std::ios_base::floatfield);

    showFPS();

    // go back to perspective mode
    toPerspective();
}




///////////////////////////////////////////////////////////////////////////////
// display frame rates
///////////////////////////////////////////////////////////////////////////////
void OpenGLEngine::showFPS()
{
    static Timer timer;
    static int count = 0;
    static std::string fps = "0.0 FPS";
    double elapsedTime = 0.0;

    ++count;

    // update fps every second
    elapsedTime = timer.getElapsedTime();
    if(elapsedTime >= 1.0)
    {
        std::stringstream ss;
        ss << std::fixed << std::setprecision(1);
        ss << (count / elapsedTime) << " FPS" << std::ends; // update fps string
        ss << std::resetiosflags(std::ios_base::fixed | std::ios_base::floatfield);
        fps = ss.str();
        count = 0;                      // reset counter
        timer.start();                  // restart timer
    }

    // draw FPS at top-right corner
    int x = windowWidth - bmFont.getTextWidth(fps.c_str()) - 1;
    int y = windowHeight - bmFont.getBaseline();
    bmFont.setColor(1, 1, 0, 1.0f);
    bmFont.drawText(x, y, fps.c_str());
}



///////////////////////////////////////////////////////////////////////////////
// set projection matrix as orthogonal
///////////////////////////////////////////////////////////////////////////////
void OpenGLEngine::toOrtho()
{
    const float N = -1.0f;
    const float F = 1.0f;

    // get current dimensions
    glfwGetWindowSize(window, &windowWidth, &windowHeight); // get window size
    glfwGetFramebufferSize(window, &fbWidth, &fbHeight);    // get framebuffer size

    // set viewport to be the entire framebuffer size
    glViewport(0, 0, (GLsizei)fbWidth, (GLsizei)fbHeight);

    // construct ortho projection matrix, not framebuffer size
    matrixProjection.identity();
    matrixProjection[0]  =  2.0f / windowWidth;
    matrixProjection[5]  =  2.0f / windowHeight;
    matrixProjection[10] = -2.0f / (F - N);
    matrixProjection[12] = -1.0f;
    matrixProjection[13] = -1.0f;
    matrixProjection[14] = -(F + N) / (F - N);
}



///////////////////////////////////////////////////////////////////////////////
// set the projection matrix as perspective
///////////////////////////////////////////////////////////////////////////////
void OpenGLEngine::toPerspective()
{
    const float N = 0.1f;
    const float F = 100.0f;
    const float FOV_Y = 40.0f / 180.0f * acos(-1.0f);    // in radian

    // get current dimensions
    glfwGetWindowSize(window, &windowWidth, &windowHeight); // get window size
    glfwGetFramebufferSize(window, &fbWidth, &fbHeight);    // get framebuffer size

    // set viewport to be the entire framebuffer size
    glViewport(0, 0, (GLsizei)fbWidth, (GLsizei)fbHeight);

    // construct perspective projection matrix
    float aspectRatio = (float)(windowWidth) / windowHeight;
    float tangent = tanf(FOV_Y / 2.0f);     // tangent of half fovY
    float h = N * tangent;                  // half height of near plane
    float w = h * aspectRatio;              // half width of near plane
    matrixProjection.identity();
    matrixProjection[0]  =  N / w;
    matrixProjection[5]  =  N / h;
    matrixProjection[10] = -(F + N) / (F - N);
    matrixProjection[11] = -1;
    matrixProjection[14] = -(2 * F * N) / (F - N);
    matrixProjection[15] =  0;
}



///////////////////////////////////////////////////////////////////////////////
// render each frame
///////////////////////////////////////////////////////////////////////////////
void OpenGLEngine::preFrame(double frameTime)
{
}

void OpenGLEngine::frame(double frameTime)
{
    // Clear buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

    // Transform camera (view)
    Matrix4 matrixView;
    matrixView.translate(0, 0, -cameraDistance);

    // Common model matrix
    Matrix4 matrixModelCommon;
    matrixModelCommon.rotateY(cameraAngleY);
    matrixModelCommon.rotateX(cameraAngleX);

    // Model matrix for each instance
    Matrix4 matrixModel(matrixModelCommon);
    matrixModel.translate(0.5, 0, 0);

    // Bind GLSL, texture
    glUseProgram(progId);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texId);

    Matrix4 matrixModelViewProjection = matrixProjection * matrixModelView;
    Matrix4 matrixNormal = matrixModelView;

    // float lightDir[] = {*sunAngle, 0.0f, -*sunAngle, 0.0f};
    int lightSector = *sunAngle / 90;
    int lightAmount = static_cast<int>(*sunAngle) % 90;

    

    // Set matrix uniforms
    matrixModelView = matrixView * matrixModel;
    matrixModelViewProjection = matrixProjection * matrixModelView;
    matrixNormal = matrixModelView;
    matrixNormal.setColumn(3, Vector4(0,0,0,1));

    // Calculate Light Direction
    float radians = *sunAngle * 3.1416 / 180.0;
    float radiansX = abs(cameraAngleX) * 3.1416 / 180.0;
    float radiansY = cameraAngleY * 3.1416 / 180.0;

    float weight = cameraAngleX / 90.0;

    float lightDir[] = {cos(radians - radiansY), sin(radians - radiansY) * -weight, sin(radians - radiansY) * (1 - abs(weight)), 0.0f};
    glUniform4fv(glGetUniformLocation(progId, "lightDirection"), 1, lightDir);

    glUniformMatrix4fv(uniformMatrixModelView, 1, false, matrixModelView.get());
    glUniformMatrix4fv(uniformMatrixModelViewProjection, 1, false, matrixModelViewProjection.get());
    glUniformMatrix4fv(uniformMatrixNormal, 1, false, matrixNormal.get());

    // Rendered with texture
    glUniform1i(uniformTextureUsed, 1);

    // Draw earth
    glBindVertexArray(vao);
    glDrawElements(GL_TRIANGLES, earth.getIndexCount(), GL_UNSIGNED_INT, (void*)0);
    glBindVertexArray(0);

    // Draw Points
    glUniform1i(glGetUniformLocation(progId, "isPoint"), GL_TRUE);
    glPointSize(5);
    glBindVertexArray(pointsVao);
    glDrawArrays(GL_POINTS, 0, numSats);
    glUniform1i(glGetUniformLocation(progId, "isPoint"), GL_FALSE);

    // Unbind
    glBindTexture(GL_TEXTURE_2D, 0);
    glBindVertexArray(0);
    glUseProgram(0);

    showInfo();

    // GUI
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    ImGui::Begin("Test Window");
    ImGui::Text("Space Debris Tracker");
    ImGui::Text(std::to_string(cameraAngleX).c_str());
    ImGui::Text(std::to_string(cameraAngleY).c_str());
    ImGui::Text(std::to_string(weight).c_str());
    ImGui::Text("Input Date (DD/MM/YYYY)");
    ImGui::InputText("Day", day, 3);
    ImGui::InputText("Month", month, 3);
    ImGui::InputText("Year", year, 5);
    ImGui::Button("Go");
    ImGui::SliderFloat("Sun Angle", this->sunAngle, 0.0f, 359.9f, "%.1f");
    ImGui::End();

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());


    

    glfwSwapBuffers(window);
}

void OpenGLEngine::postFrame(double frameTime)
{
    static double elapsedTime = 0.0;
    static int frameCount = 0;
    elapsedTime += frameTime;
    ++frameCount;
    if(elapsedTime > 1.0)
    {
        double fps = frameCount / elapsedTime;
        elapsedTime = 0;
        frameCount = 0;
        //std::cout << "FPS: " << fps << std::endl;
    }
}


//=============================================================================
// GLFW CALLBACKS
//=============================================================================

void OpenGLEngine::framebufferSizeCallback(GLFWwindow* window, int w, int h)
{
    toPerspective();
    std::cout << "Framebuffer resized: " << fbWidth << "x" << fbHeight
              << " (Window: " << windowWidth << "x" << windowHeight << ")" << std::endl;
}



void OpenGLEngine::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    {
        //std::cout << "Closing program" << std::endl;
        clearSharedMem();
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }
    else if(key == GLFW_KEY_SPACE && action == GLFW_PRESS)
    {
        earth.reverseNormals();
        initVBO();  // copy new vertext data to VBOs
    }
    else if(key == GLFW_KEY_D && action == GLFW_PRESS)
    {
        ++drawMode;
        drawMode %= 3;
        if(drawMode == 0)        // fill mode
        {
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
            glEnable(GL_DEPTH_TEST);
            glEnable(GL_CULL_FACE);
        }
        else if(drawMode == 1)  // wireframe mode
        {
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
            glDisable(GL_DEPTH_TEST);
            glDisable(GL_CULL_FACE);
        }
        else                    // point mode
        {
            glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
            glDisable(GL_DEPTH_TEST);
            glDisable(GL_CULL_FACE);
        }
    }
}

void OpenGLEngine::mouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
{
    // remember mouse position
    glfwGetCursorPos(window, &mouseX, &mouseY);

    ImGuiIO& io = ImGui::GetIO();

    if(button == GLFW_MOUSE_BUTTON_LEFT && !io.WantCaptureMouse)
    {
        if(action == GLFW_PRESS)
            mouseLeftDown = true;
        else if(action == GLFW_RELEASE)
            mouseLeftDown = false;
    }
    else if(button == GLFW_MOUSE_BUTTON_RIGHT)
    {
        if(action == GLFW_PRESS)
            mouseRightDown = true;
        else if(action == GLFW_RELEASE)
            mouseRightDown = false;
    }
    else if(button == GLFW_MOUSE_BUTTON_MIDDLE)
    {
        if(action == GLFW_PRESS)
            mouseMiddleDown = true;
        else if(action == GLFW_RELEASE)
            mouseMiddleDown = false;
    }
}

void OpenGLEngine::cursorPosCallback(GLFWwindow* window, double x, double y)
{
    if(mouseLeftDown)
    {
        cameraAngleY += (x - mouseX);
        cameraAngleX += (y - mouseY);

        if (cameraAngleX > 90.0) {
            cameraAngleX = 90.0;
        }
        if (cameraAngleX < -90.0) {
            cameraAngleX = -90.0;
        }
        mouseX = x;
        mouseY = y;
    }
    if(mouseRightDown)
    {
        cameraDistance -= (y - mouseY) * 0.2f;
        mouseY = y;
    }
}

void OpenGLEngine::scrollCallback(GLFWwindow* window, double xoffset, double yoffset) {
    if (yoffset) {
        cameraDistance += yoffset * 0.2f;
        if (cameraDistance < 1.0) {
            cameraDistance = 1.0;
        }
    }
}
