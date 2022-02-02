#ifndef BASIC
#include <SDL2\SDL_surface.h>
#include <SDL2\SDL.h>           //VERSÃO 2.0.14
#include <SDL2\SDL_main.h>  
#include <SDL2\SDL_image.h>     //VERSÃO 2.0.1
#endif


#include <GL\glew.h>            //VERSÃO 2.10
#define GLFW_INCLUDE_NONE
#include <GLFW\glfw3.h>         //VERSÃO 3.3.4
#include <cglm/cam.h>
#include <cglm/mat4.h>
#include <cglm/project.h>
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
    /*Texture data structure do deal with texture info like texture format, texture id, texture dimensions, texture active texture channel*/

    //Texture path is only used when loading textures from files
    char *TexturePath;

    GLenum format;

    GLuint texture_id;
    GLuint texture_inside_id;

    GLint has_texture; 
    GLint has_inside;
    GLint ActiveTexture;

    Color color;

    int width;
    int height;
} Texture;

typedef struct shader{
    int shaderType;

    GLuint vertex;
    GLint vertex_status;

    GLuint fragment;
    GLint fragment_status;

} Shader;


typedef struct material{
    GLfloat Ka;
    GLfloat Kd;
    GLfloat Ks;
    GLfloat ns;
    Shader shader;
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

    Texture texture_info;
    Texture normal_map;
    Vec3 *tangent_vec;
    Vec3 *bitangent_vec;

    Material out_material;
    Material in_material;
} Obj3D;

typedef struct triangle{
    int tri[3];
    int tex[3];
    int nor[3];
}Triangle;


typedef struct camera{
    /*Camera data structure to deal with camera info. 
    A camera can be either:
    - projection camera
    - orthographic camera.

    This structure stores:
    - projection camera FOV
    - camera eye position
    - camera center position, where the camera looks
    - camera view up vector
    - orthographic camera bottom, top, left and right values
    - camera view matrix
    - camera projection matrix
    */

    /*public variables*/
    float fov;
    vec3 eye;
    vec3 center;
    vec3 viewUp;
    float near;
    float far;
    float width;
    float height;
    float left;
    float right;
    float bottom;
    float top;

    /*private variables*/
    float __view[16];
    float __projection[16];
}Camera;

typedef struct dirlight{

    // public variables
    vec3 pos;
    Color color;
    Camera lightCam;

    // locations
    GLuint loc_lightPos;
    GLuint loc_lightColor;
    GLuint loc_lightSpaceMatrix;


    // private variables
    float __lightSpaceMatrix[16];
    Texture __depthMap;
    GLuint __depthMapFBO;
} DirectLight;



typedef struct scene{
    int numb_objs;
    Obj3D *array_objs;

    Vec3 *general_array;
    Vec2 *general_text;
    Vec3 *general_norm;

    GLuint *starting_indices;
    int *numb_vert;
    GLuint total_vert;

    // Locations
    GLuint loc_model;
    GLuint loc_view;
    GLuint loc_proj;
    GLuint Ka, Kd, Ks, ns;
    GLuint loc_color;
    Shader *shaders;

    Camera sceneCam;

    // Private Variables
    int __width, __height;
}Scene;





/*SHADER COMPILING FUNCTIONS*/
GLuint GLSLCompile();

GLuint GLSLCompile3D();

GLuint GLSLCompile3DTexture();

GLuint GLSLCompile3DLight();

GLuint GLSLCompile3DLightShadow();

GLuint GLSLcreateProgram();

void GLSLCompileStandardShader(GLuint program, Shader *shader);

void GLSLCompileQuadShader(GLuint program, Shader *shader);

void GLSLCompileDistancesShader(GLuint program, Shader *shader);

void GLSLattachShader(GLuint program, Shader shader);
/*SHADER COMPILING FUNCTIONS*/





/*DATA STRUCTURE ALLOCATION FUNCTIONS*/
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

void SpawnCircle3D(int numb_vert, vec3 *array, vec3 center, float radius, char *c);
/*DATA STRUCTURE ALLOCATION FUNCTIONS*/





/*VERTEX TRANSFORMATION FUNCTIONS*/
void MatrixMultiply(GLfloat *A, GLfloat *B, GLfloat *result);

void Translate(GLfloat tx, GLfloat ty, GLfloat tz, GLfloat *Transf_Mat);

void Scale(GLfloat scalex, GLfloat scaley, GLfloat scalez, GLfloat *Transf_Mat);

void RotateZaxis(GLfloat angle, GLfloat *Transf_Mat);

void RotateYaxis(GLfloat angle, GLfloat *Transf_Mat);

void RotateXaxis(GLfloat angle, GLfloat *Transf_Mat);

void RelativeRotateYaxis(GLfloat angle, GLfloat *Transf_Mat, Vec3 point);

void RelativeRotateXaxis(GLfloat angle, GLfloat *Transf_Mat, Vec3 point);

void RelativeRotateZaxis(GLfloat angle, GLfloat *Transf_Mat, Vec3 point);

void RelativeScale(GLfloat scalex, GLfloat scaley, GLfloat scalez, GLfloat *Transf_Mat, Vec3 point);

void TransformObj3D(Obj3D *Obj, Vec3 translate, Vec3 angle, Vec3 Scale, GLint model_matrix);
/*VERTEX TRANSFORMATION FUNCTIONS*/





/*MATRIX DEALING FUNCTIONS*/
GLfloat *IdentityMatrix();

