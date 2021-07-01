#include <SDL2\SDL_surface.h>
#include <SDL2\SDL.h>
#include <SDL2\SDL_image.h>
#include <GL\glew.h>
#include <float.h>
#include <stdint.h>
#define GLFW_INCLUDE_NONE
#include <GLFW\glfw3.h>
#include <libpng16\png.h>
#include "GLib.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>





GLuint GLSLCompile(){

    /*CONFIGURANDO INICIALIZAÇÃO DO GLSL*/

    const GLchar *vertex_code = "attribute vec3 position;\n"
                                "uniform mat4 mat_transformation;\n"
                                "void main(){\n"
                                    "gl_Position = mat_transformation*vec4(position, 1.0);\n"
                                "}\n";

    const GLchar *fragment_code =   "uniform vec4 color;\n"
                                    "void main(){\n"
                                        "gl_FragColor = color;\n"
                                    "}\n";


    GLuint program = glCreateProgram();
    GLuint vertex = glCreateShader(GL_VERTEX_SHADER);
    GLuint fragment = glCreateShader(GL_FRAGMENT_SHADER);

    glShaderSource(vertex, 1, &vertex_code, NULL);
    glShaderSource(fragment, 1, &fragment_code, NULL);

    glCompileShader(vertex);

    GLint vertex_status = 0;
    glGetShaderiv(vertex, GL_COMPILE_STATUS, &vertex_status);
    if(vertex_status == GL_FALSE){
        
        //descobrindo o tamanho do log de erro
        int infoLength = 512;
        glGetShaderiv(vertex, GL_INFO_LOG_LENGTH, &infoLength);

        //recuperando o log de erro e imprimindo na tela
        char info[infoLength];
        glGetShaderInfoLog(vertex, infoLength, NULL, info);

        printf("Erro de compilacao no Vertex Shader.\n");
        printf("--> %s\n", info);
    }

    glCompileShader(fragment);

    GLint fragment_status = 0;
    glGetShaderiv(fragment, GL_COMPILE_STATUS, &fragment_status);
    if(fragment_status == GL_FALSE){

        //descobrindo o tamanho do log de erro
        int infoLength = 512;
        glGetShaderiv(vertex, GL_INFO_LOG_LENGTH, &infoLength);

        //recuperando o log de erro e imprimindo na tela
        char info[infoLength];
        glGetShaderInfoLog(vertex, infoLength, NULL, info);

        printf("Erro de compilacao no Vertex Shader.\n");
        printf("--> %s\n", info);    

    }


    glAttachShader(program, vertex);
    glAttachShader(program, fragment);

    glLinkProgram(program);
    glUseProgram(program);

    return(program);

}

GLuint GLSLCompile3D(){

    /*CONFIGURANDO INICIALIZAÇÃO DO GLSL*/

    const GLchar *vertex_code = "attribute vec3 position;\n"
                                "uniform mat4 mat_transformation;\n"
                                "uniform mat4 model;\n"
                                "uniform mat4 view;\n"
                                "uniform mat4 projection;\n"
                                
                                "void main(){\n"
                                    "gl_Position = projection*view*model*vec4(position, 1.0);\n"
                                "}\n";

    const GLchar *fragment_code =   "uniform vec4 color;\n"
                                    "void main(){\n"
                                        "gl_FragColor = color;\n"
                                    "}\n";


    GLuint program = glCreateProgram();
    GLuint vertex = glCreateShader(GL_VERTEX_SHADER);
    GLuint fragment = glCreateShader(GL_FRAGMENT_SHADER);

    glShaderSource(vertex, 1, &vertex_code, NULL);
    glShaderSource(fragment, 1, &fragment_code, NULL);

    glCompileShader(vertex);

    GLint vertex_status = 0;
    glGetShaderiv(vertex, GL_COMPILE_STATUS, &vertex_status);
    if(vertex_status == GL_FALSE){
        
        //descobrindo o tamanho do log de erro
        int infoLength = 512;
        glGetShaderiv(vertex, GL_INFO_LOG_LENGTH, &infoLength);

        //recuperando o log de erro e imprimindo na tela
        char info[infoLength];
        glGetShaderInfoLog(vertex, infoLength, NULL, info);

        printf("Erro de compilacao no Vertex Shader.\n");
        printf("--> %s\n", info);
    }

    glCompileShader(fragment);

    GLint fragment_status = 0;
    glGetShaderiv(fragment, GL_COMPILE_STATUS, &fragment_status);
    if(fragment_status == GL_FALSE){

        //descobrindo o tamanho do log de erro
        int infoLength = 512;
        glGetShaderiv(vertex, GL_INFO_LOG_LENGTH, &infoLength);

        //recuperando o log de erro e imprimindo na tela
        char info[infoLength];
        glGetShaderInfoLog(vertex, infoLength, NULL, info);

        printf("Erro de compilacao no Vertex Shader.\n");
        printf("--> %s\n", info);    

    }


    glAttachShader(program, vertex);
    glAttachShader(program, fragment);

    glLinkProgram(program);
    glUseProgram(program);

    return(program);

}

