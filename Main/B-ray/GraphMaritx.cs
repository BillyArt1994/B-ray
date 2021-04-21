using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace B_ray
{
    public static class GraphMaritx
    {
        /// <summary>
        /// MVP世界转视角投影矩阵
        /// </summary>
        /// <param name="obj">物体</param>
        /// <param name="camera">相机</param>
        /// <returns></returns>
        private static Vector3 WorldToViewProjection(Vector3 vertexPos, Camera camera)
        {
            Vector3 cameraWorldPos = camera.transform.Position;
            Vector3 cameraRotation = camera.transform.Rotation;
            Vector4 objWorldPos = new Vector4(vertexPos, 1);

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

            Vector3 viewSpacePos = ((ComMaritx * TMatrix) * objWorldPos).XYZ;
            return viewSpacePos;
        }

        public static Vector3 MVP(Vector3 vertexPos, Camera camera)
        {
            return WorldToViewProjection(vertexPos, camera);
        }
    }
}
