#ifndef MESH_H
#define MESH_H
#include "Vector3.h"
#include <vector>
#include <String>
#include <fstream>
#include <iostream>
#include <sstream>
#include <climits>
#include "Triangle.h"
#include "Vertex.h"
using std::vector;

class Mesh {

public:
	vector<Triangle>& GetTriangle()  { return _triangle; }
	vector<Vertex>& GetVertexArray() { return _vertexArray; }


private:
	vector<Triangle> _triangle;
	vector<Vertex> _vertexArray;
};

Mesh ReadObjFile(std::string filePath) {
	Mesh obj;
	vector<Vector3> normal;
	vector<Vector3> texcoord;
	std::ifstream ifs;
	ifs.open(filePath, std::ios::in);
	std::string buff;

	while (getline(ifs, buff))
	{
		float x, y, z;	
		switch (buff[0])
		{
		case 'v':
			if (buff[1] == 'n')
			{
				sscanf(buff.c_str(), "vn %f %f %f", &x, &y, &z);
				normal.push_back(Vector3(x, y, z));
			}
			else if (buff[1] == 't')
			{
				sscanf(buff.c_str(), "vt %f %f %f", &x, &y, &z);
				texcoord.push_back(Vector3(x, y, z));
			}
			else
			{
				sscanf(buff.c_str(), "v %f %f %f", &x, &y, &z);
				obj.GetVertexArray().push_back(Vertex(Vector3(x, y, z)));
				obj.GetVertexArray().back().SetIndex(obj.GetVertexArray().size() - 1);
			}
			break;
		case 'f':
			char ch[100];
			strcpy_s(ch, buff.c_str());
			const char *d = " f/";
			char *p;
			p = strtok(ch, d);
			int i = 0;
			while (p)
			{
				if (i== 0)
				{
					obj.GetTriangle().push_back(Triangle());
				}
				int vexIndex = atoi(p);
				obj.GetTriangle().back().SetIndex(i, obj.GetVertexArray()[vexIndex - 1]);
				p = strtok(NULL, d);
				int texIndex = atoi(p);
				obj.GetVertexArray()[vexIndex-1].SetTexcoord(texcoord[texIndex-1]);

				p = strtok(NULL, d);
				int norIndex = atoi(p);
				obj.GetVertexArray()[vexIndex-1].SetNormal(normal[norIndex-1]);

				p = strtok(NULL, d);
				if (i<3)
				{
					i++;
				}
			}
			break;
		}
	}
	ifs.close();
	return obj;
}
#endif // !MESH_H

