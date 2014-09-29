Texture2D <float4> xTexture;
sampler TextureSampler;

float4 PShader(float3 pos : POSITION, float2 tex : TEXCOORD) : SV_TARGET
{
	return pos;
}