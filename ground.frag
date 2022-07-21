#version 330 core

// Outputs colors in RGBA
out vec4 FragColor;

in vec3 crntPos0;
in vec3 NormalO;
smooth in vec3 colorO;

uniform vec4 lightColor;
uniform vec3 lightPos;

uniform vec3 camPos;

//vec4 pointLight()
//{	
//	// used in two variables so I calculate it here to not have to do it twice
//	vec3 lightVec = lightPos - crntPos;
//
//	// intensity of light with respect to distance
//	float dist = length(lightVec);
//	float a = 3.0;
//	float b = 0.7;
//	float inten = 1.0f / (a * dist * dist + b * dist + 1.0f);
//
//	// ambient lighting
//	float ambient = 0.20f;
//
//	// diffuse lighting
//	vec3 normal = normalize(NormalO);
//	vec3 lightDirection = normalize(lightVec);
//	float diffuse = max(dot(normal, lightDirection), 0.0f);
//
//	// specular lighting
//	float specularLight = 0.50f;
//	vec3 viewDirection = normalize(camPos - crntPos);
//	vec3 reflectionDirection = reflect(-lightDirection, normal);
//	float specAmount = pow(max(dot(viewDirection, reflectionDirection), 0.0f), 16);
//	float specular = specAmount * specularLight;
//
//	return (diffuse * specular * inten + ambient) * lightColor;
//}

void main()
{
	// FragColor = vec4(color, 1.0f) * lightColor;
	// FragColor = vec4(1.0f, 1.0f, 0.0f, 1.0f);
	// FragColor = pointLight();

//	float ambient = 0.20f;
//
//	vec3 normal = normalize(NormalO);
//	vec3 lightDirection = normalize(lightPos - crntPos0);
//	float diffuse = max(dot(normal, lightDirection), 0.0f);
//
//	FragColor = vec4(colorO, 1.0f) * lightColor * (diffuse + ambient);

	 // ambient
    float ambientStrength = 0.1;
	vec3 color3 = vec3(lightColor[0], lightColor[1], lightColor[2]);
    vec3 ambient = ambientStrength * color3;
    
     // diffuse 
    vec3 norm = normalize(NormalO);
    vec3 lightDir = normalize(lightPos - crntPos0);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * color3;
    // specular
    float specularStrength = 0.5;
    vec3 viewDir = normalize(-crntPos0); // the viewer is always at (0,0,0) in view-space, so viewDir is (0,0,0) - Position => -Position
    vec3 reflectDir = reflect(-lightDir, norm);  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec3 specular = specularStrength * spec * color3; 
    
    vec3 result = (ambient + diffuse + specular) * colorO;
    FragColor = vec4(result, 1.0);
}