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

        delegate void DrawObj();
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
            //string filePath = @"C:\Users\billy\Desktop\box01.obj";
            //ObjFileRead temp = new ObjFileRead(filePath);
            //Camera mainCamera = new Camera();
            //mainCamera.transform.Position = new Vector3(0, 0, 0);
            //mainCamera.transform.Rotation = new Vector3(15,60, 0);
            //DrawMesh(temp.obj, mainCamera, e);
            DrawLine(new Vector2 (300,150),new Vector2 (60,60),e );
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

    private void ImportToolStripMenuItem_Click ( object sender,EventArgs e )
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

        private void 文件ToolStripMenuItem_Click ( object sender,EventArgs e )
        {

        }
    }
}
