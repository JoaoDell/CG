
#ifndef BASIC //define to exclude SDL-dependent functions calls and packages
#include <SDL2/SDL_config.h>
#include <SDL2/SDL_stdinc.h>
#include <SDL2\SDL_surface.h>
#include <SDL2\SDL.h>           //VERSÃO 2.0.14
#include <SDL2\SDL_image.h>     //VERSÃO 2.0.1
#endif


#include <GL\glew.h>            //VERSÃO 2.10
#include <cglm/mat4.h>
#include <float.h>
#include <stdint.h>
#define GLFW_INCLUDE_NONE
#include <GLFW\glfw3.h>         //VERSÃO 3.3.4
#include "GLib.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>



//FUNÇÃO DE INICIALIZAÇÃO DO GLSL PARA RENDERIZAÇÃO DE VERTICES 2D
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


//FUNÇÃO DE INICIALIZAÇÃO DO GLSL PARA RENDERIZAÇÃO DE VERTICES 3D
GLuint GLSLCompile3D(){

    /*CONFIGURANDO INICIALIZAÇÃO DO GLSL*/

    const GLchar *vertex_code = "attribute vec3 position;\n"
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


//FUNÇÃO DE INICIALIZAÇÃO DO GLSL PARA RENDERIZAÇÃO DE VERTICES 3D E TEXTURAS
GLuint GLSLCompile3DTexture(){

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
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_LINE_SMOOTH);
    glEnable(GL_TEXTURE_2D);

    return(program);

}


GLuint GLSLCompile3DLight(){

    /*CONFIGURANDO INICIALIZAÇÃO DO GLSL*/

    const GLchar *vertex_code = "attribute vec3 position;\n"
                                "attribute vec2 texture_coord;\n"
                                "attribute vec3 normals;\n"


                                "varying vec2 out_texture;\n"
                                "varying vec3 out_norm;\n"
                                "varying vec3 out_fragPos;\n"


                                "uniform mat4 model;\n"
                                "uniform mat4 view;\n"
                                "uniform mat4 projection;\n"
                                "uniform mat4 lightSpaceMatrix;\n"


                                
                                "void main(){\n"
                                    "gl_Position = projection*view*model*vec4(position, 1.0);\n"
                                    "out_texture = vec2(texture_coord);\n"
                                    "out_fragPos = vec3(model * vec4(position, 1.0));\n"
                                    "out_norm = vec3(model * vec4(normals, 1.0));\n"
                                "}\n";


    const GLchar *fragment_code =   "uniform vec3 lightPos;\n"
                                    "uniform vec3 lightColor;\n"
                                    "uniform vec3 ambientColor;\n"


                                    "uniform vec4 color;\n"
                                    "uniform sampler2D samplerTexture;\n"
                                    "uniform float Ka;\n"
                                    "uniform float Kd;\n"

                                    "uniform vec3 viewPos;\n"
                                    "uniform float Ks;\n"
                                    "uniform float ns;\n"
                                    


                                    "varying vec2 out_texture;\n"
                                    "varying vec3 out_norm;\n"
                                    "varying vec3 out_fragPos;\n"
                                    "varying vec4 out_lightSpace;\n"

                                    
                                    "void main(){\n"
                                        //Recalculo da Luz ambiente pra considerar uma segunda cor, a cor ambiente
                                        //Média ponderada para dar ênfase ao que mais se quer aparecendo
                                        "vec3 ambient = Ka*(0.7*ambientColor + 1.3*lightColor)/2;\n" 


                                        //Calculo da luz difusa
                                        "vec3 norm = normalize(out_norm);\n"
                                        "vec3 lightDir = normalize(lightPos - out_fragPos);\n" //Direção da luz
                                        "float Diff = max(dot(norm, lightDir), 0.0);\n" //Termo de intensidade de luz em uma superficie
                                        "vec3 diffuse = Kd*Diff*lightColor;\n"


                                        //Cálculo da luz especular
                                        "vec3 viewDir = normalize(viewPos - out_fragPos);\n" // direcao do observador/camera
                                        "vec3 reflectDir = normalize(reflect(-lightDir, norm));\n" // direcao da reflexao
                                        "float spec = pow(max(dot(viewDir, reflectDir), 0.0), ns);\n"
                                        "vec3 specular = Ks*spec*lightColor;\n"  



                                        //Calculo Final das três luzes
                                        "vec4 texture = texture2D(samplerTexture, out_texture);\n"
                                        "vec4 result = vec4((ambient + diffuse + specular), 1.0)*texture;\n"
                                        "gl_FragColor = result;\n"
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

        printf("Erro de compilacao no Fragment Shader.\n");
        printf("--> %s\n", info);    

    }


    glAttachShader(program, vertex);
    glAttachShader(program, fragment);

    glLinkProgram(program);
    glUseProgram(program);

    //Diz ao openGL para usar texturas com transparencia
    glHint(GL_LINE_SMOOTH_HINT, GL_DONT_CARE);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_LINE_SMOOTH);
    glEnable(GL_TEXTURE_2D);

    return(program);

}

GLuint GLSLCompile3DLightShadow(){

    /*CONFIGURANDO INICIALIZAÇÃO DO GLSL*/

    const GLchar *vertex_code = "attribute vec3 position;\n"
                                "attribute vec2 texture_coord;\n"
                                "attribute vec3 normals;\n"

                                "varying vec2 out_texture;\n"
                                "varying vec3 out_norm;\n"
                                "varying vec3 out_fragPos;\n"
                                "varying vec4 out_lightSpace;\n"

                                "varying vec3 out_lightPos;\n"

                                "uniform vec3 lightPos;\n"

                                "uniform mat4 model;\n"
                                "uniform mat4 view;\n"
                                "uniform mat4 projection;\n"
                                "uniform mat4 lightSpaceMatrix;\n"



                                
                                "void main(){\n"
                                    "out_texture = vec2(texture_coord);\n"
                                    "out_fragPos = vec3(model * vec4(position, 1.0));\n"
                                    "out_norm = vec3(model * vec4(normals, 1.0));\n"
                                    "out_lightSpace = lightSpaceMatrix * vec4(out_fragPos, 1.0);\n"
                                    "out_lightPos = lightPos;\n "
                                    "gl_Position = projection * view * model * vec4(position, 1.0);\n"
                                "}\n";


    const GLchar *fragment_code = 
                                    "uniform vec3 lightColor;\n"
                                    "uniform vec3 ambientColor;\n"


                                    "uniform vec4 color;\n"
                                    "uniform sampler2D samplerTexture;\n"
                                    "uniform sampler2D shadowMap;\n"
                                    "uniform float Ka;\n"
                                    "uniform float Kd;\n"


                                    "uniform vec3 viewPos;\n"
                                    "uniform float Ks;\n"
                                    "uniform float ns;\n"


                                    "varying vec2 out_texture;\n"
                                    "varying vec3 out_norm;\n"
                                    "varying vec3 out_fragPos;\n"
                                    "varying vec4 out_lightSpace;\n"

                                    "varying vec3 out_cam;\n"
                                    "varying vec3 out_lightPos;\n"



                                    "float shadowCalc(vec4 out_light){\n"
                                        "vec3 Pos = out_light.xyz/out_light.w;\n"
                                        "Pos = Pos*0.5 + 0.5;\n"
                                        "float closestDepth = texture(shadowMap, Pos.xy).r;\n"
                                        "float currentDepth = Pos.z;\n"
                                        "float bias = 0.00005;\n"
                                        "if(currentDepth > 1.0) return 0.0;\n"
                                        "else return currentDepth - bias > closestDepth ? 1.0 : 0.0;\n"
                                    "}\n"

                                    
                                    "void main(){\n"
                                        //Recalculo da Luz ambiente pra considerar uma segunda cor, a cor ambiente
                                        //Média ponderada para dar ênfase ao que mais se quer aparecendo
                                        "vec3 ambient = Ka*(1.3*ambientColor + 0.7*lightColor)*0.5;\n" 


                                        //Calculo da luz difusa
                                        "vec3 norm = normalize(out_norm);\n"
                                        "vec3 lightDir = normalize(out_lightPos - out_fragPos);\n" //Direção da luz
                                        "float Diff = max(dot(norm, lightDir), 0.0);\n" //Termo de intensidade de luz em uma superficie
                                        "vec3 diffuse = Kd*Diff*lightColor;\n"


                                        //Cálculo da luz especular
                                        "vec3 viewDir = normalize(viewPos - out_fragPos);\n" // direcao do observador/camera
                                        "vec3 reflectDir = normalize(reflect(-lightDir, norm));\n" // direcao da reflexao
                                        "float spec = pow(max(dot(viewDir, reflectDir), 0.0), ns);\n"
                                        "vec3 specular = Ks*spec*lightColor;\n"  

                                        //Calculando sombras
                                        "float shadow = shadowCalc(out_lightSpace);\n"


                                        //Calculo Final das três luzes
                                        "vec4 texture = texture2D(samplerTexture, out_texture);\n"
                                        "vec4 result = vec4((ambient + (1.0 - shadow)*(diffuse + specular)), 1.0)*texture;\n"
                                        "gl_FragColor = result;\n"
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

        printf("Erro de compilacao no Fragment Shader.\n");
        printf("--> %s\n", info);    

    }

    glAttachShader(program, vertex);
    glAttachShader(program, fragment);

    glLinkProgram(program);
    glUseProgram(program);

    //Diz ao openGL para usar texturas com transparencia
    glHint(GL_LINE_SMOOTH_HINT, GL_DONT_CARE);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_LINE_SMOOTH);
    glEnable(GL_TEXTURE_2D);


    return(program);
}


