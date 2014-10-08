cbuffer Transforms
{
	float4x4 transform;
}

struct VS_IN
{
	float4 pos : POSITION;
	float2 tex : TEXCOORD;
};

struct PS_IN
{
	float4 pos : SV_POSITION;
	float2 tex : TEXCOORD;
};

PS_IN main(VS_IN input)
{
	PS_IN output;

	output.pos = mul(input.pos, transform);
	output.tex = input.tex;

	return output;
}