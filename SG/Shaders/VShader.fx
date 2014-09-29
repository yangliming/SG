void VShader(float3 pos : POSITION,
			 float2 tex : TEXCOORD,
			 out float3 opos : POSITION,
			 out float2 otex : TEXCOORD)
{
    opos = pos;
	otex = tex;
}
