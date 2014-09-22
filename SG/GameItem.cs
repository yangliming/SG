using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace SG
{
    public abstract class GameItem
    {
        protected string gi_type;

        public GameItem(string type)
        {
            gi_type = type;
        }

        public abstract bool Use();
        public abstract string Description();

        public override string ToString()
        {
            return gi_type;
        }

        public void DecrementCount()
        {
            GameState.GameItemsPlayer[this]--;

            if (GameState.GameItemsPlayer[this] <= 0)
                GameState.GameItemsPlayer.Remove(this);
        }

        public static bool operator ==(GameItem item1, GameItem item2)
        {
            if (item1.gi_type == item2.gi_type)
                return true;
            return false;
        }

        public static bool operator !=(GameItem item1, GameItem item2)
        {
            if (item1.gi_type != item2.gi_type)
                return true;
            return false;
        }

        public override bool Equals(object item)
        {
            if (item is GameItem && this.gi_type == ((GameItem)item).gi_type)
                return true;
            return false;
        }

        public override int GetHashCode()
        {
            return base.GetHashCode();
        }
    }
}
