using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace B_ray
{
    class Sphere :HittableObject
    {
        private Vector3 _spherePos;
        private double _radius;

        public Sphere()
        {

        }
        public Sphere(Vector3 spherePos,double radius)
        {
            this._spherePos = spherePos;
            this._radius = radius;
        }

        public override double SDF(Vector3 ray)
        {
            return MyMath.Distance(ray, this._spherePos) - this._radius;
        }
    }
}
