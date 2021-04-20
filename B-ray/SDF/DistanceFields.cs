using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace B_ray
{
    public static class SDF
    {
        public static double DistanceFields ( Vector3 ray,HittableObject[] sceneObject)
        {
            double minDis = double.MaxValue;

            for ( int i = 0; i < sceneObject.Length; i++ )
            {
                double dis = sceneObject[i].SDF(ray);
                if ( dis < minDis )
                {
                    minDis = dis;
                }
            }
            return minDis;
        }

    }
}