GLuint GLSLcreateProgram(){
    GLuint program = glCreateProgram();

    //Diz ao openGL para usar texturas com transparencia
    glHint(GL_LINE_SMOOTH_HINT, GL_DONT_CARE);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_LINE_SMOOTH);
    glEnable(GL_TEXTURE_2D);


    return(program);
}


void GLSLCompileStandardShader(GLuint program, Shader *shader){

    /*CONFIGURANDO INICIALIZAÇÃO DO GLSL*/

    const GLchar *vertex_code = "attribute vec3 position;\n"
                                "attribute vec2 texture_coord;\n"
                                "attribute vec3 normals;\n"

                                "varying vec2 out_texture;\n"
                                "varying vec3 out_norm;\n"
                                "varying vec3 out_fragPos;\n"
                                "varying vec4 out_lightSpace;\n"

                                "varying vec3 out_lightPos;\n"

                                "uniform vec3 lightPos;\n"

                                "uniform mat4 model;\n"
                                "uniform mat4 view;\n"
                                "uniform mat4 projection;\n"
                                "uniform mat4 lightSpaceMatrix;\n"



                                
                                "void main(){\n"
                                    "out_texture = vec2(texture_coord);\n"
                                    "out_fragPos = vec3(model * vec4(position, 1.0));\n"
                                    "out_norm = vec3(model * vec4(normals, 1.0));\n"
                                    "out_lightSpace = lightSpaceMatrix * vec4(out_fragPos, 1.0);\n"
                                    "out_lightPos = lightPos;\n "
                                    "gl_Position = projection * view * model * vec4(position, 1.0);\n"
                                "}\n";


    const GLchar *fragment_code = 
                                    "uniform vec3 lightColor;\n"
                                    "uniform vec3 ambientColor;\n"
                                    "uniform int has_texture;\n"


                                    "uniform vec4 color;\n"
                                    "uniform sampler2D samplerTexture;\n"
                                    "uniform sampler2D shadowMap;\n"
                                    "uniform float Ka;\n"
                                    "uniform float Kd;\n"


                                    "uniform vec3 viewPos;\n"
                                    "uniform float Ks;\n"
                                    "uniform float ns;\n"


                                    "varying vec2 out_texture;\n"
                                    "varying vec3 out_norm;\n"
                                    "varying vec3 out_fragPos;\n"
                                    "varying vec4 out_lightSpace;\n"

                                    "varying vec3 out_cam;\n"
                                    "varying vec3 out_lightPos;\n"



                                    "float shadowCalc(vec4 out_light){\n"
                                        "vec3 Pos = out_light.xyz/out_light.w;\n"
                                        "Pos = Pos*0.5 + 0.5;\n"
                                        "float closestDepth = texture(shadowMap, Pos.xy).r;\n"
                                        "float currentDepth = Pos.z;\n"
                                        "float bias = 0.00005;\n"
                                        "if(currentDepth > 1.0) return 0.0;\n"
                                        "else return currentDepth - bias > closestDepth ? 1.0 : 0.0;\n"
                                    "}\n"

                                    
                                    "void main(){\n"
                                        //Recalculo da Luz ambiente pra considerar uma segunda cor, a cor ambiente
                                        //Média ponderada para dar ênfase ao que mais se quer aparecendo
                                        "vec3 ambient = Ka*(0.7*ambientColor + 1.3*lightColor)*0.5;\n" 


                                        //Calculo da luz difusa
                                        "vec3 norm = normalize(out_norm);\n"
                                        "vec3 lightDir = normalize(out_lightPos - out_fragPos);\n" //Direção da luz
                                        "float Diff = max(dot(norm, lightDir), 0.0);\n" //Termo de intensidade de luz em uma superficie
                                        "vec3 diffuse = Kd*Diff*lightColor;\n"


                                        //Cálculo da luz especular
                                        "vec3 viewDir = normalize(viewPos - out_fragPos);\n" // direcao do observador/camera
                                        "vec3 reflectDir = normalize(reflect(-lightDir, norm));\n" // direcao da reflexao
                                        "float spec = pow(max(dot(viewDir, reflectDir), 0.0), ns);\n"
                                        "vec3 specular = Ks*spec*lightColor;\n"  

                                        //Calculando sombras
                                        "float shadow = shadowCalc(out_lightSpace);\n"


                                        //Calculo Final das três luzes
                                        "vec4 result;\n"
                                        "vec4 texture;\n"

                                        "if(has_texture == 1){\n"
                                            "texture = texture2D(samplerTexture, out_texture);\n"
                                            "result = vec4((ambient + (1.0 - shadow)*(diffuse + specular)), 1.0)*texture;\n"
                                            "gl_FragColor = result;\n"
                                        "}\n"
                                        "else{\n"
                                            "result = vec4((ambient + (1.0 - shadow)*(diffuse + specular)), 1.0);\n"
                                        "}\n"
                                        "gl_FragColor = result;\n"
                                        // "gl_FragColor = vec4(1.0, 0.0, 0.0, 1.0);\n"
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





void GLSLCompileQuadShader(GLuint program, Shader *shader){

    const GLchar *vert_shader = "attribute vec3 position;\n"
                                "varying vec3 out_pos;\n"
                                "void main(){\n"
                                    "out_pos = position;\n"
                                    "gl_Position = vec4(position, 1.0);\n"
                                "}\n";

    const GLchar *frag_shader = "uniform vec4 color;\n"
                                "varying vec3 out_pos;\n"
                                "void main(){\n"
                                    "gl_FragColor = vec4(1.0, 0.0, 0.0, 0.5);\n"
                                "}\n";


    shader->vertex = glCreateShader(GL_VERTEX_SHADER);
    shader->fragment = glCreateShader(GL_FRAGMENT_SHADER);

    glShaderSource(shader->vertex, 1, &vert_shader, NULL);
    glShaderSource(shader->fragment, 1, &frag_shader, NULL);

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
        glGetShaderiv(shader->fragment, GL_INFO_LOG_LENGTH, &infoLength);

        //recuperando o log de erro e imprimindo na tela
        char info[infoLength];
        glGetShaderInfoLog(shader->fragment, infoLength, NULL, info);

        printf("Erro de compilacao no Vertex Shader.\n");
        printf("--> %s\n", info);    

    }
}


