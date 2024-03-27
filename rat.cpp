#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

using std::endl;
int main()
{
    std::cout << "rat";
    //initialize glfw
    if (!glfwInit()) {
        std::cout << "glfw failed"<<endl;
        return -1;
    }
    
    //set options
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    //initialize window
    GLFWwindow* window = glfwCreateWindow(1280, 720, "Ratworld", NULL, NULL);
    if (!window)
    {
        std::cout << "fail" << std::endl;
        glfwTerminate();
        return(-1);
    }

    glfwMakeContextCurrent(window);
    
    glewExperimental = GL_TRUE;


    //set background color
    glClearColor(.3f,.3f,.3f,1.0f);
    //loop till window close
    while (!glfwWindowShouldClose(window))
    {
        //accept inputs
        glfwPollEvents();
        //clears buffer
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glfwSwapBuffers(window);
    }


    glfwDestroyWindow(window);
    glfwTerminate();
    return 1;
}