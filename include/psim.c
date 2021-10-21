#include "../include/psim.h"
#include <SDL2/SDL_joystick.h>
#include <cglm/vec3.h>
#include <stdlib.h>
#define g 9.80665






void GLSLCompileParticleShader(GLuint program, Shader *shader){

    /*CONFIGURANDO INICIALIZAÇÃO DO GLSL*/

    const GLchar *vertex_code = "attribute vec3 position;\n"



                                "uniform mat4 model;\n"
                                "uniform mat4 view;\n"
                                "uniform mat4 projection;\n"


                                
                                "void main(){\n"
                                    "gl_Position = projection*view*model*vec4(position, 1.0);\n"
                                "}\n";


    const GLchar *fragment_code =   "uniform vec4 color;\n"
                                    "uniform vec2 resolution;\n"
                                    "uniform float time;\n"
                                    "uniform vec2 vel;\n"
                                    //Shader que colore as bolas conforme a sua velocidade
                                    "void main(){\n"
                                        "float max_vel = sqrt(pow(vel.x, 2) + pow(vel.y, 2))/20;\n"
                                        "vec2 st = gl_FragCoord.xy/resolution;\n"
                                        "gl_FragColor = vec4(max_vel + 0.5, 0.3, 1.0 - max_vel + 0.5, 1.0);\n"
                                    "}\n";


    shader->vertex = glCreateShader(GL_VERTEX_SHADER);
    shader->fragment = glCreateShader(GL_FRAGMENT_SHADER);

    glShaderSource(shader->vertex, 1, &vertex_code, NULL);
    glShaderSource(shader->fragment, 1, &fragment_code, NULL);

    glCompileShader(shader->vertex);
    glGetShaderiv(shader->vertex, GL_COMPILE_STATUS, &shader->vertex_status);
    if(shader->vertex_status == GL_FALSE){
        
        //descobrindo o tamanho do log de erro
        int infoLength = 512;
        glGetShaderiv(shader->vertex, GL_INFO_LOG_LENGTH, &infoLength);

        //recuperando o log de erro e imprimindo na tela
        char info[infoLength];
        glGetShaderInfoLog(shader->vertex, infoLength, NULL, info);

        printf("Erro de compilacao no Vertex Shader.\n");
        printf("--> %s\n", info);
    }

    glCompileShader(shader->fragment);
    glGetShaderiv(shader->fragment, GL_COMPILE_STATUS, &shader->fragment_status);
    if(shader->fragment_status == GL_FALSE){

        //descobrindo o tamanho do log de erro
        int infoLength = 512;
        glGetShaderiv(shader->vertex, GL_INFO_LOG_LENGTH, &infoLength);

        //recuperando o log de erro e imprimindo na tela
        char info[infoLength];
        glGetShaderInfoLog(shader->vertex, infoLength, NULL, info);

        printf("Erro de compilacao no Fragment Shader.\n");
        printf("--> %s\n", info);    
    }
}







void calcMomentum(Particle *particle){
    particle->momentum[0] = particle->mass*particle->speed[0];
    particle->momentum[1] = particle->mass*particle->speed[1];
    particle->momentum[2] = particle->mass*particle->speed[2];
}


void calcEnergy(Particle *particle, vec3 ground){
    vec3 height;
    glm_vec3_sub(particle->pos, ground, height);

    calcMomentum(particle);

    particle->energy = pow(glm_vec3_norm(particle->momentum), 2.0)/(2*particle->mass) + particle->mass*g*glm_vec3_norm(height);
}



void particleInit(Particle *p, vec3 pos0, vec3 speed0, vec3 ground, float radius, float mass){
    p->pos[0] = pos0[0];
    p->pos[1] = pos0[1];
    p->pos[2] = pos0[2];

    p->speed[0] = speed0[0];
    p->speed[1] = speed0[1];
    p->speed[2] = speed0[2];

    p->radius = radius;
    p->mass = mass;

    calcEnergy(p, ground);  


    p->vertex_array = (vec3 *) malloc(max_vert*sizeof(vec3));
    if(p->vertex_array == NULL) printf("Could not malloc vertex_array!\n");

    GLfloat *model = IdentityMatrix();

    for(int i = 0; i < 16; i++){
        p->model[i] = model[i];
    }

    free(model);

    SpawnCircle3D(max_vert, p->vertex_array, pos0, radius, "xy");

    p->numb_vertices = max_vert;

    p->wallcheck[0] = 0; p->wallcheck[1] = 0; p->wallcheck[2] = 0; p->wallcheck[3] = 0;

    p->pot_flag = 0;
}


