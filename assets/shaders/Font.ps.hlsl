struct PSIn
{
    float4 pos : SV_POSITION;
    float2 texCoord : TEXCOORD;
};

Texture2D objTexture : u_TextureData : register(t0);
SamplerState objSampler : u_TextureSampler : register(s0);

cbuffer u_bgColor
{
    float4 bgColor;
};
cbuffer u_fgColor
{
    float4 fgColor;
};
cbuffer u_pxRange
{
    float4 pxRange;
}; // set to distance field's pixel range

float screenPxRange(float2 texCoord);
float median(float r, float g, float b);

float4 main(PSIn input) : SV_TARGET
{
    //return objTexture.SampleLevel(objSampler, input.texCoord, 0.0f);
    float4 debug = float4(input.texCoord, .0f, 1.0f);
    float3 msd = objTexture.SampleLevel(objSampler, input.texCoord, .0f).rgb;
    float sd = median(msd.r, msd.g, msd.b);
    float screenPxDistance = screenPxRange(input.texCoord) * (sd - 0.5);
    float opacity = saturate(screenPxDistance + 0.5);
    return lerp(bgColor, fgColor, opacity);
}

float screenPxRange(float2 texCoord)
{
    uint width;
    uint height;
    uint mipLevels = 1;
    objTexture.GetDimensions(mipLevels, width, height, mipLevels);
    float2 unitRange = float2(pxRange.x, pxRange.x) / float2(width,height);
    float2 screenTexSize = float2(1.0, 1.0) / fwidth(texCoord);
    return max(0.5 * dot(unitRange, screenTexSize), 1.0);
}

float median(float r, float g, float b)
{
    return max(min(r, g), min(max(r, g), b));
}