void GLSLCompileDistancesShader(GLuint program, Shader *shader){

    const GLchar *vert_shader = "attribute vec3 position;\n"
                                "varying vec3 out_pos;\n"
                                "varying vec3 out_lightPos;\n"

                                "uniform vec3 lightPos;\n"

                                "void main(){\n"
                                    "out_pos = position;\n"
                                    "out_lightPos = lightPos;\n"
                                    "gl_Position = vec4(position, 1.0);\n"
                                "}\n";

    const GLchar *frag_shader = "uniform vec4 color;\n"
                                "uniform float radius;\n"
                                "uniform float blend;\n"
                                "uniform vec3 point = vec3(0.0, 0.0, 0.0);\n"
                                "uniform vec3 viewPos;\n"
                                // "uniform float Ks;\n"
                                // "uniform float ns;\n"
                                "uniform vec3 out_norm;\n"
                                "uniform vec3 lightColor;\n"
                                // "point.x = 0.0; point.y = 0.0; point.z = 0.0;\n"
                                

                                "varying vec3 out_pos;\n"
                                "varying vec3 out_lightPos;\n"


                                "void main(){\n"


                                    "vec3 norm = normalize(out_norm);\n"
                                    "vec3 lightDir = normalize(out_lightPos - out_pos);\n"

                                    "float Ks = 10.0;\n"
                                    "float ns = 10.0;\n"

                                    "vec3 viewDir = normalize(viewPos - out_pos);\n" // direcao do observador/camera
                                    "vec3 reflectDir = normalize(reflect(-lightDir, norm));\n" // direcao da reflexao
                                    "float spec = pow(max(dot(viewDir, reflectDir), 0.0), ns);\n"
                                    "vec3 specular = Ks*spec*lightColor;\n"  

                                    "gl_FragColor = vec4(specular, blend);\n"

                                    // "point = vec3(0.0, 0.0, 0.0);\n"
                                    // "if(length(out_pos - point) <= 0.3)"
                                    //     "gl_FragColor = vec4(1.0, 0.0, 0.0, blend);\n"
                                    // "else gl_FragColor = vec4(0.0, 0.0, 0.0, 0.0);\n"
                                "}\n";


    shader->vertex = glCreateShader(GL_VERTEX_SHADER);
    shader->fragment = glCreateShader(GL_FRAGMENT_SHADER);

    glShaderSource(shader->vertex, 1, &vert_shader, NULL);
    glShaderSource(shader->fragment, 1, &frag_shader, NULL);

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
        glGetShaderiv(shader->fragment, GL_INFO_LOG_LENGTH, &infoLength);

        //recuperando o log de erro e imprimindo na tela
        char info[infoLength];
        glGetShaderInfoLog(shader->fragment, infoLength, NULL, info);

        printf("Erro de compilacao no Vertex Shader.\n");
        printf("--> %s\n", info);    

    }
}



// void GLSLCompileShader(GLuint program, Shader *shader, char *vertex_file, char *frag_file){

//     uint32_t MAX_SIZE = LONG_MAX;

//     const GLchar *vert_shader = (const GLchar *) malloc(sizeof(const GLchar)), 
//     *frag_shader = (const GLchar *) malloc(sizeof(const GLchar));

//     FILE *vfile, *ffile;

//     fopen_s(&vfile, vertex_file, "r");

//     while(!feof(vfile)){
//         if()
//     }


//     // fread(vert_shader, null, , )
//     // fgets(vert_shader, MAX_SIZE, vfile);
    
//     fclose(vfile);


//     fopen_s(&ffile, frag_file, "r");
//     fgets(frag_shader, MAX_SIZE, ffile);
//     fclose(ffile);
    


//     // const GLchar *vert_shader = "attribute vec3 position;\n"
//     //                             "varying vec3 out_pos;\n"
//     //                             "void main(){\n"
//     //                                 "out_pos = position;\n"
//     //                                 "gl_Position = vec4(position, 1.0);\n"
//     //                             "}\n";

//     // const GLchar *frag_shader = "uniform vec4 color;\n"
//     //                             "varying vec3 out_pos;\n"
//     //                             "void main(){\n"
//     //                                 "gl_FragColor = vec4(1.0, 0.0, 0.0, 0.5);\n"
//     //                             "}\n";


//     shader->vertex = glCreateShader(GL_VERTEX_SHADER);
//     shader->fragment = glCreateShader(GL_FRAGMENT_SHADER);

//     glShaderSource(shader->vertex, 1, vert_shader, NULL);
//     glShaderSource(shader->fragment, 1, frag_shader, NULL);

//     glCompileShader(shader->vertex);

//     glGetShaderiv(shader->vertex, GL_COMPILE_STATUS, &shader->vertex_status);
//     if(shader->vertex_status == GL_FALSE){
        
//         //descobrindo o tamanho do log de erro
//         int infoLength = 512;
//         glGetShaderiv(shader->vertex, GL_INFO_LOG_LENGTH, &infoLength);

//         //recuperando o log de erro e imprimindo na tela
//         char info[infoLength];
//         glGetShaderInfoLog(shader->vertex, infoLength, NULL, info);

//         printf("Erro de compilacao no Vertex Shader.\n");
//         printf("--> %s\n", info);
//     }

//     glCompileShader(shader->fragment);

//     glGetShaderiv(shader->fragment, GL_COMPILE_STATUS, &shader->fragment_status);
//     if(shader->fragment_status == GL_FALSE){

//         //descobrindo o tamanho do log de erro
//         int infoLength = 512;
//         glGetShaderiv(shader->fragment, GL_INFO_LOG_LENGTH, &infoLength);

//         //recuperando o log de erro e imprimindo na tela
//         char info[infoLength];
//         glGetShaderInfoLog(shader->fragment, infoLength, NULL, info);

//         printf("Erro de compilacao no Vertex Shader.\n");
//         printf("--> %s\n", info);    

//     }
// }








//FUNÇÃO DE MALLOC E INICIALIZAÇÃO DE UM OBJETO 
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

//FUNÇÃO DE MALLOC E INICIALIZAÇÃO DE UM OBJETO 3D 
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
        o->texture_info.color = color;
        o->model_matrix = transf_matrix;

        return o;
    }
}


//FUNÇÃO DE MALLOC DE INICIALIZAÇÃO DE UMA CENA
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







//FUNÇÃO QUE ADICIONA UM OBJETO A UMA CENA - VERSÃO DESCONTINUADA
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


//FUNÇÃO QUE ADICIONA UM OBJETO A UMA CENA 3D - VERSÃO DESCONTINUADA
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


//FUNÇÃO QUE RETORNA UMA COR NORMALIZADA RECEBENDO UMA COR NO ESPAÇO [0, 255]
Color DefineColor(float r, float g, float b, float w){
    Color c;
    c.r = r/255;
    c.g = g/255;
    c.b = b/255;
    c.w = w;
    return c;
}


//FUNÇÃO DE DESTRUIÇÃO DE UM OBJETO
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

//FUNÇÃO DE DESTRUIÇÃO DE UM OBJETO 3D
void DestroyObj3D(Obj3D *object){
    free(object->array);
    object->array = NULL;
    free(object->normals);
    object->normals = NULL;
    free(object->texture);
    object->texture = NULL;
    free(object->model_matrix);
    object->model_matrix = NULL;
    free(object->Reference_Matrix);
    object->Reference_Matrix = NULL;
    free(&object->starting_index);
    free(&object->texture_info.color);
    free(&object->numb_vertices);
    // printf("%f, %f, %f\n", object->center_of_mass.x, object->center_of_mass.y, object->center_of_mass.z);
    free(&object->center_of_mass);
    // printf("d\n");
    free(&object->scale);
    free(&object->angle);
    free(object);
}

//FUNÇÃO DE DESTRUIÇÃO DOS DADOS DE UMA CENA - AINDA BUGADA
void DestroyScene(Scene *scene){


        printf("%d\n", scene->numb_objs);
        for (int i = 0; i < scene->numb_objs; i++){
            DestroyObj3D(&scene->array_objs[i]);
        }

        free(scene->array_objs);
        scene->array_objs = NULL;

        free(scene->numb_vert);
        scene->numb_vert = NULL;

        free(scene->starting_indices);
        scene->starting_indices = NULL;

        free(scene->starting_indices);
        scene->starting_indices = NULL;

}


//FUNÇÃO QUE CRIA UM CIRCULO NO ESPAÇO 2D
void SpawnCircle(int numb_vert, Vec2 *array, Vec2 center, float radius){
    float angle = 0.0;
    for (int i = 0; i < numb_vert; i++){
        angle += (2*M_PI)/(numb_vert);
        array[i].x = radius*cos(angle) + center.x;
        array[i].y = radius*sin(angle) + center.y;
    }
}

//FUNÇÃO QUE CRIA UM CIRCULO NO ESPAÇO 3D
void SpawnCircle3D(int numb_vert, vec3 *array, vec3 center, float radius, char *plane){

    if (strcmp(plane, "xy") == 0 || strcmp(plane, "yx") == 0 ){
        float angle = 0.0;
        for (int i = 0; i < numb_vert; i++){
            angle += (2*M_PI)/(numb_vert);
            array[i][0] = radius*cos(angle) + center[0];
            array[i][1] = radius*sin(angle) + center[1];
            array[i][2] = center[2];
        }
    }
    else if(strcmp(plane, "xz") == 0 || strcmp(plane, "zx") == 0 ){
        float angle = 0.0;
        for (int i = 0; i < numb_vert; i++){
            angle += (2*M_PI)/(numb_vert);
            array[i][0] = radius*cos(angle) + center[0];
            array[i][1] = center[1];
            array[i][2] = radius*sin(angle) + center[2];
        }
    }
    else if(strcmp(plane, "yz") == 0 || strcmp(plane, "zy") == 0 ){
        float angle = 0.0;
        for (int i = 0; i < numb_vert; i++){
            angle += (2*M_PI)/(numb_vert);
            array[i][0] = center[0];
            array[i][1] = radius*cos(angle) + center[1];
            array[i][2] = radius*sin(angle) + center[2];
        }
    }
}



