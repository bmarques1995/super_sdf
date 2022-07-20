#pragma pack_matrix( column_major )

struct VSIn
{
	float3 pos: POSITION;
    float2 texCoord : TEXCOORD;
};

cbuffer u_Model : register(b0)
{
    matrix model;
};

cbuffer u_Projection : register(b1)
{
    matrix projection;
};

struct PSIn
{
	float4 pos : SV_POSITION;
    float2 texCoord : TEXCOORD;
};


PSIn main(VSIn input)
{
    PSIn output;
    float4x4 mvp = mul(model, projection);
    output.pos = mul(float4(input.pos, 1.0f), mvp);
    output.texCoord = input.texCoord;
    return output;
}

