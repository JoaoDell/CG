#include <SDL2\SDL_surface.h>
#include <SDL2\SDL.h>           //VERSÃO 2.0.14
#include <SDL2\SDL_image.h>     //VERSÃO 2.0.1
#include <GL\glew.h>            //VERSÃO 2.10
#define GLFW_INCLUDE_NONE
#include <GLFW\glfw3.h>         //VERSÃO 3.3.4
#include <cglm\cglm.h>
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
    GLuint texture_inside_id;
    GLint has_texture; 
    GLint has_inside;
    Color color;
} Texture;

typedef struct material{
    GLfloat Ka;
    GLfloat Kd;
    GLfloat Ks;
    GLfloat ns;
}Material;

typedef struct obj3d{

    char *name;

    Vec3 *array;
    Vec3 *normals;
    Vec2 *texture;

    GLfloat angle;
    Vec3 scale;
    Vec3 center_of_mass;
    
    GLuint starting_index;
    GLuint numb_vertices;

    GLuint doc_vertex;
    GLuint doc_normals;
    GLuint doc_texture;


    GLfloat *Reference_Matrix; //Stores the "center of mass" for relative transformations
    GLfloat *model_matrix;
    GLfloat *view_matrix;
    GLfloat *projection_matrix;

    Texture texture_info;
    GLuint depth_texture_id;

    Material out_material;
    Material in_material;
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

GLuint GLSLCompile3DTexture();

GLuint GLSLCompile3DLight();

GLuint GLSLCompile3DLightShadow();

GLuint GLSLCompileQuad();

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

int TextureFromFile(char *texture_path,  Obj3D *obj);

GLuint LoneTextureFromFile(char *texture_path, GLint format);

GLuint GenerateDepthTexture();

void RenderObj3D(Obj3D Obj, GLint color, int is_inside);

void UpdateObj3D(Obj3D *Obj, GLint model, GLint view, GLint proj, Vec3 transl, Vec3 angles, Vec3 scale, int mode);

void SendLightSpaceMatrix(vec3 lightPos, vec3 lightCenter, vec3 lightUp, float near, float far, GLint loc_lightSpaceMatrix);

void IlumObj3D(Obj3D Obj, GLint Ka, GLint Kd, GLint Ks, GLint ns, vec3 cameraPos, GLint loc_view_pos, int InsideCheck);

void flip_surface(SDL_Surface* surface);

void ViewUpdate(vec3 eye, vec3 center, vec3 up, float near, float far, float fov, float largura, float altura, Obj3D *O);

void LightViewUpdate(vec3 eye, vec3 center, vec3 up, float near, float far, float fov, float largura, float altura, Obj3D *O);

void updateMousePosition(GLFWwindow *janela, double *xpos, double *ypos, float *boundaries, float largura, float altura);

int Inside_Check(vec3 origin, vec3 boundarie, vec3 position);

void PrintScene(Scene scene);

void DefineObj3DIlum(GLfloat Ka, GLfloat Kd, GLfloat Ks, GLfloat ns, Obj3D *obj);

void DefineObj3DIlumIn(GLfloat Ka, GLfloat Kd, GLfloat Ks, GLfloat ns, Obj3D *obj);

