using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace SG
{
    public static class WordHandler
    {
        private class WordTreeNode
        {
            public char NodeChar;

            public WordTreeNode Parent;
            public List<WordTreeNode> Children;

            public WordTreeNode(char c, WordTreeNode parent = null, List<WordTreeNode> children = null)
            {
                NodeChar = c;
                Parent = parent;
                Children = children != null ? children : new List<WordTreeNode>();
            }

            public bool ShallowContains(char c)
            {
                foreach (WordTreeNode node in Children)
                {
                    if (node.NodeChar == c)
                        return true;
                }

                return false;
            }

            public WordTreeNode ShallowGetNode(char c)
            {
                foreach (WordTreeNode node in Children)
                {
                    if (node.NodeChar == c)
                        return node;
                }
                return null;
            }

            public static bool operator ==(WordTreeNode w1, WordTreeNode w2)
            {
                if (object.ReferenceEquals(null, w1) && object.ReferenceEquals(null, w2))
                    return true;
                if (!object.ReferenceEquals(null, w1) && object.ReferenceEquals(null, w2))
                    return false;
                if (object.ReferenceEquals(null, w1) && !object.ReferenceEquals(null, w2))
                    return false;

                if (w1.NodeChar == w2.NodeChar)
                    return true;
                return false;
            }

            public static bool operator !=(WordTreeNode w1, WordTreeNode w2)
            {
                if (object.ReferenceEquals(null, w1) && object.ReferenceEquals(null, w2))
                    return false;
                if (!object.ReferenceEquals(null, w1) && object.ReferenceEquals(null, w2))
                    return true;
                if (object.ReferenceEquals(null, w1) && !object.ReferenceEquals(null, w2))
                    return true;

                if (w1.NodeChar != w2.NodeChar)
                    return true;
                return false;
            }

            public override bool Equals(object obj)
            {
                if (obj is WordTreeNode && this.NodeChar == ((WordTreeNode)obj).NodeChar)
                    return true;
                return false;
            }
        }

        private class WordTree
        {
            private WordTreeNode Root;

            public WordTree()
            {
                Root = new WordTreeNode('\0');
            }

            public void AddWord(string word)
            {
                WordTreeNode current = Root;
                WordTreeNode next;
                for (int i = 0; i < word.Length; i++)
                {
                    char c = char.ToUpper(word[i]);
                    next = current.ShallowGetNode(c);

                    if (next == null)
                    {
                        next = new WordTreeNode(c, current);
                        current.Children.Add(next);
                    }

                    current = next;
                }

                if (!current.ShallowContains('\0'))
                    current.Children.Add(new WordTreeNode('\0', current));
            }

            public string TypeWord()
            {
                List<WordTreeNode> Pointers = new List<WordTreeNode>();

                while (true)
                {
                    ConsoleKeyInfo key = IOUtils.ReadKey();
                    char c = char.ToUpper(key.KeyChar);

                    if (key.Key == ConsoleKey.Escape)
                        return null;

                    for (int i = 0; i < Pointers.Count; i++)
                    {
                        if (Pointers[i].ShallowContains(c))
                        {
                            Pointers[i] = Pointers[i].ShallowGetNode(c);

                            if (Pointers[i].ShallowContains('\0'))
                                return GetWord(Pointers[i]);
                        }
                        else
                        {
                            Pointers.RemoveAt(i);
                            i--;
                        }
                    }

                    if (Root.ShallowContains(c))
                        Pointers.Add(Root.ShallowGetNode(c));
                }
            }

            private string GetWord(WordTreeNode word)
            {
                if (word == null || word.NodeChar == '\0')
                    return "";
                return GetWord(word.Parent) + word.NodeChar;
            }
        }

        private static Dictionary<string, Word> Words;
        private static WordTree Characters;

        static WordHandler()
        {
            Words = new Dictionary<string, Word>();
            Characters = new WordTree();
        }

        public static void AddWord(Word word)
        {
            Characters.AddWord(word.WordName);

            if (!Words.ContainsKey(word.WordName))
                Words.Add(word.WordName.ToUpper(), word);
        }

        public static Word TypeWord()
        {
            string word = Characters.TypeWord();

            if (word == null)
                return null;

            if (Words.ContainsKey(word))
                return Words[word];

            return null;
        }
    }
}
