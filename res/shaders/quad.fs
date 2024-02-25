varying vec2 v_uv;
varying float time;
uniform float subtask;
uniform float formulas;
uniform float filters;
uniform float transformation;
uniform sampler2D texture;

void main()
{
	
	//TASK1
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
		
			//lineas verticales
			float vertical = step(sin(v_uv.x * 32.0) * 0.5 + 0.5, 0.1);

			//lineas horizontales
			float horizontal = step(cos(v_uv.y * 30.0) * 0.5 + 0.5, 0.1);

		
			// ponemos los colores
			vec3 color = vec3(0.0, 0.0, 0.0); // fondo negro
			color += vertical * vec3(1.0, 0.0, 0.0); // lineas rojas
			color += horizontal * vec3(0.0, 0.0, 1.0); // lineas azules
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
    		sinus = sinus * 0.5 + 0.5; 
    		gl_FragColor = vec4(0.0, sinus, 0.0, 1.0); 

		}
	}


	//TASK 2
	else if(filters){

		//blanco y negro
		if(subtask==1){
			vec4 color = texture2D(texture, v_uv);
			//convertimos de rgb a iluminacion con el producto escalar
			float blackandwhite = dot(color, vec3(0.3, 0.6, 0.1));

			gl_FragColor = vec4(blackandwhite, blackandwhite, blackandwhite, 1.0);
		}
		//negativo
		else if(subtask==2){
			vec3 color = texture2D(texture, v_uv);
			//colores negativos
			gl_FragColor = vec4(1-color.x,1-color.y,1-color.z, 1.0);

		}
		//filtro sepia
		else if (subtask==3){

			vec3 color = texture2D(texture, v_uv);
			//primero convertimos a blanco y negro
			vec3 blackandwhite = dot(color, vec3(0.1, 0.6, 0.1));
			//mezclamos con amarillo
			vec3 yellow = mix(blackandwhite,vec3(1,0.8,0.1), 0.5);
			gl_FragColor = vec4(yellow,1);
		}
		//subir contraste
		else if(subtask==4){

			vec3 color = texture2D(texture, v_uv);
			//primero convertimos a blanco y negro
			vec3 blackandwhite = dot(color, vec3(0.13, 0.6, 0.11));

			float contrast = 100; 
			//subimos el contraste
			vec3 apply_contrast = (blackandwhite - 0.5) * contrast + 0.5;

			gl_FragColor = vec4(apply_contrast,1.0);

		}
		//bajar brillo(?)
		else if( subtask==5){
			vec3 color = texture2D(texture, v_uv);
			//"atenuamos" los colores
			gl_FragColor = vec4(color.x*0.4,color.y*0.4,color.z*0.4,1.0);
		}
		//desenfoque
		else if(subtask==6){
			vec3 top = texture2D(texture, v_uv + vec2(0.0, 1.0 /120));
			//sacamos los 4 pixeles adyacentes
			vec3 bottom = texture2D(texture, v_uv + vec2(0.0, -1.0 / 150));
			vec3 left = texture2D(texture, v_uv + vec2(-1.0 / 150, 0.0));
			vec3 right = texture2D(texture, v_uv + vec2(1.0 / 150, 0.0));
			//hacemos la media de los 4 para desenfocar
			vec3 color= (top+bottom+left+right)/4; 
			
			gl_FragColor = vec4(color, 1.0);

		}

	}

	//TASK 3
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
	



	
	

	
    

