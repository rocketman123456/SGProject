#version 330 core
out vec4 FragColor;

in vec3 Normal;  
in vec3 FragPos;
in vec2 TexCoord;

// light color attrbuties
uniform vec3 lightPos; 
uniform vec3 objectColor;
uniform vec3 lightColor;
// texture attrbuties
uniform float mixValue;
uniform sampler2D texture1;
uniform sampler2D texture2;

void main()
{
    // ambient
    float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * lightColor;
  	
    // diffuse 
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;
            
    vec3 result = (ambient + diffuse) * objectColor;

	// linearly interpolate between both textures (80% container, 20% awesomeface)
    //FragColor = vec4(result, 1.0);
	FragColor = mix(texture(texture1, TexCoord), texture(texture2, TexCoord), mixValue);
	FragColor = FragColor * vec4(result, 1.0);
}