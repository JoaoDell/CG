#include <SDL2\SDL_surface.h>
#include <SDL2\SDL.h>
#include <SDL2\SDL_main.h>
#include <SDL2\SDL_image.h>
#include <stdio.h>
#include <stdlib.h>
#include <GL\glew.h>
#define GLFW_INCLUDE_NONE
#include <GLFW\glfw3.h>
#include <cglm\cglm.h>
#include <math.h>
#include "..\GLib.h"



GLfloat angle = 0.0;
GLfloat angle2 = 0.0;
float tx, ty, tz;
float sx, sy, sz;
Vec3 transl;
Vec3 scale;
Vec3 angles;
GLfloat largura = 1920;
GLfloat altura = 1080;

float deltaTime = 0.0f;	//Tempo entre o ultimo frame e o atual. Usado para obter uma movimentacao mais "suave" da camera pelo cenario
float lastFrame = 0.0f; //Tempo do ultimo frame 



vec3 eye0    = {10.0, 5.0, 10.0};
vec3 center0 = {0.0, 0.0, 0.0};
vec3 up0     = {0.0, 1.0, 0.0};
vec3 boundaries = {50.0, 50.0, 50.0};


float speed = 0.5;

int P = 0;

GLfloat near;

static void eye_check(){

    if(eye0[0] > boundaries[0]) eye0[0] = boundaries[0];
    else if(eye0[0] < -boundaries[0]) eye0[0] = -boundaries[0];
    if(eye0[1] > boundaries[1]) eye0[1] = boundaries[1];
    else if(eye0[1] < -boundaries[1]) eye0[1] = -boundaries[1];
    if(eye0[2] > boundaries[2]) eye0[2] = boundaries[2];
    else if(eye0[2] < -boundaries[2]) eye0[2] = -boundaries[2];

}


static void key_event(GLFWwindow* window, int key, int scancode, int action, int mods){
    printf("Pressionando tecla %d\n", key);


    vec3 aux;

    if(key == 68 && (action == 1|| action == 2)) {
        glm_vec3_cross(center0, up0, aux);
        glm_vec3_normalize(aux);


        eye0[0] += speed*aux[0];
        eye0[1] += speed*aux[1];
        eye0[2] += speed*aux[2];



    } // d

    else if(key == 65 && (action == 1|| action == 2)){
        glm_vec3_cross(center0, up0, aux);
        glm_vec3_normalize(aux);

        eye0[0] -= speed*aux[0];
        eye0[1] -= speed*aux[1];
        eye0[2] -= speed*aux[2];


    } // a

    else if(key == 87 && (action == 1|| action == 2)){
        // glm_vec3_cross(, float *b, aux)
        eye0[0] += speed*center0[0];
        eye0[1] += speed*center0[1];
        eye0[2] += speed*center0[2];

    } // w

    else if(key == 83 && (action == 1|| action == 2)){
        eye0[0] -= speed*center0[0];
        eye0[1] -= speed*center0[1];
        eye0[2] -= speed*center0[2];



    } // s

    if(key == GLFW_KEY_P && action == GLFW_PRESS && P == 0) P = 1;
    else if(key == GLFW_KEY_P && action == GLFW_PRESS && P == 1) P = 0;

}


int FirstMouse = 1;


int LastX = 960;
int LastY = 540;

float yaw = -90.0;
float pitch = 0.0; 




static void mouse_event(GLFWwindow *window, double xpos, double ypos){


    if(FirstMouse){
        LastX = xpos;
        LastY = ypos;
        FirstMouse = 0;
    }

    float xoffset = xpos - LastX;
    float yoffset = LastY - ypos;
    LastX = xpos;
    LastY = ypos;

    float sensitivity = 0.3; 
    xoffset *= sensitivity;
    yoffset *= sensitivity;

    yaw += xoffset;
    pitch += yoffset;

    if(pitch > 89.9) pitch = 89.9;
    else if(pitch < -89.9) pitch = -89.9;

    vec3 front;

    front[0] = cos(glm_rad(yaw))*cos(glm_rad(pitch));
    front[1] = sin(glm_rad(pitch));
    front[2] = sin(glm_rad(yaw))*cos(glm_rad(pitch));

    glm_normalize(front);

    center0[0] = front[0];
    center0[1] = front[1];
    center0[2] = front[2];

    // glfwSetCursorPos(window, largura/2, altura/2);
}


