#include "Word.h"

Word::Word(std::wstring word)
: m_word(word)
{
}

Word::~Word()
{
}

std::wstring Word::toString()
{
	return m_word;
}