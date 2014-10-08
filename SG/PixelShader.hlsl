Texture2D image;
SamplerState quality;

struct PS_IN
{
	float4 pos : SV_POSITION;
	float2 tex : TEXCOORD;
};

float4 main(PS_IN input) : SV_TARGET
{
	return image.Sample(quality, input.tex);
}