void psceneInit(PScene *s, int numb_part, Color part_color, Camera scene_cam, int scr_width0, int scr_height0){
    
    s = (PScene *) malloc(sizeof(PScene));
    if(s == NULL) printf("Could not malloc pscene!\n");

    s->array_objs = (Particle *) malloc(numb_part*sizeof(Particle));
    if(s->array_objs == NULL) printf("Could not malloc array_objs!\n");
    s->general_array = (vec3 *) malloc(max_vert*numb_part*sizeof(vec3));
    if(s->general_array == NULL) printf("Could not malloc general_array!\n");
    
    s->part_color = part_color;
    s->numb_part = numb_part;
    s->total_vert = numb_part*max_vert;
    s->sceneCam = scene_cam;
    s->__height = scr_height0;
    s->__width = scr_width0;
}


PScene *ppsceneInit(int numb_part, Color part_color, Camera scene_cam, int scr_width0, int scr_height0){
    
    PScene *s = (PScene *) malloc(sizeof(PScene));
    if(s == NULL) printf("Could not malloc pscene!\n");


    s->array_objs = (Particle *) malloc(numb_part*sizeof(Particle));
    if(s->array_objs == NULL) printf("Could not malloc array_objs!\n");
    // s->array_objs = NULL;

    // for(int i = 0; i < numb_part; i++){

    // }

    s->general_array = (vec3 *) malloc(max_vert*numb_part*sizeof(vec3));
    if(s->general_array == NULL) printf("Could not malloc general_array!\n");
    // s->general_array = NULL;
    
    s->part_color = part_color;
    s->numb_part = numb_part;
    s->total_vert = numb_part*max_vert;
    s->sceneCam = scene_cam;
    s->__height = scr_height0;
    s->__width = scr_width0;



    return s;
}


void pStaticUpdateObj3D(Particle *p, Camera cam, GLint model, GLint view, GLint proj){
    glUniformMatrix4fv(model, 1, GL_TRUE, p->model);
    glUniformMatrix4fv(view, 1, GL_TRUE, cam.__view);
    glUniformMatrix4fv(proj, 1, GL_TRUE, cam.__projection);
}


void particleTranslate(Particle *p, float tx, float ty, float tz, float dt){
    Translate(tx, ty, tz, p->model);
    p->pos[0] += tx; 
    p->pos[1] += ty;
    p->pos[2] += tz;
}

void gravityUpdate(Particle *p, float dt){
    p->speed[1] -= g*dt; 
}


float ljPot(float r, float epsilon, float sigma){
    return 4*epsilon*((pow((sigma)/(r), 12) - pow((sigma)/(r), 6)));
}

double dljPot(double r, double epsilon, double sigma){
    return 4.0*epsilon*(pow((sigma)/(r), 12.0) - pow((sigma)/(r), 6.0));
}



void lennardJones(Particle *p, Particle *plist, int numb_part, float epsilon, float sigma, float dt){

    vec3 rv;

    for(int i = 0; i < numb_part; i++){

        rv[0] = p->pos[0] - plist[i].pos[0]; rv[1] = p->pos[1] - plist[i].pos[1]; rv[2] = p->pos[2] - plist[i].pos[2];
        float r = glm_vec3_norm(rv);

        if(r == 0.0){continue;}

        else{
            vec3 rn; rn[0] = rv[0]/r; rn[1] = rv[1]/r; rn[2] = rv[2]/r;

            float V = 4*epsilon*(pow(sigma/r, 12) - pow(sigma/r, 6));

            float dr = sigma*0.001; //Proporcional ao raio para que a derivada não exploda

            //Força é MENOS  derivada do potencial lampada caralho
            float force = -(ljPot(r - 2*dr, epsilon, sigma) - 8*ljPot(r - 1*dr, epsilon, sigma) 
                       + 8*ljPot(r+1*dr, epsilon, sigma) - ljPot(r + 2*dr, epsilon, sigma))/12*dr;

                        
            // printf("%f %f %f ", (force*rn[0]/p->mass)*dt, (force*rn[1]/p->mass)*dt, (force*rn[2]/p->mass)*dt);
            // printf("%f %f %f ", rn[0], rn[1], rn[2]);
            // printf("%f ", r);

            // particleTranslate(p, +(force*rn[0]/p->mass)*dt, +(force*rn[1]/p->mass)*dt, +(force*rn[2]/p->mass)*dt, dt);


            plist[i].speed[0] += (force*(-rn[0])/p->mass)*dt;
            plist[i].speed[1] += (force*(-rn[1])/p->mass)*dt;
            plist[i].speed[2] += (force*(-rn[2])/p->mass)*dt;

            // p->pot_flag = 1;
            // printf("%f\n", r);
        }
    }

    // printf("\n\n");
}


