#ifndef OBJLoader_H
#define OBJLoader_H

#include "Mesh.h"
#include "Triangle.h"
#include <String>
#include <fstream>
#include <iostream>
#include <windows.h>

class OBJLoader
{
public:
	static Mesh ReadObjectFile(std::string filePath);
private:
};

Mesh OBJLoader::ReadObjectFile(std::string filePath) {
	//GameObject gameObject_00;
	//gameObject_00.name = getFileName(filePath);
	Mesh obj;
	vector<Vector3> normal, texcoord;
	vector<Triangle> triangle_array;
	vector<Vertex> vertex_array;
	unsigned vertexs_Count = 0, faces_Count=0;
	//for (size_t i = 0; i < 10; i++)
	//{
	//	obj.vertexArray.push_back(Vertex(Vector3(i), Vector3(0), Vector3(0)));
	//	obj.faces_Count += 1;
	//}

	std::ifstream ifs;
	ifs.open(filePath, std::ios::in);
	std::string buff;

	if (!ifs)
	{
		MessageBox(NULL, (LPCTSTR)TEXT("文件打开失败"), (LPCTSTR)TEXT("提示"), MB_OK);
	}

	

	if (ifs.get() == EOF)
	{
		MessageBox(NULL, (LPCTSTR)TEXT("文件内容为空"), (LPCTSTR)TEXT("提示"), MB_OK);
	}

	while (getline(ifs, buff))
	{
		char buff_line[128];
		strcpy_s(buff_line, buff.c_str());
		float x, y, z;
		switch (buff_line[0])
		{
			//case '#':
			//	std::string::size_type idx_f_object;
			//	idx_f_object = buff.find("object");
			//	if (idx_f_object == std::string::npos)
			//	{
			//		char buf[128] = { '\0' };
			//		sscanf(buff_line, "# object %s", buf);
			//		obj.name = buf;
			//	}
			//	break;
		case 'v':

			if (buff_line[1] == ' ')
			{
				sscanf(buff_line, "v %f %f %f", &x, &y, &z);
				Vertex vert(Vector3(x, y, z), Vector3(0), Vector3(0));
				vertex_array.push_back(vert);
				vertexs_Count += 1;
			}

			if (buff_line[1] == 'n')
			{
				sscanf(buff.c_str(), "vn %f %f %f", &x, &y, &z);
				normal.push_back(Vector3(x, y, z));
			}

			if (buff_line[1] == 't')
			{
				sscanf(buff.c_str(), "vt %f %f %f", &x, &y, &z);
				texcoord.push_back(Vector3(x, y, z));
			}

			break;

		case 'f':
			unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
			sscanf(buff_line, "f %i/%i/%i %i/%i/%i %i/%i/%i",
				&vertexIndex[0], &uvIndex[0], &normalIndex[0],
				&vertexIndex[1], &uvIndex[1], &normalIndex[1],
				&vertexIndex[2], &uvIndex[2], &normalIndex[2]);

			for (size_t i = 0; i < 3; i++)
			{
				vertex_array.at(vertexIndex[i] - 1).normal = normal.at(normalIndex[i] - 1);
				vertex_array.at(vertexIndex[i] - 1).texcoord = texcoord.at(uvIndex[i] - 1);
			}

			Triangle tri(&(vertex_array.at(vertexIndex[0] - 1)),
				&(vertex_array.at(vertexIndex[1] - 1)),
				&(vertex_array.at(vertexIndex[2] - 1)));
			triangle_array.push_back(tri);
			faces_Count += 1;
			break;
		}
	}
	obj.setFaceCount(faces_Count);
	obj.setVertexCount(vertexs_Count);
	vertex_array.swap(obj.vertexArray);
	triangle_array.swap(obj.triangleArray);
	ifs.close();
	return obj;
}

const char* getFileName(std::string filePath) {
	std::string s1(filePath.substr(filePath.find_last_of('\\') + 1));
	const char* r = (s1.substr(0, s1.rfind('.'))).c_str();
	return r;
}

#endif // !OBJLoader

