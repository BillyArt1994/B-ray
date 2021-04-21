using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace B_ray
{
    public class Mesh
    {
        public List<Vector3> vertexList { get; set; }
        public List<int> indexList { get; set; }

        public Mesh ()
        {
            this.vertexList = new List<Vector3>();
            this.indexList = new List<int>();
        }

        public Mesh (List<Vector3> vertex , List<int> index  )
        {
            this.vertexList = vertex;
            this.indexList = index;
        }
   
    }
}
