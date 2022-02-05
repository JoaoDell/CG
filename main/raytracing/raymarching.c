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

                                "struct cube {\n"
                                    "vec3 pos;\n"
                                    "float size;\n"
                                    "vec3 color;\n"
                                "};\n"

                                "struct plane {\n"
                                    "float y;\n"
                                    "vec3 color;\n"
                                "};\n"

                                "struct light {\n"
                                    "vec3 lightPos;\n"
                                    "vec3 lightCenter;\n"
                                    "vec3 lightColor;\n"
                                    "vec3 ambientColor;\n"
                                "};\n"

                                "const int MAX_STEPS = 255;\n"
                                "const float MAX_DIST = 500.0;\n"
                                "const float EPSILON = 0.001;\n"
                                "const float K = 10.0;\n"
                                
                                "uniform vec2 res;\n"
                                "uniform float time;\n"
                                "uniform mat4 view;\n"
                                "uniform vec3 eye;\n"
                                "uniform vec3 center;\n"

                                "varying vec3 out_pos;\n"

                                "sphere s;\n"
                                "cube c;\n"
                                "light l;\n"



                            
                                //SDF FUNCTIONS
                                "float sphereSDF(vec3 p, sphere sp){\n"
                                    "float a = 3.0;\n"
                                    "return length(p - sp.pos) - sp.radius + sin(a*p.x)*sin(a*p.y)*sin(a*p.z)/4;\n"
                                "}\n"

                                // "float sphereSDF(vec3 p, sphere sp){\n"
                                //     "return length(p - sp.pos) - sp.radius;\n"
                                // "}\n"


                                "float cubeSDF(vec3 p, cube cu){\n"
                                    // If d.x < 0, then -1 < p.x < 1, and same logic applies to p.y, p.z
                                    // So if all components of d are negative, then p is inside the unit cube
                                    "vec3 d = abs(p - cu.pos) - vec3(cu.size);\n"

                                    // Assuming p is inside the cube, how far is it from the surface?
                                    // Result will be negative or zero.
                                    "float insideDistance = min(max(d.x, max(d.y, d.z)), 0.0);\n"

                                    // Assuming p is outside the cube, how far is it from the surface?
                                    // Result will be positive or zero.
                                    "float outsideDistance = length(max(d, 0.0));\n"

                                    "return insideDistance + outsideDistance;\n"
                                "}\n"

                                "float planeSDF(vec3 p, float y){\n"
                                    "return p.y - y;\n"
                                "}\n"

                                "float surfaceSDF(vec3 p, float d1, float d2){\n"
                                    "return min(d1, d2);\n"
                                "}\n"

                                "float unionSDF(float d1, float d2){\n"
                                    "return min(d1, d2);\n"
                                "}\n"

                                "float intersectSDF(float d1, float d2){\n"
                                    "return max(d1, d2);\n"
                                "}\n"

                                "float sceneSDF(vec3 p, sphere sp, float y){\n"
                                    "float d1 = sphereSDF(p, sp);\n"
                                    "float d2 = planeSDF(p, y);\n"
                                    "return unionSDF(d1, d2);\n"
                                "}\n"






                                //NORMAL CALC FUNCTIONS
                                "vec3 cubeNormals(vec3 p, cube cu){\n"
                                    "return normalize(vec3( cubeSDF(vec3(p.x + EPSILON, p.y, p.z), cu) - cubeSDF(vec3(p.x - EPSILON, p.y, p.z), cu),\n"
                                                           "cubeSDF(vec3(p.x, p.y + EPSILON, p.z), cu) - cubeSDF(vec3(p.x, p.y - EPSILON, p.z), cu),\n"
                                                           "cubeSDF(vec3(p.x, p.y, p.z + EPSILON), cu) - cubeSDF(vec3(p.x, p.y, p.z - EPSILON), cu)));\n" 
                                "}\n"


                                "vec3 planeNormals(vec3 p, float y){\n"
                                    "return normalize(vec3( planeSDF(vec3(p.x + EPSILON, p.y, p.z), y) - planeSDF(vec3(p.x - EPSILON, p.y, p.z), y),\n"
                                                           "planeSDF(vec3(p.x, p.y + EPSILON, p.z), y) - planeSDF(vec3(p.x, p.y - EPSILON, p.z), y),\n"
                                                           "planeSDF(vec3(p.x, p.y, p.z + EPSILON), y) - planeSDF(vec3(p.x, p.y, p.z - EPSILON), y)));\n" 
                                "}\n"

                                "vec3 sphereNormals(vec3 p, sphere sp){\n"
                                    "return normalize(vec3( sphereSDF(vec3(p.x + EPSILON, p.y, p.z), sp) - sphereSDF(vec3(p.x - EPSILON, p.y, p.z), sp),\n"
                                                           "sphereSDF(vec3(p.x, p.y + EPSILON, p.z), sp) - sphereSDF(vec3(p.x, p.y - EPSILON, p.z), sp),\n"
                                                           "sphereSDF(vec3(p.x, p.y, p.z + EPSILON), sp) - sphereSDF(vec3(p.x, p.y, p.z - EPSILON), sp)));\n" 
                                "}\n"

                                "vec3 surfaceNormals(vec3 p, float d1, float d2){\n"
                                    "return normalize(vec3( surfaceSDF(vec3(p.x + EPSILON, p.y, p.z), d1, d2) - surfaceSDF(vec3(p.x - EPSILON, p.y, p.z), d1, d2),\n"
                                                           "surfaceSDF(vec3(p.x, p.y + EPSILON, p.z), d1, d2) - surfaceSDF(vec3(p.x, p.y - EPSILON, p.z), d1, d2),\n"
                                                           "surfaceSDF(vec3(p.x, p.y, p.z + EPSILON), d1, d2) - surfaceSDF(vec3(p.x, p.y, p.z - EPSILON), d1, d2)));\n" 
                                "}\n"


                                "vec3 sceneNormals(vec3 p, sphere sp, float y){\n"
                                    "return normalize(vec3( sceneSDF(vec3(p.x + EPSILON, p.y, p.z), sp, y) - sceneSDF(vec3(p.x - EPSILON, p.y, p.z), sp, y),\n"
                                                           "sceneSDF(vec3(p.x, p.y + EPSILON, p.z), sp, y) - sceneSDF(vec3(p.x, p.y - EPSILON, p.z), sp, y),\n"
                                                           "sceneSDF(vec3(p.x, p.y, p.z + EPSILON), sp, y) - sceneSDF(vec3(p.x, p.y, p.z - EPSILON), sp, y)));\n" 
                                "}\n"


                                //MISC FUNCTIONS
                                "vec3 planeTexture(vec3 p){\n"
                                    "vec3 dark = vec3(0.5);\n"
                                    "vec3 light = vec3(0.6);\n"
                                    "float l = 4;\n"
                                    "if(floor(p.x) / 2  == floor(p.x / 2)\n" 
                                    "&& floor(p.z) / 2 == floor(p.z / 2)\n"
                                    "|| (floor(p.x)  + floor(p.z) )/ 2 == floor(p.x/2 + p.z/2)) return light;\n"
                                    "else return dark;\n"
                                "}\n"

                                "vec3 borderTexture(vec3 p, vec3 camPos, vec3 objPos){\n"
                                    "vec3 point = normalize(p - objPos);\n"
                                    "vec3 dir = normalize(objPos - camPos);\n"
                                    "float param = 2.0;\n"
                                    "return clamp(abs(param*(1 + dot(point, dir))), 0.0, 1.0)*vec3(1.0, 1.0, 1.0) + vec3(0.15, 0.0, 0.0);\n"
                                "}\n"

                                "vec3 borderDerivativeTexture(vec3 camPos, vec3 objPos, vec3 norm){\n"
                                    "vec3 dir = normalize(objPos - camPos);\n"
                                    "float param = 2.0;\n"
                                    "return clamp(abs(param*(1 + dot(norm, dir))), 0.0, 1.0)*vec3(1.0, 1.0, 1.0) + vec3(0.15, 0.0, 0.0);\n"
                                "}\n"


                                //MATH FUNCTIONS
                                "mat4 viewMatrix(vec3 eye, vec3 center, vec3 up){\n"
	                                "vec3 f = normalize(center - eye);\n"
	                                "vec3 s = normalize(cross(f, up));\n"
	                                "vec3 u = normalize(cross(s, f));\n"
	                                "return mat4(\n"
		                                "vec4(s, 0.0),\n"
		                                "vec4(u, 0.0),\n"
                                        "vec4(-f, 0.0),\n"
                                        "vec4(0.0, 0.0, 0.0, 1)\n"
                                    ");\n"
                                "}\n"

                                "vec3 rayDirection(float FOV, vec2 resolution, vec2 fragCoord){\n"
                                    "vec2 uv = (fragCoord)*resolution/ 2 / resolution.y;\n"
                                    "float z = resolution.y / tan( radians(FOV) / 2.0 ) / resolution.y;\n"
                                    "return normalize(vec3(uv, -z));\n"
                                "}\n"






                                //SHADOW CALC
                                "float shadowCalc(vec3 eye, vec3 rayDir, float start, float k, sphere sp, float y){\n"
                                    "float ds = start;\n"
                                    "float dist = 0.0;\n"
                                    "float result = 1.0;\n"
                                    "vec3 p;\n"
                                    "for(int i = 0; i < MAX_STEPS; i++){\n"
                                        "p = eye + ds*rayDir;\n"
                                        "dist = sceneSDF(p, sp, y);\n"
                                        "result = min(result, k*dist/ds);\n"
                                        "ds += dist;\n"
                                        "if(result < EPSILON || ds > MAX_DIST) return clamp(result, 0.0, 1.0);\n"

                                    "}\n"
                                    "return clamp(result, 0.0, 1.0);\n"
                                "}\n"







                                //LIGHT CALC FUNCTIONS
                                "vec3 spherePhong(vec3 p, vec3 camPos, sphere sp, light li){\n"
                                    "float Ka = 1.0, Kd = 2.0, Ks = 2.5, ns = 10.0;\n"

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

                                    "return (ambient + diffuse + specular)*sp.color*borderDerivativeTexture(camPos, sp.pos, norm);\n"
                                    /*PHONG*/

                                "}\n"

                                "vec3 cubePhong(vec3 p, vec3 camPos, cube cu, light li){\n"
                                    "float Ka = 1.0, Kd = 1.0, Ks = 1.0, ns = 0.6;\n"

                                    //Cálculo das normals
                                    "vec3 norm = cubeNormals(p, cu);\n"

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

                                    "return (ambient + diffuse + specular)*cu.color*borderTexture(p, camPos, cu.pos);\n"
                                    /*PHONG*/

                                "}\n"




                                "vec3 planePhong(vec3 p, vec3 camPos, float y, light li){\n"
                                    "float Ka = 1.0, Kd = 8.0, Ks = 10.0, ns = 20.0;\n"

                                    //Cálculo das normals
                                    "vec3 norm = planeNormals(p, y);\n"

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

                                    "return (ambient + diffuse + specular)*planeTexture(p)*vec3(0.2, 0.1, 0.7);\n"
                                    /*PHONG*/

                                "}\n"

                                "vec3 surfacePhong(vec3 p, vec3 camPos, float d1, float d2, light li){\n"
                                    "float Ka = 1.0, Kd = 1.0, Ks = 1.0, ns = 0.6;\n"

                                    //Cálculo das normals
                                    "vec3 norm = surfaceNormals(p, d1, d2);\n"

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


                                "vec3 scenePhong(vec3 p, vec3 camPos, sphere sp, float y, light li){\n"
                                    "float Ka = 1.0, Kd = 10.0, Ks = 10.0, ns = 0.6;\n"

                                    //Cálculo das normals
                                    "vec3 norm = sceneNormals(p, sp, y);\n"

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

                                    
                                    "return (ambient + (diffuse + specular));\n"
                                    /*PHONG*/

                                "}\n"





                                //RAY MARCHING FUNCTIONS
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
                                
                                "vec3 rayMarchingCube(float start, vec3 eye, vec3 rayDir, cube cu, light li, vec3 color){\n"
                                    "float ds = start;\n" //quantidade a se andar ao longo da dire;áo do raio
                                    "vec3 p;\n"
                                    "for(int i = 0; i < MAX_STEPS; i++){\n"
                                        "p = eye + ds * rayDir;\n" //iterando pelo raio

                                        "float dist = cubeSDF(p, cu);\n"
                                        "if(dist < EPSILON)\n"
                                            "return cubePhong(p, eye, cu, li);\n"

                                        "ds += dist;\n" //se não atingiu nada, incrementa o passo com a distancia

                                        "if(ds >= MAX_DIST)\n"
                                            "return color;\n"
                                    "}\n"
                                    "return color;\n"

                                "}\n"


                                "vec3 rayMarchingPlane(float start, vec3 eye, vec3 rayDir, float y, light li, vec3 color){\n"
                                    "float ds = start;\n" //quantidade a se andar ao longo da dire;áo do raio
                                    "vec3 p;\n"
                                    "for(int i = 0; i < MAX_STEPS; i++){\n"
                                        "p = eye + ds * rayDir;\n" //iterando pelo raio

                                        "float dist = planeSDF(p, y);\n"
                                        "if(dist < EPSILON)\n"
                                            "return planePhong(p, eye, y, li);\n"

                                        "ds += dist;\n" //se não atingiu nada, incrementa o passo com a distancia

                                        "if(ds >= MAX_DIST)\n"
                                            "return color;\n"
                                    "}\n"
                                    "return color;\n"

                                "}\n"

                                "vec3 rayMarchingSurface(float start, vec3 eye, vec3 rayDir, cube cu, sphere sp, light li, vec3 color){\n"
                                    "float ds = start;\n" //quantidade a se andar ao longo da dire;áo do raio
                                    "vec3 p;\n"
                                    "for(int i = 0; i < MAX_STEPS; i++){\n"
                                        "p = eye + ds * rayDir;\n" //iterando pelo raio

                                        "float d1 = cubeSDF(p, cu);\n"
                                        "float d2 = sphereSDF(p, sp);\n"
                                        "float dist = intersectSDF(d1, d2);\n"
                                        "if(dist < EPSILON)\n"
                                            "return cubePhong(p, eye, cu, li)*spherePhong(p, eye, sp, li);\n"

                                        "ds += dist;\n" //se não atingiu nada, incrementa o passo com a distancia

                                        "if(ds >= MAX_DIST)\n"
                                            "return color;\n"
                                    "}\n"
                                    "return color;\n"

                                "}\n"

                                "vec3 rayMarchingScene(float start, vec3 eye, vec3 rayDir, float y, sphere sp, light li, vec3 color){\n"
                                    "float ds = start;\n" //quantidade a se andar ao longo da dire;áo do raio
                                    "vec3 p;\n"
                                    "for(int i = 0; i < MAX_STEPS; i++){\n"
                                        "p = eye + ds * rayDir;\n" //iterando pelo raio

                                        
                                        "float dist = sceneSDF(p, sp, y);\n"
                                        "if(dist < EPSILON)\n"
                                            "return scenePhong(p, eye, sp, y, li)*sp.color;\n"

                                        "ds += dist;\n" //se não atingiu nada, incrementa o passo com a distancia

                                        "if(ds >= MAX_DIST)\n"
                                            "return color;\n"
                                    "}\n"
                                    "return color;\n"

                                "}\n"
                                


                                "void main(){\n"
                                
                                    "vec3 camPos = eye;\n"
                                    "mat4 view0 = viewMatrix(camPos, center, vec3(0.0, 1.0, 0.0));\n"
                                    "vec3 rayDir = rayDirection(45.0, res, out_pos.xy);\n"

                                    // "l.lightPos = vec3(5*sin(time), 2.0, -10*cos(time));\n"
                                    "l.lightPos = vec3(-10.0, 10.0, -30.0);\n"
                                    "l.lightCenter = vec3(0.0, 0.0, 0.0);\n"
                                    "l.lightColor = vec3(1.0, 0.8, 0.0);\n"
                                    "l.ambientColor = vec3(0.9, 0.7, 1.0) - vec3(0.0);\n"
                                    "mat4 lview = viewMatrix(l.lightPos, l.lightCenter, vec3(0.0, 1.0, 0.0));\n"

                                    "s.pos = vec3(0.0, 4.0, 0.0);\n"
                                    "s.radius = 3.0*abs(cos(time));\n"
                                    "s.color = vec3(1.0, 0.6, 0.5);\n"

                                    "c.pos = vec3(0.0, 2.0, 0.0);\n"
                                    "c.size = 2.0;\n"
                                    "c.color = vec3(1.0, 0.6, 0.6);\n"

                                    "rayDir = (view0 * vec4(rayDir, 0.0)).xyz;\n"
                                

                                    "vec3 color = l.ambientColor;\n"
                                    "color = rayMarchingPlane(0.0, camPos, rayDir, 2.0, l, color);\n" 
                                    // "color = rayMarchingCube(1.0, camPos, rayDir, c, l, color);\n"     
                                    "color = rayMarchingSphere(0.0, camPos, rayDir, s, l, color);\n"
                                    // "color = rayMarchingScene(0.0, camPos, rayDir, 0.0, s, l, color);\n"                                   
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

