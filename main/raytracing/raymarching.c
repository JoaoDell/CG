#include <stdio.h>
#include <stdlib.h>
#define BASIC
#include "../../include/GLib.h"
#include <GL/glew.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <cglm/cglm.h>


void GLSLCompileRMShader(Shader *shader){
    
    const GLchar *vert_shader = "attribute vec3 position;\n"

                                "varying vec3 out_pos;\n"

                                "void main(){\n"
                                    "out_pos = position;\n"
                                    "gl_Position = vec4(position, 1.0);\n"
                                "}\n";

    const GLchar *frag_shader = "struct sphere {\n"
                                    "vec3 pos;\n"
                                    "float radius;\n"
                                    "vec3 color;\n"
                                "};\n"

                                "struct light {\n"
                                    "vec3 lightPos;\n"
                                    "vec3 lightColor;\n"
                                    "vec3 ambientColor;\n"
                                "};\n"

                                "const float value  = 1.0;\n"
                                "const int MAX_STEPS = 256;\n"
                                "const float MAX_DIST = 500.0;\n"
                                "const float EPSILON = 0.001;\n"
                                
                                "uniform vec2 res;\n"
                                "uniform float time;\n"
                                "uniform mat4 view;\n"
                                "uniform vec3 eye;\n"

                                "varying vec3 out_pos;\n"

                                "sphere s;\n"
                                "light l;\n"

                            

                                "float sphereSDF(vec3 p, sphere sp){\n"
                                    "return length(p - sp.pos) - sp.radius;\n"
                                "}\n"

                                "float cubeSDF(vec3 p, float y){\n"
                                    // If d.x < 0, then -1 < p.x < 1, and same logic applies to p.y, p.z
                                    // So if all components of d are negative, then p is inside the unit cube
                                    "vec3 d = abs(p) - vec3(y, y, y);\n"

                                    // Assuming p is inside the cube, how far is it from the surface?
                                    // Result will be negative or zero.
                                    "float insideDistance = min(max(d.x, max(d.y, d.z)), 0.0);\n"

                                    // Assuming p is outside the cube, how far is it from the surface?
                                    // Result will be positive or zero.
                                    "float outsideDistance = length(max(d, 0.0));\n"

                                    "return insideDistance + outsideDistance;\n"
                                "}\n"

                                "float surfaceSDF(vec3 p, float y){\n"
                                    "return max(cubeSDF(p, y), sphereSDF(p, s));\n"
                                "}\n"



                                "vec3 cubeNormals(vec3 p, float y){\n"
                                    "return normalize(vec3( cubeSDF(vec3(p.x + EPSILON, p.y, p.z), y) - cubeSDF(vec3(p.x - EPSILON, p.y, p.z), y),\n"
                                                           "cubeSDF(vec3(p.x, p.y + EPSILON, p.z), y) - cubeSDF(vec3(p.x, p.y - EPSILON, p.z), y),\n"
                                                           "cubeSDF(vec3(p.x, p.y, p.z + EPSILON), y) - cubeSDF(vec3(p.x, p.y, p.z - EPSILON), y)));\n" 
                                "}\n"

                                "vec3 surfaceNormals(vec3 p, float y){\n"
                                    "return normalize(vec3( surfaceSDF(vec3(p.x + EPSILON, p.y, p.z), y) - surfaceSDF(vec3(p.x - EPSILON, p.y, p.z), y),\n"
                                                           "surfaceSDF(vec3(p.x, p.y + EPSILON, p.z), y) - surfaceSDF(vec3(p.x, p.y - EPSILON, p.z), y),\n"
                                                           "surfaceSDF(vec3(p.x, p.y, p.z + EPSILON), y) - surfaceSDF(vec3(p.x, p.y, p.z - EPSILON), y)));\n" 
                                "}\n"

                                "vec3 sphereNormals(vec3 p, sphere sp){\n"
                                    "return normalize(vec3( sphereSDF(vec3(p.x + EPSILON, p.y, p.z), sp) - sphereSDF(vec3(p.x - EPSILON, p.y, p.z), sp),\n"
                                                           "sphereSDF(vec3(p.x, p.y + EPSILON, p.z), sp) - sphereSDF(vec3(p.x, p.y - EPSILON, p.z), sp),\n"
                                                           "sphereSDF(vec3(p.x, p.y, p.z + EPSILON), sp) - sphereSDF(vec3(p.x, p.y, p.z - EPSILON), sp)));\n" 
                                "}\n"






                                "vec3 spherePhong(vec3 p, vec3 camPos, sphere sp, light li){\n"
                                    "float Ka = 1.0, Kd = 1.0, Ks = 1.0, ns = 0.6;\n"

                                    //Cálculo das normals
                                    "vec3 norm = sphereNormals(p, sp);\n"

                                    /*PHONG*/
                                    "vec3 ambient = Ka*(0.7*li.ambientColor + 1.3*li.lightColor) / 2.0;\n" 


                                    //Calculo da luz difusa
                                    "vec3 lightDir = normalize(li.lightPos - p);\n" //Direção da luz
                                    "float Diff = max(dot(norm, lightDir), 0.0);\n" //Termo de intensidade de luz em uma superficie
                                    "vec3 diffuse = Kd*Diff*li.lightColor;\n"


                                    //Cálculo da luz especular
                                    "vec3 viewDir = normalize(camPos - p);\n" // direcao do observador/camera
                                    "vec3 reflectDir = normalize(reflect(-lightDir, norm));\n" // direcao da reflexao
                                    "float spec = pow(max(dot(viewDir, reflectDir), 0.0), ns);\n"
                                    "vec3 specular = Ks*spec*li.lightColor;\n"

                                    "return (ambient + diffuse + specular)*sp.color;\n"
                                    /*PHONG*/

                                "}\n"

                                "vec3 cubePhong(vec3 p, vec3 camPos, float y, light li){\n"
                                    "float Ka = 1.0, Kd = 1.0, Ks = 1.0, ns = 0.6;\n"

                                    //Cálculo das normals
                                    "vec3 norm = cubeNormals(p, y);\n"

                                    /*PHONG*/
                                    "vec3 ambient = Ka*(0.7*li.ambientColor + 1.3*li.lightColor) / 2.0;\n" 


                                    //Calculo da luz difusa
                                    "vec3 lightDir = normalize(li.lightPos - p);\n" //Direção da luz
                                    "float Diff = max(dot(norm, lightDir), 0.0);\n" //Termo de intensidade de luz em uma superficie
                                    "vec3 diffuse = Kd*Diff*li.lightColor;\n"


                                    //Cálculo da luz especular
                                    "vec3 viewDir = normalize(camPos - p);\n" // direcao do observador/camera
                                    "vec3 reflectDir = normalize(reflect(-lightDir, norm));\n" // direcao da reflexao
                                    "float spec = pow(max(dot(viewDir, reflectDir), 0.0), ns);\n"
                                    "vec3 specular = Ks*spec*li.lightColor;\n"

                                    "return (ambient + diffuse + specular);\n"
                                    /*PHONG*/

                                "}\n"

                                "vec3 surfacePhong(vec3 p, vec3 camPos, float y, light li){\n"
                                    "float Ka = 1.0, Kd = 1.0, Ks = 1.0, ns = 0.6;\n"

                                    //Cálculo das normals
                                    "vec3 norm = surfaceNormals(p, y);\n"

                                    /*PHONG*/
                                    "vec3 ambient = Ka*(0.7*li.ambientColor + 1.3*li.lightColor) / 2.0;\n" 


                                    //Calculo da luz difusa
                                    "vec3 lightDir = normalize(li.lightPos - p);\n" //Direção da luz
                                    "float Diff = max(dot(norm, lightDir), 0.0);\n" //Termo de intensidade de luz em uma superficie
                                    "vec3 diffuse = Kd*Diff*li.lightColor;\n"


                                    //Cálculo da luz especular
                                    "vec3 viewDir = normalize(camPos - p);\n" // direcao do observador/camera
                                    "vec3 reflectDir = normalize(reflect(-lightDir, norm));\n" // direcao da reflexao
                                    "float spec = pow(max(dot(viewDir, reflectDir), 0.0), ns);\n"
                                    "vec3 specular = Ks*spec*li.lightColor;\n"

                                    "return (ambient + diffuse + specular);\n"
                                    /*PHONG*/

                                "}\n"





                                "vec3 rayMarchingSphere(float start, vec3 eye, vec3 rayDir, sphere s, light li, vec3 color){\n"
                                    "float ds = start;\n" //quantidade a se andar ao longo da dire;áo do raio
                                    "vec3 p;\n"
                                    "for(int i = 0; i < MAX_STEPS; i++){\n"
                                        "p = eye + ds * rayDir;\n" //iterando pelo raio

                                        "float dist = sphereSDF(p, s);\n"
                                        "if(dist < EPSILON)\n"
                                            "return spherePhong(p, eye, s, li);\n"

                                        "ds += dist;\n" //se não atingiu nada, incrementa o passo com a distancia

                                        "if(ds >= MAX_DIST)\n"
                                            "return color;\n"
                                    "}\n"
                                    "return color;\n"

                                "}\n"
                                
                                "vec3 rayMarchingCube(float start, vec3 eye, vec3 rayDir, float y, light li, vec3 color){\n"
                                    "float ds = start;\n" //quantidade a se andar ao longo da dire;áo do raio
                                    "vec3 p;\n"
                                    "for(int i = 0; i < MAX_STEPS; i++){\n"
                                        "p = eye + ds * rayDir;\n" //iterando pelo raio

                                        "float dist = cubeSDF(p, y);\n"
                                        "if(dist < EPSILON)\n"
                                            "return cubePhong(p, eye, y, li);\n"

                                        "ds += dist;\n" //se não atingiu nada, incrementa o passo com a distancia

                                        "if(ds >= MAX_DIST)\n"
                                            "return color;\n"
                                    "}\n"
                                    "return color;\n"

                                "}\n"

                                "vec3 rayMarchingSurface(float start, vec3 eye, vec3 rayDir, float y, light li, vec3 color){\n"
                                    "float ds = start;\n" //quantidade a se andar ao longo da dire;áo do raio
                                    "vec3 p;\n"
                                    "for(int i = 0; i < MAX_STEPS; i++){\n"
                                        "p = eye + ds * rayDir;\n" //iterando pelo raio

                                        "float dist = surfaceSDF(p, y);\n"
                                        "if(dist < EPSILON)\n"
                                            "return surfacePhong(p, eye, y, li);\n"

                                        "ds += dist;\n" //se não atingiu nada, incrementa o passo com a distancia

                                        "if(ds >= MAX_DIST)\n"
                                            "return color;\n"
                                    "}\n"
                                    "return color;\n"

                                "}\n"


                                "mat4 viewMatrix(vec3 eye, vec3 center, vec3 up){\n"
	                                "vec3 f = normalize(center - eye);\n"
	                                "vec3 s = normalize(cross(f, up));\n"
	                                "vec3 u = cross(s, f);\n"
	                                "return mat4(\n"
		                                "vec4(s, 0.0),\n"
		                                "vec4(u, 0.0),\n"
                                        "vec4(-f, 0.0),\n"
                                        "vec4(0.0, 0.0, 0.0, 1)\n"
                                    ");\n"
                                "}\n"

                                "vec3 rayDirection(float FOV, vec2 resolution, vec2 fragCoord){\n"
                                    "vec2 uv = fragCoord - resolution / 2.0;\n"
                                    "float z = resolution.y / tan( radians(FOV) / 2.0 );\n"
                                    "return normalize(vec3(uv, -z));\n"
                                "}\n"


                                "void main(){\n"
                                
                                    "vec3 camPos = eye;\n"
                                    "vec2 uv = out_pos.xy * res / res.y;\n" //Enlargando o sistema de coordenadas
                                    "float z = res.y / tan( radians(45.0) / 2.0 )  / res.y;\n"
                                    "vec3 rayDir = normalize(vec3(uv, z));\n"
                                    // "vec3 rayDir = rayDirection(45.0, res, out_pos.xy);\n"

                                    "l.lightPos = vec3(sin(time), 1.0, cos(time));\n"
                                    "l.lightColor = vec3(1.0, 0.7, 0.2);\n"
                                    "l.ambientColor = vec3(0.9, 0.7, 1.0) - vec3(0.2);\n"


                                    "s.pos = vec3(0.0, 0.0, 0.0);\n"
                                    "s.radius = 1.0;\n"
                                    "s.color = vec3(1.0, 0.6, 0.9);\n"

                                    "mat4 view0 = viewMatrix(camPos, vec3(0.0, 0.0, 0.0), vec3(0.0, 1.0, 0.0));\n"
                                    // "rayDir = (view0 * vec4(rayDir, 0.0)).xyz;\n"
                                

                                    "vec3 color = l.ambientColor;\n"
                                    // "color = rayMarchingCube(1.0, camPos, rayDir, 0.2, l, color);\n"     
                                    // "color = rayMarchingSurface(1.0, camPos, rayDir, 0.07, l, color);\n" 
                                    "color = rayMarchingSphere(1.0, camPos, rayDir, s, l, color);\n"                                  
                                    "gl_FragColor = vec4(color, 1.0);\n"
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


int main(){

    glfwInit();
    glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);
    // glfwWindowHint(GLFW_SAMPLES, 8); //HABILITANDO O MULTISAMPLING NO GLFW

    vec2 resolution; resolution[0] = 1920; resolution[1] = 1080;

    GLFWwindow *screen = glfwCreateWindow(resolution[0], resolution[1], "Spheres", NULL, NULL);

    glfwMakeContextCurrent(screen);

    GLint init = glewInit();
    printf("Status da inicializacao do GLEW: %s\n", glewGetErrorString(init));

    /*Shader attachment*/
    GLuint program = GLSLcreateProgram();
    Shader spheres;
    GLSLCompileRMShader(&spheres);
    // GLSLCompileSphereShader(&spheres);
    GLSLattachShader(program, spheres);
    glUseProgram(program);
    


    /*End of shader attatchment*/

    /*Camera setup*/
    Camera mainCam;
    vec3 eye; defvec3(eye, 0.0, 0.0, -5.0);
    vec3 center; defvec3(center, 0.0, 0.0, 0.0);
    vec3 viewUp; defvec3(viewUp, 0.0, 1.0, 0.0);
    defineProjectionCamera(&mainCam, 45.0, eye, center, viewUp, 0.1, 100, resolution[0], resolution[1]);
    GLint loc_eye = glGetUniformLocation(program, "eye");
    glUniform3f(loc_eye, eye[0], eye[1], eye[2]);
    GLint loc_view = glGetUniformLocation(program, "view");
    glUniform4fv(loc_view, GL_TRUE, mainCam.__view);

    /*End of camera setup*/



    /*Objects declaring*/


    GLuint numb_vert = 4;
    vec3 vertexes[numb_vert];

    vertexes[0][0] = -1.0; vertexes[0][1] = -1.0; vertexes[0][2] = 0.0;
    vertexes[1][0] = -1.0; vertexes[1][1] = 1.0; vertexes[1][2] = 0.0;
    vertexes[2][0] = 1.0; vertexes[2][1] = -1.0; vertexes[2][2] = 0.0;
    vertexes[3][0] = 1.0; vertexes[3][1] = 1.0; vertexes[3][2] = 0.0;

    vec4 color; color[0] = 1.0; color[1] = 0.0; color[2] = 0.0; color[3] = 1.0; 

    float time = 0.0, dt = 0.01;
    GLint loc_time = glGetUniformLocation(program, "time");




    /*End of objects declaring*/

    /*Send geometry information to the shader*/
    GLuint buffer;
    glGenBuffers(1, &buffer);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertexes), vertexes, GL_DYNAMIC_DRAW);

    GLuint loc_vert = glGetAttribLocation(program, "position");
    glEnableVertexAttribArray(loc_vert);
    glVertexAttribPointer(loc_vert, 3, GL_FLOAT, GL_FALSE, sizeof(vertexes[0]), (void *) 0);

    GLint loc_res = glGetUniformLocation(program, "res");
    glUniform2f(loc_res, resolution[0], resolution[1]);


    /*End of sending geometry information to the shader*/


    /*Window*/
    glfwShowWindow(screen);
    glEnable(GL_DEPTH_TEST);
    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    glfwSwapInterval(1);
    while(!glfwWindowShouldClose(screen)){

        glfwPollEvents();
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 
        glClearColor(0.0, 0.0, 0.0, 1.0);

        time += dt;
        glUniform1f(loc_time, time);

        // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

        glfwSwapBuffers(screen);


    }

    glEnd();
    glfwDestroyWindow(screen);
    glfwTerminate();
    return 0;
}


