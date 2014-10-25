#ifndef BACKGROUND_H
#define BACKGROUND_H

#include "DrawObject.h"
#include <string>

class Background : public DrawObject
{
public:
	Background(float x, float y, float width, float height, std::wstring filename);
	~Background();

	virtual std::wstring toString();
private:
};

#endif // BACKGROUND_H