void collisionDetection(Particle *p, Particle *plist, int numb_part, float dt){

    for(int i = 0; i < numb_part; i++){

        vec3 relpos; relpos[0] = p->pos[0] - plist[i].pos[0]; relpos[1] = p->pos[1] - plist[i].pos[1]; relpos[2] = p->pos[2] - plist[i].pos[2];
        float relposnorm = glm_vec3_norm(relpos);
        
        if(relposnorm == 0 || relposnorm > p->radius + plist[i].radius) continue;

        else{


            vec3 relvel; relvel[0] = p->speed[0] - plist[i].speed[0]; relvel[1] = p->speed[1] - plist[i].speed[1]; relvel[2] = p->speed[2] - plist[i].speed[2];
            // float relvelnorm = glm_vec3_norm(relvel);

            // p->speed[0] += (2*plist[i].mass/(p->mass + plist[i].mass))*(glm_vec3_dot(relvel, relpos)/(pow(relposnorm, 2.0)))*(p->pos[0] - plist[i].pos[0]); 
            // p->speed[1] += (2*plist[i].mass/(p->mass + plist[i].mass))*(glm_vec3_dot(relvel, relpos)/(pow(relposnorm, 2.0)))*(p->pos[1] - plist[i].pos[1]);
            // p->speed[2] += (2*plist[i].mass/(p->mass + plist[i].mass))*(glm_vec3_dot(relvel, relpos)/(pow(relposnorm, 2.0)))*(p->pos[2] - plist[i].pos[2]);

            particleTranslate(p, +(2*plist[i].mass/(p->mass + plist[i].mass))*(glm_vec3_dot(relvel, relpos)/(pow(relposnorm, 2.0)))*(p->pos[0] - plist[i].pos[0]),
                                 +(2*plist[i].mass/(p->mass + plist[i].mass))*(glm_vec3_dot(relvel, relpos)/(pow(relposnorm, 2.0)))*(p->pos[1] - plist[i].pos[1]), 
                                 +(2*plist[i].mass/(p->mass + plist[i].mass))*(glm_vec3_dot(relvel, relpos)/(pow(relposnorm, 2.0)))*(p->pos[2] - plist[i].pos[2]), dt);


            // vec3 relpos1; relpos1[0] = -p->pos[0] + plist[i].pos[0]; relpos1[1] = -p->pos[1] + plist[i].pos[1]; relpos1[2] = -p->pos[2] + plist[i].pos[2];

            // vec3 relvel1; relvel1[0] = -p->speed[0] + plist[i].speed[0]; relvel1[1] = -p->speed[1] + plist[i].speed[1]; //relvel1[2] = -p->speed[2] + plist[i].speed[2];

            // plist[i].speed[0] -= ((2*p->mass)/(p->mass + plist[i].mass))*(glm_vec3_dot(relvel1, relpos1)/(pow(relposnorm, 2.0)))*(-p->pos[0] + plist[i].pos[0]);
            // plist[i].speed[1] -= ((2*p->mass)/(p->mass + plist[i].mass))*(glm_vec3_dot(relvel1, relpos1)/(pow(relposnorm, 2.0)))*(-p->pos[1] + plist[i].pos[1]);
            // plist[i].speed[2] -= ((2*p->mass)/(p->mass + plist[i].mass))*(glm_vec3_dot(relvel1, relpos1)/(pow(relposnorm, 2.0)))*(-p->pos[2] + plist[i].pos[2]);
        }
    }

}