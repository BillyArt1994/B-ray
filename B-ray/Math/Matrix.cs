using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace B_ray
{
    public class Matrix
    {
        public int row { get; set; }
        public int col { get; set; }
        public double[] element;

        public Matrix ( int a,int b )
        {
            row = a;
            col = b;
            element = new double[row * col];
        }

        public Matrix ( double[,] matrix )
        {
            row = matrix.GetLength(0);
            col = matrix.GetLength(1);
            element = matrix.Cast<double>().ToArray();
        }

        public double this[int a,int b]
        {
            get { return element[a * col + b]; }
            set { element[a * col + b] = value; }
        }

        /// <summary>
        /// 矩阵与矩阵相乘
        /// </summary>
        /// <param name="a">矩阵</param>
        /// <param name="b">矩阵</param>
        /// <returns></returns>
        private static Matrix Multiply ( Matrix a,Matrix b )
        {
            Matrix c = new Matrix(a.row,b.col);
            for ( int i = 0; i < c.row; i++ )
            {
                for ( int j = 0; j < c.col; j++ )
                {
                    for ( int k = 0; k < a.col; k++ )
                    {
                        c[i,j] += a[i,k] * b[k,j];
                    }
                }

            }
            return c;
        }

        /// <summary>
        /// 矩阵左乘三维向量
        /// </summary>
        /// <param name="a">矩阵</param>
        /// <param name="b">向量</param>
        /// <returns></returns>
        private static Vector3 Multiply ( Matrix a,Vector3 b )
        {
            Vector3 result = new Vector3(0, 0, 0);
            result.X = MyMath.Dot(new Vector3(a[0,0],a[0,1],a[0,2]),b);
            result.Y = MyMath.Dot(new Vector3(a[1,0],a[1,1],a[1,2]),b);
            result.Y = MyMath.Dot(new Vector3(a[2,0],a[2,1],a[2,2]),b);
            return result;
        }

        /// <summary>
        /// 矩阵左乘四维向量
        /// </summary>
        /// <param name="a">矩阵</param>
        /// <param name="b">向量</param>
        /// <returns></returns>
        private static Vector4 Multiply ( Matrix a,Vector4 b )
        {
            Vector4 result = new Vector4(0,0,0,0);
            result.X = MyMath.Dot(new Vector4(a[0,0],a[0,1],a[0,2],a[0,3]),b);
            result.Y = MyMath.Dot(new Vector4(a[1,0],a[1,1],a[1,2],a[1,3]),b);
            result.Y = MyMath.Dot(new Vector4(a[2,0],a[2,1],a[2,2],a[2,3]),b);
            result.Y = MyMath.Dot(new Vector4(a[3,0],a[3,1],a[3,2],a[3,3]),b);
            return result;
        }

        public static Matrix operator * ( Matrix a,Matrix b )
        { return Matrix.Multiply(a,b); }

        public static Vector3 operator * ( Matrix a,Vector3 b )
        { return Matrix.Multiply(a,b); }


    }
}
