#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>


int main()
{
    std::cout << "rat";
    glfwInit();
    GLFWwindow* window = glfwCreateWindow(640, 480, "Ratworld", NULL, NULL);
    if (!window)
    {
        std::cout << "fail" << std::endl;
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    const GLubyte* renderer = glGetString(GL_RENDERER); // get renderer string
    const GLubyte* version = glGetString(GL_VERSION); // version as a string
    printf("Renderer: %s\n", renderer);
    printf("OpenGL version supported %s\n", version);

    // tell GL to only draw onto a pixel if the shape is closer to the viewer
    glEnable(GL_DEPTH_TEST); // enable depth-testing
    glDepthFunc(GL_LESS); // depth-testing interprets a smaller value as "closer"


}