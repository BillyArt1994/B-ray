using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace B_ray
{
    public abstract class HittableObject
    {
        private Vector3 _color;
        private double _reflectRatio;

        public Vector3 Color
        {
            get
            {
                return this._color;
            }

            set
            {
                this._color = value;
            }

        }

        public HittableObject ()
        {

        }

        public double ReflectRatio
        {
            get
            {
                return this._reflectRatio;
            }

            set
            {
               this._reflectRatio = value;
            }
        }

        public HittableObject (Vector3 color)
        {

        }

        public HittableObject(Vector3 color , double value)
        {
            this._color = color;
            this.ReflectRatio = value;
        }

        public abstract double SDF( Vector3 ray);
    }
}
