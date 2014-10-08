#include "Word.h"
#include "WordHandler.h"
#include <algorithm>

WordHandler::WordHandler()
{
}

WordHandler::~WordHandler()
{
	auto iter = Words.begin();

	while (iter != Words.end())
	{
		delete iter->second;
	}
}

void WordHandler::AddWord(Word* word)
{
	std::transform(word->WordName.begin(), word->WordName.end(), word->WordName.begin(), towlower);
	Characters.AddWord(word->WordName);
	Words[word->WordName] = word;
}

Word* WordHandler::NextChar(wchar_t c)
{
	c = towlower(c);
	std::wstring word = Characters.NextChar(c);
	if (word.empty())
		return NULL;

	return Words[word];
}

WordHandler::WordTreeNode::WordTreeNode(wchar_t c, WordTreeNode* parent)
: NodeChar(c), Parent(parent)
{
}

WordHandler::WordTreeNode::~WordTreeNode()
{
	if (Parent != NULL)
	{
		delete Parent;
		Parent = NULL;
	}

	auto iter = Children.begin();
	while (iter != Children.end())
	{
		if (*iter != NULL)
		{
			delete (*iter);
			(*iter) = NULL;
		}
	}
}

bool WordHandler::WordTreeNode::ShallowContains(wchar_t c) const
{
	c = towlower(c);
	auto iter = Children.begin();
	while (iter != Children.end())
	{
		if ((*iter)->NodeChar == c)
			return true;
	}
	return false;
}

WordHandler::WordTreeNode* WordHandler::WordTreeNode::ShallowGetNode(wchar_t c)
{
	c = towlower(c);
	auto iter = Children.begin();
	while (iter != Children.end())
	{
		if ((*iter)->NodeChar == c)
			return (*iter);
	}
	return NULL;
}

bool WordHandler::WordTreeNode::operator==(const WordTreeNode& node)
{
	if (this->NodeChar == node.NodeChar)
		return true;
	return false;
}

bool WordHandler::WordTreeNode::operator!=(const WordTreeNode& node)
{
	if (this->NodeChar == node.NodeChar)
		return false;
	return true;
}

WordHandler::WordTree::WordTree()
: Root(L'\0')
{
}

WordHandler::WordTree::~WordTree()
{
	Pointers.clear();
}

void WordHandler::WordTree::AddWord(std::wstring word)
{
	WordTreeNode* current = &Root;
	WordTreeNode* next = NULL;

	for (int i = 0; i < word.length(); i++)
	{
		next = current->ShallowGetNode(word[i]);
		if (next == NULL)
		{
			next = new WordTreeNode(word[i], current);
			current->Children.push_back(next);
		}
		current = next;
	}

	if (!current->ShallowContains(L'\0'))
		current->Children.push_back(new WordTreeNode(L'\0', current));
}

std::wstring WordHandler::WordTree::NextChar(wchar_t c)
{
	auto iter = Pointers.begin();
	while (iter != Pointers.end())
	{
		if ((*iter)->ShallowContains(c))
		{
			(*iter) = (*iter)->ShallowGetNode(c);

			if ((*iter)->ShallowContains(L'\0'))
			{
				WordTreeNode* word = *iter;
				Pointers.clear();
				return GetWord(word);
			}
		}
		else
		{
			iter = Pointers.erase(iter);
		}
	}

	if (Root.ShallowContains(c))
		Pointers.push_back(Root.ShallowGetNode(c));

	return L"";
}

std::wstring WordHandler::WordTree::GetWord(WordTreeNode* node)
{
	if (node == NULL || node->NodeChar == L'\0')
		return L"";
	return GetWord(node->Parent) + node->NodeChar;
}