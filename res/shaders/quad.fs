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
		

		// Define line width
		float lineWidth = 0.1; // Adjust line width here

		// Create vertical stripes using sine and step functions
		float vertical = step(sin(v_uv.x * 32.0) * 0.5 + 0.5, lineWidth);

		// Create horizontal stripes using cosine and step functions
		float horizontal = step(cos(v_uv.y * 30.0) * 0.5 + 0.5, lineWidth);

		
		// Set colors based on stripes
		vec3 color = vec3(0.0, 0.0, 0.0); // Black background
		color += vertical * vec3(1.0, 0.0, 0.0); // Red vertical lines
		color += horizontal * vec3(0.0, 0.0, 1.0); // Blue horizontal lines
		gl_FragColor =vec4(color,1.0);	

	}
	else if (subtask==4){
		 
		 vec3 color = vec3(v_uv.x, 1.0 - v_uv.x, 0.0);
   		 gl_FragColor = vec4(color, 1.0);


	}
	else if (subtask==5){
		vec2 U = 2 * mod(float(20000/2) * v_uv /vec2(1280,720), 1) - 1;   
    	 vec4 O = vec4(step(0., U.x * U.y));
		 gl_FragColor =vec4(O);
		
		
       

	}
	else if (subtask==6){
		 float sinus =  2 * sin(v_uv.y * 10.0);
    	sinus = sinus * 0.5 + 0.5; // Normalize to 0..1
    	gl_FragColor = vec4(0.0, sinus, 0.0, 1.0); // Green wave

	}
	



	
	

	
    
}