/*
static void mouse_event(GLFWwindow* window, int button, int action, int mods){
    printf("Pressionando tecla %d\n", button);

    GLfloat Lastx = largura/2;
    GLfloat Lasty = altura/2;

    if(button == 0 && action == 1) near += 0.01; // esquerdo
    else if(button == 1 && action == 1) near -= 0.01; // direito

}*/


int WinMain(){ //A função main teve de ser alterada pra WinMain pois conflitava com a main do SDL

    /*INICIALIZACAO DO GLFW*/
    glfwInit();

    glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);

    GLFWwindow *janela = glfwCreateWindow(largura, altura, "Janela do Lamp", NULL, NULL);

    glfwMakeContextCurrent(janela);
    /*FIM DA INICIALIZACAO DO GLFW*/




    /*INICIALIZACAO DO GLEW*/
    GLint init = glewInit();
    printf("Status da inicializacao do GLEW: %s\n", glewGetErrorString(init));
    /*FIM INICIALIZACAO DO GLEW*/




    /*INICIALIZACAO E COMPILACAO DO GLSL*/
    GLuint program = GLSLCompile3DLight();
    /*FIM DA INICIALIZACAO E COMPILACAO DO GLSL*/

    




    /*INICIALIZACAO DOS VERTICES*/


    //Abaixo é a função de renderizar cenas
    Scene *scene = SceneFromFile("quadra/", "quadra.obj");





    Vec3 vert_vert[scene->total_vert];
    for(int j = 0; j < scene->total_vert; j++){    
        vert_vert[j] = scene->general_array[j];
    } 

    Vec2 text_vert[scene->total_vert];
    for(int j = 0; j < scene->total_vert; j++){    
        text_vert[j] = scene->general_text[j];
    } 

    Vec3 norm_vert[scene->total_vert];
    for(int j = 0; j < scene->total_vert; j++){    
        text_vert[j] = scene->general_text[j];
    } 
    


    printf("%d\n", scene->total_vert);


    GLfloat angle1 =  -2*M_PI/36000;
    GLfloat angle3 = 0.0;



    transl.x = 0.0; 
    transl.y = 0.0; 
    transl.z = 0.0;

    angles.x = 0.0;
    angles.y = 0.0;
    angles.z = 0.0;

    scale.x = 1.0;
    scale.y = 1.0;
    scale.z = 1.0;

    Vec3 transl0, angles0, scale0;
    transl0.x = 0.0; 
    transl0.y = 0.0; 
    transl0.z = 0.0;

    angles0.x = 0.0;
    angles0.y = 0.0;
    angles0.z = 0.0;

    scale0.x = 1.0;
    scale0.y = 1.0;
    scale0.z = 1.0;


    vec4 a[4];
    vec4 perspec[4];

    glm_mat4_identity(a);
    glm_mat4_identity(perspec);

    near = 0.1;

    
    glm_lookat(eye0, center0, up0, a);
    glm_perspective(glm_rad(45.0), largura/altura, near, 100.0, perspec);
    

    glm_mat4_transpose(a);
    glm_mat4_transpose(perspec);

    GLuint textures[scene->numb_objs];
    
    glGenTextures(scene->numb_objs, textures); //Gera um id para a quantidade de texturas n informadas, armazendo-as num vetor de tamanho n


    for(int i = 0; i < scene->numb_objs; i++){
        scene->array_objs[i].model_matrix      = IdentityMatrix();
        scene->array_objs[i].view_matrix       = mat_from_glm(a);
        scene->array_objs[i].projection_matrix = mat_from_glm(perspec);
        scene->array_objs[i].Reference_Matrix  = CoordMatrix(scene->array_objs[i].center_of_mass);

        //Inicializando as texturas de cada objeto
        scene->array_objs[i].texture_info.format = GL_RGBA;

        scene->array_objs[i].texture_info.texture_id = textures[i];
    }

    

    /*FIM DA INICIALIZACAO DOS VERTICES*/



    /*SETUP DOS BUFFERS*/
    GLuint Buffers[2];
    glGenBuffers(2, Buffers);
    glBindBuffer(GL_ARRAY_BUFFER, Buffers[0]);

    glBufferData(GL_ARRAY_BUFFER, sizeof(vert_vert), vert_vert, GL_DYNAMIC_DRAW);

    GLint loc = glGetAttribLocation(program, "position");
    GLint color = glGetUniformLocation(program, "color");
    GLint model = glGetUniformLocation(program, "model");
    GLint view = glGetUniformLocation(program, "view");
    GLint proj = glGetUniformLocation(program, "projection");

    glEnableVertexAttribArray(loc);
    glVertexAttribPointer(loc, 3, GL_FLOAT, GL_FALSE, sizeof(vert_vert[0]), (void*) 0); //Para 3D, substituir a segunda entrada por "3"

    

    // texture_id = 0;
    // cubo->texture_id = texture_id;
    // cubo->texture_info.TexturePath = "quadra/text1.png";
    // //cubo->texture_info.format = GL_RGB;
    // TextureFromFile(cubo->texture_info.TexturePath, cubo->texture_id, cubo); //A versão do SDL_image funcionando era a 2.0.1
    // //TextureFromFile("cup/textures/metallic.png", 1, cubo); //A versão do SDL_image funcionando era a 2.0.1



    
    glBindBuffer(GL_ARRAY_BUFFER, Buffers[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(text_vert), text_vert, GL_STATIC_DRAW);
    GLint loc_texture = glGetAttribLocation(program, "texture_coord");

    glEnableVertexAttribArray(loc_texture);
    glVertexAttribPointer(loc_texture, 2, GL_FLOAT, GL_FALSE, sizeof(text_vert[0]), (void*) 0);



    /*FIM DO SETUP DOS BUFFERS*/



    glfwSetKeyCallback(janela, key_event);

    
    glfwSetCursorPosCallback(janela, mouse_event);
    glfwSetCursorPos(janela, largura/2, altura/2);

    glfwShowWindow(janela);
    glEnable(GL_DEPTH_TEST); //Adicionar esta linha pra 3D
    /*LACO PRINCIPAL*/
    while(!glfwWindowShouldClose(janela)){

        glfwPollEvents();

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //Em programas em 3D, lembrar de adicionar o | GL_DEPTH_BUFFER_BIT
        glClearColor(0.0, 0.0, 0.0, 1.0);



        if(P == 1){
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        } 
        else if(P == 0){
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        }

        /*
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;  
        
        eye[0] += transl.x; eye[1] += transl.y; eye[2] += transl.z;
        center0[0] += transl.x; center0[1] += transl.y; center0[2] += transl.z;
        glm_lookat(eye, center0, up, a);
        glm_mat4_transpose(a);
        cubo->view_matrix = mat_from_glm(a);*/
        //Translate(transl.x, transl.y, transl.z, cubo->view_matrix);

        center0[0] += transl.x; center0[1] += transl.y; center0[2] += transl.z;
        eye_check();
        
        //Renderizando a cena
        for(int i = 0; i < scene->numb_objs; i++){
            View(eye0, center0, up0, &scene->array_objs[i]);
            UpdateObj3D(&scene->array_objs[i], model, view, proj, transl0, angles, scale, GLOBAL);
            RenderObj3D(scene->array_objs[i], color);
        }
        


        glfwSwapBuffers(janela);
        glfwWaitEvents();
    }
    /*FIM LACO PRINCIPAL*/

    // DestroyScene(scene);

    glfwDestroyWindow(janela);
    glfwTerminate();
    glEnd();

    return 0;
}