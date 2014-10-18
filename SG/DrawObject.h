#ifndef DRAWOBJECT_H
#define DRAWOBJECT_H

#include "TextureHandler.h"

typedef struct 
{
	float x;
	float y;
	float z;
	float width;
	float height;
	bool draw;
	TIID tIID;
} DRAWVALS, *PDRAWVALS;

class DrawObject
{
public:
	DrawObject(float x, float y, float z, float width, float height, bool draw, std::wstring filename);
	~DrawObject();

	PDRAWVALS GetDrawValues();

	void move(float x, float y, float z);

	void setX(float x);
	void setY(float y);
	void setZ(float z);
	void setWidth(float width);
	void setHeight(float height);
	void setDraw(bool draw);
	void setFilename(std::wstring filename);

	float getX() const;
	float getY() const;
	float getZ() const;
	float getWidth() const;
	float getHeight() const;
	bool getDraw() const;
	std::wstring getFilename() const;

	// virtual std::wstring toString();

private:
	std::wstring m_filename;
	DRAWVALS m_drawValues;
};

#endif // DRAWOBJECT_H