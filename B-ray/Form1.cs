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
        public static Vector3 lightpos;

        public BrayRenderer ()
        {
            InitializeComponent();
        }

        private void Form1_Load ( object sender,EventArgs e )
        {

        }

        protected override void OnPaint ( PaintEventArgs e )
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
            Vector3 cameraPos = new Vector3(0,0,-1);
            //屏幕尺寸 长512 宽512
            Vector2 screenSize = new Vector2(512,512);
            //定义一个球物体
            radius = 1;

            spherePos = new Vector3(0,0,5);
            //定义一个灯光
            lightpos = new Vector3(10,-5,0);

            Bitmap bm = new Bitmap(512,512);
            var dc = e.Graphics;

            for ( int i = 0; i < screenSize.X; i++ )
            {
                for ( int j = 0; j < screenSize.Y; j++ )
                {
                    Vector3 col;
                    //屏幕位置获得从摄像机到每个像素发射的射线向量
                    Vector3 ray = new Vector3(new Vector3(i,j,0)*new Vector3(1/screenSize.X,1/screenSize.Y,0) - cameraPos);
                    //初始射线位置p0
                    Vector3 p0 = cameraPos;
                    //进行光线步进迭代得到最终焦点位置
                    Vector3 p1 = RayMarching(p0,ray);
                    //判断p1值是否为null
                    if ( p1 == null )
                    {
                        col = new Vector3 (0,0,0);
                    }
                    else
                    {
                        //获得法线
                        Vector3 normalDir = GetNormal(p1);
                        //获得灯光向量
                        Vector3 lightDir = GetNormal(p1);
                        //获得视角向量
                        Vector3 viewDir = GetLightDir(p1,lightpos);
                        //获得半角向量
                        Vector3 halfwayDir = GetHalfwayDir(normalDir,viewDir);
                        //返回光照模型计算后的颜色
                        col = GetLightModel(lightDir,normalDir,halfwayDir);
                    }

                    col *= 255;
                    col = MyMath.Clamp(col,0,255);

                    bm.SetPixel(i,j,Color.FromArgb(255,Convert.ToInt32(col.X),Convert.ToInt32(col.Y),Convert.ToInt32(col.Z)));
                }
            }
            dc.DrawImageUnscaled(bm,0,0);
        }

        /// <summary>
        /// 光线迭代
        /// </summary>
        /// <param name="p0">初始当前位置</param>
        /// <param name="rd">射线方向</param>
        /// <param name="time">迭代次数</param>
        /// <returns>返回射线最终迭代后的位置</returns>
        public Vector3 RayMarching ( Vector3 p,Vector3 rd )
        {
            double minDis = DistanceFields(p);
            if ( minDis <= 0.01 )
            {
                return p;
            }
            Vector3 newRay = (rd * minDis + p);
            double newDis = DistanceFields(newRay);
            if ( newDis > minDis )
            {
                return null;
            }
            else
            {
                return RayMarching(p,rd);
            }
        }

        /// <summary>
        /// 获得法线
        /// </summary>
        /// <param name="p1">射线交点坐标</param>
        /// <returns>当前射线交点坐标的法线</returns>
        public Vector3 GetNormal ( Vector3 p )
        {
            double Offset = 0.000001;

            Vector3 normal = MyMath.Normalize(
                    new Vector3(DistanceFields(p + new Vector3(Offset,0,0)) - DistanceFields(p - new Vector3(Offset,0,0)),
                                DistanceFields(p + new Vector3(0,Offset,0)) - DistanceFields(p - new Vector3(0,Offset,0)),
                                DistanceFields(p + new Vector3(0,0,Offset)) - DistanceFields(p - new Vector3(0,0,Offset))) / 2
                                );
            return normal;
        }

        /// <summary>
        /// 获得物体指向灯光的向量
        /// </summary>
        /// <param name="p">射线交点坐标</param>
        /// <param name="Light">灯光坐标</param>
        /// <returns></returns>
        public Vector3 GetLightDir ( Vector3 p,Vector3 Light )
        {
            Vector3 lightDir = MyMath.Normalize(lightpos - p);
            return lightDir;
        }

        /// <summary>
        /// 获得物体指向摄像机的向量
        /// </summary>
        /// <param name="p1">射线交点坐标</param>
        /// <param name="cameraPos">摄像机坐标</param>
        /// <returns></returns>
        public Vector3 GetviewDir ( Vector3 p,Vector3 cameraPos )
        {
            Vector3 viewDir = MyMath.Normalize(p - cameraPos);
            return viewDir;
        }

        /// <summary>
        /// 获得半角向量
        /// </summary>
        /// <param name="viewDir">视角向量</param>
        /// <param name="lightDir">灯光向量</param>
        /// <returns>返回半角向量</returns>
        public Vector3 GetHalfwayDir ( Vector3 viewDir,Vector3 lightDir )
        {

            Vector3 halfwayDir = MyMath.Normalize(viewDir + lightDir);
            return halfwayDir;
        }

        /// <summary>
        /// 进行半兰伯特光照模型计算返回颜色
        /// </summary>
        /// <param name="lightDir">灯光向量</param>
        /// <param name="normalDir">法线向量</param>
        /// <param name="halfwayDir">半角向量</param>
        /// <returns>返回光照模型计算后的颜色</returns>
        public Vector3 GetLightModel ( Vector3 lightDir,Vector3 normalDir,Vector3 halfwayDir )
        {
            //HalfLambert
            double NdotL = MyMath.Dot(lightDir,normalDir) * 0.5d + 0.5d;
            double Specular = MyMath.Dot(normalDir,halfwayDir);
            Vector3 col = new Vector3(NdotL,NdotL,NdotL);//MyMath.Clamp(new Vector3 (NdotL, NdotL, NdotL)+new Vector3 (Specular, Specular, Specular),0d,1d);
            return col;
        }

        public double DistanceFields ( Vector3 ray )
        {
            double minDis;
            double shpereSDF = MyMath.Distance(ray,spherePos) - radius;
            //double planSDF = 3d;
            minDis = shpereSDF;//Math.Min(planSDF, shpereSDF);
            return minDis;
        }


        /// <summary>
        /// 绘制三角面
        /// </summary>
        /// <param name="obj">mesh模型</param>
        /// <param name="mainCamera">摄像机</param>
        /// <param name="e">绘制事件</param>                                                                                                         
        public void DrawMesh ( Mesh obj,Camera mainCamera,PaintEventArgs e )
        {
            for ( int i = 0; i < obj.vertexList.Count; i++ )
            {
                obj.vertexList[i] = GraphMaritx.MVP(obj.vertexList[i],mainCamera);
            }

            for ( int i = 0; i < obj.indexList.Count; i += 3 )
            {
                DrawLine(obj.vertexList[obj.indexList[i]].XY,obj.vertexList[obj.indexList[i + 1]].XY,e);
                DrawLine(obj.vertexList[obj.indexList[i + 1]].XY,obj.vertexList[obj.indexList[i + 2]].XY,e);
                DrawLine(obj.vertexList[obj.indexList[i + 2]].XY,obj.vertexList[obj.indexList[i]].XY,e);
            }
        }

        /// <summary>
        /// 绘制直线
        /// </summary>
        /// <param name="startPoint">起始点</param>
        /// <param name="endPoint">终点</param>
        /// <param name="e">事件</param>
        public void DrawLine ( Vector2 startPoint,Vector2 endPoint,PaintEventArgs e )
        {
            Bitmap bm = new Bitmap(640,640);
            //    var dc = this.RenderPlan.CreateGraphics();
            var dc = e.Graphics;
            Vector2 dir = endPoint - startPoint;

            double length = Math.Sqrt(dir.X * dir.X + dir.Y * dir.Y);
            length = Math.Round(length);

            for ( int i = 1; i <= length; i++ )
            {
                Vector2 pixel = new Vector2((int)(startPoint.X + (dir.X / length) * i),(int)(startPoint.Y + (dir.Y / length) * i));
                //     pixel = pixel + new Vector2(400, 200);
                bm.SetPixel((int)pixel.X,(int)pixel.Y,Color.Red);
            }
            dc.DrawImageUnscaled(bm,0,0);
        }

        private void ImportToolStripMenuItem_Click ( object sender,EventArgs e )
        {
            OpenFileDialog oPenFileDialog = new OpenFileDialog();
            oPenFileDialog.InitialDirectory = Application.StartupPath;
            oPenFileDialog.Filter = "obj|*.obj";
            oPenFileDialog.RestoreDirectory = true;
            if ( oPenFileDialog.ShowDialog() == DialogResult.OK )
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
