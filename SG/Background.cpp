#include "Background.h"

Background::Background(float x, float y, float width, float height, std::wstring filename)
	: DrawObject(x, y, -1, width, height, true, filename)
{
}

Background::~Background()
{
}

std::wstring Background::toString()
{
	return L"The background!";
}