vec3 eye0, center0, up0;

int FirstMouse = 1;
int LastX = 960; //Metade da largura
int LastY = 540; //Metade da altura
float yaw = -90.0;
float pitch = 0.0;
vec3 eye0, center0;
static void mouse_event(GLFWwindow *window, double xpos, double ypos){


    if(FirstMouse){
        LastX = xpos;
        LastY = ypos;
        FirstMouse = 0;
    }

    float xoffset = xpos - LastX;
    float yoffset = LastY - ypos;
    LastX = xpos;
    LastY = ypos;

    float sensitivity = 0.5; 
    xoffset *= sensitivity;
    yoffset *= sensitivity;

    yaw += xoffset;
    pitch += yoffset;

    if(pitch > 89.9) pitch = 89.9;
    else if(pitch < -89.9) pitch = -89.9;

    vec3 front;

    front[0] = cos(glm_rad(yaw))*cos(glm_rad(pitch));
    front[1] = sin(glm_rad(pitch));
    front[2] = sin(glm_rad(yaw))*cos(glm_rad(pitch));

    glm_normalize(front);

    center0[0] = front[0];
    center0[1] = front[1];
    center0[2] = front[2];

    // glfwSetCursorPos(window, largura/2, altura/2);
}

float speed = 0.5;

static void key_event(GLFWwindow* window, int key, int scancode, int action, int mods){
    // printf("Pressionando tecla %d\n", key);


    vec3 aux;

    if(key == 68 && (action == 1|| action == 2)) {
        glm_vec3_cross(center0, up0, aux);
        glm_vec3_normalize(aux);


        eye0[0] += speed*aux[0];
        eye0[1] += speed*aux[1];
        eye0[2] += speed*aux[2];



    } // d

    else if(key == 65 && (action == 1|| action == 2)){
        glm_vec3_cross(center0, up0, aux);
        glm_vec3_normalize(aux);

        eye0[0] -= speed*aux[0];
        eye0[1] -= speed*aux[1];
        eye0[2] -= speed*aux[2];


    } // a

    else if(key == 87 && (action == 1|| action == 2)){
        // glm_vec3_cross(, float *b, aux)
        eye0[0] += speed*center0[0];
        eye0[1] += speed*center0[1];
        eye0[2] += speed*center0[2];

    } // w

    else if(key == 83 && (action == 1|| action == 2)){
        eye0[0] -= speed*center0[0];
        eye0[1] -= speed*center0[1];
        eye0[2] -= speed*center0[2];



    } // s


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
    vec3 eye; defvec3(eye0, 20.0, 20.0, -20.0);
    // vec3 eye; defvec3(eye0, 8.0, 5.0, 7.0);
    vec3 center; defvec3(center0, 0.0, 4.0, 0.0);
    vec3 viewUp; defvec3(up0, 0.0, 1.0, 0.0);
    defineProjectionCamera(&mainCam, 90.0, eye0, center0, up0, 0.1, 100, resolution[0], resolution[1]);
    GLint loc_eye = glGetUniformLocation(program, "eye");
    glUniform3f(loc_eye, eye0[0], eye0[1], eye0[2]);
    GLint loc_center = glGetUniformLocation(program, "center");
    glUniform3f(loc_center, center0[0], center0[1], center0[2]);
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
    // glfwSetCursorPosCallback(screen, mouse_event);
    // glfwSetKeyCallback(screen, key_event);
    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    glfwSwapInterval(1);
    while(!glfwWindowShouldClose(screen)){

        glfwPollEvents();
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 
        glClearColor(0.0, 0.0, 0.0, 1.0);

        time += dt;
        glUniform1f(loc_time, time);

    
        defvec3(eye0, 20.0*sin(time), 20.0, -20.0*cos(time));
        defineProjectionCamera(&mainCam, 45.0, eye0, center0, up0, 0.01, 100, resolution[0], resolution[1]);
        glUniform3f(loc_eye, eye0[0], eye0[1], eye0[2]);
        glUniform3f(loc_center, center0[0], center0[1], center0[2]);
        glUniformMatrix4fv(loc_view, 1, GL_TRUE, mainCam.__view);
        // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

        glfwSwapBuffers(screen);


    }

    glEnd();
    glfwDestroyWindow(screen);
    glfwTerminate();
    return 0;
}


