#ifndef WORDHANDLER_H
#define WORDHANDLER_H

#include <list>
#include <map>
#include <string>

class WordHandler
{
public:
	WordHandler();
	~WordHandler();

	void AddWord(Word* word);
	Word* NextChar(wchar_t c);
private:
	class WordTreeNode
	{
	public:
		wchar_t NodeChar;
		WordTreeNode* Parent;
		std::list<WordTreeNode*> Children;

		WordTreeNode(wchar_t c, WordTreeNode* parent = NULL);
		~WordTreeNode();

		bool ShallowContains(wchar_t c) const;
		WordTreeNode* ShallowGetNode(wchar_t c);

		bool operator==(const WordTreeNode& node);
		bool operator!=(const WordTreeNode& node);
	};
	class WordTree
	{
	public:
		WordTree();
		~WordTree();

		void AddWord(std::wstring word);
		std::wstring NextChar(wchar_t c);

	private:
		WordTreeNode Root;
		std::list<WordTreeNode*> Pointers;

		std::wstring GetWord(WordTreeNode* word);
	};

	std::map<std::wstring, Word*> Words;
	WordTree Characters;
};

#endif // WORDHANDLER_H