using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace SG
{
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
}
