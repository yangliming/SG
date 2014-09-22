using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace SG
{
    public abstract class GameUnit
    {
        public int gu_totalhp;
        public int gu_currenthp;

        public int gu_attack;
        public int gu_defense;

        public string gu_type;

        public GameUnit(int totalhp, int attack, int defense, string type)
        {
            gu_totalhp = totalhp;
            gu_currenthp = totalhp;

            gu_attack = attack;
            gu_defense = defense;

            gu_type = type;
        }

        public abstract void Action();
        public abstract override string ToString();

        public void CheckDefeated()
        {
            if (gu_currenthp <= 0)
            {
                System.Console.WriteLine(gu_type + " defeated!");
            }
        }
    }
}
