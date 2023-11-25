// https://github.com/ocornut/imgui
#include "imgui.h"

// http://www.songho.ca/opengl/gl_sphere.html
#include "Sphere.h"
#include "Bmp.h"
#include "BitmapFontData.h"
#include "Matrices.h"

// https://www.glfw.org/
#include <gl.h>
#define GLFW_INCLUDE_NONE
#include <glfw3.h>

#include <iostream>

#pragma once

class OpenGLEngine {
    public:
    // Constructor
    OpenGLEngine();

    // ImGUI
    char day[3];
    char month[3];
    char year[5];

    float* sunAngle;

    // function prototypes
    void init();

    void preFrame(double frameTime);
    void frame(double frameTime);
    void postFrame(double frameTime);
    void toPerspective();
    void toOrtho();
    void initGL();
    bool initGLSL();
    void initVBO();
    bool initSharedMem();
    void clearSharedMem();
    GLuint loadTexture(const char* fileName, bool wrap=true);
    void showInfo();
    void showFPS();

    void mainEventLoop();
    void shutdown();

    // Window
    GLFWwindow* window;

    private:
    // glfw callbacks
    void framebufferSizeCallback(GLFWwindow* window, int width, int height);
    void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
    void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
    void cursorPosCallback(GLFWwindow* window, double x, double y);
    
    static void framebufferSizeCallbackWrapper(GLFWwindow* window, int width, int height) {
        OpenGLEngine* engine = static_cast<OpenGLEngine*>(glfwGetWindowUserPointer(window));
        if (engine) {
            engine->framebufferSizeCallback(window, width, height);
        }
    }

    static void keyCallbackWrapper(GLFWwindow* window, int key, int scancode, int action, int mods) {
        OpenGLEngine* engine = static_cast<OpenGLEngine*>(glfwGetWindowUserPointer(window));
        if (engine) {
            engine->keyCallback(window, key, scancode, action, mods);
        }
    }

    static void mouseButtonCallbackWrapper(GLFWwindow* window, int button, int action, int mods) {
        OpenGLEngine* engine = static_cast<OpenGLEngine*>(glfwGetWindowUserPointer(window));
        if (engine) {
            engine->mouseButtonCallback(window, button, action, mods);
        }
    }

    static void cursorPosCallbackWrapper(GLFWwindow* window, double x, double y) {
        OpenGLEngine* engine = static_cast<OpenGLEngine*>(glfwGetWindowUserPointer(window));
        if (engine) {
            engine->cursorPosCallback(window, x, y);
        }
    }

    static void errorCallback(int error, const char* description) {
        std::cout << "[ERROR]: " << description << std::endl;
    }

    // Constants
    const int   WINDOW_WIDTH    = 1280;
    const int   WINDOW_HEIGHT   = 720;
    const float CAMERA_DISTANCE = 4.0f;

    // Global Variables
    int windowWidth;
    int windowHeight;
    int fbWidth;
    int fbHeight;
    double runTime;
    bool mouseLeftDown;
    bool mouseRightDown;
    bool mouseMiddleDown;
    double mouseX, mouseY;
    float cameraAngleX;
    float cameraAngleY;
    float cameraDistance;
    int drawMode;
    GLuint vaoId1, vaoId2;      // IDs of VAO for vertex array states
    GLuint vboId1, vboId2;      // IDs of VBO for vertex arrays
    GLuint iboId1, iboId2;      // IDs of VBO for index array
    GLuint texId;
    BitmapFontData bmFont;
    Matrix4 matrixModelView;
    Matrix4 matrixProjection;

    // GLSL
    GLuint progId = 0;                  // ID of GLSL program
    GLint viewLoc;
    GLint uniformMatrixModelView;
    GLint uniformMatrixModelViewProjection;
    GLint uniformMatrixNormal;
    // GLint uniformLightPosition;
    GLint uniformLightDirection;
    GLint uniformLightAmbient;
    GLint uniformLightDiffuse;
    GLint uniformLightSpecular;
    GLint uniformMaterialAmbient;
    GLint uniformMaterialDiffuse;
    GLint uniformMaterialSpecular;
    GLint uniformMaterialShininess;
    GLint uniformMap0;
    GLint uniformTextureUsed;
    GLint attribVertexPosition;     // 0
    GLint attribVertexNormal;       // 1
    GLint attribVertexTexCoord;     // 2

    // Objects
    Sphere earth;

    // Bui-Tuong Phong shading model with texture
    const char* vsSource = R"(
    // GLSL version (OpenGL 3.3)
    #version 330
    // uniforms
    uniform mat4 matrixModelView;
    uniform mat4 matrixNormal;
    uniform mat4 matrixModelViewProjection;

    // vertex attribs (input)
    layout(location=0) in vec3 vertexPosition;
    layout(location=1) in vec3 vertexNormal;
    layout(location=2) in vec2 vertexTexCoord;

    // varyings (output)
    // out vec3 lightDirection;
    out vec3 esVertex;
    out vec3 esNormal;
    out vec2 texCoord0;
    void main()
    {
        // lightDirection = (mat3(view) * lightDir);
        esVertex = vec3(matrixModelView * vec4(vertexPosition, 1.0));
        esNormal = vec3(matrixNormal * vec4(vertexNormal, 1.0));
        texCoord0 = vertexTexCoord;
        gl_Position = matrixModelViewProjection * vec4(vertexPosition, 1.0);
    }
    )";

    const char* fsSource = R"(
    // GLSL version (OpenGL 3.3)
    #version 330
    // uniforms
    //uniform vec4 lightPosition;             // should be in the eye space
    uniform vec4 lightAmbient;              // light ambient color
    uniform vec4 lightDiffuse;              // light diffuse color
    uniform vec4 lightSpecular;             // light specular color
    uniform vec4 materialAmbient;           // material ambient color
    uniform vec4 materialDiffuse;           // material diffuse color
    uniform vec4 materialSpecular;          // material specular color
    uniform float materialShininess;        // material specular shininess
    uniform sampler2D map0;                 // texture map #1
    uniform bool textureUsed;               // flag for texture
    
    // varyings (input)
    in vec3 esVertex;
    in vec3 esNormal;
    in vec2 texCoord0;

    uniform vec4 lightDirection;

    // output
    out vec4 fragColor;
    void main()
    {
        vec3 normal = normalize(esNormal);
        vec3 light;

        vec4 lightDir = normalize(-lightDirection);

        if(lightDirection.w == 0.0)
        {
            light = normalize(lightDirection.xyz);
        }
        else
        {
            light = normalize(lightDirection.xyz - esVertex);
        }

        // if(lightPosition.w == 0.0)
        // {
        //     light = normalize(lightPosition.xyz);
        // }
        // else
        // {
        //     light = normalize(lightPosition.xyz - esVertex);
        // }

        vec3 view = normalize(-esVertex);
        vec3 reflectVec = reflect(-light, normal);  // 2 * N * (N dot L) - L

        vec3 color = lightAmbient.rgb * materialAmbient.rgb;        // begin with ambient
        float dotNL = max(dot(normal, light), 0.0);
        color += lightDiffuse.rgb * materialDiffuse.rgb * dotNL;    // add diffuse
        if(textureUsed)
            color *= texture(map0, texCoord0).rgb;                  // modulate texture map
        float dotVR = max(dot(view, reflectVec), 0.0);
        color += pow(dotVR, materialShininess) * lightSpecular.rgb * materialSpecular.rgb; // add specular
        fragColor = vec4(color, materialDiffuse.a);                 // set frag color
    }
    )";

};