GLfloat *CoordMatrix(Vec3 array);

GLfloat *mat_from_glm(vec4 *array);

Vec3 CenterOfMass(Vec3 *array, int size);

Vec3 RelativeCenterOfMass(Vec3 center0, GLfloat *Ref_Matrix);

void printMatrix(GLfloat *array);

GLfloat *viewMatrix(Vec3 Cam_Pos, Vec3 Target_Pos);

GLfloat *ArrayFromVec3(Vec3 *array, int size);
/*MATRIX DEALING FUNCTIONS*/






/*FILE READING FUNCTIONS*/
Obj3D *Obj3DFromFile(char *vertex_path);

Obj3D *Objs3DFromFile(char *vertex_path, unsigned int starting_vertex, unsigned int starting_texture, unsigned int starting_normals);

Scene *SceneFromFile(char *vertex_path, char *vertex_name, int width, int height);


Texture *CreateEmptyTexture(int ActiveTexture, int Min_Filter, int Mag_Filter, int Wrap_S, int Wrap_T, GLenum format, int width, int height);

#ifndef BASIC  
int TextureFromFile(char *texture_path,  Obj3D *obj);

int normalMapFromFile(char *texture_path, Obj3D *obj, int Active_texture_channel);

GLuint LoneTextureFromFile(char *texture_path, GLint format);
 
void flip_surface(SDL_Surface* surface);
#endif
/*FILE READING FUNCTIONS*/




/*SHADOW GENERATION FUNCTIONS*/
GLuint GenerateDepthTexture();
/*SHADOW GENERATION FUNCTIONS*/





/*LOOP RENDERING FUNCTIONS*/
void RenderObj3D(Obj3D Obj, GLint color, int is_inside);

void UpdateObj3D(Obj3D *Obj, Camera cam, GLint model, GLint view, GLint proj, Vec3 transl, Vec3 angles, Vec3 scale, int mode, int transform_check);

void StaticUpdateObj3D(Obj3D *Obj, Camera cam, GLint model, GLint view, GLint proj);

void IlumObj3D(Obj3D Obj, GLint Ka, GLint Kd, GLint Ks, GLint ns, vec3 cameraPos, GLint loc_view_pos, int InsideCheck);

void ViewUpdate(vec3 eye, vec3 center, vec3 up, float near, float far, float fov, float largura, float altura, Camera *cam);

int Inside_Check(vec3 origin, vec3 boundarie, vec3 position);
/*LOOP RENDERING FUNCTIONS*/




/*SCENE DEALING FUNCTIONS*/
void PrintScene(Scene scene);

int sceneWidth(Scene scene);

int sceneHeight(Scene scene);

void setSceneCam(Scene *scene, Camera cam);

void getLocationView3D(GLuint program, GLuint *loc_model, GLuint *loc_view, GLuint *loc_proj);

void getLocationLightConstants(GLuint program, GLuint *Ka, GLuint *Kd, GLuint *Ks, GLuint *ns);

void shaderReorderScene(Scene *scene);
/*SCENE DEALING FUNCTIONS*/




/*ILUMINATION PARAMETER FUNCTIONS*/
void DefineObj3DIlum(GLfloat Ka, GLfloat Kd, GLfloat Ks, GLfloat ns, Obj3D *obj);

void DefineObj3DIlumIn(GLfloat Ka, GLfloat Kd, GLfloat Ks, GLfloat ns, Obj3D *obj);
/*ILUMINATION PARAMETER FUNCTIONS*/


/*CAMERA FUNCTIONS*/
void defineProjectionCamera(Camera *camera, float fov, vec3 eye, vec3 center, vec3 viewUp, float near, float far, float width, float height);

void defineOrthogonalCamera(Camera *camera, vec3 eye, vec3 center, vec3 viewUp, float near, float far, float left, float right, float bottom, float top);

float *viewFromCam(Camera cam);

float *projFromCam(Camera cam);

/*CAMERA FUNCTIONS*/




/*LIGHT DEALING FUNCTIONS*/
float *LightSpaceMatrix(Camera cam);

float *camView(Camera *cam);

float *camProj(Camera *cam);

void SetLightParams(DirectLight *light, vec3 light_pos, Color color, Camera lightCam, Texture DepthMap, GLuint DepthMapFBO);

GLuint GetDirectDepthMapFBO(DirectLight light);

GLuint DepthMapFrameBufferObject(Texture DepthMap);

Texture GetDirectDepthMap(DirectLight light);

void SendLightNumb(GLuint loc_numbLights, int numb_lights);

void SendLight(DirectLight light);

void SendLights(GLuint *loc_lights, GLuint *loc_lightsColor, GLuint loc_lightSpaceMatrix, DirectLight *lights, int numb_lights);

void ShadowUpdate(Scene *scene, DirectLight light, int inside_check);

void getLocationLightParams(GLuint program, GLuint *loc_lightPos, GLuint *loc_lightColor, GLuint *loc_lightSpaceMatrix);
/*END OF LIGHT DEALING FUNCTIONS*/




/*SHADER DEALING FUNCTIONS*/


/*END OF SHADER DEALING FUNCTIONS*/




/*NEW/EXPERIMENTAL FUNCTIONS*/
void debugScene(Scene s);

void Quad(vec3 *quad);

void blendlim(float *blend);

void defvec3(float *array, float x, float y, float z);
/*NEW/EXPERIMENTAL FUNCTIONS*/