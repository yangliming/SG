using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace SG
{

    public class Synnies : Word
    {
        /// <summary>
        /// A word to describe things that synergize together,
        /// it's a concept that I came up with after dreaming
        /// about trying to understand some quiz and having people
        /// help me explain what Synnies was. I don't really understand
        /// the idea of synnies, but I want to be able to incorporate it
        /// as a game mechanic. It is not meant to be a Word, but it
        /// is here for the meantime so I won't forget about it.
        /// </summary>
        public Synnies()
            : base("Synnies")
        {
        }
    }

    public class Strength : Word
    {
        public Strength()
            : base("Strength")
        {
        }

        public override void Action()
        {
            System.Console.WriteLine("You used Strength!");
        }

        public override string Description()
        {
            return "Word Strength!";
        }
    }

    public class Tears : Word
    {
        public Tears()
            : base("Tears")
        {
        }

        public override void Action()
        {
            throw new NotImplementedException();
        }

        public override string Description()
        {
            return "Word Tears";
        }
    }
}
