#version 330 core
out vec4 FragColor;

in VS_OUT {
    vec3 FragPos;
    vec3 Normal;
    vec2 TexCoords;
} fs_in;

uniform vec3 diffuse;
uniform vec4 custom_color;
uniform bool is_texture_used;
uniform sampler2D texture_diffuse1;

uniform vec3 lightPos;
uniform vec3 viewPos;

void main() {
    vec3 color;
    if (is_texture_used)
        color += texture(texture_diffuse1, fs_in.TexCoords).rgb;
    else
        color += diffuse;
    color = mix(color, vec3(custom_color), custom_color.w);
    
    vec3 ambient = 0.05 * color;
    
    vec3 lightDir = normalize(lightPos - fs_in.FragPos);
    vec3 normal = normalize(fs_in.Normal);
    float diff = max(dot(lightDir, normal), 0.0);
    vec3 diffuse = diff * color;
    
    vec3 viewDir = normalize(viewPos - fs_in.FragPos);
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = 0.0;
    vec3 halfwayDir = normalize(lightDir + viewDir);
    spec = pow(max(dot(normal, halfwayDir), 0.0), 32.0);
    
    vec3 specular = vec3(0.3) * spec;
    vec3 result = ambient + diffuse + specular;
    FragColor = vec4(result, 1.0);
}

vec3 CalcPointLight() {} // TODO: DO THIS