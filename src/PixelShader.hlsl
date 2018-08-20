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

float4 main(VS_OUTPUT input) : SV_TARGET
{
	return ObjTexture.Sample(ObjSamplerState, input.TexCoord);
	//return float4(0.0f, 0.0f, 1.0f, 1.0f);
}