// GLEW
#define GLEW_STATIC
#include <GL/glew.h>

// GLFW
#include <GLFW/glfw3.h>

#include <iostream>
#include <unistd.h>
#include "shader.h"

// Window dimensions
const GLint WIDTH=800, HEIGHT=600;

int main() {
    // Init GLFW
    glfwInit();
    
    // Set required options for GLFW
    glfwWindowHint( GLFW_CONTEXT_VERSION_MAJOR, 3 );
    glfwWindowHint( GLFW_CONTEXT_VERSION_MINOR, 3 );
    glfwWindowHint( GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE );
    glfwWindowHint( GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE );
    
    // Create a GLFWwindow object that we can use for GLFW`s functions
    GLFWwindow *window = glfwCreateWindow( WIDTH, HEIGHT, "Triangle", nullptr, nullptr );
    
    int screenWidth, screenHeight;
    
    glfwGetFramebufferSize(window, &screenWidth, &screenHeight);
    
    if ( nullptr == window) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        
        return -1;
    }
    
    glfwMakeContextCurrent(window);
    
    // Set this to true so GLEW knows to use a modern approach to retrieving function pointers and extensions
    glewExperimental = GL_TRUE;
    
    // Initialize GLEW to setup the OpenGL Function pointers
    if (GLEW_OK != glewInit()) {
        std::cout << "Failed to initialize GLEW" << std::endl;
        
        return -1;
    }
    
    // Define the viewport dimensions
    glViewport( 0, 0, screenWidth, screenHeight);
    
    // build and compile our shader program
    // ------------------------------------
    Shader ourShader("/Users/juliorenner/Google Drive/Faculdade/Processamento Gráfico/Trabalhos/triangle/triangle/shader.vs", "/Users/juliorenner/Google Drive/Faculdade/Processamento Gráfico/Trabalhos/triangle/triangle/shader.fs"); // you can name your shader files however you like
    
    // Set up vertex data (and buffer(s)) and attribute pointers
    GLfloat vertices[] = {
        // vertices         // colors
        -0.5f, -1.0f, 0.0f, 1.0f, 0.0f, 0.0f,    // bottom left
        0.5f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f,    // bottom right
        0.0f,  0.0f, 0.0f, 0.0f, 0.0f, 1.0f,    // top
        0.5f,  1.0f, 0.0f, 1.0f, 0.0f, 0.0f,    // bottom left
        -0.5f,  1.0f, 0.0f, 0.0f, 1.0f, 0.0f,    // bottom right
        0.0f,  0.0f, 0.0f, 0.0f, 0.0f, 1.0f,    // top
    };
    
    GLuint VBO, VAO;
    glGenVertexArrays( 1, &VAO );
    glGenBuffers( 1, &VBO );
    
    // Bind the Vertex Array Object first, then bind and set vertex buffer(s) and attribute pointer(s).
    glBindVertexArray( VAO );
    glBindBuffer( GL_ARRAY_BUFFER, VBO );
    glBufferData( GL_ARRAY_BUFFER, sizeof( vertices ), vertices, GL_STATIC_DRAW);
    
    // position attribute
    glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof( GLfloat ), (GLvoid * ) 0 );
    glEnableVertexAttribArray( 0 );
    
    // color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3* sizeof(float)));
    glEnableVertexAttribArray(1);
    
    glBindBuffer( GL_ARRAY_BUFFER, 0);
    
    glBindVertexArray( 0 );
    
    //while the window is not closed
    while (!glfwWindowShouldClose(window)) {
        // Check if any events have been activated (key pressed, mouse moved, etc.) and call corresponding response function
        glfwPollEvents();
        
        // Render
        // Clear the colorbuffer
        glClearColor( 0.2f, 0.3f, 0.3f, 1.0f);
        glClear( GL_COLOR_BUFFER_BIT );
        
        // Draw triangle
        ourShader.use();
        glBindVertexArray( VAO );
        glDrawArrays( GL_TRIANGLES, 0, 6 );
        
        // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
        // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
        // glBindVertexArray(0);
        
        // Swap the screen buffers
        glfwSwapBuffers( window );
    }
    
    // Properly de-allocate all resources once they've outlived their purpose
    glDeleteVertexArrays( 1, &VAO );
    glDeleteBuffers( 1, &VBO );
    
    // Terminate GLFW, clearing any resources allocated by GLFW.
    glfwTerminate();
    
    return EXIT_SUCCESS;
}
