#include <iostream>
#include <GLFW/glfw3.h>


int main()
{
    std::cout << "rat";
    glfwInit();
    GLFWwindow* window = glfwCreateWindow(640, 480, "OpenGL Triangle", NULL, NULL);
    if (!window)
    {
        std::cout << "fail" << std::endl;
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    int rat=0;
    std::cin >> rat;
    std::cout << "rat2";

}