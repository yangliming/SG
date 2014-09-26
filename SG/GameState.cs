using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace SG
{
    public static class GameState
    {
        public static Player GamePlayer;
        public static List<GameUnit> GameUnitsEnemies;

        public static Dictionary<GameItem, int> GameItemsPlayer;

        static GameState()
        {
            GamePlayer = new Player();
            GameUnitsEnemies = new List<GameUnit>();
            GameItemsPlayer = new Dictionary<GameItem, int>();
        } 

        public static bool Running()
        {
            if (GameUnitsEnemies.Count > 0)
                return true;
            else
                return false;
        }

        public static void TakeTurn()
        {
            GamePlayer.Action();

            foreach (GameUnit gu in GameUnitsEnemies)
            {
                if (gu.gu_currenthp > 0)
                    gu.Action();
            }
        }

        public static void ClearDefeated()
        {
            var toRemove =
                GameUnitsEnemies.Where(gu =>
                    {
                        if (gu.gu_currenthp <= 0)
                            return true;
                        return false;
                    });

            for (int i = 0; i < toRemove.Count(); i++)
                RemoveGameUnit(toRemove.ElementAt(i));
        }

        public static void AddEnemy(GameUnit enemy)
        {
            GameUnitsEnemies.Add(enemy);
        }

        public static void AddItem(GameItem item, int amount = 1)
        {
            if (amount < 1)
                return;

            if (!GameItemsPlayer.ContainsKey(item))
                GameItemsPlayer.Add(item, amount);
            else
                GameItemsPlayer[item] += amount;
        }

        public static List<KeyValuePair<GameItem, int>> GetItems()
        {
            return GameItemsPlayer.ToList();
        }

        public static void RemoveGameUnit(GameUnit gu)
        {
            GameUnitsEnemies.Remove(gu);
        }
    }
}
