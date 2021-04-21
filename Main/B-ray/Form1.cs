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
        public static Vector3 lightpos;
        public static Vector3 lightpos2;
        public static Vector3 cameraPos;
        public static Vector2 screenSize;
        public static HittableObject[] sceneObject;

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
            cameraPos = new Vector3(0,0,-1);
            //屏幕尺寸 长512 宽512
            screenSize = new Vector2(512,512);
            //定义一个灯光
            lightpos = new Vector3(3,-5,0);
            //定义一个球物体
            HittableObject sphere = new Sphere(new Vector3(2,0,7),1,new Vector3(0.5,1,1),1,88,1);
            //定义一个平面
            HittableObject plane = new Plane(new Vector3(0,1.5,0),new Vector3(0,1,0),1,88,1);
            //定义一个环
            HittableObject torus = new Torus(new Vector3(-0.3,1,4),new Vector2(0.7,0.25),new Vector3(0.95,0.3,0.12),1,48,0.5);
            //定义一个正方体
            HittableObject box = new Box(new Vector3(-2,-0.6,9),new Vector3(1.3,2.1,1.3),new Vector3(0.95,0.95,0.05),1,25,0.3);

            sceneObject = new HittableObject[] { plane,torus,box,sphere };

            Bitmap bm = new Bitmap(512,512);
            var dc = e.Graphics;

            for ( int i = 0; i < screenSize.X; i++ )
            {
                for ( int j = 0; j < screenSize.Y; j++ )
                {
                    Vector3 col;
                    //屏幕位置获得从摄像机到每个像素发射的射线向量
                    Vector3 ray = new Vector3(new Vector3(i - screenSize.X / 2,j - screenSize.Y / 2,0) * new Vector3(1 / screenSize.X,1 / screenSize.Y,0) - cameraPos);
                    //初始射线位置p0
                    Vector3 p0 = cameraPos;
                    //进行光线步进迭代得到最终位置
                    int objectIndex;
                    Vector3 p1 = RayMarching(p0,ray,140,out objectIndex);
                    //获得法线
                    Vector3 normalDir = GetNormal(p1);
                    //返回光照模型计算后的颜色
                    if (objectIndex == 0)
                    {
                        sceneObject[objectIndex].Color = CheckerBoard(p1,1);
                    }
                    col = objectIndex == -1 ? new Vector3(0) : computeLightModel(sceneObject[objectIndex], p1, normalDir);

                    //计算反射光并返回新颜色
                    col = objectIndex == -1 ? new Vector3(0) :RayRelfect(col,p1,ray,normalDir,sceneObject[objectIndex].ReflectRatio);
                   
                    col = MyMath.Clamp(col,0,1);
                    col *= 255;
                    bm.SetPixel(i,j,Color.FromArgb(255,Convert.ToInt32(col.X),Convert.ToInt32(col.Y),Convert.ToInt32(col.Z)));
                }
            }
            dc.DrawImageUnscaled(bm,0,0);
        }

        /// <summary>
        /// 光线迭代
        /// </summary>
        /// <param name="p">初始当前位置</param>
        /// <param name="rd">射线方向</param>
        /// <param name="time">迭代次数</param>
        /// <returns>返回射线最终迭代后的位置</returns>
        public Vector3 RayMarching ( Vector3 p,Vector3 rd,int time,out int objectIndex)
        {
            Vector2 minDis;
            Vector3 startPos = p;
            objectIndex = -1;
            for ( int i = 0; i < time; i++ )
            {

                minDis = DistanceFields(startPos);
               
                if (minDis.X<0.01)
                {
                    objectIndex = (int)minDis.Y;
                    return startPos;
                }
                else if ( minDis.X > 15 )
                {
                    objectIndex = -1;
                    return startPos;
                }
                else
                {
                    startPos = (rd * minDis.X + startPos);
                }

            }
            return startPos;
        }

        public Vector3 RayRelfect ( Vector3 col,Vector3 p,Vector3 ray,Vector3 normalDir,double rayScale )
        {
            Vector3 rd = GetRelfectDir(MyMath.Normalize(ray),normalDir);
            int objectIndex;
            Vector3 p1 = RayMarching(p + normalDir * 0.1,rd,80,out objectIndex);
            Vector3 normalDirN = GetNormal(p1);
            if (objectIndex == 0)
            {
                sceneObject[objectIndex].Color = CheckerBoard(p1,1);
            }
            Vector3 relfectCol = objectIndex == -1?  new Vector3(0): computeLightModel(sceneObject[objectIndex],p1,normalDirN);
            relfectCol *= rayScale;

            col += relfectCol;

            if ( relfectCol <= 0.01 )
            {
                return col;
            }
            else
            {
                return RayRelfect(col,p1,rd,normalDirN,rayScale * 0.6);
            }
        }

        public Vector3 GetRelfectDir ( Vector3 ray,Vector3 normal )
        {
            Vector3 relfectDir = ray - normal * 2 * (MyMath.Dot(ray,normal));
            return relfectDir;
        }

        /// <summary>
        /// 返回距离场最小距离
        /// </summary>
        /// <param name="ray">射线</param>
        /// <returns>最小距离</returns>
        public Vector2 DistanceFields ( Vector3 ray )
        {
            Vector2 minDis = new Vector2(double.MaxValue,0);
            for ( int i = 0; i < sceneObject.Length; i++ )
            {
                double dis = sceneObject[i].SDF(ray);
                if ( dis < minDis.X )
                {
                    minDis.X = dis;
                    minDis.Y = i;
                }
            }

            // 融合 并未处理颜色
            //double minDis = SmoothUnion(sceneObject[0].SDF(ray),sceneObject[1].SDF(ray),1);
            //minDis = SmoothUnion(minDis,sceneObject[2].SDF(ray),1);
            //minDis = SmoothUnion(minDis,sceneObject[3].SDF(ray),1);
            //Vector2 minDisfinal = new Vector2(minDis,0);

            return minDis;
        }


        double SmoothUnion(double d1, double d2, double k)
        {
            double h = MyMath.Clamp(0.5 + 0.5 * (d2 - d1) / k, 0.0, 1.0);
            return MyMath.Lerp(d2, d1, h) - k * h * (1.0 - h);
        }

        /// <summary>
        /// 获得法线
        /// </summary>
        /// <param name="p">射线交点坐标</param>
        /// <returns>当前射线交点坐标的法线</returns>
        public Vector3 GetNormal ( Vector3 p )
        {
            double Offset = 0.03;

            Vector3 normal = MyMath.Normalize(
                    new Vector3(DistanceFields(p + new Vector3(Offset,0,0)).X - DistanceFields(p - new Vector3(Offset,0,0)).X,
                                DistanceFields(p + new Vector3(0,Offset,0)).X - DistanceFields(p - new Vector3(0,Offset,0)).X,
                                DistanceFields(p + new Vector3(0,0,Offset)).X - DistanceFields(p - new Vector3(0,0,Offset)).X) / 2
                                );
            return normal;
        }

        /// <summary>
        /// 获得物体指向灯光的向量
        /// </summary>
        /// <param name="p">射线交点坐标</param>
        /// <param name="Light">灯光坐标</param>
        /// <returns></returns>
        public Vector3 GetLightDir ( Vector3 p,Vector3 lightpos )
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
            Vector3 viewDir = MyMath.Normalize(cameraPos - p);
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
        /// 获得阴影
        /// </summary>
        /// <param name="p">像素射线最后落点位置</param>
        /// <param name="lightpos">灯光位置</param>
        /// <returns>阴影值</returns>
        public double GetShandow ( Vector3 p,Vector3 normalDir,int time )
        {
            Vector3 rd = lightpos - p;
            Vector3 rdNor = MyMath.Normalize(rd);
            int index;
            Vector3 Shandow = RayMarching(p + (normalDir * 0.3),rdNor,time,out index);
            double dis = MyMath.Distance(p,Shandow);

            if ( dis < rd.Lenght )
            {
                return 0;
            }
            else
            {
                return 1;
            }
        }

        /// <summary>
        /// 棋盘格
        /// </summary>
        /// <param name="p"></param>
        /// <param name="size"></param>
        /// <returns></returns>
        public Vector3 CheckerBoard ( Vector3 p,double size )
        {
            double zScale = Math.Floor(p.Z / size) % 2 == 0 ? 1 : 0;
            double grid = Math.Floor(p.X / size + zScale) % 2 == 0 ? 0 : 1;
            Vector3 col = MyMath.Lerp(new Vector3(0.78,0.28,0.15),new Vector3(0.98,0.83,0.04),grid);
            return col;
        }

        /// <summary>
        /// 进行半兰伯特光照模型计算返回颜色
        /// </summary>
        /// <param name="lightDir">灯光向量</param>
        /// <param name="normalDir">法线向量</param>
        /// <param name="halfwayDir">半角向量</param>
        /// <returns>返回光照模型计算后的颜色</returns>
        public Vector3 computeLightModel ( HittableObject obj,Vector3 p,Vector3 normalDir )
        {
            //获得灯光向量
            Vector3 lightDir = GetLightDir(p,lightpos);
            //获得视角向量
            Vector3 viewDir = GetviewDir(p,cameraPos);
            //获得半角向量
            Vector3 halfwayDir = GetHalfwayDir(viewDir,lightDir);
            //获得阴影
            double Shandow = GetShandow(p,normalDir,35);
            //HalfLambert
            double NdotL = MyMath.Clamp(MyMath.Dot(lightDir,normalDir),0.001,1);
            double NdotH = MyMath.Dot(normalDir,halfwayDir);
            double ambient = 0.1;
            double Specular = Math.Pow(Math.Max(0,MyMath.Dot(normalDir,halfwayDir)),obj.Gloss);
            //乘漫反射颜色
            Vector3 col = new Vector3(NdotL,NdotL,NdotL) * obj.Color;
            //乘阴影
            col *= Shandow*0.8;
            //加高光颜色
            col += new Vector3(Specular) * new Vector3(obj.Specular);
            //乘灯光颜色
            col *= new Vector3(1, 0.95, 0.95);
            //加环境光
            col += new Vector3(0.49,0.63,1) * ambient;
            col = MyMath.Clamp(col,0,1);
            return col;
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
