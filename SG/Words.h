#ifndef WORDS_H
#define WORDS_H

#include "Word.h"

class Strength : public Word
{
public:
	Strength();
	~Strength();

	virtual void action();
	virtual std::wstring description();
private:
};


#endif // WORDS_H