GLuint GLSLCompile3DLight(){

    /*CONFIGURANDO INICIALIZAÇÃO DO GLSL*/

    const GLchar *vertex_code = "attribute vec3 position;\n"
                                "attribute vec2 texture_coord;\n"


                                "varying vec2 out_texture;\n"


                                "uniform mat4 model;\n"
                                "uniform mat4 view;\n"
                                "uniform mat4 projection;\n"


                                
                                "void main(){\n"
                                    "gl_Position = projection*view*model*vec4(position, 1.0);\n"
                                    "out_texture = vec2(texture_coord);\n"
                                "}\n";

    const GLchar *fragment_code =   "uniform vec4 color;\n"
                                    "varying vec2 out_texture;\n"
                                    "uniform sampler2D samplerTexture;\n"



                                    "void main(){\n"
                                        "vec4 texture = texture2D(samplerTexture, out_texture);\n"
                                        "gl_FragColor = texture;\n"
                                    "}\n";


    GLuint program = glCreateProgram();
    GLuint vertex = glCreateShader(GL_VERTEX_SHADER);
    GLuint fragment = glCreateShader(GL_FRAGMENT_SHADER);

    glShaderSource(vertex, 1, &vertex_code, NULL);
    glShaderSource(fragment, 1, &fragment_code, NULL);

    glCompileShader(vertex);


    GLint vertex_status = 0;
    glGetShaderiv(vertex, GL_COMPILE_STATUS, &vertex_status);
    if(vertex_status == GL_FALSE){
        
        //descobrindo o tamanho do log de erro
        int infoLength = 512;
        glGetShaderiv(vertex, GL_INFO_LOG_LENGTH, &infoLength);

        //recuperando o log de erro e imprimindo na tela
        char info[infoLength];
        glGetShaderInfoLog(vertex, infoLength, NULL, info);

        printf("Erro de compilacao no Vertex Shader.\n");
        printf("--> %s\n", info);
    }

    glCompileShader(fragment);

    GLint fragment_status = 0;
    glGetShaderiv(fragment, GL_COMPILE_STATUS, &fragment_status);
    if(fragment_status == GL_FALSE){

        //descobrindo o tamanho do log de erro
        int infoLength = 512;
        glGetShaderiv(vertex, GL_INFO_LOG_LENGTH, &infoLength);

        //recuperando o log de erro e imprimindo na tela
        char info[infoLength];
        glGetShaderInfoLog(vertex, infoLength, NULL, info);

        printf("Erro de compilacao no Vertex Shader.\n");
        printf("--> %s\n", info);    

    }


    glAttachShader(program, vertex);
    glAttachShader(program, fragment);

    glLinkProgram(program);
    glUseProgram(program);

    //Diz ao openGL para usar texturas com transparencia
    glHint(GL_LINE_SMOOTH_HINT, GL_DONT_CARE);
    glEnable( GL_BLEND );
    glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
    glEnable(GL_LINE_SMOOTH);
    glEnable(GL_TEXTURE_2D);

    return(program);

}




Obj *SpawnObject(Vec2 *array, int starting_index, int numb_vertices, Color color, GLfloat *transf_matrix){

    //int n = sizeof(array)/sizeof(Vec2);

    Obj *o;
    o = (Obj *) malloc(sizeof(Obj));
    if (o == NULL){
        return NULL;
    }
    else{

        o->array = array;
        o->starting_index = starting_index;
        o->numb_vertices = numb_vertices;
        o->color = color;
        o->transf_matrix = transf_matrix;

        return o;
    }
}


Obj3D *SpawnObject3D(Vec3 *array, int starting_index, int numb_vertices, Color color, GLfloat *transf_matrix){

    //int n = sizeof(array)/sizeof(Vec2);

    Obj3D *o;
    o = (Obj3D *) malloc(sizeof(Obj3D));
    if (o == NULL){
        return NULL;
    }
    else{

        o->array = array;
        o->normals = NULL;
        o->texture = NULL;
        o->starting_index = starting_index;
        o->numb_vertices = numb_vertices;
        o->color = color;
        o->model_matrix = transf_matrix;

        return o;
    }
}



Scene *SpawnScene(int numb_vert, int numb_objs){
    Scene *s;
    s = (Scene *) malloc(numb_vert*sizeof(Vec2) + 2*numb_objs*sizeof(int));
    if (s == NULL){
        return NULL;
    }
    else{
        s->array_objs = NULL;
        s->numb_vert = NULL;
        s->starting_indices = NULL;
        return s;
    }
}



void AppendScene(Obj **obj_array, int numb_objects, Vec2 *scene){

    int vert = 0;
    //int numb_vert[numb_objects];
    //int starting_index[numb_objects];
    //starting_index[0] = 0;


    for(int i = 0; i < numb_objects; i++){
        vert += obj_array[i]->numb_vertices;
        //numb_vert[i] = obj_array[i]->numb_vertices;
    }


    Vec2 array[vert];

    for (int i = 0; i < numb_objects; i++){
        if( i < numb_objects - 1){
            obj_array[i+1]->starting_index = obj_array[i]->numb_vertices;
            //starting_index[i+1] = obj_array[i+1]->starting_index;
        }
        for (int j = obj_array[i]->starting_index; j < (obj_array[i]->numb_vertices + obj_array[i]->starting_index); j++){
            //printf("vertice %i: %f, %f\n\n", j, obj_array[i]->array[j - obj_array[i]->starting_index].x, obj_array[i]->array[j - obj_array[i]->starting_index].y);
            array[j] = obj_array[i]->array[j - obj_array[i]->starting_index];
            //printf("vertice %i: %f, %f\n\n", j, array[j].x, array[j].y);
        }   
    }
    
    for(int i = 0; i < vert; i++){
        scene[i] = array[i];
    }
}

