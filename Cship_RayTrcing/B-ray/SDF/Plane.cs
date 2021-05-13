using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace B_ray
{
    class Plane : HittableObject
    {
        private Vector3 _pos;

        public Plane()
        {

        }

        public Plane(Vector3 pos,Vector3 color,double specular,double gloss,double reflectRatio ) : base(color,specular,gloss,reflectRatio)
        {
            this._pos = pos;
        }

        public override double SDF(Vector3 ray)
        {
            return _pos.Y - ray.Y;
        }
    }
}
