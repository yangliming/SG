using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace SG
{
    public class Rat : GameUnit
    {
        public Rat()
            : base(5,
                   1,
                   0,
                   "Rat")
        {
        }

        public override void Action()
        {
            System.Console.WriteLine("Rat's Turn!");
            System.Console.WriteLine();
            System.Console.ReadKey(true);

            var rand = new Random();
            int toAttack = rand.Next(GameState.GameUnitsPlayers.Count);

            System.Console.WriteLine("Rat Attacks " + GameState.GameUnitsPlayers[toAttack].gu_type);
            System.Console.WriteLine();

            var gu_player = GameState.GameUnitsPlayers[toAttack];

            int damage = this.gu_attack - gu_player.gu_defense;

            if (damage < 1)
                damage = 1;

            gu_player.gu_currenthp -= damage;
            System.Console.WriteLine("Rat did " + damage + " points of damage!");
            System.Console.WriteLine();

            System.Console.ReadKey(true);
            System.Console.Clear();
        }

        public override string ToString()
        {
            return "Rat: " + "HP: " + this.gu_currenthp + "/" + this.gu_totalhp;
        }
    }
}