//FUNÇÃO QUE MULTIPLICA MATRIZES
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


//FUNÇÃO DE TRANSLAÇÃO
void Translate(GLfloat tx, GLfloat ty, GLfloat tz, GLfloat *Transf_Mat){


    GLfloat translation_matrix[16] = {1.0, 0.0, 0.0,  tx,
                                      0.0, 1.0, 0.0,  ty,
                                      0.0, 0.0, 1.0,  tz,
                                      0.0, 0.0, 0.0, 1.0};

    MatrixMultiply(translation_matrix, Transf_Mat, Transf_Mat);
}


//FUNÇÃO DE ESCALA 
void Scale(GLfloat scalex, GLfloat scaley, GLfloat scalez, GLfloat *Transf_Mat){
    
    GLfloat scale_matrix[16] = {scalex,     0.0, 0.0, 0.0,
                                    0.0, scaley, 0.0, 0.0,
                                    0.0,     0.0, scalez, 0.0,
                                    0.0,     0.0, 0.0, 1.0};

    MatrixMultiply(scale_matrix, Transf_Mat, Transf_Mat);
}


//FUNÇÃO DE ROTAÇÃO EM RELAÇÃO AO EIXO Z
void RotateZaxis(GLfloat angle, GLfloat *Transf_Mat){

    GLfloat rotation_matrix[16] = { cos(angle), sin(angle), 0.0, 0.0,
                                   -sin(angle), cos(angle), 0.0, 0.0,
                                           0.0,        0.0, 1.0, 0.0,
                                           0.0,        0.0, 0.0, 1.0};

    MatrixMultiply(rotation_matrix, Transf_Mat, Transf_Mat);
}


//FUNÇÃO DE ROTAÇÃO EM RELAÇÃO AO EIXO Y
void RotateYaxis(GLfloat angle, GLfloat *Transf_Mat){

    GLfloat rotation_matrix[16] = { cos(angle), 0.0, sin(angle), 0.0,
                                           0.0, 1.0,        0.0, 0.0,
                                   -sin(angle), 0.0, cos(angle), 0.0,
                                           0.0, 0.0,        0.0, 1.0};

    MatrixMultiply(rotation_matrix, Transf_Mat, Transf_Mat);
}


//FUNÇÃO DE ROTAÇÃO EM RELAÇÃO AO EIXO X
void RotateXaxis(GLfloat angle, GLfloat *Transf_Mat){

    GLfloat rotation_matrix[16] = {1.0,         0.0,        0.0, 0.0,
                                   0.0,  cos(angle), sin(angle), 0.0,
                                   0.0, -sin(angle), cos(angle), 0.0,
                                   0.0,         0.0,        0.0, 1.0};
                                

    MatrixMultiply(rotation_matrix, Transf_Mat, Transf_Mat);
}

//FUNÇÃO QUE ROTACIONA UM OBJETO AO REDOR DO EIXO Y EM RELAÇÃO AO SEU CENTRO DE MASSA
void RelativeRotateYaxis(GLfloat angle, GLfloat *Transf_Mat, Vec3 point){

    Translate(-point.x, -point.y, -point.z, Transf_Mat);
    RotateYaxis(angle, Transf_Mat);
    Translate(point.x, point.y, point.z, Transf_Mat);

}

//FUNÇÃO QUE ROTACIONA UM OBJETO AO REDOR DO EIXO X EM RELAÇÃO AO SEU CENTRO DE MASSA
void RelativeRotateXaxis(GLfloat angle, GLfloat *Transf_Mat, Vec3 point){

    Translate(-point.x, -point.y, -point.z, Transf_Mat);
    RotateXaxis(angle, Transf_Mat);
    Translate(point.x, point.y, point.z, Transf_Mat);
  
}

//FUNÇÃO QUE ROTACIONA UM OBJETO AO REDOR DO EIXO Z EM RELAÇÃO AO SEU CENTRO DE MASSA
void RelativeRotateZaxis(GLfloat angle, GLfloat *Transf_Mat, Vec3 point){

    Translate(-point.x, -point.y, -point.z, Transf_Mat);
    RotateZaxis(angle, Transf_Mat);
    Translate(point.x, point.y, point.z, Transf_Mat);

}

//FUNÇÃO QUE AUMENTA O TAMANHO DE UM OBJETO EM RELAÇÃO AO SEU CENTRO DE MASSA
void RelativeScale(GLfloat scalex, GLfloat scaley, GLfloat scalez, GLfloat *Transf_Mat, Vec3 point){

    Translate(-point.x, -point.y, -point.z, Transf_Mat);
    Scale(scalex, scaley, scalez, Transf_Mat);
    Translate(point.x, point.y, point.z, Transf_Mat);

}

//FUNÇÃO QUE TRANSFORMA A POSIÇÃO DE UM OBJETO EM RELAÇÃO AO SEU CENTRO DE MASSA
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



//FUNÇÃO QUE RETORNA UMA MATRIZ IDENTIDADE
GLfloat *IdentityMatrix(){
    GLfloat *I;
    I = (GLfloat *) malloc(16*sizeof(GLfloat));
    I[0] =  1.0; I[1] =  0.0; I[2] =  0.0; I[3] =  0.0;
    I[4] =  0.0; I[5] =  1.0; I[6] =  0.0; I[7] =  0.0;
    I[8] =  0.0; I[9] =  0.0; I[10] = 1.0; I[11] = 0.0;
    I[12] = 0.0; I[13] = 0.0; I[14] = 0.0; I[15] = 1.0;
    return I;
}



//FUNÇÃO QUE TRADUZ UMA MATRIZ DE COORDENADAS EM UMA MATRIZ ARRAY
GLfloat *CoordMatrix(Vec3 array){
    GLfloat *C;
    C = (GLfloat *) malloc(16*sizeof(GLfloat));
    C[0] =  array.x; C[1] = 0.0; C[2] = 0.0; C[3] =  0.0;
    C[4] =  array.y; C[5] = 0.0; C[6] = 0.0; C[7] =  0.0;
    C[8] =  array.z; C[9] = 0.0; C[10] =0.0; C[11] = 0.0;
    C[12] =     1.0; C[13] =0.0; C[14] =0.0; C[15] = 0.0;
    return C;
}

//FUNÇÃO QUE TRADUZ A MATRIZ DO GLM EM UMA MATRIZ DE FORMATO ARRAY
GLfloat *mat_from_glm(vec4 *array){
    GLfloat *C;
    C = (GLfloat *) malloc(16*sizeof(GLfloat));
    C[0]  =  array[0][0]; C[1] =  array[0][1]; C[2]  = array[0][2]; C[3] =  array[0][3];
    C[4]  =  array[1][0]; C[5] =  array[1][1]; C[6]  = array[1][2]; C[7] =  array[1][3];
    C[8]  =  array[2][0]; C[9] =  array[2][1]; C[10] = array[2][2]; C[11] = array[2][3];
    C[12] =  array[3][0]; C[13] = array[3][1]; C[14] = array[3][2]; C[15] = array[3][3];
    return C;
}


//FUNÇÃO QUE CALCULA O CENTRO DE MASSA DE UM ARRAY DE VERTICES
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


//FUNÇÃO QUE ATUALIZA O CENTRO DE MASSA
Vec3 RelativeCenterOfMass(Vec3 center0, GLfloat *Ref_Matrix){

    Vec3 center = center0; 
    center.x += Ref_Matrix[0];
    center.y += Ref_Matrix[4];
    center.z += Ref_Matrix[8];

    return center;
}





//FUNÇÃO QUE IMPRIME UMA MATRIZ
void printMatrix(GLfloat *array){
    for(int i = 0; i < 4 ; i++){
            printf("%f %f %f %f\n\n", array[4*i + 0], array[4*i + 1], array[4*i + 2], array[4*i + 3]);
    }
}






//FUNÇÃO DE GERAÇÃO DA MATRIZ VIEW - FEITA ANTES DO GLM
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



//FUNÇÃO QUE TRANSFORMA UM VEC3 EM SUA RESPECTIVA MATRIZ EM COORDENADAS HOMOGENEAS
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




//FUNÇÃO QUE LÊ UM OBJETO DE UM .OBJ DE MANEIRA GERAL
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
            out_vert[3*i + k] = verti[j];
        }
    }
    // printf("b\n");

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

    Obj->model_matrix = NULL;
    Obj->Reference_Matrix = NULL;

    Obj->angle = 0.0;
    Obj->texture_info.color = DefineColor(255.0, 0.0, 0.0, 1.0);
    Vec3 scale; scale.x = 1.0; scale.y = 1.0; scale.z = 1.0;

    Obj->scale = scale;
    Obj->starting_index = 0;
    Obj->texture_info.has_texture = 0;



    return(Obj);
}



