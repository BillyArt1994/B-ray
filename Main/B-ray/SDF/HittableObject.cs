using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace B_ray
{
    public abstract class HittableObject
    {
        private Vector3 _color;
        private double _reflectRatio;
        private double _gloss;
        private double _specular;

        public Vector3 Color
        {
            get
            {
                return this._color;
            }

            set
            {
                this._color = value;
            }

        }

        public double ReflectRatio
        {
            get
            {
                return this._reflectRatio;
            }

            set
            {
               this._reflectRatio = value;
            }
        }

        public double Gloss
        {
            get
            {
                return _gloss;
            }

            set
            {
                _gloss = value;
            }
        }

        public double Specular
        {
            get
            {
                return _specular;
            }

            set
            {
                _specular = value;
            }
        }

        public HittableObject ()
        {

        }

        /// <summary>
        /// 构造材质
        /// </summary>
        /// <param name="color">漫反射</param>
        /// <param name="specular">高光强度</param>
        /// <param name="gloss">光泽度</param>
        /// <param name="reflectRatio">反射系数</param>
        public HittableObject ( Vector3 color,double specular,double gloss,double reflectRatio )
        {
            this._color = color;
            this._gloss = gloss;
            this._reflectRatio = reflectRatio;
            this._specular = specular;
        }

        public abstract double SDF( Vector3 ray);
    }
}
