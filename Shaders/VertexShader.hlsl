cbuffer cbPerObject
{
	float4x4 WVP;
	bool HasTexture;
};

Texture2D ObjTexture;
SamplerState ObjSamplerState;

struct VS_OUTPUT
{
	float4 pos : SV_POSITION;
	float2 TexCoord : TEXCOORD;
};

VS_OUTPUT main(float4 pos : POSITION, float2 TexCoord : TEXCOORD)
{
	VS_OUTPUT output;
	output.pos = mul(pos, WVP);
	output.TexCoord = TexCoord;
	return output;
}