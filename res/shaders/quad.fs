varying vec2 v_uv;
varying float time;
uniform float subtask;
uniform float formulas;
uniform float filters;
uniform float transformation;
uniform sampler2D texture;
void main()
{
	//vec3 color= vec3(1.0);
	//1
	if(formulas){

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
			 float sinus =  2 * sin(v_uv.y * 8.5)+1;
    		//sinus = sinus * 0.5 + 0.5; // Normalize to 0..1
    		gl_FragColor = vec4(0.0, sinus, 0.0, 1.0); // Green wave

		}
	}
	else if(filters){

		//blanco y negro
		if(subtask==1){
			vec4 color = texture2D(texture, v_uv);
			float luminance = dot(color, vec3(0.2989, 0.5870, 0.1140));
			gl_FragColor = vec4(luminance, luminance, luminance, 1.0);
		}
		//negativo
		else if(subtask==2){
			vec3 color = texture2D(texture, v_uv);
			gl_FragColor = vec4(1-color.x,1-color.y,1-color.z, 1.0);

		}
		//sepia
		else if (subtask==3){

			vec3 color = texture2D(texture, v_uv);
			vec3 swizzled = mix(color.y, color.x, 0.5);
			gl_FragColor = vec4(swizzled,1);
		}
		//resaltar sombras
		else if(subtask==4){
			vec3 color = texture2D(texture, v_uv);
			vec3 top = texture2D(texture, v_uv + vec2(0.0, 1.0 / 700));
			vec3 bottom = texture2D(texture, v_uv + vec2(0.0, -1.0 / 700));
			vec3 left = texture2D(texture, v_uv + vec2(-1.0 / 700, 0.0));
			vec3 right = texture2D(texture, v_uv + vec2(1.0 / 700, 0.0));
			vec3 dx = mix(right, left, 0.5);
			vec3 dy = mix(top, bottom, 0.5);
			vec3 edge = mix(dot(dx-0.2, dx+0.2), dot(dy-0.1, dy+0.1), 0.1);
			gl_FragColor = vec4(mix(color, edge, 1), 0.5);

		}
		//
		else if(subtask==6){
			vec3 top = texture2D(texture, v_uv + vec2(0.0, 1.0 / 150));
			vec3 bottom = texture2D(texture, v_uv + vec2(0.0, -1.0 / 150));
			vec3 left = texture2D(texture, v_uv + vec2(-1.0 / 150, 0.0));
			vec3 right = texture2D(texture, v_uv + vec2(1.0 / 150, 0.0));
			vec3 color = mix(mix(mix(top, bottom, 0.2), left, 0.2), right, 0.2);
			gl_FragColor = vec4(color, 1.0);

		}
	}
	else if(transformation){
		
		//pixelar
		if(subtask==1){

			//bajamos la cantidad de uv
			vec2 pixelatedUV = floor(v_uv *100) / 100; 

			vec3 color = texture2D(texture, pixelatedUV);

			gl_FragColor = vec4(color, 1.0);

		}
		//distorsionar
		else if(subtask==2){

			//creamos distorsiones en los 2 ejes
			float X = sin(v_uv.x * 6.0) * 0.15; 
			float Y = sin(v_uv.y * 5.0) * 0.1;

			//desplazamos los UV
			vec2 distortedUV = v_uv + vec2(X, Y);

			vec3 color = texture2D(texture, distortedUV);
			gl_FragColor = vec4(color, 1.0);



		}
	}
}
	



	
	

	
    

