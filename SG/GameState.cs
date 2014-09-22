using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace SG
{
    public static class GameState
    {
        public static List<GameUnit> GameUnitsInPlay;

        public static List<GameUnit> GameUnitsPlayers;
        public static List<GameUnit> GameUnitsEnemies;

        public static Dictionary<GameItem, int> GameItemsPlayer;

        static GameState()
        {
            GameUnitsInPlay = new List<GameUnit>();
            GameUnitsPlayers = new List<GameUnit>();
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
            foreach (GameUnit gu in GameUnitsInPlay)
            {
                if (gu.gu_currenthp > 0)
                    gu.Action();
            }
        }

        public static void ClearDefeated()
        {
            var toRemove =
                GameUnitsInPlay.Where(gu =>
                    {
                        if (gu.gu_currenthp <= 0)
                            return true;
                        return false;
                    });

            for (int i = 0; i < toRemove.Count(); i++)
            {
                RemoveGameUnit(toRemove.ElementAt(i));
            }
        }

        public static void AddPlayer(GameUnit player)
        {
            GameUnitsInPlay.Add(player);
            GameUnitsPlayers.Add(player);
        }

        public static void AddEnemy(GameUnit enemy)
        {
            GameUnitsInPlay.Add(enemy);
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
            GameUnitsInPlay.Remove(gu);
            GameUnitsPlayers.Remove(gu);
            GameUnitsEnemies.Remove(gu);
        }
    }
}