void AppendScene3D(Obj3D **obj_array, int numb_objects, Vec3 *scene){

    int vert = 0;
    //int numb_vert[numb_objects];
    //int starting_index[numb_objects];
    //starting_index[0] = 0;


    for(int i = 0; i < numb_objects; i++){
        vert += obj_array[i]->numb_vertices;
        //numb_vert[i] = obj_array[i]->numb_vertices;
    }


    Vec3 array[vert];

    for (int i = 0; i < numb_objects; i++){
        if( i < numb_objects - 1){
            obj_array[i+1]->starting_index = obj_array[i]->numb_vertices;
        }
        for (int j = obj_array[i]->starting_index; j < (obj_array[i]->numb_vertices + obj_array[i]->starting_index); j++){
            array[j] = obj_array[i]->array[j - obj_array[i]->starting_index];
        }   
    }
    
    for(int i = 0; i < vert; i++){
        scene[i] = array[i];
    }
}



Color DefineColor(float r, float g, float b, float w){
    Color c;
    c.r = r/255;
    c.g = g/255;
    c.b = b/255;
    c.w = w;
    return c;
}



void DestroyObj(Obj *object){
    free(object->array);
    object->array = NULL;
    free(object->transf_matrix);
    object->transf_matrix = NULL;
    free(&object->starting_index);
    free(&object->color);
    free(&object->numb_vertices);
    free(object);
}


void DestroyObj3D(Obj3D *object){
    free(object->array);
    object->array = NULL;
    free(object->normals);
    object->normals = NULL;
    free(object->texture);
    object->texture = NULL;
    free(object->model_matrix);
    object->model_matrix = NULL;
    free(object->view_matrix);
    object->view_matrix = NULL;
    free(object->projection_matrix);
    object->projection_matrix = NULL;
    free(object->Reference_Matrix);
    object->Reference_Matrix = NULL;
    free(&object->starting_index);
    free(&object->color);
    free(&object->numb_vertices);
    free(&object->center_of_mass);
    free(&object->scale);
    free(&object->angle);
    free(object);
}


void DestroyScene(Scene *scene){

        for (int i = 0; i < scene->numb_objs; i++){
            DestroyObj3D(scene->array_objs[i]);
        }

        free(scene->array_objs);
        scene->array_objs = NULL;

        free(scene->numb_vert);
        scene->numb_vert = NULL;

        free(scene->starting_indices);
        scene->starting_indices = NULL;

}



void SpawnCircle(int numb_vert, Vec2 *array, Vec2 center, float radius){
    float angle = 0.0;
    for (int i = 0; i < numb_vert; i++){
        angle += (2*M_PI)/(numb_vert);
        array[i].x = radius*cos(angle) + center.x;
        array[i].y = radius*sin(angle) + center.y;
    }
}


void SpawnCircle3D(int numb_vert, Vec3 *array, Vec3 center, float radius, char *plane){

    if (strcmp(plane, "xy") == 0 || strcmp(plane, "yx") == 0 ){
        float angle = 0.0;
        for (int i = 0; i < numb_vert; i++){
            angle += (2*M_PI)/(numb_vert);
            array[i].x = radius*cos(angle) + center.x;
            array[i].y = radius*sin(angle) + center.y;
            array[i].z = center.z;
        }
    }
    else if(strcmp(plane, "xz") == 0 || strcmp(plane, "zx") == 0 ){
        float angle = 0.0;
        for (int i = 0; i < numb_vert; i++){
            angle += (2*M_PI)/(numb_vert);
            array[i].x = radius*cos(angle) + center.x;
            array[i].y = center.y;
            array[i].z = radius*sin(angle) + center.z;
        }
    }
    else if(strcmp(plane, "yz") == 0 || strcmp(plane, "zy") == 0 ){
        float angle = 0.0;
        for (int i = 0; i < numb_vert; i++){
            angle += (2*M_PI)/(numb_vert);
            array[i].x = center.x;
            array[i].y = radius*cos(angle) + center.y;
            array[i].z = radius*sin(angle) + center.z;
        }
    }
}




void MatrixMultiply(GLfloat *A, GLfloat *B, GLfloat *result){


    //A*B
    GLfloat aux = 0.0;

    GLfloat resuaux[16];

    for(int i = 0; i < 16; i++){
        resuaux[i] = result[i];
    }



    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++){
            aux = 0.0;
            for(int k = 0; k < 4; k++){
                aux += A[k + 4*i]*B[4*k + j];
            }
            resuaux[j + 4*i] = aux;
        }
    }

    for(int i = 0; i < 16; i++){
        result[i] = resuaux[i];
    }
}



void Translate(GLfloat tx, GLfloat ty, GLfloat tz, GLfloat *Transf_Mat){


    GLfloat translation_matrix[16] = {1.0, 0.0, 0.0,  tx,
                                      0.0, 1.0, 0.0,  ty,
                                      0.0, 0.0, 1.0,  tz,
                                      0.0, 0.0, 0.0, 1.0};

    MatrixMultiply(translation_matrix, Transf_Mat, Transf_Mat);
}