//FUNÇÃO QUE LÊ UM OBJETO DE UM ARQUIVO DE FORMA RELATIVA EM RELAÇÃO AOS INDICES INICIAIS
Obj3D *Objs3DFromFile(char *vertex_path, unsigned int starting_vertex, unsigned int starting_texture, unsigned int starting_normals){

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

    char *name = (char *) malloc(size*sizeof(char));

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

        if(strcmp(line, "o") == 0){
            sscanf(line2, "%s\n", name);
        }
        
        

        else if(strcmp(line, "v") == 0){
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
            n++;
            // printf("%f %f %f\n", norm[n].x, norm[n].y, norm[n].z);

 
        }
        else if ( strcmp(line, "f" ) == 0 ){ //Se for indice das faces
            sscanf(line2, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &face.tri[0], &face.tex[0], &face.nor[0],
                                                          &face.tri[1], &face.tex[1], &face.nor[1], 
                                                          &face.tri[2], &face.tex[2], &face.nor[2]);
            // printf("%d %d %d\n", face.nor[0], face.nor[1], face.nor[2]);
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
            j = fac[i].tri[k] -1 - starting_vertex;
            out_vert[3*i + k] = verti[j];
        }
    }
    // printf("b\n");

    Vec3 *out_norm;
    out_norm = (Vec3 *) malloc(3*numb_fac*sizeof(Vec3));
    if(out_norm == NULL){
        printf("Cant malloc out_norm!\n");
        free(fac);
        free(out_vert);
        return NULL;
    }

    j = 0;
    // printf("%d\n", starting_normals);
    for(unsigned int i = 0; i < numb_fac; i++){
        for(int k = 0; k < 3 ; k++){  
            j = fac[i].nor[k] -1 - starting_normals;
            // printf("%d\n", n);
            // printf("%d %f %f %f\n", j, norm[j].x, norm[j].y, norm[j].z);
            out_norm[3*i + k] = norm[j];
            // printf("%f %f %f\n", out_norm[3*i + k].x, out_norm[3*i + k].y, out_norm[3*i + k].z);
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
            j = fac[i].tex[k] - 1 - starting_texture;
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

    Obj->name = name;
    
    Obj->array   = out_vert;
    Obj->normals = out_norm;
    Obj->texture = out_text;

    Obj->numb_vertices = 3*numb_fac;
    Obj->center_of_mass = CenterOfMass(Obj->array, Obj->numb_vertices);

    Obj->doc_vertex = numb_vert;
    Obj->doc_normals = numb_norm;
    Obj->doc_texture = numb_text;

    Obj->model_matrix      = IdentityMatrix();
    Obj->Reference_Matrix  = IdentityMatrix();

    Obj->angle = 0.0;
    Obj->texture_info.color = DefineColor(255.0, 0.0, 0.0, 1.0);
    Vec3 scale; scale.x = 1.0; scale.y = 1.0; scale.z = 1.0;

    Obj->scale = scale;
    Obj->starting_index = starting_vertex;
    Obj->texture_info.has_texture = 0;
    Obj->texture_info.has_inside  = 0;

    Obj->normal_map.has_texture = 0;
    Obj->normal_map.has_inside = 0;
    Obj->normal_map.color = DefineColor(0.0, 255.0, 0.0, 1.0);



    return(Obj);
}






//FUNÇÃO QUE LÊ VÁRIOS OBJETOS DE UM ARQUIVO .OBJ
Scene *SceneFromFile(char *vertex_file, char *vertex_name, int width, int height){

    int size = 500;
    char vertex_path[size];
    strcpy(vertex_path, vertex_file);
    strcat(vertex_path, vertex_name);


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
  
                fprintf(file, "%s", lineaux);           
                
        }

        fclose(file);
    }

    fclose(raw);
   
    

    //Alocação de memória para a estrutura a ser retornada pela função
    Scene *scene = (Scene *) malloc(sizeof(Scene));


    scene->array_objs       = (Obj3D *) malloc(numb_objs*sizeof(Obj3D));
    scene->numb_vert        = (int *) malloc(numb_objs*sizeof(int));
    scene->starting_indices = (unsigned int *) malloc(numb_objs*sizeof(unsigned int));

    unsigned int vert = 0;
    unsigned int tex  = 0;
    unsigned int norm = 0;

    unsigned int total_vert = 0;



    if(scene->array_objs == NULL){
        printf("Could no malloc array_objs!\n");
        for (int i = 0; i < numb_objs; i++) remove(files[i]);
        for (int i = 0; i < numb_objs; i++) free(files[i]);
        free(scene);
        free(files);
        return NULL;
    }
    if(scene->numb_vert == NULL){
        printf("Could no malloc numb_vert!\n");
        free(scene->array_objs);
        free(scene);
        for (int i = 0; i < numb_objs; i++) remove(files[i]);
        for (int i = 0; i < numb_objs; i++) free(files[i]);
        free(files);
        return NULL;
    }

    if(scene->starting_indices == NULL){
        
        printf("Could no malloc starting_indices!\n");
        // free(&scene->numb_objs);
        free(scene->array_objs);
        free(scene->numb_vert);
        free(scene);
        for (int i = 0; i < numb_objs; i++) remove(files[i]);
        for (int i = 0; i < numb_objs; i++) free(files[i]);
        free(files);
        return NULL;
    }


    
    scene->array_objs[0] = *Objs3DFromFile(files[0], 0, 0, 0);
    
    vert += scene->array_objs[0].doc_vertex;
    norm += scene->array_objs[0].doc_normals;
    tex += scene->array_objs[0].doc_texture;

    scene->numb_vert[0]         = scene->array_objs[0].numb_vertices;
    scene->starting_indices[0]  = scene->array_objs[0].starting_index;

    total_vert += scene->array_objs[0].numb_vertices;
    

    for (int j = 1; j < numb_objs; j++){
 
        
        //Lê os objetos individualmente
        scene->array_objs[j]        = *Objs3DFromFile(files[j], vert, tex, norm);
                                                        

        vert += scene->array_objs[j].doc_vertex;
        norm += scene->array_objs[j].doc_normals;
        tex += scene->array_objs[j].doc_texture;

        if(&scene->array_objs[j] == NULL){
            printf("Could no extract obj!\n");
            free(scene->starting_indices);
            free(scene->array_objs);
            free(scene->numb_vert);
            free(scene);
            for (int i = 0; i < numb_objs; i++) remove(files[i]);
            for (int i = 0; i < numb_objs; i++) free(files[i]);
            free(files);
            return NULL;
        }


        
        scene->numb_vert[j]         = scene->array_objs[j].numb_vertices;
        scene->starting_indices[j]  = total_vert;
        scene->array_objs[j].starting_index = total_vert;


        total_vert += scene->array_objs[j].numb_vertices;

    }

    
    scene->numb_objs = numb_objs;

    scene->general_array = (Vec3 *) malloc(total_vert*sizeof(Vec3));
    scene->general_text = (Vec2 *) malloc(total_vert*sizeof(Vec2));
    scene->general_norm = (Vec3 *) malloc(total_vert*sizeof(Vec3));

    unsigned int iter_vert = 0;

    for(int i = 0; i < numb_objs; i++){
        for(unsigned int j = 0; j < scene->array_objs[i].numb_vertices; j++){
            scene->general_array[iter_vert + j] = scene->array_objs[i].array[j];
            scene->general_text[iter_vert + j] = scene->array_objs[i].texture[j];
            // printf("%d %f %f %f\n", i, scene->array_objs[i].normals[j].x, scene->array_objs[i].normals[j].y, scene->array_objs[i].normals[j].z);
            scene->general_norm[iter_vert + j] = scene->array_objs[i].normals[j];
            // printf("%d %f %f %f\n", i, scene->general_norm[iter_vert + j].x, scene->general_norm[iter_vert + j].y, scene->general_norm[iter_vert + j].z);

        }
        iter_vert += scene->array_objs[i].numb_vertices;
    }

    scene->total_vert = total_vert;
    scene->__width = width;
    scene->__height = height;


    //Deleta todos os arquivos auxiliares criados
    for (int i = 0; i < numb_objs; i++) remove(files[i]);

    //Libera a memora alocada para o array de strings
    for (int i = 0; i < numb_objs; i++) free(files[i]);

    //Libera memória do ponteiro em si (isso está certo?)
    free(files);


    return(scene);
}

//FUNÇÃO MORTA DE LEITURA DE TEXTURAS
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


