using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace SG
{
    public class Potion : GameItem
    {
        private const int HealAmount = 10;

        public Potion()
            : base("Potion")
        {
        }

        public override bool Use()
        {
            System.Console.WriteLine("Who do you want to use potion on?");
            for (int i = 1; i <= GameState.GameUnitsPlayers.Count; i++)
                System.Console.WriteLine(i + ": " + GameState.GameUnitsPlayers[i - 1].ToString());
            System.Console.WriteLine("B: Back");
            System.Console.WriteLine();

            int toUse;
            char cmd;
            do
            {
                cmd = char.ToUpper(System.Console.ReadKey(true).KeyChar);

                if (cmd == 'B')
                    return false;
            }
            while (!int.TryParse(cmd.ToString(), out toUse)
                || toUse < 1
                || toUse > GameState.GameUnitsPlayers.Count);

            int heal;
            var gu_player = GameState.GameUnitsPlayers[toUse - 1];
            if (gu_player.gu_totalhp == gu_player.gu_currenthp)
            {
                System.Console.WriteLine("Unit already at full hp!");
                return false;
            }
            else if (gu_player.gu_currenthp + HealAmount > gu_player.gu_totalhp)
                heal = gu_player.gu_totalhp - gu_player.gu_currenthp;
            else
                heal = HealAmount;

            gu_player.gu_currenthp += heal;

            System.Console.WriteLine("Healed " + gu_player.gu_type + " by " + heal + " points!");

            base.DecrementCount();
            return true;
        }

        public override string Description()
        {
            return "Heals any unit by " + HealAmount + " points!";
        }
    }

    public class Rock : GameItem
    {
        private const int DamageAmount = 5;

        public Rock()
            : base("Rock")
        {
        }

        public override bool Use()
        {
            System.Console.WriteLine("Who do you want to use rock on?");
            for (int i = 1; i <= GameState.GameUnitsEnemies.Count; i++)
                System.Console.WriteLine(i + ": " + GameState.GameUnitsEnemies[i - 1].ToString());
            System.Console.WriteLine("B: Back");
            System.Console.WriteLine();

            int toUse;
            char cmd;
            do
            {
                cmd = char.ToUpper(System.Console.ReadKey(true).KeyChar);

                if (cmd == 'B')
                    return false;
            }
            while (!int.TryParse(cmd.ToString(), out toUse)
                || toUse < 1
                || toUse > GameState.GameUnitsEnemies.Count);

            var gu_enemy = GameState.GameUnitsEnemies[toUse - 1];
            int damage = DamageAmount - gu_enemy.gu_defense;
            gu_enemy.gu_currenthp -= damage;

            System.Console.WriteLine("Damaged " + gu_enemy.gu_type + " by " + damage + " points!");

            base.DecrementCount();
            return true;
        }

        public override string Description()
        {
            return "Damages enemy unit by " + DamageAmount + " points!";
        }
    }
}
