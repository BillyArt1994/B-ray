using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace B_ray
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        private void Form1_Load(object sender, EventArgs e)
        {

        }

        protected override void OnPaint(PaintEventArgs e)
        {
            base.OnPaint(e);
            Camera mainCamera = new Camera();
            GameObject box = new GameObject();
            box.transform.Position = new Vector3(0, 0, 0);
            mainCamera.transform.Position = new Vector3(0,0,-5);
            Vector3 MVP_pos = WorldToViewProjection(box, mainCamera);
        }

        /// <summary>
        /// 绘制直线
        /// </summary>
        /// <param name="startPoint">起始点</param>
        /// <param name="endPoint">终点</param>
        /// <param name="e">事件</param>
        private void DrawLine(Point startPoint, Point endPoint, PaintEventArgs e)
        {
            Bitmap bm = new Bitmap(640, 640);
            var dc = e.Graphics;

            Point dir = new Point(0, 0);
            dir.X = endPoint.X - startPoint.X;
            dir.Y = endPoint.Y - startPoint.Y;

            double length = Math.Sqrt(dir.X * dir.X + dir.Y * dir.Y);
            length = Math.Round(length);

            for (int i = 1; i <= length; i++)
            {
                Point pixel = new Point((int)(startPoint.X + (dir.X / length) * i), (int)(startPoint.Y + (dir.Y / length) * i));
                bm.SetPixel(pixel.X, pixel.Y, Color.Red);
            }
            dc.DrawImageUnscaled(bm, 0, 0);
        }

        private void DrawBox(float size)
        {
            Vector3 p0 = new Vector3(1, 1, 1);
            Vector3 p1 = new Vector3(1, 0, 1);
            Vector3 p2 = new Vector3(-1, 0, 1);
            Vector3 p3 = new Vector3(-1, 1, 1);
            Vector3 p4 = new Vector3(-1, 1, -1);
            Vector3 p5 = new Vector3(-1, 0, -1);
            Vector3 p6 = new Vector3(1, 0, -1);
            Vector3 p7 = new Vector3(1, 1, -1);
            Vector3[] point = { p0, p1, p2, p3, p4, p5, p6, p7 };
        }

        /// <summary>
        /// MVP世界转视角投影矩阵
        /// </summary>
        /// <param name="obj">物体</param>
        /// <param name="camera">相机</param>
        /// <returns></returns>
        public Vector3 WorldToViewProjection(GameObject obj, Camera camera)
        {
            Vector3 cameraWorldPos = camera.transform.Position;
            Vector3 cameraRotation = camera.transform.Rotation;
            Vector4 objWorldPos = new Vector4 (obj.transform.Position,1);

            //平移矩阵
            double[,] Tarry = { { 1, 0, 0, -cameraWorldPos.X }, { 0, 1, 0, -cameraWorldPos.Y }, { 0, 0, 1, -cameraWorldPos.Z }, { 0, 0, 0, 1 } };
            Matrix TMatrix = new Matrix(Tarry);

            #region 旋转矩阵
            /*
            //X轴矩阵
            double[,] Xarry = { { 1,0,0 },{ 0,MyMath.Cos(cameraRotation.X),MyMath.Sin(cameraRotation.X) },{ 0,-MyMath.Sin(cameraRotation.X),MyMath.Cos(cameraRotation.X) } };
            Matrix XAxisMaritx = new Matrix(Xarry);
            //Y轴矩阵
            double[,] Yarry = { { MyMath.Cos(cameraRotation.Y),0,-MyMath.Sin(cameraRotation.Y) },{ 0,1,0 },{ MyMath.Sin(cameraRotation.Y),0,MyMath.Cos(cameraRotation.Y) } };
            Matrix YAxisMaritx = new Matrix(Yarry);
            //Z轴矩阵
            double[,] zarry = { { MyMath.Cos(cameraRotation.Z),MyMath.Sin(cameraRotation.Z),0 },{ -MyMath.Sin(cameraRotation.Z),MyMath.Cos(cameraRotation.Z),0 },{ 0,0,1 } };
            Matrix ZAxisMaritx = new Matrix(zarry);
            //XYZ矩阵顺序:Z---->Y---->X
            Matrix W2VMaritx = ZAxisMaritx * (XAxisMaritx * YAxisMaritx);
            */

            #endregion

            //复合矩阵
            double[,] comzarry = {{MyMath.Cos(cameraRotation.Z)*MyMath.Cos(cameraRotation.Y)+MyMath.Sin(cameraRotation.X)*MyMath.Sin(cameraRotation.Y)*MyMath.Sin(cameraRotation.Z),MyMath.Cos(cameraRotation.X)*MyMath.Sin(cameraRotation.Z),-MyMath.Cos(cameraRotation.Z)*MyMath.Sin(cameraRotation.Y)+MyMath.Sin(cameraRotation.Z)* MyMath.Sin(cameraRotation.X)* MyMath.Cos(cameraRotation.Y) ,0},
                                  {-MyMath.Sin(cameraRotation.Z)*MyMath.Cos(cameraRotation.Y)+MyMath.Cos(cameraRotation.Z)*MyMath.Sin(cameraRotation.X)*MyMath.Sin(cameraRotation.Y),MyMath.Cos(cameraRotation.X)*MyMath.Cos(cameraRotation.Z),MyMath.Sin(cameraRotation.Z)*MyMath.Sin(cameraRotation.Y)+MyMath.Cos(cameraRotation.Z)* MyMath.Sin(cameraRotation.X)*MyMath.Cos(cameraRotation.Y) ,0},
                                  {MyMath.Cos(cameraRotation.X)*MyMath.Sin(cameraRotation.Y),-MyMath.Sin(cameraRotation.X),MyMath.Cos(cameraRotation.X)*MyMath.Cos(cameraRotation.Y),0},
                                   {0,0,0,1 }};
            Matrix ComMaritx = new Matrix(comzarry);

            Vector3 viewSpacePos = ((ComMaritx*TMatrix) * objWorldPos).XYZ;
            return viewSpacePos;
        }
    }
}
