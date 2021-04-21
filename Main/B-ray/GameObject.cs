using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace B_ray
{
    public class GameObject
    {
        public GameObject ()
        {
            this.transform = new Transform();
        }
        public Transform transform { set; get; }
    }
}