Texture *CreateEmptyTexture(int ActiveTexture, int Min_Filter, int Mag_Filter, int Wrap_S, int Wrap_T, GLenum format, int width, int height){
        
    GLuint tex;

    glGenTextures(1, &tex);
    glActiveTexture(ActiveTexture);
    glBindTexture(GL_TEXTURE_2D, tex);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, Min_Filter);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, Mag_Filter);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, Wrap_S); 
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, Wrap_T);
    glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_FLOAT, NULL);


    Texture *texture = (Texture *) malloc(sizeof(Texture));
    texture->TexturePath = NULL;
    texture->texture_id = tex;
    texture->ActiveTexture = ActiveTexture;
    texture->has_inside = 0;
    texture->texture_inside_id = -1;
    texture->format = format;
    texture->color = DefineColor(255.0, 0.0, 0.0, 1.0);
    texture->width = width;
    texture->height = height;

    return texture;
}




#ifndef BASIC
//FUNÇÃO PARA CARREGAR IMAGENS EM TEXTURAS ASSOCIADAS A UM OBJETO
int TextureFromFile(char *texture_path, Obj3D *obj){

    SDL_Surface *s;
    if(SDL_Init(SDL_INIT_VIDEO) < 0){
        printf("SDL could not initialize: %s\n", SDL_GetError());
        obj->texture_info.has_texture = 0;
        return 0;
    }
    else{
        int imgFlags = IMG_INIT_PNG;
        if( !(IMG_Init(imgFlags) & imgFlags)){
            printf("IMG could not initialize: %s\n", IMG_GetError());
            obj->texture_info.has_texture = 0;
            SDL_Quit();
            return 0;
        }
        else{
            s = IMG_Load(texture_path);
            if(s == NULL){
                printf("Unable to extract texture!");
                obj->texture_info.has_texture = 0;
                IMG_Quit();
                SDL_Quit();
                return 0;
            }
            else{
                flip_surface(s); //Função para ajustar a imagem, que estava originalmente vindo de ponta cabeça
                obj->texture_info.has_texture = 1;

                glGenTextures(1, &obj->texture_info.texture_id);
                glBindTexture(GL_TEXTURE_2D, obj->texture_info.texture_id); //Binda a textura na gpu
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST); 
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


int normalMapFromFile(char *texture_path, Obj3D *obj, int Active_texture_channel){

    SDL_Surface *s;
    if(SDL_Init(SDL_INIT_VIDEO) < 0){
        printf("SDL could not initialize: %s\n", SDL_GetError());
        obj->normal_map.has_texture = 0;
        return 0;
    }
    else{
        int imgFlags = IMG_INIT_PNG;
        if( !(IMG_Init(imgFlags) & imgFlags)){
            printf("IMG could not initialize: %s\n", IMG_GetError());
            obj->normal_map.has_texture = 0;
            SDL_Quit();
            return 0;
        }
        else{
            s = IMG_Load(texture_path);
            if(s == NULL){
                printf("Unable to extract texture!");
                obj->normal_map.has_texture= 0;
                IMG_Quit();
                SDL_Quit();
                return 0;
            }
            else{
                flip_surface(s); //Função para ajustar a imagem, que estava originalmente vindo de ponta cabeça
                obj->normal_map.has_texture = 1;

                glGenTextures(1, &obj->normal_map.texture_id);
                glActiveTexture(Active_texture_channel); //Ativando canal de textura do normal map
                glBindTexture(GL_TEXTURE_2D, obj->normal_map.texture_id); //Binda a textura na gpu
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST); 
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        
                glTexImage2D(GL_TEXTURE_2D, 0, obj->normal_map.format, s->w, s->h, 0, obj->normal_map.format, GL_UNSIGNED_BYTE, s->pixels);

                // glActiveTexture(GL_TEXTURE0); //retornando ao canal de textura principal

                obj->normal_map.ActiveTexture = Active_texture_channel;

                SDL_FreeSurface(s);
                IMG_Quit();
                SDL_Quit();

                
                /*CÁLCULO DOS VETORES TANGENTE E BITANGENTE*/
                //COM A GRANDE AJUDA DE https://learnopengl.com/Advanced-Lighting/Normal-Mapping

                //CADA ELEMENTO DESSE ARRAY VAI SER UM VETOR TANGENTE E BITANGENTE CORRESPONDENTE À UM TRIANGULO
                obj->tangent_vec = (Vec3 *) malloc((obj->numb_vertices)*sizeof(Vec3));
                obj->bitangent_vec = (Vec3 *) malloc((obj->numb_vertices)*sizeof(Vec3));

                for(int i = 0; i < obj->numb_vertices/3; i++){

                    Vec3 edge1, edge2;
                    Vec2 deltaUV1, deltaUV2;

                    edge1.x = obj->array[3*i + 1].x - obj->array[3*i].x;
                    edge1.y = obj->array[3*i + 1].y - obj->array[3*i].y;
                    edge1.z = obj->array[3*i + 1].z - obj->array[3*i].z;

                    edge2.x = obj->array[3*i + 2].x - obj->array[3*i].x;
                    edge2.y = obj->array[3*i + 2].y - obj->array[3*i].y;
                    edge2.z = obj->array[3*i + 2].z - obj->array[3*i].z; 

                    deltaUV1.x = obj->texture[3*i + 1].x - obj->texture[3*i].x;
                    deltaUV1.y = obj->texture[3*i + 1].y - obj->texture[3*i].y;

                    deltaUV2.x = obj->texture[3*i + 2].x - obj->texture[3*i].x;
                    deltaUV2.y = obj->texture[3*i + 2].y - obj->texture[3*i].y;

                    float f = 1.0/(deltaUV1.x * deltaUV2.y - deltaUV2.x * deltaUV1.y);

                    

                    obj->tangent_vec[3*i + 0].x = f * (deltaUV2.y * edge1.x - deltaUV1.y * edge2.x);
                    obj->tangent_vec[3*i + 0].y = f * (deltaUV2.y * edge1.y - deltaUV1.y * edge2.y);
                    obj->tangent_vec[3*i + 0].z = f * (deltaUV2.y * edge1.z - deltaUV1.y * edge2.z);
                    obj->tangent_vec[3*i + 1].x = f * (deltaUV2.y * edge1.x - deltaUV1.y * edge2.x);
                    obj->tangent_vec[3*i + 1].y = f * (deltaUV2.y * edge1.y - deltaUV1.y * edge2.y);
                    obj->tangent_vec[3*i + 1].z = f * (deltaUV2.y * edge1.z - deltaUV1.y * edge2.z);
                    obj->tangent_vec[3*i + 2].x = f * (deltaUV2.y * edge1.x - deltaUV1.y * edge2.x);
                    obj->tangent_vec[3*i + 2].y = f * (deltaUV2.y * edge1.y - deltaUV1.y * edge2.y);
                    obj->tangent_vec[3*i + 2].z = f * (deltaUV2.y * edge1.z - deltaUV1.y * edge2.z);

                    obj->bitangent_vec[3*i + 0].x = f * (-deltaUV2.x * edge1.x + deltaUV1.x * edge2.x);
                    obj->bitangent_vec[3*i + 0].y = f * (-deltaUV2.x * edge1.y + deltaUV1.x * edge2.y);
                    obj->bitangent_vec[3*i + 0].z = f * (-deltaUV2.x * edge1.z + deltaUV1.x * edge2.z);  
                    obj->bitangent_vec[3*i + 1].x = f * (-deltaUV2.x * edge1.x + deltaUV1.x * edge2.x);
                    obj->bitangent_vec[3*i + 1].y = f * (-deltaUV2.x * edge1.y + deltaUV1.x * edge2.y);
                    obj->bitangent_vec[3*i + 1].z = f * (-deltaUV2.x * edge1.z + deltaUV1.x * edge2.z);   
                    obj->bitangent_vec[3*i + 2].x = f * (-deltaUV2.x * edge1.x + deltaUV1.x * edge2.x);
                    obj->bitangent_vec[3*i + 2].y = f * (-deltaUV2.x * edge1.y + deltaUV1.x * edge2.y);
                    obj->bitangent_vec[3*i + 2].z = f * (-deltaUV2.x * edge1.z + deltaUV1.x * edge2.z);                     
                }

                /*TÉRMINO DO CÁLCULO DOS VETORES TANGENTE E BITANGENTE*/



                return 1;
            }
        }
    }
}




//FUNÇÃO PARA RENDERIZAR TEXTURA NÃO ASSOCIADA NECESSARIAMENTE A UM OBJETO
GLuint LoneTextureFromFile(char *texture_path, GLint format){

    SDL_Surface *s;
    if(SDL_Init(SDL_INIT_VIDEO) < 0){
        printf("SDL could not initialize: %s\n", SDL_GetError());
        return 0;
    }
    else{
        int imgFlags = IMG_INIT_PNG;
        if( !(IMG_Init(imgFlags) & imgFlags)){
            printf("IMG could not initialize: %s\n", IMG_GetError());
            SDL_Quit();
            return 0;
        }
        else{
            s = IMG_Load(texture_path);
            if(s == NULL){
                printf("Unable to extract texture!");
                IMG_Quit();
                SDL_Quit();
                return 0;
            }
            else{
                flip_surface(s); 

                GLuint a = 0;
                glGenTextures(1, &a);
                glBindTexture(GL_TEXTURE_2D, a); //Binda a textura na gpu
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); //Filtros de repeticao: GL_REPEAT -> repeticao simples
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST); //Filtros de maginificao e minificacao: GL_LINEAR
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        
                glTexImage2D(GL_TEXTURE_2D, 0, format, s->w, s->h, 0, format, GL_UNSIGNED_BYTE, s->pixels);

                SDL_FreeSurface(s);
                IMG_Quit();
                SDL_Quit();
                return a;
            }
        }
    }
}




