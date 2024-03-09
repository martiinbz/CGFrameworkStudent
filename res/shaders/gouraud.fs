
varying vec2 v_uv; 
uniform sampler2D lee; 

varying vec3 v_color; 

void main() {
    vec4 textureColor = texture2D(lee, v_uv); 

    
    vec3 iluminacion = v_color * textureColor.rgb; 

    gl_FragColor = vec4(iluminacion, textureColor.a); 
}


