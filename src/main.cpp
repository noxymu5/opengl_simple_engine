#include <iostream>

#include <GLEW/glew.h>
#include <GLFW/glfw3.h>

#include "shader.h"
#include "texture.h"
#include "buffers.h"
#include "vertex_array_object.h"

void error_callback(int error, const char* description)
{
    fprintf(stderr, "Error: %s\n", description);
}

int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_ANY_PROFILE);

    glfwSetErrorCallback(error_callback);

    GLFWwindow* window = glfwCreateWindow(800, 600, "Test window", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glewInit();
    glViewport(0, 0, 800, 600);

    float verticesData[] = {
        // positions            // texture coords
        0.5f,  0.5f, 0.0f,      1.0f, 1.0f,   // top right
        0.5f, -0.5f, 0.0f,      1.0f, 0.0f,   // bottom right
        -0.5f, -0.5f, 0.0f,     0.0f, 0.0f,   // bottom left
        -0.5f,  0.5f, 0.0f,     0.0f, 1.0f    // top left 
    };
    unsigned int indices[] = {
        0, 1, 2,   // first triangle
        0, 2, 3,   // first triangle
    };

    //shaders preparation
    Shader shader("../shaders/simple_vertex_shader.vs", "../shaders/simple_fragment_shader.fs", 5 * sizeof(float));
    //shaders preparation end

    //texture preparation
    Texture texture0("../assets/textures/container.jpg", GL_RGB);
    Texture texture1("../assets/textures/kotik_yuy.jpg", GL_RGB, 1);
    //texture preparation end
    
    //vertex and index data preparation
    VertexArrayObject vao;

    VertexBuffer vBuffer(verticesData, sizeof(verticesData));
    IndexBuffer iBuffer(indices, sizeof(indices));

    shader.SetVertexAttribute("aPos", 3, GL_FLOAT, GL_FALSE, 0);
    shader.SetVertexAttribute("aTexCoords", 2, GL_FLOAT, GL_FALSE, 3 * sizeof(float));

    vao.UnBind();
    //vertex and index data preparation end

    shader.Use();

    shader.SetUniform("texture0", 0);
    shader.SetUniform("texture1", 1);
    
    float lastTime = 0;
    float mixFactorSpeed = 0.2;

    float currentMixFactor = 0;
    while(!glfwWindowShouldClose(window))
    {
        float currTime = glfwGetTime();
        float deltaTime = currTime - lastTime;
        lastTime = currTime;

        currentMixFactor += mixFactorSpeed * deltaTime;
        if (currentMixFactor > 1 || currentMixFactor < 0) {
            mixFactorSpeed *= -1;
        }

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        
        glm::mat4 trf = glm::mat4(1.0f);
        trf = glm::rotate(trf, (float)currTime, glm::vec3(0.0, 0.0, 1.0));

        shader.Use();
        shader.SetUniform("mixFactor", currentMixFactor);
        shader.SetUniform("trf", &trf);

        texture0.Bind();
        texture1.Bind();

        vao.Bind();
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        vao.UnBind();

        glfwPollEvents();
        glfwSwapBuffers(window);
    } 

    glfwTerminate();
    return 0;
}