void Scale(GLfloat scalex, GLfloat scaley, GLfloat scalez, GLfloat *Transf_Mat){
    
    GLfloat scale_matrix[16] = {scalex,     0.0, 0.0, 0.0,
                                    0.0, scaley, 0.0, 0.0,
                                    0.0,     0.0, scalez, 0.0,
                                    0.0,     0.0, 0.0, 1.0};

    MatrixMultiply(scale_matrix, Transf_Mat, Transf_Mat);
}



void RotateZaxis(GLfloat angle, GLfloat *Transf_Mat){

    GLfloat rotation_matrix[16] = { cos(angle), sin(angle), 0.0, 0.0,
                                   -sin(angle), cos(angle), 0.0, 0.0,
                                           0.0,        0.0, 1.0, 0.0,
                                           0.0,        0.0, 0.0, 1.0};

    MatrixMultiply(rotation_matrix, Transf_Mat, Transf_Mat);
}



void RotateYaxis(GLfloat angle, GLfloat *Transf_Mat){

    GLfloat rotation_matrix[16] = { cos(angle), 0.0, sin(angle), 0.0,
                                           0.0, 1.0,        0.0, 0.0,
                                   -sin(angle), 0.0, cos(angle), 0.0,
                                           0.0, 0.0,        0.0, 1.0};

    MatrixMultiply(rotation_matrix, Transf_Mat, Transf_Mat);
}



void RotateXaxis(GLfloat angle, GLfloat *Transf_Mat){

    GLfloat rotation_matrix[16] = {1.0,         0.0,        0.0, 0.0,
                                   0.0,  cos(angle), sin(angle), 0.0,
                                   0.0, -sin(angle), cos(angle), 0.0,
                                   0.0,         0.0,        0.0, 1.0};
                                

    MatrixMultiply(rotation_matrix, Transf_Mat, Transf_Mat);
}



//useful matrices
GLfloat *IdentityMatrix(){
    GLfloat *I;
    I = (GLfloat *) malloc(16*sizeof(GLfloat));
    I[0] =  1.0; I[1] =  0.0; I[2] =  0.0; I[3] =  0.0;
    I[4] =  0.0; I[5] =  1.0; I[6] =  0.0; I[7] =  0.0;
    I[8] =  0.0; I[9] =  0.0; I[10] = 1.0; I[11] = 0.0;
    I[12] = 0.0; I[13] = 0.0; I[14] = 0.0; I[15] = 1.0;
    return I;
}




GLfloat *CoordMatrix(Vec3 array){
    GLfloat *C;
    C = (GLfloat *) malloc(16*sizeof(GLfloat));
    C[0] =  array.x; C[1] = 0.0; C[2] = 0.0; C[3] =  0.0;
    C[4] =  array.y; C[5] = 0.0; C[6] = 0.0; C[7] =  0.0;
    C[8] =  array.z; C[9] = 0.0; C[10] =0.0; C[11] = 0.0;
    C[12] =     1.0; C[13] =0.0; C[14] =0.0; C[15] = 0.0;
    return C;
}


GLfloat *mat_from_glm(vec4 *array){
    GLfloat *C;
    C = (GLfloat *) malloc(16*sizeof(GLfloat));
    C[0]  =  array[0][0]; C[1] =  array[0][1]; C[2]  = array[0][2]; C[3] =  array[0][3];
    C[4]  =  array[1][0]; C[5] =  array[1][1]; C[6]  = array[1][2]; C[7] =  array[1][3];
    C[8]  =  array[2][0]; C[9] =  array[2][1]; C[10] = array[2][2]; C[11] = array[2][3];
    C[12] =  array[3][0]; C[13] = array[3][1]; C[14] = array[3][2]; C[15] = array[3][3];
    return C;
}



Vec3 CenterOfMass(Vec3 *array, int size){

    Vec3 center;
    center.x = 0.0;
    center.y = 0.0;
    center.z = 0.0;


    for(int i = 0; i < size; i++){
        center.x += array[i].x;
        center.y += array[i].y;
        center.z += array[i].z;
    }

    center.x = center.x/size;
    center.y = center.y/size;
    center.z = center.z/size;

    return center;
}

Vec3 RelativeCenterOfMass(Vec3 center0, GLfloat *Ref_Matrix){

    Vec3 center = center0; 
    center.x += Ref_Matrix[0];
    center.y += Ref_Matrix[4];
    center.z += Ref_Matrix[8];

    return center;
}


void printMatrix(GLfloat *array){
    for(int i = 0; i < 4 ; i++){
            printf("%f %f %f %f\n\n", array[4*i + 0], array[4*i + 1], array[4*i + 2], array[4*i + 3]);
    }
}

void RelativeRotateYaxis(GLfloat angle, GLfloat *Transf_Mat, Vec3 point){

    Translate(-point.x, -point.y, -point.z, Transf_Mat);
    RotateYaxis(angle, Transf_Mat);
    Translate(point.x, point.y, point.z, Transf_Mat);

}


void RelativeRotateXaxis(GLfloat angle, GLfloat *Transf_Mat, Vec3 point){

    Translate(-point.x, -point.y, -point.z, Transf_Mat);
    RotateXaxis(angle, Transf_Mat);
    Translate(point.x, point.y, point.z, Transf_Mat);
  
}

