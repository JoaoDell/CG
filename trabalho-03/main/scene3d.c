/*NOMES                          - NÚMEROS USP*/
/*João Victor Dell Agli Floriano - 10799783*/
/*Karoliny Oliveira              - 10368020*/
/*Alex Soares Prestes            - 10407962*/


//PROJETO DESENVOLVIDO NO WINDOWS 
//COMANDO DE COMPILAÇÃO:  gcc scene3d.c ..\GLib.c -lglfw3 -lglew32 -lgdi32 -lopengl32 -lSDL2_image -lSDL2main -lSDL2 -o scene3d


#include <SDL2\SDL_surface.h>
#include <SDL2\SDL.h>           //VERSÃO 2.0.14
#include <SDL2\SDL_main.h>     
#include <SDL2\SDL_image.h>     //VERSÃO 2.0.1
#include <cglm/cam.h>
#include <cglm/mat4.h>
#include <cglm/project.h>
#include <stdio.h>
#include <stdlib.h>
#include <GL\glew.h>            //VERSÃO 2.10
#define GLFW_INCLUDE_NONE
#include <GLFW\glfw3.h>         //VERSÃO 3.3.4
#include <cglm\cglm.h>
#include <math.h>
#include "..\include\GLib.h"



/*INICIALIZANDO FUNÇÕES PARA EVENTOS DE TECLADO E TEMAIS VARIÁVEIS*/
GLfloat largura = 1920;
GLfloat altura = 1080;




GLfloat angle = 0.0;
float tx, ty, tz;
float sx, sy, sz;
Vec3 transl;
Vec3 scale;
Vec3 angles;
//Já tinha uma estrutura Vec3 bem antes de instalar o glm, e não tive tempo de mudar o nome

vec3 eye0    = {10.0, 5.0, 10.0};
vec3 center0 = {0.0, 0.0, 0.0};
vec3 up0     = {0.0, 1.0, 0.0};

vec3 boundaries = {100, 100, 100}; //Fronteiras a não ser passadas

vec3 galpao0 = {2.055846, -0.007984, -18.088926}; // Fronteiras para verificar se a camera está dentro de um objeto
vec3 galpao1 = {17.985043, 10.072246, -8.044674};

float speed = 0.5; //Velocidade de movimento pelo cenário


int O = 0; 
GLfloat near = 0.1;
int N = 0;
GLfloat far = 500;
int F = 0;
GLfloat fov = 45.0;
int Fo = 0;


int U = 0;
int P = 0;
GLfloat globalKa = 1.0;



static void eye_check(){

    if(eye0[0] > boundaries[0]) eye0[0] = boundaries[0];
    else if(eye0[0] < -boundaries[0]) eye0[0] = -boundaries[0];
    if(eye0[1] > boundaries[1]) eye0[1] = boundaries[1];
    else if(eye0[1] < -boundaries[1]) eye0[1] = -boundaries[1];
    if(eye0[2] > boundaries[2]) eye0[2] = boundaries[2];
    else if(eye0[2] < -boundaries[2]) eye0[2] = -boundaries[2];

}



static void key_event(GLFWwindow* window, int key, int scancode, int action, int mods){
    // printf("Pressionando tecla %d\n", key);


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

    if(key == GLFW_KEY_O && action == GLFW_PRESS && O == 0) O = 1;
    else if(key == GLFW_KEY_O && action == GLFW_PRESS && O == 1) O = 0;

    if(key == GLFW_KEY_Q && action == GLFW_PRESS) F = 1;
    else if(key == GLFW_KEY_E && action == GLFW_PRESS) F = -1;
    if(key == GLFW_KEY_Q && action == GLFW_RELEASE) F = 0; //esquerdo
    else if(key == GLFW_KEY_E && action == GLFW_RELEASE) F = 0; // direito

    if(key == GLFW_KEY_U && action == GLFW_PRESS) U = 1; //Parametro de luz
    else if(key == GLFW_KEY_U && action == GLFW_RELEASE) U = 0; 

    if(key == GLFW_KEY_P && action == GLFW_PRESS) P = 1; //Parametro de luz
    else if(key == GLFW_KEY_P && action == GLFW_RELEASE) P = 0; 
}


