using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace SG
{
    public abstract class Word
    {
        public string WordName;

        public Word(string word)
        {
            WordName = word;
        }

        public abstract void Action();
        public abstract string Description();

        public override string ToString()
        {
            return WordName;
        }
    }
}
