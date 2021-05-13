using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace B_ray
{
    public class Transform
    {
        public Transform ()
        {
            this.Position = new Vector3();
            this.Rotation = new Vector3();
            this.Scale = new Vector3();
        }
        public Vector3 Position { get; set; }

        public Vector3 Rotation { get; set; }

        public Vector3 Scale { get; set; }
    }
}
