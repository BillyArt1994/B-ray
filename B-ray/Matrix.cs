using System;
using System.IO;
using System.Diagnostics;

namespace B_ray
{
    public class Matrix
    {
        public float[,] element;
        private int _row;
        private int _col;

        public int Col
        {
            get
            {
                return _col;
            }

            set
            {
                _col = value;
            }
        }

        public int Row
        {
            get
            {
                return _row;
            }

            set
            {
                _row = value;
            }
        }

        public Matrix()
        {

        }

        public Matrix(int row,int col)
        {
            _row = row;
            _col = col;
            element = new float[row, col];
        }

        public void SetValue(float [] a )
        {
            int j = 0;
            for (int i = 0; i < element.Length; i++)
            {
                j ++ ;
                if (j>_row)
                {
                    j = 0;
                }
                element[j, j] = a[i];
            }
        }

        public float ReadValue(int row,int col)
        {
            return element[row, col];
        }

        }
    }
}
