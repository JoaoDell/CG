#include "../include/psim.h"
#include <GLFW/glfw3.h>
#include <cglm/vec3.h>
#include <stdlib.h>
#include <time.h>


#define scr_height 1080
#define scr_width 1920
#define e 1.0

float timei;
int timec;



void wall_check(Particle *p, PScene s, float dt){
    if(p->pos[0] + p->radius <= s.scene_domain.left[0]) {p->speed[0] = -e*p->speed[0]; particleTranslate(p, -(p->pos[0] - s.scene_domain.left[0]), 0.0, 0.0, dt);}
    if(p->pos[1] + p->radius <= s.scene_domain.left[1]) {p->speed[1] = -e*p->speed[1]; particleTranslate(p, 0.0, -(p->pos[1] - s.scene_domain.left[1]), 0.0, dt);}
    if(p->pos[2] + p->radius <= s.scene_domain.left[2]) {p->speed[2] = -e*p->speed[2]; particleTranslate(p, 0.0, 0.0, -(p->pos[2] - s.scene_domain.left[2]), dt);}
    if(p->pos[0] + p->radius >= s.scene_domain.right[0]) {p->speed[0] = -e*p->speed[0]; particleTranslate(p, -(-p->pos[0] + s.scene_domain.right[0]), 0.0, 0.0, dt);}
    if(p->pos[1] + p->radius >= s.scene_domain.right[1]) {p->speed[1] = -e*p->speed[1]; particleTranslate(p, 0.0, -(-p->pos[1] + s.scene_domain.right[1]), 0.0, dt);}
    if(p->pos[2] + p->radius >= s.scene_domain.right[2]) {p->speed[2] = -e*p->speed[2]; particleTranslate(p, 0.0, 0.0, -(-p->pos[2] + s.scene_domain.right[2]), dt);}
}


