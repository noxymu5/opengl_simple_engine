#include <iostream>
#include <random>
#include <iomanip>

#include <GLEW/glew.h>
#include <GLFW/glfw3.h>

#include "shader.h"
#include "texture.h"
#include "buffers.h"
#include "vertex_array_object.h"
#include "camera.h"
#include "transform.h"

void error_callback(int error, const char* description) {
    fprintf(stderr, "Error: %s\n", description);
}

Transform CreateRandomizedTransform(std::default_random_engine eng, std::uniform_real_distribution<> distr, bool fixedY = false) {
    float rndX = distr(eng) - M_PI;
    float rndY = distr(eng) - M_PI;
    float rndZ = distr(eng) - M_PI;

    float rndRot = distr(eng);
    float rndScale = distr(eng) / (4 * M_PI);

    Transform res;
    res.Scale(glm::vec3(1.0) * rndScale);
    res.Translate(glm::vec3(rndX, (fixedY ? 5 : rndY), rndZ));
    res.Rotate((float)rndRot, glm::vec3(0.1, 0.5, 1));

    return res;
}

int main()
{
    const float width = 800;
    const float height = 600;

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_ANY_PROFILE);

    glfwSetErrorCallback(error_callback);

    GLFWwindow* window = glfwCreateWindow(width, height, "Test window", NULL, NULL);
    if (window == NULL) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glewInit();

    glViewport(0, 0, width, height);
    glEnable(GL_DEPTH_TEST);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    Camera camera(window, width / 2, height / 2);
    
    float verticesData[] = {
        // positions            // texture coords
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
        0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
        0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
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
    // IndexBuffer iBuffer(indices, sizeof(indices));

    shader.SetVertexAttribute("aPos", 3, GL_FLOAT, GL_FALSE, 0);
    shader.SetVertexAttribute("aTexCoords", 2, GL_FLOAT, GL_FALSE, 3 * sizeof(float));

    vao.UnBind();
    //vertex and index data preparation end

    shader.Use();

    shader.SetUniform("texture0", 0);
    shader.SetUniform("texture1", 1);

    glm::mat4 view(1.0f);
    view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f)); 
    glm::mat4 proj = glm::perspective(glm::radians(45.0f), width/height, 0.1f, 100.0f);

    std::random_device rd;
    std::default_random_engine eng(rd());
    std::uniform_real_distribution<> distr(0, 4 * M_PI);

    Transform cubeTransforms[36];
    for (int i = 0; i < 36; ++i) {
        distr(eng);
        cubeTransforms[i] = CreateRandomizedTransform(eng, distr);
    }

    float lastTime = 0;
    float mixFactorSpeed = 1;
    float currentMixFactor = 0;
    
    float moveDownSpeed = 1;

    while(!glfwWindowShouldClose(window)) {
        float currTime = glfwGetTime();
        float deltaTime = currTime - lastTime;
        lastTime = currTime;

        camera.UpdateCamera(deltaTime);
        
        currentMixFactor += mixFactorSpeed * deltaTime;
        if (currentMixFactor > 1 || currentMixFactor < 0) {
            mixFactorSpeed *= -1;
        }

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        shader.Use();
        shader.SetUniform("mixFactor", currentMixFactor);

        texture0.Bind();
        texture1.Bind();

        vao.Bind();
        for (int i = 0; i < 36; ++i) {
            cubeTransforms[i].Rotate(deltaTime, glm::vec3(0.1, 0.5, 1));
            cubeTransforms[i].Translate(glm::vec3(0, -1, 0) * deltaTime * moveDownSpeed);

            glm::mat4 mvpMatr = proj * camera.GetCameraMatr() * cubeTransforms[i].Get();
            shader.SetUniform("trf", &mvpMatr);
            glDrawArrays(GL_TRIANGLES, 0, 36);

            glm::vec3 currPos = cubeTransforms[i].GetPosition();
            if (currPos[1] < -5) {
                distr(eng);
                cubeTransforms[i] = CreateRandomizedTransform(eng, distr, true);
            }
        }
        vao.UnBind();

        glfwPollEvents();
        glfwSwapBuffers(window);
    } 

    glfwTerminate();
    return 0;
}