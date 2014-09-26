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
            IOUtils.WriteLine("Rat's Turn!");
            IOUtils.WriteLine();
            IOUtils.ReadKey();

            var gu_player = GameState.GamePlayer;
            IOUtils.WriteLine("Rat Attacks " + gu_player.gu_type);
            int damage = this.gu_attack - gu_player.gu_defense;
            IOUtils.ReadKey();

            if (damage < 1)
                damage = 1;

            gu_player.gu_currenthp -= damage;
            IOUtils.WriteLine("Rat did " + damage + " points of damage!");

            IOUtils.ReadKey();
            IOUtils.Clear();
        }

        public override string ToString()
        {
            return "Rat: " + "HP: " + this.gu_currenthp + "/" + this.gu_totalhp;
        }
    }
}
