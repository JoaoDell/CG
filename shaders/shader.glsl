#ifdef GL_FRAGMENT_PRECISION_MEDIUM
    precision mediump float;
#else
    precision lowp float;
    precision lowp int;
#endif

uniform float u_time; //Variável padrão do glslCanvas que usa a variação do tempo
uniform vec2 u_resolution; //Variavel padrão do glslCanvas que usa a resolução da tela
uniform vec2 u_mouse;


float plot(vec2 st, float pct){
    return smoothstep(pct - 0.001, pct, st.y) - 
           smoothstep(pct, pct + 0.5, st.y);
}



void main(){
    float p = 0.3;
    vec2 st = gl_FragCoord.xy/u_resolution;

    // float y = pow(st.x, 1.0*abs(cos(u_time)));
    float y = 0.3 ;
    // float y = sin(st.x);

    vec3 color = vec3(y);

    float pct = plot(st, y);

    color = pct*vec3(1.0, 0.5, 0.0);

    gl_FragColor = vec4(color, 1.0);
    
}