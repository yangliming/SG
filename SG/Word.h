#ifndef WORD_H
#define WORD_H

#include <string>

class Word
{
public:
	std::wstring m_word;

	Word(std::wstring word);
	virtual ~Word();

	virtual void action() = 0;
	virtual std::wstring description() = 0;
	virtual std::wstring toString();
};

#endif // WORD_H