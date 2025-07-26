#include <GL/glew.h> // glew should include opengl headers, therefore must be first
#include <GLFW/glfw3.h>
#include <iostream>
#include <cstdlib>
#include <cstddef>
#include <Eigen/Dense>

// remember this -lGLEW -lglfw -lGL -I/usr/include/eigen3

using namespace std;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

const char *vertexShaderSource = "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\0";

const char *fragmentShaderSource = "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
    "}\0";

const char *fragmentShaderSource2 = "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "   FragColor = vec4(0.0f, 0.5f, 0.5f, 1.0f);\n"
    "}\0";

unsigned int vertexShader, fragmentShader, fragmentShader2, shaderProgram, shaderProgram2;
GLuint vbos[2];
GLuint vaos[2];

float verts1[] = {
    -0.25f, 0.0f, 0.0f,
    -0.5f, 0.5f, 0.0f,
    -0.75f, 0.0f, 0.0f
};

float verts2[] = {
    0.25f, 0.0f, 0.0f,
    0.5f, 0.5f, 0.0f,
    0.75f, 0.0f, 0.0f
};



int main(){

    // initialize glfw
    glfwInit();

    // configure glfw
    // glfwWindowHint(OPTIONTOCONFIG, SETOPTIONTOTHIS)

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);

    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    // Example set the option GLFW_OPENGL_PROFILE to GLFW_OPENGL_CORE_PROFILE
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // creates the window that will become the main context of the thread
    GLFWwindow* window = glfwCreateWindow(800, 600, "Learn OpenGL", NULL, NULL);

    // make sure window is not null
    if(window == NULL){
        cout << "Failed" << endl;
        glfwTerminate();
        return -1;
    }
    // makes our window the main context of the thread
    glfwMakeContextCurrent(window);

    glewExperimental = GL_TRUE;

    GLenum err = glewInit();

    if(GLEW_OK != err){
        cerr << "Error: " << glewGetErrorString(err) << endl;
    }
    cout << "Status: Using Glew " << glewGetString(GLEW_VERSION) << endl;
    cout << "Status: OpenGL version " << glGetString(GL_VERSION) << endl;

    // first two args set the location of the lower left corner of the window
    glViewport(0, 0, 800, 600);

    // ===---=== 

    //creates empty shader returns ID for use
    vertexShader = glCreateShader(GL_VERTEX_SHADER); 
    // first arg is where the source will be compiled to, the second the numOfStrings in source, the third is the source code itself
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL); 
    //compiles the shader    
    glCompileShader(vertexShader);


    //Same as Vertex, but fragments :p
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    fragmentShader2 = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader2, 1, &fragmentShaderSource2, NULL);
    glCompileShader(fragmentShader2);

    shaderProgram = glCreateProgram();

    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    shaderProgram2 = glCreateProgram();

    glAttachShader(shaderProgram2, vertexShader);
    glAttachShader(shaderProgram2, fragmentShader2);
    glLinkProgram(shaderProgram2);

    // check for failure

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    glGenVertexArrays(2, vaos);
    glGenBuffers(2, vbos);

    
    glBindVertexArray(vaos[0]);
    glBindBuffer(GL_ARRAY_BUFFER, vbos[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(verts1), verts1, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), ((void*)0));
    glEnableVertexAttribArray(0);
    
    glBindVertexArray(vaos[1]);
    glBindBuffer(GL_ARRAY_BUFFER, vbos[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(verts2), verts2, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), ((void*)0));
    glEnableVertexAttribArray(0);

    glBindVertexArray(0);

    // the render loop
    while(!glfwWindowShouldClose(window)){

        processInput(window);

        // sets a color for after using glClear
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shaderProgram);
        glBindVertexArray(vaos[0]);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glUseProgram(shaderProgram2);
        glBindVertexArray(vaos[1]);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        // glClear clears the buffer we want

        glfwPollEvents();
        glfwSwapBuffers(window);
    }

    // free that sheeeet
    glfwTerminate();
    return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height){
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window){
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS){
        glfwSetWindowShouldClose(window, true);
    }
}