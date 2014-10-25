#ifndef WORDHANDLER_H
#define WORDHANDLER_H

#include <list>
#include <map>
#include <string>

class Word;

class WordHandler
{
public:
	WordHandler();
	~WordHandler();

	void addWord(Word* word);
	Word* nextChar(wchar_t c);
private:
	class WordTreeNode
	{
	public:
		wchar_t m_nodechar;
		WordTreeNode* m_parent;
		std::list<WordTreeNode*> m_children;

		WordTreeNode(wchar_t c, WordTreeNode* parent = NULL);
		~WordTreeNode();

		bool shallowContains(wchar_t c) const;
		WordTreeNode* shallowGetNode(wchar_t c);

		bool operator==(const WordTreeNode& node);
		bool operator!=(const WordTreeNode& node);
	};
	class WordTree
	{
	public:
		WordTree();
		~WordTree();

		void addWord(std::wstring word);
		std::wstring nextChar(wchar_t c);

	private:
		WordTreeNode m_root;
		std::list<WordTreeNode*> m_pointers;

		std::wstring getWord(WordTreeNode* word);
	};

	std::map<std::wstring, Word*> m_words;
	WordTree m_characters;
};

#endif // WORDHANDLER_H