using System;
using System.Collections.Generic;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace B_ray
{
    public static class Draw
    {
        public static void DrawMesh(Mesh obj, Camera mainCamera, PaintEventArgs e)
        {
            for (int i = 0; i < obj.vertexList.Count; i++)
            {
                obj.vertexList[i] = GraphMaritx.MVP(obj.vertexList[i], mainCamera);
            }

            for (int i = 0; i < obj.indexList.Count; i+=3)
            {
                DrawLine(obj.vertexList[obj.indexList[i]].XY, obj.vertexList[obj.indexList[i + 1]].XY,e);
                DrawLine(obj.vertexList[obj.indexList[i + 1]].XY, obj.vertexList[obj.indexList[i + 2]].XY,e);
                DrawLine(obj.vertexList[obj.indexList[i + 2]].XY, obj.vertexList[obj.indexList[i]].XY,e);
            }
        }

        /// <summary>
        /// 绘制直线
        /// </summary>
        /// <param name="startPoint">起始点</param>
        /// <param name="endPoint">终点</param>
        /// <param name="e">事件</param>
        private static void DrawLine(Vector2 startPoint, Vector2 endPoint, PaintEventArgs e)
        {
            Bitmap bm = new Bitmap(640, 640);
            var dc = e.Graphics;

            Vector2 dir = endPoint - startPoint;

            double length = Math.Sqrt(dir.X * dir.X + dir.Y * dir.Y);
            length = Math.Round(length);

            for (int i = 1; i <= length; i++)
            {
                Vector2 pixel = new Vector2((int)(startPoint.X + (dir.X / length) * i), (int)(startPoint.Y + (dir.Y / length) * i));
                pixel = pixel + new Vector2(400, 200);
                bm.SetPixel((int)pixel.X, (int)pixel.Y, Color.Red);
            }
            dc.DrawImageUnscaled(bm, 0, 0);
        }
    }
}
