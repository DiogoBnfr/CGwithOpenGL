#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

void framebuffer_size_callback(GLFWwindow *window, int width, int height);
void processInput(GLFWwindow *window, float *red, float *green, float *blue);

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
        GLFWwindow *window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "OpenGL Color Selector", NULL, NULL);
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

        float red = 0.0;
        float green = 0.0;
        float blue = 0.0;

        // render loop
        while (!glfwWindowShouldClose(window))
        {
                glfwWaitEventsTimeout(0.1);

                // input
                processInput(window, &red, &green, &blue);

                // render
                glClearColor(red, green, blue, 1.0f);
                glClear(GL_COLOR_BUFFER_BIT);

                // glfw swap buffers and poll IO events (key pressed/released, mouse moved etc.)
                glfwSwapBuffers(window);
                glfwPollEvents();
        }

        glfwTerminate();
        return EXIT_SUCCESS;
}

// process all input query GLFW whether relevant keys are pressed/released this frame and react accordingly
void processInput(GLFWwindow *window, float *red, float *green, float *blue)
{
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        {
                glfwSetWindowShouldClose(window, true);
        }
                
        if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS)
        {
                glfwWaitEventsTimeout(0.1);
                *red += 0.1;
        }

        if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
        {
                glfwWaitEventsTimeout(0.1);
                *red -= 0.1;
        }

        if (glfwGetKey(window, GLFW_KEY_G) == GLFW_PRESS)
        {
                glfwWaitEventsTimeout(0.1);
                *green += 0.1;
        }

        if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS)
        {
                glfwWaitEventsTimeout(0.1);
                *green -= 0.1;
        }

        if (glfwGetKey(window, GLFW_KEY_B) == GLFW_PRESS)
        {
                glfwWaitEventsTimeout(0.1);
                *blue += 0.1;
        }

        if (glfwGetKey(window, GLFW_KEY_V) == GLFW_PRESS)
        {
                glfwWaitEventsTimeout(0.1);
                *blue -= 0.1;
        }
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
        // make sure the viewport matches the new window dimensions; note that width and
        // height will be significantly larger tha specified on retina displays.
        glViewport(0, 0, width, height);
}