//FUNÇÃO PARA INVERTER VERTICALMENTE UMA IMAGEM
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
#endif



GLuint GenerateDepthTexture(){
    const GLuint SHADOW_WIDTH = 1024, SHADOW_HEIGHT = 1024;

    GLuint DepthMap;
    glGenTextures(1, &DepthMap);
    glBindTexture(GL_TEXTURE_2D, DepthMap);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER); 
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, SHADOW_WIDTH, SHADOW_HEIGHT, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);

    return DepthMap;
}

//FUNÇÃO PARA MANDAR PARA GPU AS INFORMAÇÕES DAS MATRIZES DE TRANSFORMAÇÕES
void UpdateObj3D(Obj3D *Obj, Camera cam, GLint model, GLint view, GLint proj, Vec3 transl, Vec3 angles, Vec3 scale, int mode, int transform_check){
    if(transform_check){

        if(mode == 0){ //TRANSFORMAÇÕES EM RELAÇÃO AO MUNDO
            TransformObj3D(Obj, transl, angles, scale, model);
            glUniformMatrix4fv(model, 1, GL_TRUE, Obj->model_matrix);
            glUniformMatrix4fv(view, 1, GL_TRUE, cam.__view);
            glUniformMatrix4fv(proj, 1, GL_TRUE, cam.__projection);
        }

        else{         //TRANSFORMAÇÕES EM RELAÇÃO AO SEU CENTRO DE MASSA
            Scale(scale.x, scale.y, scale.z, Obj->model_matrix);
            RotateYaxis(angles.y, Obj->model_matrix);
            RotateXaxis(angles.x, Obj->model_matrix);
            RotateZaxis(angles.z, Obj->model_matrix);
            Translate(transl.x, transl.y, transl.z, Obj->model_matrix);

            glUniformMatrix4fv(model, 1, GL_TRUE, Obj->model_matrix);
            glUniformMatrix4fv(view, 1, GL_TRUE, cam.__view);
            glUniformMatrix4fv(proj, 1, GL_TRUE, cam.__projection);
        }
    }
    else{

        glUniformMatrix4fv(model, 1, GL_TRUE, Obj->model_matrix);
        glUniformMatrix4fv(view, 1, GL_TRUE, cam.__view);
        glUniformMatrix4fv(proj, 1, GL_TRUE, cam.__projection);

    }
}

void StaticUpdateObj3D(Obj3D *Obj, Camera cam, GLint model, GLint view, GLint proj){
    glUniformMatrix4fv(model, 1, GL_TRUE, Obj->model_matrix);
    glUniformMatrix4fv(view, 1, GL_TRUE, camView(&cam));
    glUniformMatrix4fv(proj, 1, GL_TRUE, camProj(&cam));
}

//FUNÇÃO PARA MANDAR PARA RENDERIZAR OS VERTICES E TEXTURAS DOS OBJETOS
void RenderObj3D(Obj3D Obj, GLint color, int is_inside){


    if(Obj.texture_info.has_texture){//SE O OBJETO TIVER TEXTURA
        if(Obj.texture_info.has_inside && is_inside){//SE O OBJETO ESTIVER NO INTERIOR E O OBJETO TIVER TEXTURA INTERIOR
            glBindTexture(GL_TEXTURE_2D, Obj.texture_info.texture_inside_id);
            for(int i = 0; i < Obj.numb_vertices/3; i++){
                glDrawArrays(GL_TRIANGLES, 3*i + Obj.starting_index, 3);
            }
        }
        else{                       //RENDERIZAÇÃO NORMAL
            glBindTexture(GL_TEXTURE_2D, Obj.texture_info.texture_id);
            for(int i = 0; i < Obj.numb_vertices/3; i++){
                glDrawArrays(GL_TRIANGLES, 3*i + Obj.starting_index, 3);
            }
        }
    }

    else{                           //SE O OBJETO NÃO TIVER TEXTURA, RENDERIZA COM UAM COR BASE
        glUniform4f(color, Obj.texture_info.color.r, Obj.texture_info.color.g, Obj.texture_info.color.b, Obj.texture_info.color.w);
        for(int i = 0; i < Obj.numb_vertices/3; i++){
            glDrawArrays(GL_TRIANGLES, 3*i + Obj.starting_index, 3);
        }
    }
}



//FUNÇÃO PARA TESTE DO SHADOWMAP


//FUNÇÃO DE ENVIO DOS COEFICIENTES DE ILUMINAÇÃO PARA A GPU
void IlumObj3D(Obj3D Obj, GLint Ka, GLint Kd, GLint Ks, GLint ns, vec3 cameraPos, GLint loc_view_pos, int InsideCheck){

    glUniform3f(loc_view_pos, cameraPos[0], cameraPos[1], cameraPos[2]);

    if(InsideCheck){
        glUniform1f(Ka, Obj.in_material.Ka);
        glUniform1f(Kd, Obj.in_material.Kd);
        glUniform1f(Ks, Obj.in_material.Ks);
        glUniform1f(ns, Obj.in_material.ns);
    }
    else{
        glUniform1f(Ka, Obj.out_material.Ka);
        glUniform1f(Kd, Obj.out_material.Kd);
        glUniform1f(Ks, Obj.out_material.Ks);
        glUniform1f(ns, Obj.out_material.ns);
    }
}



//FUNÇÃO PARA ATUALIZAR O STATUS DAS MATRIZES VIEW E PROJECTION
void ViewUpdate(vec3 eye, vec3 center, vec3 up, float near, float far, float fov, float largura, float altura, Camera *cam){
    
    vec3 aux;

    aux[0] = center[0] + eye[0];
    aux[1] = center[1] + eye[1];
    aux[2] = center[2] + eye[2];

    defineProjectionCamera(cam, fov, eye, aux, up, near, far, largura, altura);
}



//FUNÇÃO PARA CHECAR SE A CAMERA ESTÁ DENTRO DE UM OBJETO COM FRONTEIRAS BEM DEFINIDAS
int Inside_Check(vec3 origin, vec3 boundarie, vec3 position){ //Função para verficiar se a camera esdtá dentro de algum lugar
    if(position[0] > origin[0] && position[0] < boundarie[0] &&
       position[1] > origin[1] && position[1] < boundarie[1] &&
       position[2] > origin[2] && position[2] < boundarie[2])
            return 1;
    else return 0;
}


//FUNÇÃO PARA IMPRIMIR OS OBJETOS DE UMA CENA E SEUS NOMES
void PrintScene(Scene scene){
    for(int i = 0; i < scene.numb_objs; i++)
        printf("%s\n", scene.array_objs[i].name);
}

int sceneWidth(Scene scene){
    return scene.__width;
}

int sceneHeight(Scene scene){
    return scene.__height;
}

void setSceneCam(Scene *scene, Camera cam){
    scene->sceneCam = cam;
}

void getLocationView3D(GLuint program, GLuint *loc_model, GLuint *loc_view, GLuint *loc_proj){
    *loc_model = glGetUniformLocation(program, "model");
    *loc_view = glGetUniformLocation(program, "view");
    *loc_proj = glGetUniformLocation(program, "projection");
}

void getLocationLightConstants(GLuint program, GLuint *Ka, GLuint *Kd, GLuint *Ks, GLuint *ns){
    *Ka = glGetUniformLocation(program, "Ka");
    *Kd = glGetUniformLocation(program, "Kd");
    *Ks = glGetUniformLocation(program, "Ks");
    *ns = glGetUniformLocation(program, "ns"); 
}


