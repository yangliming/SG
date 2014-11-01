#include "Word.h"
#include "WordHandler.h"
#include <algorithm>

WordHandler::WordHandler()
{
}

WordHandler::~WordHandler()
{
	auto iter = m_words.begin();

	while (iter != m_words.end())
	{
		delete iter->second;
		iter++;
	}
}

void WordHandler::addWord(Word* word)
{
	std::transform(word->m_word.begin(), word->m_word.end(), word->m_word.begin(), towlower);
	m_characters.addWord(word->m_word);
	m_words[word->m_word] = word;
}

Word* WordHandler::nextChar(wchar_t c)
{
	c = towlower(c);
	std::wstring word = m_characters.nextChar(c);
	if (word.empty())
		return NULL;

	return m_words[word];
}

WordHandler::WordTreeNode::WordTreeNode(wchar_t c, WordTreeNode* parent)
: m_nodechar(c), m_parent(parent)
{
}

WordHandler::WordTreeNode::~WordTreeNode()
{
	auto iter = m_children.begin();
	while (iter != m_children.end())
	{
		if (*iter != nullptr)
		{
			delete (*iter);
			(*iter) = nullptr;
		}
		iter++;
	}
}

bool WordHandler::WordTreeNode::shallowContains(wchar_t c) const
{
	c = towlower(c);
	auto iter = m_children.begin();
	while (iter != m_children.end())
	{
		if ((*iter)->m_nodechar == c)
			return true;
		iter++;
	}
	return false;
}

WordHandler::WordTreeNode* WordHandler::WordTreeNode::shallowGetNode(wchar_t c)
{
	c = towlower(c);
	auto iter = m_children.begin();
	while (iter != m_children.end())
	{
		if ((*iter)->m_nodechar == c)
			return (*iter);
		iter++;
	}
	return NULL;
}

bool WordHandler::WordTreeNode::operator==(const WordTreeNode& node)
{
	if (this->m_nodechar == node.m_nodechar)
		return true;
	return false;
}

bool WordHandler::WordTreeNode::operator!=(const WordTreeNode& node)
{
	if (this->m_nodechar == node.m_nodechar)
		return false;
	return true;
}

WordHandler::WordTree::WordTree()
: m_root(L'\0')
{
}

WordHandler::WordTree::~WordTree()
{
	m_pointers.clear();
}

void WordHandler::WordTree::addWord(std::wstring word)
{
	WordTreeNode* current = &m_root;
	WordTreeNode* next = NULL;

	for (int i = 0; i < word.length(); i++)
	{
		next = current->shallowGetNode(word[i]);
		if (next == NULL)
		{
			next = new WordTreeNode(word[i], current);
			current->m_children.push_back(next);
		}
		current = next;
	}

	if (!current->shallowContains(L'\0'))
		current->m_children.push_back(new WordTreeNode(L'\0', current));
}

std::wstring WordHandler::WordTree::nextChar(wchar_t c)
{
	auto iter = m_pointers.begin();
	while (iter != m_pointers.end())
	{
		if ((*iter)->shallowContains(c))
		{
			(*iter) = (*iter)->shallowGetNode(c);

			if ((*iter)->shallowContains(L'\0'))
			{
				WordTreeNode* word = *iter;
				m_pointers.clear();
				return getWord(word);
			}
		}
		else
		{
			iter = m_pointers.erase(iter);
		}
		iter++;
	}

	if (m_root.shallowContains(c))
		m_pointers.push_back(m_root.shallowGetNode(c));

	return L"";
}

std::wstring WordHandler::WordTree::getWord(WordTreeNode* node)
{
	if (node == NULL || node->m_nodechar == L'\0')
		return L"";
	return getWord(node->m_parent) + node->m_nodechar;
}