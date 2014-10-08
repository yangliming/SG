#ifndef GLOBAL_H
#define GLOBAL_H

struct VECTOR3
{
	float X;
	float Y;
	float Z;
};

struct VECTOR4
{
	float X;
	float Y;
	float Z;
	float W;
};

struct COLOR
{
	float R;
	float G;
	float B;
	float A;
};

struct TEXCOORD
{
	float U;
	float V;
};

struct VERTEX
{
	VECTOR3 Position;
	TEXCOORD TexCoords;

	VERTEX(float x, float y, float z, float u, float v)
	{
		Position.X = x;
		Position.Y = y;
		Position.Z = z;
		TexCoords.U = u;
		TexCoords.V = v;
	}
};

#endif // GLOBAL_H