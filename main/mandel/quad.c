#include "mandel.h"


GLuint GLSLCompileQuad(){

    const GLchar *vert_shader = "attribute vec3 position;\n"
                                "varying vec3 out_pos;\n"
                                "void main(){\n"
                                    "out_pos = position;\n"
                                    "gl_Position = vec4(position, 1.0);\n"
                                "}\n";

    const GLchar *frag_shader = "uniform vec4 color;\n"
                                "varying vec3 out_pos;\n"
                                "void main(){\n"
                                    "gl_FragColor = vec4(out_pos, 1.0);\n"
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