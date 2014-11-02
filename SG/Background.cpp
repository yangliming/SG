#include "Background.h"
#include "misc.h"

Background::Background(float x, float y, float width, float height, std::wstring filename)
	: DrawObject(x, y, DEPTH_LVL_9, width, height, true, filename)
{
}

Background::~Background()
{
}

std::wstring Background::toString()
{
	return L"The background!";
}