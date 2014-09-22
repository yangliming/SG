using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace SG
{
    public class Fighter : GameUnit
    {
        public Fighter()
            : base(10,
                   3,
                   0,
                   "Fighter")
        {
        }

        public override void Action()
        {
            System.Console.WriteLine("Fighter's Turn!");

            Console.ForegroundColor = ConsoleColor.Red;
            System.Console.WriteLine("HP : " + gu_currenthp + "/" + gu_totalhp);

            Console.ForegroundColor = ConsoleColor.Yellow;
            System.Console.WriteLine("Attack: " + gu_attack);

            Console.ForegroundColor = ConsoleColor.Green;
            System.Console.WriteLine("Defense : " + gu_defense);

            System.Console.WriteLine();
            Console.ResetColor();

        GetAction:
            System.Console.WriteLine("Options: ");
            System.Console.WriteLine("A: Attack");
            System.Console.WriteLine();

            char cmd = char.ToUpper(System.Console.ReadKey(true).KeyChar);

            switch (cmd)
            {
                case 'A':
                    System.Console.WriteLine("Choose who to Attack");
                    for (int i = 1; i <= GameState.GameUnitsEnemies.Count; i++)
                        System.Console.WriteLine(i + ": " + GameState.GameUnitsEnemies[i - 1].ToString());
                    System.Console.WriteLine();

                    cmd = System.Console.ReadKey(true).KeyChar;

                    int enemy;
                    if (!int.TryParse(cmd.ToString(), out enemy)
                        || enemy < 1
                        || enemy > GameState.GameUnitsEnemies.Count)
                        goto case 'A';

                    var gu_enemy = GameState.GameUnitsEnemies[enemy - 1];

                    int damage = this.gu_attack - gu_enemy.gu_defense;

                    if (damage < 1)
                        damage = 1;
                        
                    gu_enemy.gu_currenthp -= damage;
                    System.Console.WriteLine("Fighter did " + damage + " points of damage!");
                    gu_enemy.CheckDefeated();

                    break;
                default:
                    goto GetAction;
            }

            System.Console.ReadKey(true);
            System.Console.Clear();
        }

        public override string ToString()
        {
            return "Fighter: " + "HP: " + this.gu_currenthp + "/" + this.gu_totalhp;
        }
    }
}
