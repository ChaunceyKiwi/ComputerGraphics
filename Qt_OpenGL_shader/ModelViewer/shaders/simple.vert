#version 330
layout(location = 0) in vec3 position;
layout(location = 1) in vec3 color;
layout(location = 2) in vec3 normal_;

out vec4 vColor;
uniform mat4 mvpMatrix;

void main()
{
    float diffuse;

    if (normal_.x == 0.0 && normal_.y == 0.0 && normal_.z == 0.0){
        diffuse = 1.0;
    }
    else{
        vec4 new_normal = normalize(mvpMatrix * vec4(normal_,0.0));

        vec4 LightPosition1 = vec4(3000,0,0,0);
        vec4 LightPosition2 = vec4(0,0,3000,0);
        vec4 LightPosition3 = vec4(0,3000,0,0);
        vec4 LightPosition4 = vec4(-3000,0,0,0);
        vec4 LightPosition5 = vec4(0,0,-3000,0);
        vec4 LightPosition6 = vec4(0,-3000,0,0);

        vec4 lightVec1 = normalize(LightPosition1 - mvpMatrix * gl_Position);
        vec4 lightVec2 = normalize(LightPosition2 - mvpMatrix * gl_Position);
        vec4 lightVec3 = normalize(LightPosition3 - mvpMatrix * gl_Position);
        vec4 lightVec4 = normalize(LightPosition4 - mvpMatrix * gl_Position);
        vec4 lightVec5 = normalize(LightPosition5 - mvpMatrix * gl_Position);
        vec4 lightVec6 = normalize(LightPosition6 - mvpMatrix * gl_Position);

        float diffuse1 = 0.2 * max(dot(lightVec1, new_normal), 0.0);
        float diffuse2 = 0.2 * max(dot(lightVec2, new_normal), 0.0);
        float diffuse3 = 0.4 * max(dot(lightVec3, new_normal), 0.0);
        float diffuse4 = 0.2 * max(dot(lightVec4, new_normal), 0.0);
        float diffuse5 = 0.2 * max(dot(lightVec5, new_normal), 0.0);
        float diffuse6 = 0.4 * max(dot(lightVec6, new_normal), 0.0);
        diffuse = diffuse1+diffuse2+diffuse3+diffuse4+diffuse5+diffuse6;

        if (diffuse < 0.125)
              diffuse = 0.125;
        if (diffuse > 1.00)
              diffuse = 1.00;
    }

    gl_Position =  mvpMatrix * vec4(position, 1.0);
    vColor = vec4(color*diffuse, 1.0f);
}
