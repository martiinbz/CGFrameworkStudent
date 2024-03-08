varying vec3 v_world_normal;

void main()
{
    vec3 color=v_world_normal;
    gl_FragColor=vec4(color,1.0);
}
