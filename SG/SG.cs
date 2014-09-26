﻿using System;
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
            GameState.AddItem(new Potion(), 5);
            GameState.AddItem(new Rock(), 3);
            GameState.AddEnemy(new Rat());
            GameState.AddEnemy(new Rat());
            WordHandler.AddWord(new Strength());

            while (GameState.Running())
            {
                GameState.TakeTurn();
                GameState.ClearDefeated();
            }
        }
    }
}