int FirstMouse = 1;


int LastX = 960; //Metade da largura
int LastY = 540; //Metade da altura

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



static void mouse_click(GLFWwindow* window, int button, int action, int mods){


    if(button == 0 && action == GLFW_PRESS) N = 1; // esquerdo
    else if(button == 1 && action == GLFW_PRESS) N = 2; // direito

    if(button == 0 && action == GLFW_RELEASE) N = 0; //esquerdo
    else if(button == 1 && action == GLFW_RELEASE) N = 0; // direito

}

static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset){
    if(yoffset > 0) Fo = 1;
    else if(yoffset < 0) Fo = -1;
    yoffset = 0.0l;
}


int WinMain(){ //A função main teve de ser alterada pra WinMain pois conflitava com a main do SDL

    /*INICIALIZACAO DO GLFW*/
    glfwInit();

    glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);
    glfwWindowHint(GLFW_SAMPLES, 4); //HABILITANDO O MULTISAMPLING NO GLFW

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


    //Abaixo é a função de coletar os vários objetos em um .obj
    Scene *scene = SceneFromFile("quadra/", "quadra.obj");

    


    /*COPIANDO OS VERTICES PARA MANDAR PARA GPU*/
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
        norm_vert[j] = scene->general_norm[j];
    } 
    


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


    //Variáveis a não serem alteradas 
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

    GLfloat angle_anim = 0.0;
    GLfloat angle_anim2 = 0.0;
    GLfloat angle_anim3 = 0.0;

    
    glm_lookat(eye0, center0, up0, a);
    glm_perspective(glm_rad(fov), largura/altura, near, far, perspec);
    

    glm_mat4_transpose(a);
    glm_mat4_transpose(perspec);

    


    for(int i = 0; i < scene->numb_objs; i++){
        scene->array_objs[i].model_matrix      = IdentityMatrix();
        scene->array_objs[i].view_matrix       = mat_from_glm(a);
        scene->array_objs[i].projection_matrix = mat_from_glm(perspec);
        scene->array_objs[i].Reference_Matrix  = CoordMatrix(scene->array_objs[i].center_of_mass);

        //Inicializando as texturas de cada objeto
        scene->array_objs[i].texture_info.format = GL_RGBA;
    }


    /*ORDEM DOS OBJETOS

        1  - banco_Cube.001
        2  - cesta1_Cylinder
        3  - cesta2_Cylinder.002
        4  - galpao_Cube.002
        5  - telhado_Cube.005
        6  - ch├úo_Plane
        7  - bolafora_Sphere.002
        8  - bola2_Sphere.003
        9  - bola3_Sphere.004
        10 - estante1_Cube
        11 - estante2_Cube.004
        12 - bola5_Sphere.006
        13 - bola4_Sphere.005
        14 - caixa_cima1_Cube.006
        15 - caixa_baixo_Cube.008
        16 - caixa_cima2_Cube.009
        17 - skybox_Cube.007
        18 - caixa_energia_Cube.010
        19 - cabos_Cylinder.001
        20 - grades_Cube.011 
    */

    /*INICIALIZAÇÃO DAS TEXTURAS*/


    /*ATENÇÃO, IMPORTANTE*/
    //A versão do SDL_image funcionando era a 2.0.1, anteriores a esta estavam bugando.
    //Este bug inclusive já foi identificado por outros pela internet, e submetido aos desenvolvedores.

    TextureFromFile("quadra/textures/banco.png", &scene->array_objs[0]);
    TextureFromFile("quadra/textures/cesta1.png", &scene->array_objs[1]);
    TextureFromFile("quadra/textures/cesta2.png", &scene->array_objs[2]);
    TextureFromFile("quadra/textures/text1.png", &scene->array_objs[3]);
    TextureFromFile("quadra/textures/telhado.png", &scene->array_objs[4]);
    TextureFromFile("quadra/textures/chão.png", &scene->array_objs[5]);
    TextureFromFile("quadra/textures/bola1.png", &scene->array_objs[6]); //bola central
    TextureFromFile("quadra/textures/bola1.png", &scene->array_objs[7]);
    TextureFromFile("quadra/textures/bola1.png", &scene->array_objs[8]);
    TextureFromFile("quadra/textures/estante.png", &scene->array_objs[9]);
    TextureFromFile("quadra/textures/estante.png", &scene->array_objs[10]);
    TextureFromFile("quadra/textures/bola1.png", &scene->array_objs[11]);
    TextureFromFile("quadra/textures/bola1.png", &scene->array_objs[12]);
    TextureFromFile("quadra/textures/caixa_cima2.png", &scene->array_objs[13]);
    TextureFromFile("quadra/textures/caixa_baixo.png", &scene->array_objs[14]);
    TextureFromFile("quadra/textures/caixa_cima2.png", &scene->array_objs[15]);

    scene->array_objs[16].texture_info.format = GL_RGB;
    TextureFromFile("quadra/textures/skybox2.png", &scene->array_objs[16]);
    RelativeRotateXaxis(M_PI/2, scene->array_objs[16].model_matrix, scene->array_objs[16].center_of_mass);//Rotação para ajustar a skybox

                                                                           
    TextureFromFile("quadra/textures/caixa_energia.png", &scene->array_objs[17]);
    TextureFromFile("quadra/textures/cabos.png", &scene->array_objs[18]);
    TextureFromFile("quadra/textures/grades.png", &scene->array_objs[19]); //A grade deve vir por ultimo para que a transparência dela valha

    scene->array_objs[3].texture_info.texture_inside_id = LoneTextureFromFile("quadra/textures/text_in.png", GL_RGBA);
    scene->array_objs[3].texture_info.has_inside = 1;

    //DEFININDO OS PARAMETROS DE ILUMINAÇÃO DE CADA OBJETO
    DefineObj3DIlum(globalKa, 1.0, 0.5, 5, &scene->array_objs[0]);
    DefineObj3DIlum(globalKa, 1.0, 1.0, 40, &scene->array_objs[1]);
    DefineObj3DIlum(globalKa, 1.0, 1.0, 40, &scene->array_objs[2]);
    DefineObj3DIlum(globalKa, 1.0, 0.7, 1, &scene->array_objs[3]);
    DefineObj3DIlum(globalKa, 1.0, 0.9, 2, &scene->array_objs[4]);
    DefineObj3DIlum(globalKa, 1.0, 0.8, 7.0, &scene->array_objs[5]);
    DefineObj3DIlum(globalKa, 1.0, 10.0, 100, &scene->array_objs[6]); //Bola central
    DefineObj3DIlum(globalKa, 1.0, 10.0, 100, &scene->array_objs[7]);
    DefineObj3DIlum(globalKa, 1.0, 10.0, 100, &scene->array_objs[8]);
    DefineObj3DIlum(globalKa, 1.0, 0.9, 10, &scene->array_objs[9]);
    DefineObj3DIlum(globalKa, 1.0, 0.9, 10, &scene->array_objs[10]);
    DefineObj3DIlum(globalKa, 1.0, 10.0, 100, &scene->array_objs[11]);
    DefineObj3DIlum(globalKa, 1.0, 10.0, 100, &scene->array_objs[12]);
    DefineObj3DIlum(globalKa, 1.0, 1.0, 10, &scene->array_objs[13]);
    DefineObj3DIlum(globalKa, 1.0, 1.0, 10, &scene->array_objs[14]);
    DefineObj3DIlum(globalKa, 1.0, 1.0, 10, &scene->array_objs[15]);
    DefineObj3DIlum(1.0, 0.0, 0.0, 1.0, &scene->array_objs[16]);
    DefineObj3DIlum(globalKa, 1.0, 1.0, 10, &scene->array_objs[17]);
    DefineObj3DIlum(globalKa, 1.0, 1.0, 10, &scene->array_objs[18]);
    DefineObj3DIlum(globalKa, 1.0, 20.0, 100, &scene->array_objs[19]);

    for(int i = 0; i < scene->numb_objs; i++){
        //Parametros de iluminação no ambiente interno, os Kds e Kss estão nulos para que não sofram influencia da luz externa
        DefineObj3DIlumIn(globalKa, 0.0, 0.0, 1.0, &scene->array_objs[i]);
    }



    Vec3 lightPos;
    lightPos.x = -80.0;
    lightPos.y = 80.0;
    lightPos.z = 0.0; 

    Color lightColor = DefineColor(217.0, 93.0, 13.0, 1.0);
    Color ambientColor = DefineColor(255.0, 255.0, 255.0, 1.0);
    
    /*FIM DA INICIALIZAÇÃO DAS TEXTURAS*/
    

    /*FIM DA INICIALIZACAO DOS VERTICES*/






    /*SETUP DOS BUFFERS*/
    GLuint Buffers[3];
    glGenBuffers(3, Buffers);

    //VERTICES DOS OBJETOS
    glBindBuffer(GL_ARRAY_BUFFER, Buffers[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vert_vert), vert_vert, GL_DYNAMIC_DRAW);

    GLint loc = glGetAttribLocation(program, "position");
    GLint color = glGetUniformLocation(program, "color");
    GLint model = glGetUniformLocation(program, "model");
    GLint view = glGetUniformLocation(program, "view");
    GLint proj = glGetUniformLocation(program, "projection");


    glEnableVertexAttribArray(loc);
    glVertexAttribPointer(loc, 3, GL_FLOAT, GL_FALSE, sizeof(vert_vert[0]), (void*) 0); //Para 3D, substituir a segunda entrada por "3"



    //VERTICES DE TEXTURA
    glBindBuffer(GL_ARRAY_BUFFER, Buffers[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(text_vert), text_vert, GL_STATIC_DRAW);
    GLint loc_texture = glGetAttribLocation(program, "texture_coord");

    glEnableVertexAttribArray(loc_texture);
    glVertexAttribPointer(loc_texture, 2, GL_FLOAT, GL_FALSE, sizeof(text_vert[0]), (void*) 0);




    //VERTICES DAS NORMAIS
    glBindBuffer(GL_ARRAY_BUFFER, Buffers[2]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(norm_vert), norm_vert, GL_STATIC_DRAW);
    
    GLint loc_norm = glGetAttribLocation(program, "normals");
    GLint loc_lightPos = glGetUniformLocation(program, "lightPos");
    GLint loc_lightColor = glGetUniformLocation(program, "lightColor");
    GLint loc_ambientColor = glGetUniformLocation(program, "ambientColor");
    GLint loc_viewPos = glGetUniformLocation(program, "viewPos");
    GLint Ka = glGetUniformLocation(program, "Ka");
    GLint Kd = glGetUniformLocation(program, "Kd");
    GLint Ks = glGetUniformLocation(program, "Ks");
    GLint ns = glGetUniformLocation(program, "ns"); 

    glUniform3f(loc_lightPos, lightPos.x, lightPos.y, lightPos.z);
    glUniform3f(loc_lightColor, lightColor.r, lightColor.g, lightColor.b);
    glUniform3f(loc_ambientColor, ambientColor.r, ambientColor.g, ambientColor.b);


    glEnableVertexAttribArray(loc_norm);
    glVertexAttribPointer(loc_norm, 3, GL_FLOAT, GL_FALSE, sizeof(norm_vert[0]), (void*) 0);

    /*FIM DO SETUP DOS BUFFERS*/








    /* REGISTRANDO EVENTOS DE ENTRADA*/
    glfwSetKeyCallback(janela, key_event);
    glfwSetMouseButtonCallback(janela, mouse_click);
    glfwSetCursorPosCallback(janela, mouse_event);
    glfwSetScrollCallback(janela, scroll_callback);
    glfwSetCursorPos(janela, largura/2, altura/2);
    double mousex, mousey;
    glfwGetCursorPos(janela, &mousex, &mousey);
    /*FIM DOS REGISTROS DE EVENTOS DE ENTRADA*/



    glfwShowWindow(janela);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_MULTISAMPLE); //HABILITANDO O MULTISAMPLING NO OPENGL

    /*LACO PRINCIPAL*/
    while(!glfwWindowShouldClose(janela)){

        glfwPollEvents();


        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 
        glClearColor(0.0, 0.0, 0.0, 1.0);


        /*PARAMETROS PROJECTION E RENDERIZAÇÃO*/
        if(O == 1)
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        else if(O == 0)
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        if(F == 1) far += 1.0;
        else if(F == -1) far -= 1.0;
        if(N == 1) near += 0.1;
        else if(N == 2) near -= 0.1;
        if(Fo == -1){fov += 1.0; Fo = 0;} 
        else if(Fo == 1){fov -= 1.0; Fo = 0;} 
        if(fov > 90.0) fov = 90.0;
        else if (fov < 0.0) fov = 0.0;
        if(far <= near) far = near;
        else if(far >= 500.0) far = 500.0;          
        if(near <= 0.01) near = 0.01;
        else if(near >= far) near = far;

        if(U == 1) globalKa += 0.001;
        if(P == 1) globalKa -= 0.001;
        if(globalKa > 1.0) globalKa = 1.0;
        else if(globalKa < 0.0) globalKa = 0.0;
        /*FIM DOS PARAMETROS PROJECTION, RENDERIZAÇÃO E ILUMINAÇÃO*/


        



        /*ANIMAÇÃO*/

        // IlumObj3D(scene->array_objs[6], Ka, Kd, Ks, ns, eye0, loc_viewPos);
        angle_anim += M_PI/3600000;
        angle_anim2 += M_PI/270;     
        angle_anim3 += M_PI/1080;  
        Translate(0, 0.005*cos(angle_anim2), 0, scene->array_objs[6].model_matrix);
        glUniform3f(loc_lightPos, lightPos.x*sin(angle_anim3), lightPos.y*cos(angle_anim3), lightPos.z);
        /*FIM DA ANIMAÇÃO*/






        //Renderizando a cena
        center0[0] += transl.x; center0[1] += transl.y; center0[2] += transl.z;
        eye_check();

        for(int i = 0; i < scene->numb_objs; i++){
            ViewUpdate(eye0, center0, up0, near, far, fov, largura, altura, &scene->array_objs[i]);
            UpdateObj3D(&scene->array_objs[i], model, view, proj, transl0, angles, scale, GLOBAL);
            DefineObj3DIlum(globalKa, scene->array_objs[i].out_material.Kd, scene->array_objs[i].out_material.Ks, scene->array_objs[i].out_material.ns, &scene->array_objs[i]);
            DefineObj3DIlumIn(globalKa, scene->array_objs[i].in_material.Kd, scene->array_objs[i].in_material.Ks, scene->array_objs[i].in_material.ns, &scene->array_objs[i]);
            IlumObj3D(scene->array_objs[i], Ka, Kd, Ks, ns, eye0, loc_viewPos, Inside_Check(galpao0, galpao1, eye0));
            RenderObj3D(scene->array_objs[i], color, Inside_Check(galpao0, galpao1, eye0));
        }

        
        glfwSwapBuffers(janela);
    }
    /*FIM LACO PRINCIPAL*/


    glfwDestroyWindow(janela);
    glfwTerminate();
    glEnd();

    return 0;
}