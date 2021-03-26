using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace B_ray
{
    public class Mesh
    {
        public Vector3[] vertexList { get; set; }
        public int[] indexList { get; set; }

        public Mesh ()
        {

        }

        public Mesh ( Vector3[] vertex ,int[] index  )
        {
            this.vertexList = vertex;
            this.indexList = index;
        }
   
    }
}
