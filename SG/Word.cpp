#include "Word.h"

Word::Word(std::wstring word)
: m_word(word)
{
}

std::wstring Word::toString()
{
	return m_word;
}