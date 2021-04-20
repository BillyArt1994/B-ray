using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace B_ray
{
    class Torus : HittableObject
    {
        private Vector3 _pos;
        private Vector2 _size;

        public Torus()
        {

        }

        public Torus(Vector3 pos,Vector2 size)
        {
            this._pos = pos;
            this._size = size;
        }

        public override double SDF(Vector3 ray)
        {
            Vector3 d = ray - this._pos;
            Vector2 q = new Vector2(d.XZ.Lenght - this._size.X, d.Y);
            return q.Lenght - this._size.Y;
        }
    }
}
