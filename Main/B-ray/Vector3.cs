using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace B_ray
{
    public class Vector3 :Vector
    {
        private float x;
        private float y;
        private float z;

        public float X
        {
            get
            {
                return x;
            }

            set
            {
                x = value;
            }
        }

        public float Y
        {
            get
            {
                return y;
            }

            set
            {
                y = value;
            }
        }

        public float Z
        {
            get
            {
                return z;
            }

            set
            {
                z = value;
            }
        }

        public Vector3 ()
        {

        }

        public Vector3 ( Vector3 a )
        {
            this.X = a.X;
            this.Y = a.Y;
            this.Z = a.Z;
        }

        public Vector3 ( float x,float y,float z )
        {
            this.X = x;
            this.Y = y;
            this.Z = z;
        }

        public static Vector3 operator + ( Vector3 a,Vector3 b )
        {
            Vector3 result = new Vector3(a.x + b.x,a.y + b.y,a.z + b.z);
            return result;
        }

        public static Vector3 operator - ( Vector3 a,Vector3 b )
        {
            Vector3 result = new Vector3(a.x - b.x,a.y - b.y,a.z - b.z);
            return result;
        }

        public static Vector3 operator * ( float a,Vector3 b )
        {
            Vector3 result = new Vector3(a* b.x,a * b.y,a * b.z);
            return result;
        }

        public static Vector3 operator * (Vector3 a ,float b )
        {
            Vector3 result = new Vector3(a.x *b,a.y * b,a.z * b);
            return result;
        }
    }
}
