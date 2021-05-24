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
	vector<Triangle> GetTriangle() const { return _triangle; }
	void SetTriangle(Triangle trg) { _triangle.push_back(trg); }
	void SetTriangle(int& index,Vertex& vertex) { _triangle.back().SetIndex(index, vertex); }
private:
	vector<Triangle> _triangle;
};

Mesh ReadObjFile(std::string filePath) {
	Mesh obj;
	std::ifstream ifs;
	ifs.open(filePath, std::ios::in);
	std::string buff;
	vector<Vector3> normal;
	vector<Vector3> texcoord;
	vector<Vertex> vertex;

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
				vertex.push_back(Vertex(Vector3(x, y, z)));
				vertex.back().SetIndex(vertex.size() - 1);
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
				if (i== 0)
				{
					obj.SetTriangle(Triangle());
				}
				int vexIndex = atoi(p);
				obj.SetTriangle(i, vertex[vexIndex - 1]);
				p = strtok(NULL, d);
				int texIndex = atoi(p);
				vertex[vexIndex-1].SetTexcoord(texcoord[texIndex-1]);

				p = strtok(NULL, d);
				int norIndex = atoi(p);
				vertex[vexIndex-1].SetNormal(normal[norIndex-1]);

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