void shaderReorderScene(Scene *scene){
}

//FUNÇÃO PARA ATRIBUIR COEFICIENTES DE ILUMINAÇÃO A UM OBJETO
void DefineObj3DIlum(GLfloat Ka, GLfloat Kd, GLfloat Ks, GLfloat ns, Obj3D *obj){
    obj->out_material.Ka = Ka;
    obj->out_material.Kd = Kd;
    obj->out_material.Ks = Ks;
    obj->out_material.ns = ns;
}

//FUNÇÃO PARA ATRIBUIR COEFICIENTES DE ILUMINAÇÃO INTERNA A UM OBJETO
void DefineObj3DIlumIn(GLfloat Ka, GLfloat Kd, GLfloat Ks, GLfloat ns, Obj3D *obj){
    obj->in_material.Ka = Ka;
    obj->in_material.Kd = Kd;
    obj->in_material.Ks = Ks;
    obj->in_material.ns = ns;
}





/*CAMERA FUNCTIONS*/

void defineProjectionCamera(Camera *camera, float fov, vec3 eye, vec3 center, vec3 viewUp, float near, float far, float width, float height){

    camera->fov = fov;
    camera->near = near;
    camera->far = far;
    camera->width = width;
    camera->height = height;
    camera->bottom = 0.0;
    camera->top = 0.0;
    camera->left = 0.0;
    camera->right = 0.0;


    camera->eye[0] = eye[0];
    camera->eye[1] = eye[1];
    camera->eye[2] = eye[2];

    camera->center[0] = center[0];
    camera->center[1] = center[1];
    camera->center[2] = center[2];

    camera->viewUp[0] = viewUp[0];
    camera->viewUp[1] = viewUp[1];
    camera->viewUp[2] = viewUp[2];



    mat4 view;
    mat4 proj;

    glm_mat4_identity(view);
    glm_mat4_identity(proj);

    glm_lookat(eye, center, viewUp, view);
    glm_perspective(glm_rad(fov), width/height, near, far, proj);
    
    glm_mat4_transpose(view);
    glm_mat4_transpose(proj);

    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++){
            camera->__view[4*i + j] = view[i][j];
            camera->__projection[4*i + j] = proj[i][j];
        }
    }
}

void defineOrthogonalCamera(Camera *camera, vec3 eye, vec3 center, vec3 viewUp, float near, float far, float left, float right, float bottom, float top){

    camera->fov = 0.0;
    camera->near = near;
    camera->far = far;
    camera->width = 0.0;
    camera->height = 0.0;
    camera->bottom = bottom;
    camera->top = top;
    camera->left = left;
    camera->right = right;


    camera->eye[0] = eye[0];
    camera->eye[1] = eye[1];
    camera->eye[2] = eye[2];

    camera->center[0] = center[0];
    camera->center[1] = center[1];
    camera->center[2] = center[2];

    camera->viewUp[0] = viewUp[0];
    camera->viewUp[1] = viewUp[1];
    camera->viewUp[2] = viewUp[2];



    mat4 view;
    mat4 ortho;

    glm_mat4_identity(view);
    glm_mat4_identity(ortho);

    glm_lookat(eye, center, viewUp, view);
    glm_ortho(left, right, bottom, top, near, far, ortho);
    
    /*glm works with the transposed matrix, so we got to transpose it back*/
    glm_mat4_transpose(view);
    glm_mat4_transpose(ortho);

    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++){
            camera->__view[4*i + j] = view[i][j];
            camera->__projection[4*i + j] = ortho[i][j];
        }
    }
}



float *LightSpaceMatrix(Camera lightCam){
    float *lsm = IdentityMatrix();

    MatrixMultiply(lightCam.__projection, lightCam.__view, lsm);

    return lsm;
}

float *camView(Camera *cam){
    return cam->__view;
}

float *camProj(Camera *cam){
    return cam->__projection;
}

void SetLightParams(DirectLight *light, vec3 light_pos, Color color, Camera lightCam, Texture DepthMap, GLuint DepthMapFBO){
    for(int i = 0; i < 3; i++)
        light->pos[i] = light_pos[i];
    
    light->color.r = color.r;
    light->color.g = color.g;
    light->color.b = color.b;
    light->color.w = color.w;

    light->lightCam = lightCam;

    float *lsm = LightSpaceMatrix(lightCam);

    for(int i = 0; i < 16; i++){
        light->__lightSpaceMatrix[i] = lsm[i];
    }

    free(lsm);

    light->__depthMap = DepthMap;
    light->__depthMapFBO = DepthMapFBO;
}



GLuint GetDirectDepthMapFBO(DirectLight light){
    return light.__depthMapFBO;
}

Texture GetDirectDepthMap(DirectLight light){
    return light.__depthMap;
}



GLuint DepthMapFrameBufferObject(Texture DepthMap){
    /*FUNCTION TO SETUP A DEPTH FRAMEBUFFER*/

    GLuint DepthMapFBO;
    glGenFramebuffers(1, &DepthMapFBO);
    glClear(GL_DEPTH_BUFFER_BIT);
    glBindFramebuffer(GL_FRAMEBUFFER, DepthMapFBO);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, DepthMap.texture_id, 0);
    glDrawBuffer(GL_NONE);
    glReadBuffer(GL_NONE);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    return DepthMapFBO;
}




void SendLightNumb(GLuint loc_numbLights, int numb_lights){
    glUniform1i(loc_numbLights, numb_lights);
}



void SendLight(DirectLight light){
    glUniform3f(light.loc_lightPos, light.pos[0], light.pos[1], light.pos[2]);
    glUniform3f(light.loc_lightColor, light.color.r, light.color.g, light.color.b);
    glUniformMatrix4fv(light.loc_lightSpaceMatrix, 1, GL_TRUE, light.__lightSpaceMatrix);
}


void SendLights(GLuint *loc_lights, GLuint *loc_lightsColor, GLuint loc_lightSpaceMatrix, DirectLight *lights, int numb_lights){
    for(int i = 0; i < numb_lights; i++) 
        SendLight(lights[i]);
}


void ShadowUpdate(Scene *scene, DirectLight light, int inside_check){
    glViewport(0, 0, light.__depthMap.width, light.__depthMap.height);
    glBindFramebuffer(GL_FRAMEBUFFER, light.__depthMapFBO);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glActiveTexture(GL_TEXTURE0);
    for(int i = 0; i < scene->numb_objs; i++){
        StaticUpdateObj3D(&scene->array_objs[i], light.lightCam, scene->loc_model, scene->loc_view, scene->loc_proj);
        RenderObj3D(scene->array_objs[i], scene->loc_color, inside_check);
    }
}

void getLocationLightParams(GLuint program, GLuint *loc_lightPos, GLuint *loc_lightColor, GLuint *loc_lightSpaceMatrix){
    *loc_lightPos = glGetUniformLocation(program, "lightPos");
    *loc_lightColor = glGetUniformLocation(program, "lightColor");
    *loc_lightSpaceMatrix = glGetUniformLocation(program, "lightSpaceMatrix");
}




void GLSLattachShader(GLuint program, Shader shader){
    glAttachShader(program, shader.vertex);
    glAttachShader(program, shader.fragment);

    glLinkProgram(program);
}



void debugScene(Scene s){

    printf("vertices:\n");
    for(int i = 0; i < s.total_vert; i++){
        printf("%0.3f, %0.3f, %0.3f\n", s.general_array[i].x, s.general_array[i].y, s.general_array[i].z);
    }

    printf("\n");

    printf("texture vertices:\n");
    for(int i = 0; i < s.total_vert; i++){
        printf("%0.3f, %0.3f\n", s.general_text[i].x, s.general_text[i].y);
    }

    printf("\n");

    printf("normals:\n");
    for(int i = 0; i < s.total_vert; i++){
        printf("%0.3f, %0.3f, %0.3f\n", s.general_norm[i].x, s.general_norm[i].y, s.general_norm[i].z);
    }
}


void Quad(vec3 *quad){


    quad[0][0] = -1.0; quad[0][1] = -1.0; quad[0][2] = 0.0;
    quad[1][0] = -1.0; quad[1][1] = 1.0; quad[1][2] = 0.0;
    quad[2][0] = 1.0; quad[2][1] = -1.0; quad[2][2] = 0.0;
    quad[3][0] = 1.0; quad[3][1] = 1.0; quad[3][2] = 0.0;

}

void blendlim(float *blend){
    if(*blend < 0.0) *blend = 0.0;
    else if(*blend > 1.0) *blend = 1.0;
}

void defvec3(float *array, float x, float y, float z){
    array[0] = x; array[1] = y; array[2] = z;
}