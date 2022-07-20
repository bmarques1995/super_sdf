#version 400 core

in vec2 v_TexCoord;
out vec4 outColor;
uniform sampler2D textureSampler;
uniform vec4 bgColor;
uniform vec4 fgColor;
uniform float pxRange;

float median(float r, float g, float b);
float screenPxRange();

void main(void)
{
    vec4 debug = vec4(v_TexCoord, .0f, 1.0f);
	vec3 msd = texture(textureSampler, v_TexCoord).rgb;
    float sd = median(msd.r, msd.g, msd.b);
    float screenPxDistance = screenPxRange()*(sd - 0.5);
    float opacity = clamp(screenPxDistance + 0.5, 0.0, 1.0);
    outColor = mix(bgColor, fgColor, opacity);
}

float median(float r, float g, float b)
{
    return max(min(r, g), min(max(r, g), b));
}

float screenPxRange()
{
    vec2 unitRange = vec2(pxRange)/vec2(textureSize(textureSampler, 0));
    vec2 screenTexSize = vec2(1.0)/fwidth(v_TexCoord);
    return max(0.5*dot(unitRange, screenTexSize), 1.0);
}
