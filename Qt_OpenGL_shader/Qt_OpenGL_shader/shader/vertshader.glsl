#ifdef GL_ES
precision mediump int;
precision mediump float;
#endif

attribute vec4 colAttr;
attribute vec4 posAttr;
attribute vec4 norAttr;
varying vec4 col;
uniform mat4 mvpMatrix;
void main()
{
    vec4 LightPosition1 = vec4(3000,0,0,0);
    vec4 LightPosition2 = vec4(0,0,3000,0);
    vec4 LightPosition3 = vec4(0,3000,0,0);
    vec4 LightPosition4 = vec4(-3000,0,0,0);
    vec4 LightPosition5 = vec4(0,0,-3000,0);
    vec4 LightPosition6 = vec4(0,-3000,0,0);

    vec4 new_normal = normalize(mvpMatrix * norAttr);

    gl_Position = mvpMatrix * posAttr;

    vec4 lightVec1 = normalize(LightPosition1 - mvpMatrix * gl_Position);
    vec4 lightVec2 = normalize(LightPosition2 - mvpMatrix * gl_Position);
    vec4 lightVec3 = normalize(LightPosition3 - mvpMatrix * gl_Position);
    vec4 lightVec4 = normalize(LightPosition4 - mvpMatrix * gl_Position);
    vec4 lightVec5 = normalize(LightPosition5 - mvpMatrix * gl_Position);
    vec4 lightVec6 = normalize(LightPosition6 - mvpMatrix * gl_Position);


    float diffuse1 = 0.3 * max(dot(lightVec1, new_normal), 0.0);
    float diffuse2 = 0.3 * max(dot(lightVec2, new_normal), 0.0);
    float diffuse3 = 0.3 * max(dot(lightVec3, new_normal), 0.0);
    float diffuse4 = 0.3 * max(dot(lightVec4, new_normal), 0.0);
    float diffuse5 = 0.3 * max(dot(lightVec5, new_normal), 0.0);
    float diffuse6 = 0.3 * max(dot(lightVec6, new_normal), 0.0);
    float diffuse = diffuse1+diffuse2+diffuse3+diffuse4+diffuse5+diffuse6;

    if (diffuse < 0.125)
          diffuse = 0.125;
    if (diffuse > 1.00)
          diffuse = 1.00;

    gl_PointSize = 10.0;

    col = colAttr*diffuse;
}
