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

        delegate void DrawObj();
        public BrayRenderer()
        {
            InitializeComponent();
        }

        private void Form1_Load(object sender, EventArgs e)
        {

        }

        protected override void OnPaint(PaintEventArgs e)
        {
            base.OnPaint(e);
            string filePath = @"C:\Users\billy\Desktop\box01.obj";
            ObjFileRead temp = new ObjFileRead(filePath);
            Camera mainCamera = new Camera();
            mainCamera.transform.Position = new Vector3(0, 0, 0);
            mainCamera.transform.Rotation = new Vector3(15,60, 0);
            Draw.DrawMesh(temp.obj, mainCamera, e);
        }

        private void ImportToolStripMenuItem_Click ( object sender,EventArgs e )
        {
            OpenFileDialog oPenFileDialog = new OpenFileDialog();
            oPenFileDialog.InitialDirectory = Application.StartupPath;
            oPenFileDialog.Filter = "obj|*.obj";
            oPenFileDialog.RestoreDirectory = true;
            if (oPenFileDialog.ShowDialog() == DialogResult.OK)
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
