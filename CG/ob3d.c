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


GLfloat yaw = 0.0;
GLfloat pitch = 0.0;

int FirstMouse = 1;


vec3 center0 = {0.0, 0.0, 0.0};

int P = 0;

GLfloat near;

static void key_event(GLFWwindow* window, int key, int scancode, int action, int mods){
    printf("Pressionando tecla %d\n", key);

    if(key == 263 && action == 1) angles.y = -2*M_PI/3600; // seta esquerda
    else if( key == 262 && action == 1) angles.y = 2*M_PI/3600; // seta direita
    else if( key == 264 && action == 1) angles.x = -2*M_PI/3600; // seta cima
    else if( key == 265 && action == 1) angles.x = 2*M_PI/3600; // seta baixo
    else if(action == 0) {angles.x = 0.0; angles.y = 0.0;}

    if(key == 68 && action == 1) transl.x += 0.01; // d
    else if(key == 65 && action == 1) transl.x -= 0.01; // a
    else if(key == 87 && action == 1) transl.y += 0.01; // w
    else if(key == 83 && action == 1) transl.y -= 0.01; // s
    else if(action == 0){transl.x = 0.0; transl.y = 0.0;}

    if(key == 69 && action == 1) transl.z += 0.01; // d
    else if(key == 81 && action == 1) transl.z -= 0.01; // a
    else if(action == 0){transl.z = 0.0;}

    if(key == 69 && action == 1) transl.z += 0.01; // d
    else if(key == 81 && action == 1) transl.z -= 0.01; // a
    else if(action == 0){transl.z = 0.0;}

    if(key == GLFW_KEY_P && action == GLFW_PRESS && P == 0) P = 1;
    else if(key == GLFW_KEY_P && action == GLFW_PRESS && P == 1) P = 0;

}

GLfloat LastX = 960;
GLfloat LastY = 540;

