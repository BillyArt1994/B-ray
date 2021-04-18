using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace B_ray
{
    abstract class HittableObject
    {
        private Vector3 _color;
        private double _reflectRatio;

        public HittableObject()
        {

        }

        public HittableObject(Vector3 color , double value)
        {
            this._color = color;
            this._reflectRatio = value;
        }

        public abstract double SDF( Vector3 ray);
    }
}
