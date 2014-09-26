using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace SG
{
    public class Player : PlayableUnit
    {

        public Player()
            : base(10,
                   3,
                   0,
                   "Player")
        {
        }

        public override void Action()
        {
            IOUtils.WriteLine("Player's Turn!");

            IOUtils.SetForegroundColor(ConsoleColor.Red);
            IOUtils.WriteLine("HP : " + gu_currenthp + "/" + gu_totalhp);

            IOUtils.SetForegroundColor(ConsoleColor.Yellow);
            IOUtils.WriteLine("Attack: " + gu_attack);

            IOUtils.SetForegroundColor(ConsoleColor.Green);
            IOUtils.WriteLine("Defense : " + gu_defense);

            IOUtils.WriteLine();
            IOUtils.ResetColor();

        GetAction:
            IOUtils.WriteLine("Options: ");
            IOUtils.WriteLine("A: Attack");
            IOUtils.WriteLine("B: Skills");
            IOUtils.WriteLine("C: Words");
            IOUtils.WriteLine("D: Items");
            IOUtils.WriteLine();

            char cmd = char.ToUpper(IOUtils.ReadKey().KeyChar);

            switch (cmd)
            {
                case 'A':
                    IOUtils.WriteLine("Choose who to Attack");
                    for (int i = 1; i <= GameState.GameUnitsEnemies.Count; i++)
                        IOUtils.WriteLine(i + ": " + GameState.GameUnitsEnemies[i - 1].ToString());
                    IOUtils.WriteLine();

                    int enemy;
                    do
                    {
                        cmd = IOUtils.ReadKey().KeyChar;
                    }
                    while (!int.TryParse(cmd.ToString(), out enemy)
                        || enemy < 1
                        || enemy > GameState.GameUnitsEnemies.Count);

                    var gu_enemy = GameState.GameUnitsEnemies[enemy - 1];

                    int damage = this.gu_attack - gu_enemy.gu_defense;

                    if (damage < 1)
                        damage = 1;
                        
                    gu_enemy.gu_currenthp -= damage;
                    IOUtils.WriteLine("Player did " + damage + " points of damage!");
                    gu_enemy.CheckDefeated();

                    break;

                case 'B':


                    break;

                case 'C':

                    IOUtils.WriteLine("Type a word to use:");

                    Word word = WordHandler.TypeWord();
                    if (word != null)
                        word.Action();

                    break;

                case 'D':
                    if (GameState.GameItemsPlayer.Count == 0)
                    {
                        IOUtils.WriteLine("No Items!");
                        goto GetAction;
                    }

                    IOUtils.WriteLine("Inventory:");
                    var items = GameState.GetItems();


                    for (int i = 1; i <= items.Count; i++)
                        IOUtils.WriteLine(i + ": " + items[i - 1].Key.ToString() + ", " + items[i - 1].Value + " remaining");
                    IOUtils.WriteLine("B: Back");
                    IOUtils.WriteLine();

                    int item;
                    do
                    {
                        cmd = char.ToUpper(IOUtils.ReadKey().KeyChar);
                        if (cmd == 'B')
                            goto GetAction;
                    }
                    while (!int.TryParse(cmd.ToString(), out item)
                        || item < 1
                        || item > items.Count);

                    if (!items[item - 1].Key.Use())
                        goto GetAction;
                    break;
                default:
                    goto GetAction;
            }

            IOUtils.ReadKey();
            IOUtils.Clear();
        }
    }
}
