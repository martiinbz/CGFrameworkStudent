uniform mat4 u_model;
uniform mat4 u_viewprojection;
uniform vec3 m; //light position
uniform vec3 u_eyePosition; // camera position
uniform vec3 Ia; // ambient
uniform vec3 Imd; // diffuse
uniform vec3 Ims; // specular
uniform float u_shininess; 
uniform vec3 Ka; 
uniform vec3 Kd; 
uniform vec3 Ks; 



varying vec2 v_uv;
varying vec3 v_world_position;
varying vec3 v_world_normal;

// New varying for the lighting calculation
varying vec3 v_color;

void main() {
    v_uv = gl_MultiTexCoord0.xy;

    vec3 world_position = (u_model * vec4( gl_Vertex.xyz, 1.0)).xyz;
    vec3 world_normal = (u_model * vec4( gl_Normal.xyz, 0.0)).xyz; //normalizamos la world_normal solo


    v_world_position = world_position;
    v_world_normal = normalize(world_normal);

    
    vec3 N = normalize(world_normal); // Normal
    vec3 L = normalize(m - world_position.xyz); // from p to m
    vec3 V = normalize(u_eyePosition - world_position.xyz); // from p to eye
    vec3 R = reflect(-L, N); // reflection of the inverted L over N

  
    vec3 ambient = Ka * Ia;

    float diff = clamp(dot(N, L), 0.0,1.0);
    vec3 diffuse = Kd * (diff * Imd);

    float spec = pow(clamp(dot(V, R), 0.0,1.0), u_shininess);
    vec3 specular = Ks * (spec * Ims);

    float distance = length(m - world_position.xyz);
    float attenuation = 1.0 / (distance * distance);

    
    vec3 v_IP = ambient + attenuation * (diffuse + specular);

     v_color = v_IP;

    gl_Position = u_viewprojection * vec4(world_position,1.0);
}