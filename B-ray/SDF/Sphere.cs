using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace B_ray
{
    class Sphere :HittableObject
    {
        private Vector3 _pos;
        private double _radius;

        public Sphere()
        {

        }

        public Sphere(Vector3 Pos,double radius)
        {
            this._pos = Pos;
            this._radius = radius;
        }

        public override double SDF(Vector3 ray)
        {
            return MyMath.Distance(ray, this._pos) - this._radius;
        }
    }
}