void RelativeRotateZaxis(GLfloat angle, GLfloat *Transf_Mat, Vec3 point){

    Translate(-point.x, -point.y, -point.z, Transf_Mat);
    RotateZaxis(angle, Transf_Mat);
    Translate(point.x, point.y, point.z, Transf_Mat);

}

void RelativeScale(GLfloat scalex, GLfloat scaley, GLfloat scalez, GLfloat *Transf_Mat, Vec3 point){

    Translate(-point.x, -point.y, -point.z, Transf_Mat);
    Scale(scalex, scaley, scalez, Transf_Mat);
    Translate(point.x, point.y, point.z, Transf_Mat);

}


void TransformObj3D(Obj3D *Obj, Vec3 translate, Vec3 angle, Vec3 Scale, GLint model_matrix){

    Translate(translate.x, translate.y, translate.z, Obj->Reference_Matrix);

    Vec3 relcenter = RelativeCenterOfMass(Obj->center_of_mass, Obj->Reference_Matrix);

    RelativeRotateXaxis(angle.x, Obj->model_matrix, relcenter);
    RelativeRotateYaxis(angle.y, Obj->model_matrix, relcenter);
    RelativeRotateZaxis(angle.z, Obj->model_matrix, relcenter);
    RelativeScale(Scale.x, Scale.y, Scale.z, Obj->model_matrix, relcenter);
    Translate(translate.x, translate.y, translate.z, Obj->model_matrix);

    glUniformMatrix4fv(model_matrix, 1, GL_TRUE, Obj->model_matrix);

}




GLfloat *viewMatrix(Vec3 Cam_Pos, Vec3 Target_Pos){

    Vec3 Norm;
    Vec3 upVec;
    Vec3 vecProdu;
    Vec3 vecProdv;
    GLfloat mod; //Aarmazena o modulo de um vetor

    mod = 0.0;
    

    Norm.x = Cam_Pos.x - Target_Pos.x;
    Norm.y = Cam_Pos.y - Target_Pos.y;
    Norm.z = Cam_Pos.z - Target_Pos.z;

    mod = sqrt(Norm.x*Norm.x + Norm.y*Norm.y + Norm.z*Norm.z);
    
    if(mod != 0.0){
        Norm.x = Norm.x/mod;
        Norm.y = Norm.y/mod;
        Norm.z = Norm.z/mod;
    }


    upVec.x = 0.0;
    upVec.y = 1.0;
    upVec.z = 0.0;

    vecProdu.x = Norm.y*upVec.z - Norm.z*upVec.y;
    vecProdu.y = Norm.z*upVec.x - Norm.x*upVec.z;
    vecProdu.z = Norm.x*upVec.y - Norm.y*upVec.x;

    mod = sqrt(vecProdu.x*vecProdu.x + vecProdu.y*vecProdu.y + vecProdu.z*vecProdu.z);

    if(mod != 0.0){
        vecProdu.x = vecProdu.x/mod;
        vecProdu.y = vecProdu.y/mod;
        vecProdu.z = vecProdu.z/mod;
    }


    vecProdv.x = vecProdu.y*Norm.z - vecProdu.z*Norm.y;
    vecProdv.y = vecProdu.z*Norm.x - vecProdu.x*Norm.z;
    vecProdv.z = vecProdu.x*Norm.y - vecProdu.y*Norm.x;

    mod = sqrt(vecProdv.x*vecProdv.x + vecProdv.y*vecProdv.y + vecProdv.z*vecProdv.z);

    if(mod != 0.0){
        vecProdv.x = vecProdv.x/mod;
        vecProdv.y = vecProdv.y/mod;
        vecProdv.z = vecProdv.z/mod;
    }


    GLfloat P0[16]  = { 1.0, 0.0, 0.0, -Cam_Pos.x,
                        0.0, 1.0, 0.0, -Cam_Pos.y,
                        0.0, 0.0, 1.0, -Cam_Pos.z,
                        0.0, 0.0, 0.0,        1.0 };

    GLfloat *Rot = IdentityMatrix();


    Rot[0] = vecProdu.x; Rot[1] = vecProdu.y; Rot[2] = vecProdu.z; Rot[3]  = 0.0;
    Rot[4] = vecProdv.x; Rot[5] = vecProdv.y; Rot[6] = vecProdv.z; Rot[7]  = 0.0;
    Rot[8] =     Norm.x; Rot[9] =     Norm.y; Rot[10] =    Norm.z; Rot[11] = 0.0;
    Rot[12] =       0.0; Rot[13] =       0.0; Rot[14] =       0.0; Rot[15] = 1.0;

    

    MatrixMultiply(Rot, P0, Rot);
    printMatrix(Rot);

    return Rot;
}


GLfloat *ArrayFromVec3(Vec3 *array, int size){
    GLfloat *float_array;
    float_array = (GLfloat *) malloc(3*size*sizeof(Vec3));

    for(int i = 0; i < size; i++){
        float_array[i]     = array[i].x;
        float_array[i + 1] = array[i].y;
        float_array[i + 2] = array[i].z;
    }

    return float_array;
}





