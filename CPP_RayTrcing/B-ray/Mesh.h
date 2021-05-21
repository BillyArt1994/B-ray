#ifndef MESH_H
#define MESH_H
#include "Vector3.h"
#include <vector>
#include <String>
#include <fstream>
#include <iostream>
#include <sstream>
#include "Triangle.h"
#include "Vertex.h"
using std::vector;


class Mesh {

public:
	vector<Triangle> triangle;
	vector<Vertex> vertex;
};

Mesh ReadObjFile(std::string filePath) {
	Mesh obj;
	std::ifstream ifs;
	ifs.open(filePath, std::ios::in);
	std::string buff;
	while (getline(ifs, buff))
	{
		float x, y, z;	
		vector<Vector3> normal;
		vector<Vector3> texcoord;
		switch (buff[0])
		{
		case 'v':
			if (buff[1] == 'n')
			{
				sscanf(buff.c_str(), "vn %f %f %f", &x, &y, &z);
				obj.vertex.push_back(Vertex(Vector3(x, y, z)));
			}
			else if (buff[1] == 't')
			{
				sscanf(buff.c_str(), "vn %f %f %f", &x, &y, &z);
				texcoord.push_back(Vector3(x, y, z));
			}
			else
			{
				sscanf(buff.c_str(), "v %f %f %f", &x, &y, &z);
				normal.push_back(Vector3(x, y, z));
			}
			break;
		case 'f':
			char ch[25];
			strcpy_s(ch, buff.c_str());
			const char *d = " f/";
			char *p;
			p = strtok(ch, d);
			int i = 0;
			while (p)
			{
				while (i== 0)
				{
					obj.triangle.push_back(Triangle());
				}
				int vexIndex = atoi(p);
				obj.triangle[i].SetIndex(i,vexIndex);

				p = strtok(NULL, d);
				int texIndex = atoi(p);
				obj.vertex[vexIndex].SetTexcoord(texcoord[texIndex]);

				p = strtok(NULL, d);
				int norIndex = atoi(p);
				obj.vertex[vexIndex].SetNormal(normal[norIndex]);

				p = strtok(NULL, d);
				if (i<3)
				{
					i++;
				}
				else
				{
					i = 0;
				}
			}
			break;
		}
	}
	ifs.close();
	return obj;
}
#endif // !MESH_H

