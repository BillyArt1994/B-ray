using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace B_ray
{
    public static class MyMath
    {
        /// <summary>
        /// 三角函数获得cosθ值
        /// </summary>
        /// <param name="a">角度</param>
        /// <returns></returns>
        public static double Cos (double a)
        {

            return Math.Cos(a / 180 * Math.PI);
        }

        /// <summary>
        /// 三角函数获得sinθ值
        /// </summary>
        /// <param name="a">角度</param>
        /// <returns></returns>
        public static double Sin ( double a )
        {

            return Math.Sin(a / 180 * Math.PI);
        }

        /// <summary>
        /// 三角函数获得tanθ值
        /// </summary>
        /// <param name="a">角度</param>
        /// <returns></returns>
        public static double Tan ( double a )
        {

            return Math.Tan(a / 180 * Math.PI);
        }

        /// <summary>
        /// 三维向量点乘
        /// </summary>
        /// <param name="a">向量a</param>
        /// <param name="b">向量b</param>
        /// <returns></returns>
        public static double Dot (Vector3 a,Vector3 b)
        {
            return a.X * b.X + a.Y * b.Y + a.Z * b.Z;
        }

        /// <summary>
        /// 四维向量点乘
        /// </summary>
        /// <param name="a">向量a</param>
        /// <param name="b">向量b</param>
        /// <returns></returns>
        public static double Dot ( Vector4 a,Vector4 b )
        {
            return a.X * b.X + a.Y * b.Y + a.Z * b.Z+a.W*b.W;
        }
    }
}
