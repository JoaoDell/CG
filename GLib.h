#include <SDL2\SDL_surface.h>
#include <SDL2\SDL.h>
#include <SDL2\SDL_image.h>
#include <GL\glew.h>
#define GLFW_INCLUDE_NONE
#include <GLFW\glfw3.h>
#include <cglm\cglm.h>
#include <libpng16\png.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>


#define RELATIVE 0
#define GLOBAL   1

typedef struct vector2{
    float x,y;
}Vec2;

typedef struct vector3{
    float x,y,z;
}Vec3;


typedef struct color{
    float r,g,b,w;
}Color;


typedef struct obj{
    Vec2 *array;
    GLint starting_index;
    GLint numb_vertices;
    Color color;
    GLfloat *transf_matrix;
} Obj;

typedef struct texture{
    char *TexturePath;
    GLenum format;
    GLuint texture_id;
    GLint has_texture; 
    Color color;
} Texture;

typedef struct obj3d{
    Vec3 *array;
    Vec3 *normals;
    Vec2 *texture;

    GLfloat angle;
    Vec3 scale;
    Vec3 center_of_mass;
    
    GLint starting_index;
    GLuint numb_vertices;

    GLuint doc_vertex;
    GLuint doc_normals;
    GLuint doc_texture;

    GLfloat *Reference_Matrix; //Stores the "center of mass" for relative transformations
    GLfloat *model_matrix;
    GLfloat *view_matrix;
    GLfloat *projection_matrix;

    Texture texture_info;
} Obj3D;

typedef struct triangle{
    int tri[3];
    int tex[3];
    int nor[3];
}Triangle;



typedef struct scene{
    int numb_objs;
    Obj3D *array_objs;
    Vec3 *general_array;
    Vec2 *general_text;
    Vec3 *general_norm;
    GLuint *starting_indices;
    int *numb_vert;
    GLuint total_vert;
}Scene;



GLuint GLSLCompile();

GLuint GLSLCompile3D();

GLuint GLSLCompile3DLight();

Obj *SpawnObject(Vec2 *array, int starting_index, int numb_vertices, Color color, GLfloat *transf_matrix);

Obj3D *SpawnObject3D(Vec3 *array, int starting_index, int numb_vertices, Color color, GLfloat *transf_matrix);

Scene *SpawnScene(int numb_vert, int numb_objs);

void AppendScene(Obj **obj_array, int numb_objects, Vec2 *scene);

void AppendScene3D(Obj3D **obj_array, int numb_objects, Vec3 *scene);

void DestroyScene(Scene *scene);

Color DefineColor(float r, float g, float b, float w);

void DestroyObj(Obj *object);

void DestroyObj3D(Obj3D *object);

void SpawnCircle(int numb_vert, Vec2 *array, Vec2 center, float radius);

void SpawnCircle3D(int numb_vert, Vec3 *array, Vec3 center, float radius, char *c);

void MatrixMultiply(GLfloat *A, GLfloat *B, GLfloat *result);

void Translate(GLfloat tx, GLfloat ty, GLfloat tz, GLfloat *Transf_Mat);

void Scale(GLfloat scalex, GLfloat scaley, GLfloat scalez, GLfloat *Transf_Mat);

void RelativeScale(GLfloat scalex, GLfloat scaley, GLfloat scalez, GLfloat *Transf_Mat, Vec3 point);

void RotateZaxis(GLfloat angle, GLfloat *Transf_Mat);

void RotateYaxis(GLfloat angle, GLfloat *Transf_Mat);

void RotateXaxis(GLfloat angle, GLfloat *Transf_Mat);

GLfloat *IdentityMatrix();

GLfloat *CoordMatrix(Vec3 array);

GLfloat *mat_from_glm(vec4 *array);

Vec3 CenterOfMass(Vec3 *array, int size);

Vec3 RelativeCenterOfMass(Vec3 center0, GLfloat *Ref_Matrix);

void printMatrix(GLfloat *array);

void RelativeRotateYaxis(GLfloat angle, GLfloat *Transf_Mat, Vec3 point);

void RelativeRotateXaxis(GLfloat angle, GLfloat *Transf_Mat, Vec3 point);

void RelativeRotateZaxis(GLfloat angle, GLfloat *Transf_Mat, Vec3 point);

void TransformObj3D(Obj3D *Obj, Vec3 translate, Vec3 angle, Vec3 Scale, GLint model_matrix);

GLfloat *viewMatrix(Vec3 Cam_Pos, Vec3 Target_Pos);

GLfloat *ArrayFromVec3(Vec3 *array, int size);

Obj3D *Obj3DFromFile(char *vertex_path);

Obj3D *Objs3DFromFile(char *vertex_path, unsigned int starting_vertex, unsigned int starting_texture, unsigned int starting_normals);

Scene *SceneFromFile(char *vertex_path, char *vertex_name);

int TextureFromFile(char *texture_path, int texture_id,  Obj3D *obj);

void RenderObj3D(Obj3D Obj, GLint color);

void UpdateObj3D(Obj3D *Obj, GLint model, GLint view, GLint proj, Vec3 transl, Vec3 angles, Vec3 scale, int mode);

void flip_surface(SDL_Surface* surface);

void View(vec3 eye, vec3 center, vec3 up, Obj3D *O);
