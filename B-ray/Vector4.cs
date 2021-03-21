using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace B_ray
{
    public class Vector4 :Vector
    {
        private float _x;
        private float _y;
        private float _z;
        private float _w;

        public float X
        {
            get
            {
                return _x;
            }

            set
            {
                _x = value;
            }
        }

        public float Y
        {
            get
            {
                return _y;
            }

            set
            {
                _y = value;
            }
        }

        public float Z
        {
            get
            {
                return _z;
            }

            set
            {
                _z = value;
            }
        }

        public float W
        {
            get
            {
                return _w;
            }

            set
            {
                _w = value;
            }
        }

        public Vector4 (){

        }

        public Vector4 ( Vector4 a )
        {
            this.X = a.X;
            this.Y = a.Y;
            this.Z = a.Z;
            this.W = a.W;
        }

        public Vector4 ( float x,float y,float z,float w )
        {
            this.X = x;
            this.Y = y;
            this.Z = z;
            this.W = w;
        }

        public static float operator * ( Vector4 a,Vector4 b )
        {
            float result = a.X*b.X+a.Y*b.Y+a.Z*b.Z+a.W*b.W;
            return result;
        }
    }
}
