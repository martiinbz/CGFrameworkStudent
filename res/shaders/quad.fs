varying vec2 v_uv;

void main()
{
	//vec3 color2= vec3(distance(vec2(0.5*1.2,0.5),v_uv));
	//vec3 color = mix(vec3(0,0,1),vec3(1,0,0),v_uv);
	vec3 color= vec3(0.8,1.0,1.0);



	gl_FragColor =vec4(color,1.0) ;
}
