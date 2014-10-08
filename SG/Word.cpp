#include "Word.h"

Word::Word(std::wstring word)
: WordName(word)
{
}

std::wstring Word::ToString()
{
	return WordName;
}