void main()
{
	vec3 normal, lightDir;
	vec4 diffuse, ambient, globalAmbient;
	float NdotL, NdotHV;
	vec4 specular=vec4(0,0,0,0);

	normal = normalize(gl_NormalMatrix * gl_Normal);

	vec4 pointEyeSpace=(gl_ModelViewMatrix*gl_Vertex);

	lightDir = normalize(vec3(gl_LightSource[0].position)-pointEyeSpace.xyz);

	NdotL = max(dot(normal, lightDir), 0.0);
	
	vec4 cameraDir=-pointEyeSpace;
	vec4 halfVector=normalize((lightDir+ cameraDir));
	
	if (NdotL > 0.0) {

		// normalize the half-vector, and then compute the
		// cosine (dot product) with the normal
		NdotHV = max(dot(normal, halfVector.xyz),0.0);
		specular = gl_FrontMaterial.specular * gl_LightSource[0].specular *
				pow(NdotHV,gl_FrontMaterial.shininess);
	}
	
	gl_FrontColor =  NdotL * diffuse +specular ;

	gl_Position = ftransform();
}