#include "mandel.h"




int main(){

    glfwInit();
    glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);

    vec2 resolution; resolution[0] = 1920; resolution[1] = 1080;

    GLFWwindow *screen = glfwCreateWindow(resolution[0], resolution[1], "Mandel", NULL, NULL);

    glfwMakeContextCurrent(screen);

    GLint init = glewInit();
    printf("Status da inicializacao do GLEW: %s\n", glewGetErrorString(init));

    /*Shader attachment*/
    GLuint program = GLSLCompileQuad();


    /*End of shader attatchment*/

    /*Objects declaring*/
    GLuint numb_vert = 4;
    vec3 vertexes[numb_vert];

    vec3 origin, bottom_left, top_right, top_left;
    vertexes[0][0] = -1.0; vertexes[0][1] = -1.0; vertexes[0][2] = 0.0;
    vertexes[1][0] = -1.0; vertexes[1][1] = 1.0; vertexes[1][2] = 0.0;
    vertexes[2][0] = 1.0; vertexes[2][1] = -1.0; vertexes[2][2] = 0.0;
    vertexes[3][0] = 1.0; vertexes[3][1] = 1.0; vertexes[3][2] = 0.0;

    vec4 color; color[0] = 1.0; color[1] = 0.0; color[2] = 0.0; color[3] = 1.0; 
    

    /*End of objects declaring*/

    /*Send geometry information to the shader*/
    GLuint buffer;
    glGenBuffers(1, &buffer);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertexes), vertexes, GL_DYNAMIC_DRAW);

    GLuint loc_vert = glGetAttribLocation(program, "position");
    glEnableVertexAttribArray(loc_vert);
    glVertexAttribPointer(loc_vert, 2, GL_FLOAT, GL_FALSE, sizeof(vertexes[0]), (void *) 0);


    GLuint loc_color = glGetUniformLocation(program, "color");
    glUniform4f(loc_color, color[0], color[1], color[2], color[3]);

    /*End of sending geometry information to the shader*/


    /*Window*/
    glfwShowWindow(screen);

    glfwSwapInterval(1);
    while(!glfwWindowShouldClose(screen)){

        glfwPollEvents();
        glClear(GL_COLOR_BUFFER_BIT);
        glClearColor(0.0, 0.0, 0.0, 1.0);

        // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

        glfwSwapBuffers(screen);


    }

    glEnd();
    glfwDestroyWindow(screen);
    glfwTerminate();
    return 0;
}


