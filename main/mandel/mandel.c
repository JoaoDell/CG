#include "mandel.h"


GLuint GLSLCompileQuad(){

    const GLchar *vert_shader = "attribute vec3 position;\n"
                                "uniform mat4 model;\n"

                                "varying vec3 out_pos;\n"
                                "void main(){\n"
                                    "out_pos = vec3(model*vec4(position, 1.0));\n"
                                    "gl_Position = vec4(position, 1.0);\n"
                                "}\n";

    const GLchar *frag_shader = "#define product(a, b) vec2(a.x*b.x-a.y*b.y, a.x*b.y+a.y*b.x)\n"
                                "#define conjugate(a) vec2(a.x,-a.y)\n"
                                "#define divide(a, b) vec2(((a.x*b.x+a.y*b.y)/(b.x*b.x+b.y*b.y)),((a.y*b.x-a.x*b.y)/(b.x*b.x+b.y*b.y)))\n"

                                "uniform vec4 color;\n"
                                "uniform vec2 resolution;\n"
                                // "uniform int max_iter;\n"

                                "varying vec3 out_pos;\n"
                                "void main(){\n"
                                    "int max_iter = 40;\n"
                                    "vec3 mandel = out_pos;\n"
                                    "for(int i = 0; i < max_iter; i++){\n"
                                        "mandel = vec3(product(mandel.xy, mandel.xy), 0.0) + out_pos;\n"
                                    "}\n"
                                    "if(mandel.x > 1.0) mandel.x = 1.0;\n"
                                    "if(mandel.y > 1.0) mandel.y = 1.0;\n"
                                    "gl_FragColor = vec4(0.0, mandel.xy, 1.0);\n"
                                "}\n";


    GLuint program = glCreateProgram();
    GLuint vertex = glCreateShader(GL_VERTEX_SHADER);
    GLuint fragment = glCreateShader(GL_FRAGMENT_SHADER);

    glShaderSource(vertex, 1, &vert_shader, NULL);
    glShaderSource(fragment, 1, &frag_shader, NULL);

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

    return program;
}


GLfloat *IdentityMatrix(){
    GLfloat *I;
    I = (GLfloat *) malloc(16*sizeof(GLfloat));
    I[0] =  1.0; I[1] =  0.0; I[2] =  0.0; I[3] =  0.0;
    I[4] =  0.0; I[5] =  1.0; I[6] =  0.0; I[7] =  0.0;
    I[8] =  0.0; I[9] =  0.0; I[10] = 1.0; I[11] = 0.0;
    I[12] = 0.0; I[13] = 0.0; I[14] = 0.0; I[15] = 1.0;
    return I;
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

void RelativeScale(GLfloat scalex, GLfloat scaley, GLfloat scalez, GLfloat *Transf_Mat, vec3 point){

    Translate(-point[0], -point[1], -point[2], Transf_Mat);
    Scale(scalex, scaley, scalez, Transf_Mat);
    Translate(point[0], point[1], point[2], Transf_Mat);

}