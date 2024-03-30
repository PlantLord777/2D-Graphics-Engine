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

static GLFWwindow* w ;
string lastkey="rat";

static bool init=false;

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
        lastkey = key;
        

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

        init = true;

        

        


        return 1;
    }

    
    //if theres a memory leak its probably caused here
    __declspec(dllexport) BSTR  GetInput()
    {
        if (init) {
            glfwPollEvents();
        }

        //yes this is required
        char* char_ = new char[lastkey.length() +1];
        strcpy(char_, lastkey.c_str());

       
        //std::cout << "c++ output " << char_ << std::endl;
        
        
        BSTR b = SysAllocString(CA2W(char_));
        delete[] char_;
        return b;
    }

    __declspec(dllexport) void  Buffer()
    {
        if (init) {
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            glfwSwapBuffers(w);
        }
        
    }

    __declspec(dllexport) void drawSquare(double x1, double y1, double sidelength)
    {
        
        glClear(GL_COLOR_BUFFER_BIT);
        glColor3f(0.0, 1.0, 0.0);
        glBegin(GL_POLYGON);
        glVertex3f(2.0, 4.0, 0.0);
        glVertex3f(8.0, 4.0, 0.0);
        glVertex3f(8.0, 6.0, 0.0);
        glVertex3f(2.0, 6.0, 0.0);
        glEnd();
        glFlush();

        //glew
        std::cout << "square" << std::endl;
    }


    __declspec(dllexport) void  ResetInput()
    {
        lastkey = "none";
        
    }
}

