#ifndef WORD_H
#define WORD_H

#include <string>

class Word
{
public:
	std::wstring WordName;

	Word(std::wstring word);
	virtual void Action() = 0;
	virtual std::wstring Description() = 0;
	virtual std::wstring ToString();
};

#endif // WORD_H