#ifdef GL_FRAGMENT_PRECISION_MEDIUM
    precision mediump float;
#else
    precision lowp float;
    precision lowp int;
#endif

uniform float u_time; //Variável padrão do glslCanvas que usa a variação do tempo
uniform vec2 u_resolution; //Variavel padrão do glslCanvas que usa a resolução da tela
uniform vec2 u_mouse;


float plot(vec2 st, float pct, float upper, float down){
    return smoothstep(pct - down, pct, 1.0) - 
           smoothstep(pct, pct + upper, 1.0);
}


float circle(vec2 st, vec2 center, float radius, float inner_smooth, float outer_smooth){
    /*Function to plot a circle*/

    float y = pow(radius, 2.0)*(pow(st.x - center.x, 2.0) + pow(st.y - center.y, 2.0));

    return smoothstep(y - outer_smooth, y, 1.0) - 
           smoothstep(y, y + inner_smooth, 1.0);
}



void main(){
    float p = 0.3;
    vec2 st = gl_FragCoord.xy/u_resolution;
    vec2 mouse = u_mouse.xy/u_resolution;

    float y = 25.0*(pow(st.x - mouse.x, 2.0) + pow(st.y - mouse.y, 2.0));
    float y1 = st.x;



    vec3 color = vec3(1.0);
    vec3 color2 = vec3(0.8, 0.6, 1.0);
    vec3 color3 = vec3(1.0, 1.0, 1.0);

    float circ = circle(st, vec2(0.45, 0.5), 10.0, -0.005, 0.005);
    float circ2 = circle(st, vec2(0.5, 0.595), 10.0, -0.005, 0.005);
    float circ3 = circle(st, vec2(0.55, 0.5), 10.0, -0.005, 0.005);
    // float pl = plot(st, y1 + 0.5*cos(u_time), 0.9, 0.9);

    color3 = circ3*vec3(0.0, 1.0, 0.0);
    color2 = circ2*vec3(0.0, 0.0, 1.0);
    color  = circ*vec3(1.0, 0.0, 0.0);


    gl_FragColor = vec4(color, 1.0) + vec4(color2, 1.0) + vec4(color3, 1.0);
    
}