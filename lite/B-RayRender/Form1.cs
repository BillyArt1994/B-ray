using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace B_RayRender
{
    public partial class Form1 : Form
    {
        public static Vector3 cameraPos;
        public static Vector2 screenSize;
        public static Vector3 spherePos;
        public static double sphereRadius;

        public Form1()
        {
            InitializeComponent();
        }

        private void Form1_Load(object sender, EventArgs e)
        {

        }

        protected override void OnPaint(PaintEventArgs e)
        {
            cameraPos = new Vector3(0, 0, -1);
            screenSize = new Vector2(512, 512);
            spherePos = new Vector3(0, 0, 5);
            sphereRadius = 1;

            #region 
            base.OnPaint(e);
            Bitmap bm = new Bitmap(512, 512);
            var dc = e.Graphics;
            #endregion

            for (int i = 0; i < screenSize.X; i++)
            {
                for (int j = 0; j < screenSize.Y; j++)
                {
                    Vector3 col;
                    Vector3 ray = new Vector3(new Vector2(i, j) / screenSize * 2 - 1, 0)-cameraPos;
                    Vector3 rd = MyMath.Normalize(ray);
                    Vector3 p0 = cameraPos;
                    Vector3 p1 = RayMarching(p0,rd,80);
                    Vector3 normal = GetNormal(p1);
                    col = normal;
                    col *= 255;
                 //   col = p1;
                    col = MyMath.Clamp(col,0,255);
                    bm.SetPixel(i, j, Color.FromArgb(255, Convert.ToInt32(col.X), Convert.ToInt32(col.Y), Convert.ToInt32(col.Z)));
                }
            }

            dc.DrawImageUnscaled(bm, 0, 0);
        }

        public Vector3 RayMarching(Vector3 p, Vector3 rd, int time)
        {
            if (time <= 0)
            {
                return p;
            }

            double minDis = DistanceField(p);
            if (minDis <= 0.01 )
            {
                return p;
            }
            else
            {
                Vector3 newP = p + rd * minDis;
                return RayMarching(newP, rd, time - 1);
            }

        }

        public double SphereSDF(Vector3 p)
        {
            double minDis = MyMath.Distance(p, spherePos) - sphereRadius;
            return minDis;
        }

        public double DistanceField(Vector3 p)
        {
            double sphereSDF = SphereSDF(p);
            double planSDF = 1.5 - p.Y;
            double planRSDF = 5 - p.X;
            double planLSDF = Math.Abs(-5 -p.X);
            double minDis = Math.Min(planSDF, sphereSDF);
            minDis = Math.Min(minDis, planLSDF);
            minDis = Math.Min(minDis, planRSDF);
            return minDis;
        }

        public Vector3 GetNormal(Vector3 p)
        {
            double Offset = 0.00001;

            Vector3 normal = MyMath.Normalize(
                    new Vector3(DistanceField(p + new Vector3(Offset, 0, 0))- DistanceField(p - new Vector3(Offset, 0, 0)),
                                DistanceField(p + new Vector3(0, Offset, 0))- DistanceField(p - new Vector3(0, Offset, 0)),
                                DistanceField(p + new Vector3(0, 0, Offset))- DistanceField(p - new Vector3(0, 0, Offset))));
            return normal;
        }

    }
}