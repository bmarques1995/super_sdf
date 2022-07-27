#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <stb_image.h>

#include "Implementation/Graphics/GL4/GL4Shader.hh"
#include "Implementation/Graphics/GL4/GL4VertexBuffer.hh"
#include "Implementation/Graphics/GL4/GL4Texture.hh"
#include "Implementation/Graphics/GL4/GL4IndexBuffer.hh"
#include "Implementation/Graphics/GL4/GL4Context.hh"
#include "Implementation/Graphics/GL4/GL4InputLayout.hh"
#include "Implementation/Window/GLFW/GLFWWindow.hh"

#include <iostream>
#include "wrappers/Image.hh"
#include <FontFace.hh>
#include <Glyph.hh>
#include <FileHandler.hh>

// settings
const unsigned int SCR_WIDTH = 600;
const unsigned int SCR_HEIGHT = 600;

int main()
{
    SuperSDF::FontFace* font = new SuperSDF::FontFace("assets/fonts/NotoSansJP-Light.otf", 64);
    
    SuperSDF::Glyph glyph(U'の', *font);
    glyph.PrintContours();
    SuperSDF::Glyph glyph2(U'乪', *font);
    glyph2.PrintContours();
    SuperSDF::Glyph glyph3(U'バ', *font);
    glyph3.PrintContours();
        
    Window* window = new GLFWWindow(SCR_WIDTH, SCR_HEIGHT, "Super SDF Sample");

    Context* context = new GL4Context(std::any_cast<GLFWwindow*>(window->GetWindowPointer()));
    context->SetClearColor(1.0f,.7f,.3f);

    // build and compile our shader zprogram
    // ------------------------------------

    std::string vertexSource, fragmentSource;

    SuperSDF::FileHandler::ReadTextFile("assets/shaders/Texture.vs.glsl", &vertexSource);
    SuperSDF::FileHandler::ReadTextFile("assets/shaders/Texture.fs.glsl", &fragmentSource);

    Shader* ourShader = new GL4Shader(vertexSource.c_str(), fragmentSource.c_str());

    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------
    float x = 1.0;
    float vertices[] = {
        // positions          // colors           // texture coords
         0.5f/x,  0.5f/x, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // top right
         0.5f/x, -0.5f/x, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // bottom right
        -0.5f/x, -0.5f/x, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // bottom left
        -0.5f/x,  0.5f/x, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f  // top left 
    };
    unsigned int indices[] = {  
        0, 1, 3, // first triangle
        1, 2, 3  // second triangle
    };

    std::initializer_list<BufferElement> elements = 
    {
        {ShaderDataType::Float3, "aPos", false},
        {ShaderDataType::Float3, "aColor", false},
        {ShaderDataType::Float2, "aTexCoord", false}
    };

    VertexBuffer* vertexBuffer = new GL4VertexBuffer(vertices, sizeof(vertices));
    IndexBuffer* indexBuffer = new GL4IndexBuffer(indices, sizeof(indices));
    InputLayout* inputLayout = new GL4InputLayout(elements);

    // load and create a texture 
    // -------------------------

    Image* image = new Image("assets/images/container.jpg");

    Texture* texture = new GL4Texture(*image);
    
    delete image;


    // render loop
    // -----------
    while (!window->ShouldClose())
    {
        // input
        window->Update();

        // render
        context->Clear();

        // bind Texture
        texture->Bind();

        // render container
        ourShader->Bind();
        vertexBuffer->Bind();
        indexBuffer->Bind();
        inputLayout->Bind();
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        context->Present();
        
    }

    delete texture;
    delete inputLayout;
    delete indexBuffer;
    delete vertexBuffer;
    delete ourShader;
    delete context;
    delete window;

    delete font;

    return 0;
}


