#include <stdio.h>
#include <stdlib.h>
#include <GL/glew.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <cglm/cglm.h>



GLuint GLSLCompileQuad();

GLfloat *IdentityMatrix();

void MatrixMultiply(GLfloat *A, GLfloat *B, GLfloat *result);

void Translate(GLfloat tx, GLfloat ty, GLfloat tz, GLfloat *Transf_Mat);

void Scale(GLfloat scalex, GLfloat scaley, GLfloat scalez, GLfloat *Transf_Mat);

void RelativeScale(GLfloat scalex, GLfloat scaley, GLfloat scalez, GLfloat *Transf_Mat, vec3 point);