Obj3D *Obj3DFromFile(char *vertex_path){

    FILE *raw;
    fopen_s(&raw, vertex_path, "r");

    int size = 500;

    unsigned int numb_vert = 0;
    unsigned int numb_text = 0;
    unsigned int numb_norm = 0;
    unsigned int numb_fac = 0;
    
    
    
    Vec3 vert;
    Vec3 normal;
    Vec2 uv;
    Triangle face;

    while(1){ //loop para coletar o numero de vertices, texturas, normais e faces
        
        char line[size];
        int check;


        check = fscanf(raw, "%s\n", line);

        
        
        
        if(check == EOF) break;
        

        //printf("%s\n", line);

        if(strcmp(line, "v") == 0){
            numb_vert += 1;        
        }
        else if ( strcmp(line, "vt") == 0 ){ //Se for coordenada de textura
            numb_text += 1;
        }
        else if ( strcmp(line, "vn" ) == 0 ){ //Se for coordenada de normal
            numb_norm += 1;
        }
        else if ( strcmp(line, "f" ) == 0 ){ //Se for indice das faces
            numb_fac += 1;
        }

    }


    fclose(raw);

    // printf("%d %d %d %d\n", numb_vert, numb_text, numb_norm, numb_fac);
    Vec3 verti[numb_vert];
    unsigned int v = 0;
    Vec2 text[numb_text];
    unsigned int t = 0;
    Vec3 norm[numb_norm];
    unsigned int n = 0;

    Triangle *fac = (Triangle *) malloc(numb_fac*sizeof(Triangle));
    unsigned int f = 0;


    
    fopen_s(&raw, vertex_path, "r");


    while(1){//loop para armazenar os vertices, texturas, normais e faces
        char line[size];
        char line2[size];
        char line3[size];
        


        int check;
        check = fscanf(raw, "%s\n", line);

        fgets(line2, size, raw);
        
        
        
        if(check == EOF) break;
        

        if(strcmp(line, "v") == 0){
            sscanf(line2, "%f %f %f\n", &vert.x, &vert.y, &vert.z);
            verti[v] = vert;
            v++;          
        }
        else if ( strcmp(line, "vt") == 0 ){ //Se for coordenada de textura
            sscanf(line2, "%f %f\n", &uv.x, &uv.y );
            text[t] = uv;
            t++;
        }
        else if ( strcmp(line, "vn" ) == 0 ){ //Se for coordenada de normal
            sscanf(line2, "%f %f %f\n", &normal.x, &normal.y, &normal.z);
            norm[n] = normal;
 
        }
        else if ( strcmp(line, "f" ) == 0 ){ //Se for indice das faces
            sscanf(line2, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &face.tri[0], &face.tex[0], &face.nor[0],
                                                          &face.tri[1], &face.tex[1], &face.nor[1], 
                                                          &face.tri[2], &face.tex[2], &face.nor[2]);
            fac[f] = face;
            f++;
        }
    }


    Vec3 *out_vert;
    out_vert = (Vec3 *) malloc(3*numb_fac*sizeof(Vec3));
    if(out_vert == NULL){
        printf("Cant malloc out_vert!\n");
        free(fac);
        return NULL;
    }

    unsigned int j = 0;
    for(unsigned int i = 0; i < numb_fac; i++){ 
        for(int k = 0; k < 3 ; k++){  
            j = fac[i].tri[k] -1;
            if(&out_vert[3*i + k] == NULL){
                printf("pqp\n");
            }     
            out_vert[3*i + k] = verti[j];
        }
    }

    Vec3 *out_norm;
    out_norm = (Vec3 *) malloc(3*numb_fac*sizeof(Vec3));
    if(out_norm == NULL){
        printf("Cant malloc out_norm!\n");
        free(fac);
        free(out_vert);
        return NULL;
    }

    j = 0;
    for(unsigned int i = 0; i < numb_fac; i++){
        for(int k = 0; k < 3 ; k++){
            j = fac[i].nor[k] -1;
            out_norm[3*i + k] = norm[j];
        }
    }
    
    Vec2 *out_text;
    out_text = (Vec2 *) malloc(3*numb_fac*sizeof(Vec2));
    if(out_text == NULL){
        printf("Cant malloc out_text!\n");
        free(fac);
        free(out_vert);
        free(out_norm);
        return NULL;
    }

    j = 0;
    for(unsigned int i = 0; i < numb_fac; i++){
        for(int k = 0; k < 3 ; k++){
            j = fac[i].tex[k] - 1;
            out_text[3*i + k] = text[j];

        }
    }

    free(fac);
    fac = NULL;

    fclose(raw);

    Obj3D *Obj;
    Obj = (Obj3D *) malloc(sizeof(Obj3D));
    if(Obj == NULL){
        printf("Could not malloc Obj\n");
        free(out_vert);
        free(out_norm);
        free(out_text);
        return NULL;    
    }
    
    Obj->array   = out_vert;
    Obj->normals = out_norm;
    Obj->texture = out_text;

    Obj->numb_vertices = 3*numb_fac;
    Obj->center_of_mass = CenterOfMass(Obj->array, Obj->numb_vertices);

    Obj->projection_matrix = NULL;
    Obj->view_matrix = NULL;
    Obj->model_matrix = NULL;
    Obj->Reference_Matrix = NULL;

    Obj->angle = 0.0;
    Obj->color = DefineColor(255.0, 0.0, 0.0, 1.0);
    Vec3 scale; scale.x = 1.0; scale.y = 1.0; scale.z = 1.0;

    Obj->scale = scale;
    Obj->starting_index = 0;
    Obj->has_texture = 0;


    printf("b\n");

    return(Obj);
}







