using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace B_ray
{
    public class Vector3
    {
        private double x;
        private double y;
        private double z;

        public double X
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

        public double Y
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

        public double Z
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

        public Vector3 ( double x,double y,double z )
        {
            this.X = x;
            this.Y = y;
            this.Z = z;
        }

        private static Vector3 Plus (Vector3 a,Vector3 b )
        {
            return new Vector3(a.x + b.x,a.y + b.y,a.z + b.z);
        }

        private static Vector3 Subtraction ( Vector3 a,Vector3 b )
        {
            return new Vector3(a.x - b.x,a.y - b.y,a.z - b.z);
        }

        private static Vector3 Multiply ( Vector3 a,double b )
        {
            return new Vector3(a.x * b,a.y * b,a.z * b);
        }

        public static Vector3 operator + ( Vector3 a,Vector3 b )
        {
            return Vector3.Plus(a,b);
        }

        public static Vector3 operator - ( Vector3 a,Vector3 b )
        {
            return Vector3.Subtraction(a,b);
        }

        public static Vector3 operator * (Vector3 a ,double b )
        { 
            return Vector3.Multiply(a,b);
        }
    }
}
