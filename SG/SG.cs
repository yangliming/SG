using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace SG
{
    public class SG
    {
        public static void Main()
        {
            GameState.AddPlayer(new Fighter());
            GameState.AddEnemy(new Rat());
            GameState.AddEnemy(new Rat());

            while (GameState.Running())
            {
                GameState.TakeTurn();
                GameState.ClearDefeated();
            }
        }
    }
}
