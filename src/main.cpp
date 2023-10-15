#include "glad/glad.h"
#include <GLFW/glfw3.h>

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

#include "Renderer.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Shader.h"


int main(void) {
  // Setting opengl version 3.3, core profile
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  GLFWwindow* window;

  /* Initialize the library */
  if (!glfwInit()) return -1;

  /* Create a windowed mode window and its OpenGL context */
  window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
  if (!window) {
    glfwTerminate();
    return -1;
  }

  /* Make the window's context current */
  glfwMakeContextCurrent(window);

  /* load glad */
  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    std::cout << "Couldn't load opengl\n";
    glfwTerminate();
    return -1;
  }

  std::cout << glGetString(GL_VERSION) << std::endl;
{
    //vertices of the triangle
    float positions[] = {
        -0.5f, 0.0f, // 0
         0.5f, 0.0f, // 1
         0.5f, 0.5f, // 2
        -0.5f, 0.5f  // 3
    };

    // WARNING:indices have to be usigned int
    unsigned int indices[] = {
        0 , 1, 2,
        2, 3, 0
    };

    unsigned int vao;
    GLCall(glGenVertexArrays(1, &vao));
    GLCall(glBindVertexArray(vao));

    VertexArray va;
    VertexBuffer vb (positions, sizeof(positions));
    VertexBufferLayout layout;
    layout.push<float>(2);
    va.addBuffer(vb, layout);

    IndexBuffer ib(indices, 6);

    // shaders
    Shader shader("res/shaders/basic.shader");
    shader.bind();

    vb.unbind();
    ib.unbind();
    shader.unbind();
    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        GLCall(va.bind());
        GLCall(ib.bind());
        GLCall(shader.bind());
        //glDrawArrays(GL_TRIANGLES, 0, 3);
        GLCall(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr));

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

}
    glfwTerminate();
    return 0;
}