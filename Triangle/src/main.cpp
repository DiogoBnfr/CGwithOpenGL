#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

void framebuffer_size_callback(GLFWwindow *window, int width, int height);
void processInput(GLFWwindow *window);

// Settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

// Shaders source codes
const char *vertexShaderSource =
    "#version 460 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main() {\n"
    " gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\0";
const char *fragmentShaderSource =
    "#version 460 core\n"
    "out vec4 FragColor;\n"
    "void main() {\n"
    "  FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
    "}\0";

int main(void) {
  if (!glfwInit()) {
    std::cout << "Failed to initialize GLFW" << std::endl;
    return EXIT_FAILURE;
  }

  glfwWindowHint(GLFW_SAMPLES, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

  GLFWwindow *window;
  window =
      glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "OpenGL Triangle", NULL, NULL);
  if (window == NULL) {
    std::cout << "Failed to open GLFW window" << std::endl;
    return EXIT_FAILURE;
  }
  glfwMakeContextCurrent(window);

  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    std::cout << "Failed to initialize GLAD" << std::endl;
    return EXIT_FAILURE;
  }

  glViewport(0, 0, 800, 600);
  glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

  // ..:: Creating  and compiling vertex shader object ::..
  unsigned int vertexShader;
  vertexShader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
  glCompileShader(vertexShader);

  // Creating compile-checking variables
  int success;
  char infoLog[512];

  // Checking for compile-time erros in vertexShader
  glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(vertexShader, sizeof(infoLog), NULL, infoLog);
    std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n"
              << infoLog << std::endl;
  }

  // ..:: Creating  and compiling fragment shader object ::..
  unsigned int fragmentShader;
  fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
  glCompileShader(fragmentShader);

  // Checking for compile-time erros in fragmentShader
  glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(fragmentShader, sizeof(infoLog), NULL, infoLog);
    std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n"
              << infoLog << std::endl;
  }

  // ..:: Creating a shader program object ::..
  unsigned int shaderProgram;
  shaderProgram = glCreateProgram();

  // Attaching compiled shaders to the program object
  glAttachShader(shaderProgram, vertexShader);
  glAttachShader(shaderProgram, fragmentShader);
  glLinkProgram(shaderProgram);

  // Checking shader program linking
  glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
  if (!success) {
    glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
    std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n"
              << infoLog << std::endl;
  }

  // Activating shader program
  glUseProgram(shaderProgram);

  // Shader objects are dispensable after linking
  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);

  // ..:: Creating a Vertex Array Object (VAO) ::..
  unsigned int VAO;
  glGenVertexArrays(1, &VAO);

  // Triangle vertex data
  float vertices[] = {
      -0.5f, -0.5f, 0.0f, // left
      0.5f,  -0.5f, 0.0f, // right
      0.0f,  0.5f,  0.0f  // top
  };

  // ..:: Creating a Vertex Buffer Objects (VBO) ::..
  unsigned int VBO;
  glGenBuffers(1, &VBO);

  /*
   * This line of code tells OpenGL, “I want to use the buffer object with
   * the ID VBO for vertex attribute data.” After this call, any
   * subsequent operations that deal with vertex attributes will affect
   * this buffer until another buffer is bound to the GL_ARRAY_BUFFER
   * target.
   */
  glBindBuffer(GL_ARRAY_BUFFER, VBO);

  // Copies the vertex data into the buffer's memory
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  // ..:: Initialization code ::..
  // 1. Bind VAO
  glBindVertexArray(VAO);
  // 2. Copy our vertices array in a buffer for OpenGL to use
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
  // 3. Set vertex attributes pointers
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
  glEnableVertexAttribArray(0);

  glBindBuffer(GL_ARRAY_BUFFER, 0);

  /*
   * You can unbind the VAO afterwards so other VAO calls won't accidentally
   * modify this VAO, but this rarely happens. Modifying other VAOs requires a
   * call to glBindVertexArray anyways so we generally don't unbind VAOs (nor
   * VBOs) when it's not directly necessary.
   */
  glBindVertexArray(0);

  // uncomment this call to draw in wireframe polygons.
  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

  // Render loop
  while (!glfwWindowShouldClose(window)) {
    processInput(window);

    // Make the triangle draw responsible to window resizing
    glClear(GL_COLOR_BUFFER_BIT);

    // ..:: Drawing ::..
    // 4. Draw the object
    glUseProgram(shaderProgram);
    /*
     * Seeing as we only have a single VAO there's no need to bind it every
     * time, but we'll do so to keep things a bit more organized.
     */
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    // glBindVertexArray(0); // no need to unbind it every time

    /*
     * GLFW swap buffers and poll IO events (keys pressed/released, mouse moved
     * etc.)
     */
    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  // OPTIONAL: de-allocate all resources once they've outlived their purpose
  glDeleteVertexArrays(1, &VAO);
  glDeleteBuffers(1, &VBO);
  glDeleteProgram(shaderProgram);

  // GLFW terminate, clearing all previously allocated GLFW resources.
  glfwTerminate();
  return EXIT_SUCCESS;
}

void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
  glViewport(0, 0, width, height);
}

void processInput(GLFWwindow *window) {
  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    glfwSetWindowShouldClose(window, true);
}
