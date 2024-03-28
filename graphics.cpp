#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include < stdio.h > 
#include <string.h>
#include <windows.h>
#include <atlbase.h>
#include <atlconv.h>

using std::endl;
using std::string;

GLFWwindow* w ;
string lastkey="rat";
//this is neccessary for export as dll
extern "C" {


    __declspec(dllexport) void HandleKeyInput(GLFWwindow* w, int key, int status, int action, int mods) {
        string k = "";
        k += key;
        k += " ";
        k += status;
        k += " ";
        k += action;
        k += " ";
        k += mods; 
        lastkey = k;
        

    }

  

    __declspec(dllexport) int rat()
    {
        //initialize glfw
        if (!glfwInit()) {
            std::cout << "glfw failed" << endl;
            return -1;
        }

        //set options
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        //initialize window
        
        w =  glfwCreateWindow(1280, 720, "Ratworld", NULL, NULL);
        if (!w)
        {
            std::cout << "fail" << std::endl;
            glfwTerminate();
            return(-1);
        }

        glfwMakeContextCurrent(w);

        glewExperimental = GL_TRUE;


        //set background color
        glClearColor(.3f, .3f, .3f, 1.0f);

        glfwSetKeyCallback(w, HandleKeyInput);
        //loop till window close
        /*while (!glfwWindowShouldClose(window))
        {
            //accept inputs
            glfwPollEvents();
            //clears buffer
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            glfwSwapBuffers(window);
        }*/

        
        return 1;
    }

    

    __declspec(dllexport) BSTR  GetInput()
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glfwSwapBuffers(w);
        
        glfwPollEvents();
        

        //yes this is required
        char* char_ = new char[lastkey.length() +1];

        strcpy(char_, lastkey.c_str());
        std::cout << "c++ output " << char_ << std::endl;

        return SysAllocString(CA2W(char_));
    }
}