static void mouse_event(GLFWwindow *janela, double Xpos, double Ypos){ //Não consegui implementar o movimento do mouse

    GLdouble x_pos;
    GLdouble y_pos;
    glfwGetCursorPos(janela, &x_pos, &y_pos);
    //glfwSetCursorPos(janela, largura/2, altura/2);

    if(FirstMouse){
        LastX = Xpos;
        LastY = Ypos;
        FirstMouse = 0;

    }


    GLfloat xoffset = x_pos - 960;
    GLfloat yoffset = 540 - y_pos;
    LastX = Xpos;
    LastY = Ypos;

    GLfloat sens = 0.3;
    xoffset *= sens;    //Calcula o quanto o angulo da camera em X foi alterado 
    yoffset *= sens;    //Calcula o quanto o angulo da camera em Y foi alterado

    yaw += xoffset;     //Calcula o angulo atual da camera em X
    pitch += yoffset;   //Calcula o angulo atual da camera em Y

    /*
    if (pitch >= M_PI/2 - M_PI/20 ) pitch = M_PI/2 - M_PI/20;    //Define limites para o angulo da camera em Y
    if (pitch <= -M_PI/2 + M_PI/20) pitch = -M_PI/2 + M_PI/20;*/

    
    if (pitch >= 90.0) pitch = 90.0;    //Define limites para o angulo da camera em Y
    if (pitch <= -90.0) pitch = -90.0;

    //Com base nos angulos da camera em X e Y calcula o ponto para o qual a camera esta olhando
    vec3 front;
    
    /*
    front[0] = (largura/2)*cos(yaw)*cos(pitch);
    front[1] = (altura/2)*sin(pitch);
    front[2] = (largura/2)*sin(yaw)*cos(pitch);*/

    
    front[0] = sin(glm_rad(yaw)) * cos(glm_rad(pitch));
    front[1] = sin(glm_rad(pitch));
    front[2] = cos(glm_rad(yaw)) * cos(glm_rad(pitch));

    glm_normalize(front);
    center0[0] = front[0];
    center0[1] = front[1];
    center0[2] = front[2];

    
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

    Obj3D *cubo = Obj3DFromFile("quadra/lojinha.obj");
    cubo->texture_info.format = GL_RGBA;

    //Abaixo é a função de renderizar cenas
    // Scene *scene = SceneFromFile("quadra/", "quadra.obj");
    // printf("a\n");

    // printf("%llu\n", sizeof(scene));
    // DestroyScene(scene);


    //printf("a\n");
                   

    cubo->model_matrix = IdentityMatrix();
    cubo->Reference_Matrix = CoordMatrix(cubo->center_of_mass);


    

    Vec3 tri[cubo->numb_vertices];
    for(int j = 0; j < cubo->numb_vertices; j++){    
        tri[j] = cubo->array[j];
    }   

    Vec2 text_vert[cubo->numb_vertices];
    for(int j = 0; j < cubo->numb_vertices; j++){    
        text_vert[j] = cubo->texture[j];
    }  

    printf("%d\n", cubo->numb_vertices);


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


    GLfloat up[3] = {0.0, 1.0, 0.0};
    GLfloat center[3] = {0.0, 0.0, 0.0};
    GLfloat eye[3] = {20.0, 20.0, 20.0};


    vec4 a[4];
    vec4 perspec[4];

    glm_mat4_identity(a);
    glm_mat4_identity(perspec);

    near = 0.1;

    

    
    glm_lookat(eye, center, up, a);
    glm_perspective(glm_rad(45.0), largura/altura, near, 100.0, perspec);
    

    glm_mat4_transpose(a);
    glm_mat4_transpose(perspec);

    cubo->view_matrix = mat_from_glm(a);
    cubo->projection_matrix = mat_from_glm(perspec);

    Translate(-cubo->center_of_mass.x,-cubo->center_of_mass.y, -cubo->center_of_mass.z, cubo->Reference_Matrix);
    cubo->center_of_mass = CenterOfMass(cubo->array, cubo->numb_vertices);
    

    /*FIM DA INICIALIZACAO DOS VERTICES*/



    /*SETUP DOS BUFFERS*/
    GLuint Buffers[2];
    glGenBuffers(2, Buffers);
    glBindBuffer(GL_ARRAY_BUFFER, Buffers[0]);

    glBufferData(GL_ARRAY_BUFFER, sizeof(tri), tri, GL_DYNAMIC_DRAW);

    GLint loc = glGetAttribLocation(program, "position");
    GLint color = glGetUniformLocation(program, "color");
    GLint model = glGetUniformLocation(program, "model");
    GLint view = glGetUniformLocation(program, "view");
    GLint proj = glGetUniformLocation(program, "projection");

    glEnableVertexAttribArray(loc);
    glVertexAttribPointer(loc, 3, GL_FLOAT, GL_FALSE, sizeof(tri[0]), (void*) 0); //Para 3D, substituir a segunda entrada por "3"

    
    GLuint texture_id;

    //"cup/textures/Base_color.png"

    texture_id = 0;
    cubo->texture_id = texture_id;
    cubo->texture_info.TexturePath = "quadra/text1.png";
    //cubo->texture_info.format = GL_RGB;
    TextureFromFile(cubo->texture_info.TexturePath, cubo->texture_id, cubo); //A versão do SDL_image funcionando era a 2.0.1
    //TextureFromFile("cup/textures/metallic.png", 1, cubo); //A versão do SDL_image funcionando era a 2.0.1

    /*CODIGO MORTO*///Nao sei pra que serve esses 
    GLuint textures;
    
    glGenTextures(1, &textures); //Gera um id para a quantidade de texturas n informadas, armazendo-as num vetor de tamanho n
    /*CODIGO MORTO*/
    
    glBindBuffer(GL_ARRAY_BUFFER, Buffers[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(text_vert), text_vert, GL_STATIC_DRAW);
    GLint loc_texture = glGetAttribLocation(program, "texture_coord");

    glEnableVertexAttribArray(loc_texture);
    glVertexAttribPointer(loc_texture, 2, GL_FLOAT, GL_FALSE, sizeof(text_vert[0]), (void*) 0);



    /*FIM DO SETUP DOS BUFFERS*/



    glfwSetKeyCallback(janela, key_event);


    
    glfwSetCursorPosCallback(janela, mouse_event);



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



        UpdateObj3D(cubo, model, view, proj, transl, angles, scale);

        RenderObj3D(*cubo, color);
        


        glfwSwapBuffers(janela);
    }
    /*FIM LACO PRINCIPAL*/

    DestroyObj3D(cubo);

    glfwDestroyWindow(janela);
    glfwTerminate();
    glEnd();

    return 0;
}