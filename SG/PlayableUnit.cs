using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace SG
{
    public abstract class PlayableUnit : GameUnit
    {
        public PlayableUnit(int hp, int att, int def, string type)
            : base(hp, att, def, type)
        {
        }

        public override string ToString()
        {
            return this.gu_type + ": HP: " + this.gu_currenthp + "/" + this.gu_totalhp;
        }
    }
}
