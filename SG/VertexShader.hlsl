cbuffer cbCamera : register(b0)
{
	float4x4 wvp;
}

cbuffer cbVertex : register(b1)
{
	float4x4 v0;
	float4x4 v1;
	float4x4 v2;
	float4x4 v3;
}

struct VS_IN
{
	uint index : INDEX;
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

	switch (input.index)
	{
	case 0:
		output.pos = mul(input.pos, v0); break;
	case 1:
		output.pos = mul(input.pos, v1); break;
	case 2:
		output.pos = mul(input.pos, v2); break;
	case 3:
		output.pos = mul(input.pos, v3); break;
	default:
		output.pos = input.pos; break;
	}

	output.pos = mul(output.pos, wvp);
	output.tex = input.tex;

	return output;
}