Scene *SceneFromFile(char *vertex_file, char *vertex_name){

    int size = 500;
    char vertex_path[size];
    strcpy(vertex_path, vertex_file);
    strcat(vertex_path, vertex_name);

    // printf("%s\n", vertex_path);



    FILE *raw;
    fopen_s(&raw, vertex_path, "r");


    unsigned int numb_objs = 0;

    while(1){ //loop para coletar o numero de vertices, texturas, normais e faces
        
        char line[size];
        int check;


        check = fscanf(raw, "%s\n", line);
   
        
        if(check == EOF) break;

        if(strcmp(line, "o") == 0) numb_objs += 1;
        

    }
    fclose(raw);


    //Declarando o array de strings (está certo dar esse malloc? Estava tentando fazer do jeito convencional mas não estava dando certo)
    char **files = (char **) malloc(numb_objs*sizeof(char *));

    long save_last_line = 0;


    fopen_s(&raw, vertex_path, "rb"); //Modo rb importante para o ftell e o fseek funcionarem adequadamente


    //SEGMENTAÇÃO DO ARQUIVO PRINCIPAL EM ARQUIVOS MENORES
    for(int i = 0; i < numb_objs; i++){


        char file_path[30] = "file";
        char numb[numb_objs];
        char *copy = (char *) malloc(size*sizeof(char));



        _itoa(i, numb, 10);
        strcat(file_path, numb);

        strcpy(copy, vertex_file);
        strcat(copy, file_path);



        files[i] = copy;
        
        // printf("%s\n", files[i]);


        FILE *file;
        fopen_s(&file, copy, "w");



        char lineaux[size];
        char lineaux2[size];


        int iter = 0;

        
        //Procura o próximo objeto no arquivo
        fseek(raw, save_last_line, SEEK_SET);


        while(1){

                //Salva cada linha para posterior procura na fseek
                save_last_line = ftell(raw);

                fgets(lineaux, size, raw);



                sscanf(lineaux, "%s\n", lineaux2);

                if(feof(raw)) break;

                else if( strcmp(lineaux2, "o") == 0){

                    if(iter == 0) iter++;
                    else break;
                }

                // fputs(lineaux, file);   
                fprintf(file, "%s", lineaux);           
                
        }

        fclose(file);
    }

    fclose(raw);
   
    // for(int i = 0; i < numb_objs; i++){
    //     printf("%s\n", files[i]);
    // }

    //Alocação de memória para a estrutura a ser retornada pela função
    Scene *scene;

    scene->array_objs       = (Obj3D **) malloc(numb_objs*sizeof(Obj3D *));
    scene->numb_objs        = *(int *) malloc(sizeof(int)); 
    scene->numb_vert        = (int *) malloc(numb_objs*sizeof(int));
    scene->starting_indices = (int *) malloc(numb_objs*sizeof(int));

    if(scene->array_objs == NULL){
        printf("Could no malloc array_objs!\n");
        return NULL;
    }
    if(scene->numb_vert == NULL){
        printf("Could no malloc numb_vert!\n");
        free(&scene->numb_objs);
        free(scene->array_objs);
        return NULL;
    }
    if(scene->starting_indices == NULL){
        
        printf("Could no malloc starting_indices!\n");
        free(&scene->numb_objs);
        free(scene->array_objs);
        free(scene->numb_vert);
        return NULL;
    }

    // printf("a\n");

    for (int j = 0; j < numb_objs; j++){

        printf("%s\n", files[j]);   

        //Lê os objetos individualmente
        scene->array_objs[j]        = Obj3DFromFile(files[j]);
        scene->numb_vert[j]         = scene->array_objs[j]->numb_vertices;
        scene->starting_indices[j]  = scene->array_objs[j]->starting_index;

    }

    scene->numb_objs = numb_objs;

    //Deleta todos os arquivos auxiliares criados
    for (int i = 0; i < numb_objs; i++) remove(files[i]);

    //Libera a memora alocada para o array de strings
    for (int i = 0; i < numb_objs; i++) free(files[i]);

    //Libera memória do ponteiro em si (isso está certo?)
    free(files);


    return(scene);
}

