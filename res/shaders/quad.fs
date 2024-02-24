varying vec2 v_uv;
varying float time;
uniform float subtask;
void main()
{
	//vec3 color= vec3(1.0);
	//1
	if(subtask==1){

		vec3 color = mix(vec3(0,0,1),vec3(1,0,0),v_uv.x);
		gl_FragColor =vec4(color,1.0);	

	}
	else if (subtask==2){
		vec3 color= vec3(distance(vec2(0.5,0.5),v_uv));
		gl_FragColor =vec4(color,1.0);	

	}
	else if (subtask==3){
		float s = sin(time + v_uv.x * 10.0) * 0.1 + 0.5; // Adjust frequency and amplitude here
		float t = cos(time + v_uv.y * 10.0) * 0.1 + 0.5;

		vec2 pattern = step(s, t);

		vec3 color = mix(vec3(1.0, 0.0, 0.0), vec3(0.0, 0.0, 1.0), pattern.x * pattern.y);
		gl_FragColor =vec4(color,1.0);	
	}
	else if (subtask==4){


	}
	else if (subtask==5){


	}
	else if (subtask==6){

	}
	



	
	

	
    
}