int WinMain(){

    glfwInit();
    glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);
    glfwWindowHint(GLFW_SAMPLES, 4); //Habilitando o antialiasing

    GLFWwindow *janela = glfwCreateWindow(scr_width, scr_height, "Partisim", NULL, NULL);

    glfwMakeContextCurrent(janela);


    GLint init = glewInit();
    printf("Status da inicializacao do GLEW: %s\n", glewGetErrorString(init));


    GLuint program = GLSLcreateProgram();

    Shader part_shader;
    GLSLCompileParticleShader(program, &part_shader);
    GLSLattachShader(program, part_shader);
    

    /*INICIALIZAÇÃO DOS VERTICES*/

    /*CAMERAS*/
    Camera mainCam;
    vec3 eye; eye[0] = 0.0; eye[1] = 0.0; eye[2] = 1400.0;
    vec3 center; center[0] = 0.0; center[1] = 0.0; center[2] = 0.0;
    vec3 up; up[0] = 0.0; up[1] = 1.0; up[2] = 0.0;

    Camera secondCam;
    vec3 eye1; eye1[0] = -60.0; eye1[1] = -60.0; eye1[2] = 60.0;
    vec3 center1; center1[0] = 30.0; center1[1] = 30.0; center1[2] = -30.0;
    vec3 up1; up1[0] = 0.0; up1[1] = 1.0; up1[2] = 0.0;

    // float ratio = scr_height/scr_width;

    defineProjectionCamera(&mainCam, 45.0, eye, center, up, 0.1, 4000, scr_width, scr_height);
    defineProjectionCamera(&secondCam, 45.0, eye1, center1, up1, 0.1, 400, scr_width, scr_height);
    // defineOrthogonalCamera(&secondCam, eye, center, up, 0.1, 4000, -scr_width/2, scr_width/2, -scr_height/2, scr_height/2);
    /*END OF CAMERA SETUP*/

    //Iniciando a quantidade de linhas, colunas, e com isso, a quantidade de particulas
    int row = 20, column = 20;
    int npart = row*column;
    //Iniciando a cena
    PScene *PScene = ppsceneInit(row*column, DefineColor(200, 200, 200, 1.0), mainCam, scr_width, scr_height);

    //Definindo o dompinio da simulação
    float horizontal = 800.0;
    float vertical = 500.0;
    float c = 0.0;

    PScene->scene_domain.left[0]  = -horizontal; PScene->scene_domain.left[1] = -vertical; PScene->scene_domain.left[2]  = c;
    PScene->scene_domain.right[0] =  horizontal; PScene->scene_domain.right[1] = vertical; PScene->scene_domain.right[2] = c;



    float radius = 8.0; //radio padrão base
    float spacing = 3*radius; //O espaço entre as particulas
    float xoffset = 0.0, yoffset = 0.0; //offsets para direcionar a nuvem de particulas
    float mass0 = 1e-4, mass = mass0; // massa padrão base e variável da massa
    float massmul = 0.0; //quanto uma massa pode ser maior
    float MAX_MASS = mass0*(1 + massmul); //definindo a massa máxima para o calculo do raio

    //Abaixo, o cálculo do gerador de particulas é feito sob demanda, mudando com o raio e quantidade de particulas
    //Isso é feito para que a nuvem de particulas sempre comece centralizada, podendo ter a posição mudada pelos offsets
    vec3 pos0; pos0[0] = -spacing*(row/2) + xoffset; pos0[1] = -spacing*(column/2) + yoffset; pos0[2] = 0.0;
    vec3 ground; ground[0] = 0.0; ground[1] = -5000.0; ground[2] = 0.0;
    vec3 pos; pos[0] = 0.0; pos[1] = 0.0; pos[2] = 0.0;


    //Geração das particulas
    srand(glfwGetTime());
    for(int i = 0; i < row; i++){
        for(int j = 0; j < column; j++){
            vec3 posi; posi[0] = pos0[0] + j*spacing; posi[1] = pos0[1] + i*spacing; posi[2] = pos0[2];
            vec3 speedi; speedi[0] = pow(-1, floor(rand()))*rand()/40000; speedi[1] = pow(-1, floor(rand()))*rand()/40000; speedi[2] = 0.0;
            // vec3 speedi; speedi[0] = 0; speedi[1] = 0; speedi[2] = 0.0;
            // mass = 1e-4*(1 + massmul*rand()/RAND_MAX); //calculo da massa, que possibilitará o calculo de um raio condizente
            //massa maior -> raio maior, massa menor -> raio menor
            particleInit(&PScene->array_objs[column*i + j], posi, speedi, ground, (mass/MAX_MASS)*radius, mass);
        }
        pos0[0] = -spacing*(row/2) + xoffset;
    }

    // pow(-1, floor(rand()))*rand()/40000


    //Copiando os vertices das particulas para renderização
    vec3 vertexes[max_vert*row*column];

    int k = 0;
    for(int i = 0; i < row*column; i++){
        for(int j = 0; j < max_vert; j++){
            k = max_vert*i + j;
            vertexes[k][0] = PScene->array_objs[i].vertex_array[j][0];
            vertexes[k][1] = PScene->array_objs[i].vertex_array[j][1];
            vertexes[k][2] = PScene->array_objs[i].vertex_array[j][2];
        }
    }


    GLuint buffer;
    glGenBuffers(1, &buffer);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertexes), vertexes, GL_DYNAMIC_DRAW);

    GLint loc_vert = glGetAttribLocation(program, "position");
    glEnableVertexAttribArray(loc_vert);
    glVertexAttribPointer(loc_vert, 3, GL_FLOAT, GL_FALSE, sizeof(vertexes[0]), (void *) 0);

    GLint loc_color = glGetUniformLocation(program, "color");
    vec2 resolution; resolution[1] = scr_width; resolution[0] = scr_height;
    GLint loc_res = glGetUniformLocation(program, "resolution");
    glUniform2f(loc_res, resolution[0], resolution[1]);
    GLint loc_time = glGetUniformLocation(program, "time");
    GLint loc_vel = glGetUniformLocation(program, "vel");

    getLocationView3D(program, &PScene->loc_model, &PScene->loc_view, &PScene->loc_proj);



    timec = 0;
    timei = 0.0;
    float dt = 0.1;






    glfwShowWindow(janela);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_MULTISAMPLE); //HABILITANDO O MULTISAMPLING NO OPENGL (ANTIALIASING)

    glfwSwapInterval(1);
    while(!glfwWindowShouldClose(janela)){

        timec++;
        timei = timec*dt;
        printf("Tempo de simulacao: %f\n", timei);
        glUniform1f(loc_time, timei);



        glfwPollEvents();
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 
        glClearColor(0.0, 0.0, 0.0, 1.0);


// Código paralelizado com OpenMP
#pragma omp parallel default(none) shared(dt, PScene, radius) num_threads(16)
{
#pragma omp for
        for(int i = 0; i < PScene->numb_part; i++){ 
            /*PHYS UPDATE*/
            // gravityUpdate(&PScene->array_objs[i], dt);
            lennardJones(&PScene->array_objs[i], PScene->array_objs, PScene->numb_part, 1.5, PScene->array_objs[i].radius, dt);
            particleTranslate(&PScene->array_objs[i], PScene->array_objs[i].speed[0]*dt, 
                                                      PScene->array_objs[i].speed[1]*dt, 
                                                      PScene->array_objs[i].speed[2]*dt, dt);
            wall_check(&PScene->array_objs[i], *PScene, dt);
        }
}

        for(int i = 0; i < PScene->numb_part; i++){
            PScene->array_objs[i].pot_flag = 0;
            pStaticUpdateObj3D(&PScene->array_objs[i], PScene->sceneCam, PScene->loc_model, PScene->loc_view, PScene->loc_proj);
            glUniform4f(loc_color, PScene->part_color.r, PScene->part_color.g, PScene->part_color.b, PScene->part_color.w);
            glUniform2f(loc_vel, PScene->array_objs[i].speed[0], PScene->array_objs[i].speed[1]);
            glDrawArrays(GL_TRIANGLE_FAN, max_vert*i, max_vert);
        }

        

        glfwSwapBuffers(janela);
    }


    glfwTerminate();
    return 0;
}

