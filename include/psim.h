#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <GL/glew.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <math.h>
#include <cglm/cam.h>
#include <cglm/mat4.h>
#include <cglm/project.h>
#include <cglm\cglm.h>
#include "../include/GLib.h"

#define max_vert 32




typedef struct particle{
    vec3 pos;
    vec3 speed;
    float mass;
    vec3 momentum;

    float energy;

    float radius;
    vec3 *vertex_array;
    GLuint starting_index;
    GLint numb_vertices;

    GLfloat model[16];

    int wallcheck[4];

    int pot_flag;

} Particle;

typedef struct{
    vec3 left, right;
} Domain;

typedef struct particle_scene{
    int numb_part;
    Particle *array_objs;

    vec3 *general_array;

    GLuint total_vert;
    Color part_color;

    // Locations
    GLuint loc_model;
    GLuint loc_view;
    GLuint loc_proj;
    GLuint loc_color;

    Camera sceneCam;

    Domain scene_domain;

    // Private Variables
    int __width, __height;
}PScene;


void GLSLCompileParticleShader(GLuint program, Shader *shader);



void calcMomentum(Particle *particle);

void calcEnergy(Particle *particle, vec3 ground);



void particleInit(Particle *p, vec3 pos0, vec3 speed0, vec3 ground, float radius, float mass);


void psceneInit(PScene *s, int numb_part, Color part_color, Camera scene_cam, int scr_width0, int scr_height0);

PScene *ppsceneInit(int numb_part, Color part_color, Camera scene_cam, int scr_width0, int scr_height0);

void pStaticUpdateObj3D(Particle *p, Camera cam, GLint model, GLint view, GLint proj);

void particleTranslate(Particle *p, float tx, float ty, float tz, float dt);

void gravityUpdate(Particle *p, float dt);

float ljPot(float r, float epsilon, float sigma);

void lennardJones(Particle *p, Particle *plist, int numb_part, float epsilon, float sigma, float dt);

void collisionDetection(Particle *p, Particle *plist, int numb_part, float dt);