#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include < stdio.h > 
#include <string.h>
#include <windows.h>
#include <atlbase.h>
#include <atlconv.h>
#include <fstream>
#include <sstream>
using std::endl;
using std::string;

static GLFWwindow* w ;
string lastkey="none";
GLuint shaderProgram;

static bool init=false;





//this is neccessary for export as dll
extern "C" {

    //cant return strings directly due to exporting as dll so i set string by reference
    __declspec(dllexport) void readFile(string fileloc, string& out) {
        std::ifstream file(fileloc);
        std::stringstream content;
        if (!file.fail())
        {
            content << file.rdbuf();
        }
        std::cout << "conetent " << content.str() << std::endl;

        out = content.str();
        

    }

    __declspec(dllexport) GLuint CreateShader(string fileloc, GLuint shadertype)
    {
        GLuint shader = glCreateShader(shadertype);
        std::cout << "here2" << std::endl;
        string filecontent;
        readFile(fileloc, filecontent);
        const char* shaderSource = filecontent.c_str();
        
        glShaderSource(shader, 1, &shaderSource, nullptr);
        glCompileShader(shader);
        int success=1;
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            char infoLog[512];
            glGetShaderInfoLog(shader, 512, nullptr, infoLog);
            std::cout << "Shader error " << infoLog << std::endl;
        }

        return shader;
    }

    __declspec(dllexport) GLuint CreateProgram()
    {
        GLuint vertexShader = CreateShader("../../../../shaders/vertshader.rat", GL_VERTEX_SHADER);
        GLuint fragmentShader = CreateShader("../../../../shaders/fragshader.rat", GL_FRAGMENT_SHADER);

        GLuint program = glCreateProgram();
        glAttachShader(program, vertexShader);
        glAttachShader(program, fragmentShader);

        glLinkProgram(program);
        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);

        return program;
    }



    __declspec(dllexport) void HandleKeyInput(GLFWwindow* w, int key, int status, int action, int mods) {
        string k = "";


        std::ostringstream oss;
        oss << key << " " << status << " " << action << " " << mods;
        
        lastkey = oss.str();
        

    }

    __declspec(dllexport) void framebuffer_size_callback(GLFWwindow* window, int width, int height)
    {
        glViewport(0, 0, width, height);
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
        
        w =  glfwCreateWindow(1920, 1080, "Ratworld", NULL, NULL);
        if (!w)
        {
            std::cout << "fail" << std::endl;
            glfwTerminate();
            return(-1);
        }



        glfwMakeContextCurrent(w);

        //initialize glew
        if (glewInit() != GLEW_OK) {
            std::cout << "glew failed" << endl;
            return -1;
        }

        glViewport(0, 0, 1920, 1080);
        glfwSetFramebufferSizeCallback(w, framebuffer_size_callback);


       
        glewExperimental = GLEW_OK;

        //set background color
        glClearColor(.3f, .3f, .3f, 1.0f);

        glfwSetKeyCallback(w, HandleKeyInput);
        

        


        shaderProgram = CreateProgram();
        //no clue what this means but its required
        

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
            glfwSwapBuffers(w);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            
            
            int width, height;
            glfwGetFramebufferSize(w, &width, &height);
            glViewport(0, 0, width, height);
        }
        
    }

    __declspec(dllexport) void drawSquare(float x, float y,float sidelength, float r, float g, float b)
    {
        
        float vertices[] = {
            x+ sidelength,  y+ sidelength, 0.0f,  // top right
            sidelength +x, y, 0.0f,  // bottom right
            x, y, 0.0f,  // bottom left
            x,  sidelength+y, 0.0f   // top left 
        };
        unsigned int indices[] = { 
            0, 1, 3,   // first triangle
            1, 2, 3    // second triangle
        };

        GLuint VBO, VAO, EBO;
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        glGenBuffers(1, &EBO);
        glBindVertexArray(VAO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices),vertices,GL_STATIC_DRAW);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);

        glBindBuffer(GL_ARRAY_BUFFER,0);
        glBindVertexArray(0);

        int vertexColorLocation = glGetUniformLocation(shaderProgram, "ourColor");

        
        glUseProgram(shaderProgram);
        glUniform4f(vertexColorLocation, r, g, b, 1.0f);
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);

        glDeleteVertexArrays(1, &VAO);
        glDeleteBuffers(1, &VBO);
        glDeleteBuffers(1, &EBO);
       

        //std::cout << "square" << std::endl;
    }


    __declspec(dllexport) void  ResetInput()
    {
        lastkey = "none";
        
    }

    

}

