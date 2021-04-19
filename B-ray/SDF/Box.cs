using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace B_ray
{
    class Box :HittableObject
    {
        private Vector3 _pos;
        private Vector3 _size;

        public Box()
        {

        }
        public Box(Vector3 pos,Vector3 size)
        {
            this._pos = pos;
            this._size = size;
        }

        public override double SDF(Vector3 ray)
        {
            Vector3 q = MyMath.Abs(ray - this._pos) - this._size;
            double result = MyMath.Max(q, 0).Lenght + Math.Min(Math.Max(q.X, Math.Max(q.Y, q.Z)), 0);
            return result;
        }
    }
}
