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

        static GameState()
        {
            GameUnitsInPlay = new List<GameUnit>();
            GameUnitsPlayers = new List<GameUnit>();
            GameUnitsEnemies = new List<GameUnit>();
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

        public static void RemoveGameUnit(GameUnit gu)
        {
            GameUnitsInPlay.Remove(gu);
            GameUnitsPlayers.Remove(gu);
            GameUnitsEnemies.Remove(gu);
        }
    }
}
