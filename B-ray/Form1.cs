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
   
    public partial class BrayRenderer : Form
    {
        public static double radius;
        public static Vector3 spherePos;
        public static int j =  1;
        public static Vector3[] p1 = new Vector3[262144];

        public BrayRenderer()
        {
            InitializeComponent();
        }

        private void Form1_Load(object sender, EventArgs e)
        {

        }

        protected override void OnPaint(PaintEventArgs e)
        {
            base.OnPaint(e);
            #region 读取文件
            //string filePath = @"C:\Users\billy\Desktop\box01.obj";
            //ObjFileRead temp = new ObjFileRead(filePath);
            //Camera mainCamera = new Camera();
            //mainCamera.transform.Position = new Vector3(0, 0, 0);
            //mainCamera.transform.Rotation = new Vector3(15,60, 0);
            //DrawMesh(temp.obj, mainCamera, e);
            //DrawLine(new Vector2 (300,150),new Vector2 (60,60),e );
            #endregion

            //实例主摄像机
            Vector3 cameraPos = new Vector3(0, 0, -1);
            //屏幕尺寸 长512 宽512
            Vector2 screenSize = new Vector2(512,512);
            //定义一个球物体
            radius = 1;

            spherePos = new Vector3(0, 0,5);

            //屏幕位置获得从摄像机到每个像素发射的射线
            Vector3[] ray = new Vector3[(int)(screenSize.X*screenSize.Y)];
            for (int i = (int)-screenSize.X/2; i < screenSize.X/ 2; i++)
            {
                for (int j = (int)-screenSize.Y/2; j < screenSize.Y/2; j++)
                {
                    ray[(int)((i+screenSize.X/2)*screenSize.Y+j+ screenSize.Y/2)] = new Vector3(new Vector3 (i, j, 0)*new Vector3(1/ screenSize.X,1/screenSize.Y,0) - cameraPos);
                }
            }

            Vector3[] p0 = new Vector3[(int)(screenSize.X * screenSize.Y)];

            for (int i = 0; i < ray.Length; i++)
            {
                p0[i] = cameraPos;
            }

            Vector3[] result =  RayMarching(p0,ray,50);

            Bitmap bm = new Bitmap(512, 512);
            var dc = e.Graphics;

            for (int i = 0; i < screenSize.X; i++)
            {
                for (int j = 0; j < screenSize.Y; j++)
                {
                    double color = MyMath.Distance(cameraPos, result[j + (int)(i * screenSize.Y)]);
                    color /= 255;
                    color = MyMath.Clamp(color, 0, 255);
                    bm.SetPixel(i, j, Color.FromArgb(255, (int)color, (int)color, (int)color));
                }
            }
            dc.DrawImageUnscaled(bm, 0, 0);
        }

        public Vector3[] RayMarching(Vector3[] p0,Vector3[] rd,int time)
        {
            for (int i = 0; i < p0.Length; i++)
            {
           //     double minDis = MyMath.Distance(p0[i],spherePos) - radius;
                double minDis =Math.Min(MyMath.Distance(p0[i],spherePos) - radius,Math.Abs(50 - p0[i].Y))  ;
                if ( minDis <= 0.01 )
                {
                    continue;
                }
                else
                {
                    p1[i] = (rd[i] * minDis + p0[i]);
                }
            }
            j++;
            if (j<time)
            {
                RayMarching(p1, rd, time);
            }
            return p1;
        }

        /// <summary>
        /// 绘制三角面
        /// </summary>
        /// <param name="obj">mesh模型</param>
        /// <param name="mainCamera">摄像机</param>
        /// <param name="e">绘制事件</param>                                                                                                         
        public void DrawMesh(Mesh obj, Camera mainCamera, PaintEventArgs e)
        {
            for (int i = 0; i < obj.vertexList.Count; i++)
            {
                obj.vertexList[i] = GraphMaritx.MVP(obj.vertexList[i], mainCamera);
            }

            for (int i = 0; i < obj.indexList.Count; i += 3)
            {
                DrawLine(obj.vertexList[obj.indexList[i]].XY, obj.vertexList[obj.indexList[i + 1]].XY, e);
                DrawLine(obj.vertexList[obj.indexList[i + 1]].XY, obj.vertexList[obj.indexList[i + 2]].XY, e);
                DrawLine(obj.vertexList[obj.indexList[i + 2]].XY, obj.vertexList[obj.indexList[i]].XY, e);
            }
        }

        /// <summary>
        /// 绘制直线
        /// </summary>
        /// <param name="startPoint">起始点</param>
        /// <param name="endPoint">终点</param>
        /// <param name="e">事件</param>
        public void DrawLine(Vector2 startPoint, Vector2 endPoint, PaintEventArgs e)
        {
            Bitmap bm = new Bitmap(640, 640);
            //    var dc = this.RenderPlan.CreateGraphics();
            var dc = e.Graphics;
            Vector2 dir = endPoint - startPoint;

            double length = Math.Sqrt(dir.X * dir.X + dir.Y * dir.Y);
            length = Math.Round(length);

            for (int i = 1; i <= length; i++)
            {
                Vector2 pixel = new Vector2((int)(startPoint.X + (dir.X / length) * i), (int)(startPoint.Y + (dir.Y / length) * i));
                //     pixel = pixel + new Vector2(400, 200);
                bm.SetPixel((int)pixel.X, (int)pixel.Y, Color.Red);
            }
            dc.DrawImageUnscaled(bm, 0, 0);
        }

        private void ImportToolStripMenuItem_Click(object sender, EventArgs e)
        {
            OpenFileDialog oPenFileDialog = new OpenFileDialog();
            oPenFileDialog.InitialDirectory = Application.StartupPath;
            oPenFileDialog.Filter = "obj|*.obj";
            oPenFileDialog.RestoreDirectory = true;
            if (oPenFileDialog.ShowDialog() == DialogResult.OK)
            {
                string filePath = oPenFileDialog.FileName;
                ObjFileRead temp = new ObjFileRead(filePath);
            }
        }

        private void 文件ToolStripMenuItem_Click(object sender, EventArgs e)
        {

        }
    }
}
