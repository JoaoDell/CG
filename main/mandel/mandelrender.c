#include "mandel.h"

float speed = 1.0, dt = 0.01, scale = 1.0;
vec3 offset;
int iter = 30;



static void key_event(GLFWwindow* window, int key, int scancode, int action, int mods){
    // printf("Pressionando tecla %d\n", key);


    vec3 aux;

    if(key == GLFW_KEY_A && (action == 1|| action == 2)) {
        offset[0] -= speed*dt;
    } 

    else if(key == GLFW_KEY_D && (action == 1|| action == 2)){
        offset[0] += speed*dt;
    } 

    else if(key == GLFW_KEY_S && (action == 1|| action == 2)){
        offset[1] -= speed*dt;
    }

    else if(key == GLFW_KEY_W && (action == 1|| action == 2)){
        offset[1] += speed*dt;
    } 


    else if(key == GLFW_KEY_E && (action == 1|| action == 2)){
        scale = 1.01;
        dt *= scale;

    } 

    else if(key == GLFW_KEY_Q && (action == 1|| action == 2)){
        scale = 0.99;
        dt *= scale;

    } 

    else if(key == GLFW_KEY_X && (action == 1|| action == 2)){
        if(iter < 50) iter += 1;

    } 

    else if(key == GLFW_KEY_Z && (action == 1|| action == 2)){
        if(iter > 2) iter -= 1;
    } 

    else scale = 1.0;

    // if(key == GLFW_KEY_P && action == GLFW_PRESS && P == 0) P = 1;
    // else if(key == GLFW_KEY_P && action == GLFW_PRESS && P == 1) P = 0;

    // if(key == GLFW_KEY_Q && action == GLFW_PRESS) F = 1;
    // else if(key == GLFW_KEY_E && action == GLFW_PRESS) F = -1;
    // if(key == GLFW_KEY_Q && action == GLFW_RELEASE) F = 0; //esquerdo
    // else if(key == GLFW_KEY_E && action == GLFW_RELEASE) F = 0; // direito
}




int main(){

    glfwInit();
    glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);
    // glfwWindowHint(GLFW_SAMPLES, 8); //HABILITANDO O MULTISAMPLING NO GLFW

    vec2 resolution; resolution[0] = 1920; resolution[1] = 1080;

    GLFWwindow *screen = glfwCreateWindow(resolution[0], resolution[1], "Mandel", NULL, NULL);

    glfwMakeContextCurrent(screen);

    GLint init = glewInit();
    printf("Status da inicializacao do GLEW: %s\n", glewGetErrorString(init));

    /*Shader attachment*/
    GLuint program = GLSLCompileQuad();


    /*End of shader attatchment*/

    /*Objects declaring*/
    offset[0] = 0.0;
    offset[1] = 0.0;
    offset[2] = 0.0;

    GLuint numb_vert = 4;
    vec3 vertexes[numb_vert];

    vec3 origin, bottom_left, top_right, top_left;
    vertexes[0][0] = -1.0; vertexes[0][1] = -1.0; vertexes[0][2] = 0.0;
    vertexes[1][0] = -1.0; vertexes[1][1] = 1.0; vertexes[1][2] = 0.0;
    vertexes[2][0] = 1.0; vertexes[2][1] = -1.0; vertexes[2][2] = 0.0;
    vertexes[3][0] = 1.0; vertexes[3][1] = 1.0; vertexes[3][2] = 0.0;

    vec4 color; color[0] = 1.0; color[1] = 0.0; color[2] = 0.0; color[3] = 1.0; 


    GLfloat *model = IdentityMatrix();

    Scale(resolution[0]/resolution[1], 1.0, 1.0, model);

    

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

    GLuint loc_res = glGetUniformLocation(program, "resolution");
    glUniform2f(loc_res, resolution[0], resolution[1]);

    GLuint loc_model = glGetUniformLocation(program, "model");
    glUniformMatrix4fv(loc_model, 1, GL_TRUE, model);

    GLuint loc_iter = glGetUniformLocation(program, "mmax_iter");
    glUniform1i(loc_iter, iter);
    /*End of sending geometry information to the shader*/


    /*Window*/
    glfwShowWindow(screen);
    glfwSetKeyCallback(screen, key_event);
    // glEnable(GL_MULTISAMPLE); //HABILITANDO O MULTISAMPLING NO OPENGL (ANTIALIASING)

    glfwSwapInterval(1);
    while(!glfwWindowShouldClose(screen)){

        glfwPollEvents();
        glClear(GL_COLOR_BUFFER_BIT);
        glClearColor(0.0, 0.0, 0.0, 1.0);

        // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        model[3] = offset[0];
        model[7] = offset[1];
        
        RelativeScale(scale, scale, 1.0, model, offset);
        glUniformMatrix4fv(loc_model, 1, GL_TRUE, model);
        glUniform1i(loc_iter, iter);

        printf("%f\n", dt);
        glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

        glfwSwapBuffers(screen);


    }

    glEnd();
    glfwDestroyWindow(screen);
    glfwTerminate();
    return 0;
}


