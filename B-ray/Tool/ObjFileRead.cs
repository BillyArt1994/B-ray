using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace B_ray
{
    public class ObjFileRead
    {
        public Mesh obj { get; set; }

        public ObjFileRead ()
        {
            this.obj = new Mesh();
        }

        public ObjFileRead (string path )
        {
            StreamReader objReader = new StreamReader(path);
            string textLine = "";
            while ( objReader.Peek() !=-1 )
            {
                textLine = objReader.ReadLine();

            }
        }
    }
}
