#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

void framebuffer_size_callback(GLFWwindow *window, int width, int height);
void processInput(GLFWwindow *window);

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

int main()
{
        glfwInit();
        // define glfw major version
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        // define glfw minor version
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        // define opengl profile
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

        // glfw window creation
        GLFWwindow *window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "OpenGL Input", NULL, NULL);
        if (window == NULL)
        {
                std::cout << "Failed to create GLFW window" << std::endl;
                glfwTerminate();
                return EXIT_FAILURE;
        }
        glfwMakeContextCurrent(window);
        glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

        // glad load all OpenGL function pointers
        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        {
                std::cout << "Failed to initialize GLAD" << std::endl;
                return EXIT_FAILURE;
        }

        // render loop
        while (!glfwWindowShouldClose(window))
        {
                // input
                processInput(window);

                // render
                glClearColor(0.1f, 2.2f, 3.9f, 1.0f);
                glClear(GL_COLOR_BUFFER_BIT);

                // glfw swap buffers and poll IO events (key pressed/released, mouse moved etc.)
                glfwSwapBuffers(window);
                glfwPollEvents();
        }

        glfwTerminate();
        return EXIT_SUCCESS;
}

// process all input query GLFW whether relevant keys are pressed/released this frame and react accordingly
void processInput(GLFWwindow *window)
{
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
                glfwSetWindowShouldClose(window, true);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
        // make sure the viewport matches the new window dimensions; note that width and
        // height will be significantly larger tha specified on retina displays.
        glViewport(0, 0, width, height);
}