#version 330 core
out vec4 FragColor;

in vec3 FragPos;  
in vec3 Normal;
in vec3 Position;
in vec2 TexCoords;

uniform vec3 cameraPos;
uniform sampler2D texture_diffuse1;
uniform sampler2D texture_specular1;
uniform sampler2D texture_normal1;
uniform sampler2D texture_height1;
uniform samplerCube skybox;

void main()
{
    vec3 I = normalize(Position - cameraPos);
    vec3 R = reflect(I, normalize(Normal));

    // ambient
    vec4 ambient = vec4(texture(texture_diffuse1, TexCoords).rgb, 1.0);

    // diffuse 
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(R - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec4 diffuse = vec4(texture(skybox, R).rgb, 1.0) * diff * texture(texture_height1, TexCoords);

    // specular
    vec3 viewDir = normalize(cameraPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32.0);
    vec4 specular = vec4(texture(skybox, R).rgb, 1.0) * spec * texture(texture_specular1, TexCoords);

    //FragColor = texture(texture_diffuse1, TexCoords);
    //FragColor = vec4(texture(skybox, R).rgb, 1.0);
    FragColor = ambient + diffuse + specular;
}
