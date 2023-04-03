#include <stdio.h>
#include <stdlib.h>
#define BASIC
#include "../../include/GLib.h"
#include <GL/glew.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <cglm/cglm.h>


typedef struct sphere{
    vec3 pos;
    float radius;
    Color color;
    
    GLint loc_pos;
    GLint loc_radius;
    GLint loc_color;
} Sphere;

void GLSLCompileSphereShader(Shader *shader){
    
    const GLchar *vert_shader = "attribute vec3 position;\n"
                                "uniform mat4 view;\n"
                                "uniform mat4 proj;\n"

                                "varying mat4 transf;\n"
                                "varying vec3 out_pos;\n"
                                "void main(){\n"
                                    "transf = proj*view;\n"
                                    "out_pos = (vec4(position, 1.0)).xyz;\n"
                                    "gl_Position = vec4(position, 1.0);\n"
                                "}\n";

    const GLchar *frag_shader = "struct sphere {\n"
                                    "vec3 pos;\n"
                                    "float radius;\n"
                                    "vec3 color;\n"
                                "};\n"

                                "uniform vec4 color;\n"
                                "varying vec3 out_pos;\n"
                                "varying mat4 transf;\n"
                                "uniform vec3 camPos;\n"
                                "uniform sphere spheres[3];\n"

                                "uniform vec2 res;\n"

                                "float sphereS(vec3 pos, vec3 sphere_pos){\n"
                                    "return length(pos - sphere_pos);\n"
                                "};\n"

                                "void sphereDraw(float len, sphere s){\n"
                                    "if( len < s.radius )\n"
                                        "gl_FragColor = vec4(s.color, 1.0);\n"
                                "}\n"


                                "void main(){\n"
                                    "vec3 pos = out_pos;\n"
                                    "gl_FragColor = vec4(0.0, 0.0, 0.0, 1.0);\n" //pintando o canvas de preto primeiro
                                    "for(int i = 0; i < 3; i++){\n"
                                        // "vec3 sp = vec3(transf*vec4(spheres[i].pos, 1.0));\n"
                                        "sphereDraw(sphereS(pos, spheres[i].pos), spheres[i]);\n"
                                    "}\n"
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

void GLSLCompileRMShader(Shader *shader){
    
    const GLchar *vert_shader = "attribute vec3 position;\n"
                                "uniform mat4 view;\n"
                                "uniform mat4 proj;\n"

                                "varying mat4 transf;\n"
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

                                "uniform vec4 color;\n"
                                "varying vec3 out_pos;\n"
                                "varying mat4 transf;\n"
                                "uniform vec3 camPos;\n"
                                "uniform sphere spheres[3];\n"

                                // "uniform vec2 res;\n"

                                "const float FOV = 1.0;\n"
                                "const int MAX_STEPS = 256;\n"
                                "const float MAX_DIST = 500;\n"
                                "const float EPSILON = 0.001;\n"

                            


                            

                                "float sphereS(vec3 pos, vec3 sphere_pos){\n"
                                    "return length(pos - sphere_pos);\n"
                                "};\n"

                                "vec2 map(vec3 p){\n"
                                    //sphere
                                    "float sphereDist = length(p) - 1.0;\n"
                                    "float sphereID = 1.0;\n"
                                    "vec2 sphere = vec2(sphereDist, sphereID);\n"
                                    "vec2 res = sphere;\n"
                                    "return res;\n"
                                "}\n"

                                "vec2 rayMarch(vec3 ro, vec3 rd){\n"
                                    "vec2 hit, object;\n"
                                    "for(int i = 0; i < MAX_STEPS; i++){\n"
                                        "vec3 p = ro + object.x * rd;\n"
                                        "hit = map(p);\n"
                                        "object.x += hit.x;\n"
                                        "object.y = hit.y;\n"
                                        "if (abs(hit.x) < EPSILON || object.x > MAX_DIST) break;\n"
                                    "}\n"
                                    "return object;\n"
                                "}\n"


                                "void render(vec3 col, vec2 uv){\n"
                                    "vec3 ro = vec3(0.0, 0.0, -5.0);\n"
                                    "vec3 rd = normalize(vec3(uv, FOV));\n"

                                    "vec2 object = rayMarch(ro, rd);\n"

                                    "if(object.x < MAX_DIST){\n"
                                        "col += 3.0 / object.x;\n"
                                    "}\n"
                                "}\n"



                                "void main(){\n"
                                    "vec2 res = vec2(1.0, 1.0);\n"

                                    "vec2 uv = (2.0 * out_pos.xy - res)/res.y;\n"

                                    // "vec3 pos = out_pos;\n"
                                    // "gl_FragColor = vec4(0.0, 0.0, 0.0, 1.0);\n" //pintando o canvas de preto primeiro
                                    "vec3 col;\n"
                                    "render(col, uv);\n"
                                    "gl_FragColor = vec4(col, 1.0);\n"
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

void defineSphere(Sphere *sphere, float *pos, float radius, Color color){
    sphere->pos[0] = pos[0]; sphere->pos[1] = pos[1]; sphere->pos[2] = pos[2];
    sphere->radius = radius;
    sphere->color = color;
}


void glGetSphereLocation(Sphere *sphere, GLint program, char *pos_loc, char *radius_loc, char *color_loc){
    sphere->loc_pos    = glGetUniformLocation(program, pos_loc);
    sphere->loc_radius = glGetUniformLocation(program, radius_loc);
    sphere->loc_color  = glGetUniformLocation(program, color_loc);
}

void sendSphere(Sphere sphere, GLint program){
    glUniform3f(sphere.loc_pos, sphere.pos[0], sphere.pos[1], sphere.pos[2]);
    glUniform1f(sphere.loc_radius, sphere.radius);
    glUniform3f(sphere.loc_color, sphere.color.r, sphere.color.g, sphere.color.b);
}


int FirstMouse = 1;


int LastX = 540; //Metade da largura
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

int main(){

    glfwInit();
    glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);
    // glfwWindowHint(GLFW_SAMPLES, 8); //HABILITANDO O MULTISAMPLING NO GLFW

    vec2 resolution; resolution[0] = 1080; resolution[1] = 1080;

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
    defvec3(eye0, 0.0, 0.0, 0.9);
    defvec3(center0, 0.0, 0.0, 0.0);
    vec3 viewUp; defvec3(viewUp, 0.0, 1.0, 0.0);

    
    defineProjectionCamera(&mainCam, 45.0, eye0, center0, viewUp, 0.01, 100, resolution[0], resolution[1]);

    /*End of camera setup*/



    /*Objects declaring*/


    GLuint numb_vert = 4;
    vec3 vertexes[numb_vert];

    vertexes[0][0] = -1.0; vertexes[0][1] = -1.0; vertexes[0][2] = 0.0;
    vertexes[1][0] = -1.0; vertexes[1][1] = 1.0; vertexes[1][2] = 0.0;
    vertexes[2][0] = 1.0; vertexes[2][1] = -1.0; vertexes[2][2] = 0.0;
    vertexes[3][0] = 1.0; vertexes[3][1] = 1.0; vertexes[3][2] = 0.0;

    vec4 color; color[0] = 1.0; color[1] = 0.0; color[2] = 0.0; color[3] = 1.0; 



    Sphere spherelist[3];
    float pos1[] = {-0.3, 0.0, 0.0}; float pos2[] = {0.7, 0.0, 0.0}; float pos3[] = {0.5, 0.0, 0.0};
    defineSphere(&spherelist[0], pos1, 0.1, DefineColor(255, 0, 0, 1.0));
    defineSphere(&spherelist[1], pos2, 0.1, DefineColor(0, 255, 55, 1.0));
    defineSphere(&spherelist[2], pos3, 0.1, DefineColor(133, 55, 255, 1.0));

    glGetSphereLocation(&spherelist[0], program, "spheres[0].pos", "spheres[0].radius", "spheres[0].color");
    glGetSphereLocation(&spherelist[1], program, "spheres[1].pos", "spheres[1].radius", "spheres[1].color");
    glGetSphereLocation(&spherelist[2], program, "spheres[2].pos", "spheres[2].radius", "spheres[2].color");

    sendSphere(spherelist[0], program);
    sendSphere(spherelist[1], program);
    sendSphere(spherelist[2], program);


    /*End of objects declaring*/

    /*Send geometry information to the shader*/
    GLuint buffer;
    glGenBuffers(1, &buffer);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertexes), vertexes, GL_DYNAMIC_DRAW);

    GLuint loc_vert = glGetAttribLocation(program, "position");
    glEnableVertexAttribArray(loc_vert);
    glVertexAttribPointer(loc_vert, 3, GL_FLOAT, GL_FALSE, sizeof(vertexes[0]), (void *) 0);

    GLint loc_view = glGetUniformLocation(program, "view");
    GLint loc_proj = glGetUniformLocation(program, "proj");
    // GLint loc_res = glGetUniformLocation(program, "res");

    // glUniform2f(loc_res, resolution[0], resolution[1]);

    glUniformMatrix4fv(loc_view, 1, GL_TRUE, mainCam.__view);
    glUniformMatrix4fv(loc_proj, 1, GL_TRUE, mainCam.__projection);


    /*End of sending geometry information to the shader*/


    /*Window*/
    glfwShowWindow(screen);
    glEnable(GL_DEPTH_TEST);
    glfwSetCursorPosCallback(screen, mouse_event);
    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    glfwSwapInterval(1);
    while(!glfwWindowShouldClose(screen)){

        glfwPollEvents();
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 
        glClearColor(0.0, 0.0, 0.0, 1.0);

        
        defineProjectionCamera(&mainCam, 45.0, eye0, center0, viewUp, 0.01, 100, resolution[0], resolution[1]);
        glUniformMatrix4fv(loc_view, 1, GL_TRUE, mainCam.__view);
        glUniformMatrix4fv(loc_proj, 1, GL_TRUE, mainCam.__projection);

        // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

        glfwSwapBuffers(screen);


    }

    glEnd();
    glfwDestroyWindow(screen);
    glfwTerminate();
    return 0;
}