//FUNÇÃO MORTA E LEITURA DE TEXTURAS
/*int TextureFromFile(char *file_name, png_uint_32 *w, png_uint_32 *h, png_bytepp row_pointers) {
   png_structp png_ptr;
   png_infop info_ptr;
   int sig_read = 0;
   //png_uint_32 width, height;
   int bit_depth, color_type, interlace_type;
   FILE *fp;

   if ((fp = fopen(file_name, "rb")) == NULL)
      return 0;

   
   png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);

   if (png_ptr == NULL)
   {
      fclose(fp);
      return 0;
   }

   info_ptr = png_create_info_struct(png_ptr);
   if (info_ptr == NULL)
   {
      fclose(fp);
      png_destroy_read_struct(&png_ptr, NULL, NULL);
      return 0;
   }

   if (setjmp(png_jmpbuf(png_ptr)))
   {

      png_destroy_read_struct(&png_ptr, &info_ptr, NULL);
      fclose(fp);

      return 0;
   }


   png_init_io(png_ptr, fp);


   png_set_sig_bytes(png_ptr, sig_read);

   //png_read_png(png_ptr, info_ptr, PNG_TRANSFORM_IDENTITY, NULL);


    //O PROGRAMA NÃO DEU READ ERROR SE USADAS AS FUNÇÕES DE BAIXO NÍVEL NDO ARQUIVO DE EXEMPLO


   png_read_info(png_ptr, info_ptr);

   png_get_IHDR(png_ptr, info_ptr, w, h, &bit_depth, &color_type, &interlace_type, NULL, NULL);


    png_set_strip_16(png_ptr); 

   //w = (png_uint_32 *) malloc(sizeof(png_uint_32)); 
   //h = (png_uint_32 *) malloc(sizeof(png_uint_32)); 
   *w = 0;
   *h = 0;

   *w          = png_get_image_width(png_ptr, info_ptr);
   *h          = png_get_image_height(png_ptr, info_ptr);
   color_type  = png_get_color_type(png_ptr, info_ptr);
   bit_depth   = png_get_bit_depth(png_ptr, info_ptr);

   printf("%d %d\n", *w, *h);

   



   int number_passes = png_set_interlace_handling(png_ptr);




   png_bytep row_pointerss[*h];

   //printf("a\n");
   for (int row = 0; row < *h; row++)
      row_pointerss[row] = NULL;
   for (int row = 0; row < *h; row++)
      row_pointerss[row] = png_malloc(png_ptr, png_get_rowbytes(png_ptr, info_ptr));


    //png_read_image(png_ptr, row_pointerss);

   for (int pass = 0; pass < number_passes; pass++){
      for (int y = 0; y < *h; y++)
        png_read_rows(png_ptr, &row_pointerss[y], NULL, 1);
   }

   png_read_end(png_ptr, info_ptr);




   row_pointers = row_pointerss; //Essa passagem não está dando certo, arrumar


   png_destroy_read_struct(&png_ptr, &info_ptr, NULL);


   fclose(fp);


   return 1;

}*/


int TextureFromFile(char *texture_path, int texture_id, Obj3D *obj){

    SDL_Surface *s;
    if(SDL_Init(SDL_INIT_VIDEO) < 0){
        printf("SDL could not initialize: %s\n", SDL_GetError());
        obj->has_texture = 0;
        return 0;
    }
    else{
        int imgFlags = IMG_INIT_PNG;
        if( !(IMG_Init(imgFlags) & imgFlags)){
            printf("IMG could not initialize: %s\n", IMG_GetError());
            obj->has_texture = 0;
            SDL_Quit();
            return 0;
        }
        else{
            s = IMG_Load(texture_path);
            if(s == NULL){
                printf("Unable to extract texture!");
                obj->has_texture = 0;
                IMG_Quit();
                SDL_Quit();
                return 0;
            }
            else{
                flip_surface(s); 
                obj->has_texture = 1;

                glBindTexture(GL_TEXTURE_2D, texture_id); //Binda as texturas na gpu
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); //Filtros de repeticao: GL_REPEAT -> repeticao simples
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST); //Filtros de maginificao e minificacao: GL_LINEAR
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        
                glTexImage2D(GL_TEXTURE_2D, 0, obj->texture_info.format, s->w, s->h, 0, obj->texture_info.format, GL_UNSIGNED_BYTE, s->pixels);

                SDL_FreeSurface(s);
                IMG_Quit();
                SDL_Quit();
                return 1;
            }
        }
    }
}

void UpdateObj3D(Obj3D *Obj, GLint model, GLint view, GLint proj, Vec3 transl, Vec3 angles, Vec3 scale){
    TransformObj3D(Obj, transl, angles, scale, model);
    glUniformMatrix4fv(view, 1, GL_TRUE, Obj->view_matrix);
    glUniformMatrix4fv(proj, 1, GL_TRUE, Obj->projection_matrix);
}


void RenderObj3D(Obj3D Obj, GLint color){

    if(Obj.has_texture){
        glBindTexture(GL_TEXTURE_2D, Obj.texture_id);
        for(int i = 0; i < Obj.numb_vertices/3; i++){
            glDrawArrays(GL_TRIANGLES, 3*i, 3);
        }
    }

    else{
        glUniform4f(color, Obj.color.r, Obj.color.g, Obj.color.b, Obj.color.w);
        for(int i = 0; i < Obj.numb_vertices/3; i++){
            glDrawArrays(GL_TRIANGLES, 3*i, 3);
        }
    }
}


void flip_surface(SDL_Surface* surface){ //Função tirada de https://stackoverflow.com/questions/65815332/flipping-a-surface-vertically-in-sdl2
    SDL_LockSurface(surface);
    
    int pitch = surface->pitch; // row size
    char temp[pitch]; // intermediate buffer
    char* pixels = (char*) surface->pixels;
    
    for(int i = 0; i < surface->h / 2; ++i) {
        // get pointers to the two rows to swap
        char* row1 = pixels + i*pitch;
        char* row2 = pixels + (surface->h - i - 1)*pitch;
        
        // swap rows
        memcpy(temp, row1, pitch);
        memcpy(row1, row2, pitch);
        memcpy(row2, temp, pitch);
    }
    

    SDL_UnlockSurface(surface);
}

