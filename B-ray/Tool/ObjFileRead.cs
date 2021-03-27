using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Text.RegularExpressions;

namespace B_ray
{
    public class ObjFileRead
    {
        public Mesh obj { get; set; }

        public ObjFileRead ()
        {
            
        }

        public ObjFileRead (string path )
        {
            StreamReader objReader = new StreamReader(path);
            this.obj = new Mesh();
            string textLine = "";
            while ( objReader.Peek() !=-1 )
            {
                textLine = objReader.ReadLine();
                if (textLine.IndexOf("v") == 0)
                {
                    string[] temp = Regex.Split(textLine,"\\s+", RegexOptions.IgnoreCase);
                    obj.vertexList.Add(new Vector3(Convert.ToDouble(temp[1]), Convert.ToDouble(temp[2]), Convert.ToDouble(temp[3])));
                }
                else if (textLine.IndexOf("f")==0)
                {
                    string[] temp = textLine.Split(' ');
                    for (int i = 1; i < temp.Length-1; i++)
                    {
                        obj.indexList.Add(Convert.ToInt32(temp[i]) - 1);
                    }
                }
            }

        }
    }
}
