#ifndef OBJLoader_H
#define OBJLoader_H

#include "Mesh.h"
#include "Triangle.h"
#include "GameObject.h"
#include <String>
#include <fstream>
#include <iostream>
#include <windows.h>

class OBJLoader
{
public:
	static GameObject* ReadObjectFile(std::string filePath);
private:
};

GameObject* OBJLoader::ReadObjectFile(std::string filePath) {
	GameObject *gameObject= new GameObject();
	Mesh* obj =nullptr;
	vector<Vector3> normal, texcoord;
	vector<Triangle> triangle_array;
	vector<Vertex> vertex_array;
	unsigned vertexs_Count = 0, faces_Count=0,vertexindex_Offest =1;

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
		case '#':
				if (buff_line[2] == 'o')
				{
					if (obj != nullptr)
					{
						obj->setFaceCount(faces_Count);
						faces_Count = 0;
						obj->setVertexCount(vertexs_Count);
						vertexindex_Offest += vertexs_Count;
						vertexs_Count = 0;
						obj->vertexArray.swap(vertex_array);
						obj->triangleArray.swap(triangle_array);
						gameObject->mesh.push_back(obj);
						gameObject->meshCount += 1;
					}
					obj = new Mesh();
				}
				break;

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
				vertex_array.at(vertexIndex[i] - vertexindex_Offest).normal = normal.at(normalIndex[i] - 1);
				vertex_array.at(vertexIndex[i] - vertexindex_Offest).texcoord = texcoord.at(uvIndex[i] - 1);
			}

			Triangle tri(&(vertex_array.at(vertexIndex[0] - vertexindex_Offest)),
				&(vertex_array.at(vertexIndex[1] - vertexindex_Offest)),
				&(vertex_array.at(vertexIndex[2] - vertexindex_Offest)));
			triangle_array.push_back(tri);
			faces_Count += 1;
			break;
		}
	}
	obj->setFaceCount(faces_Count);
	obj->setVertexCount(vertexs_Count);
	obj->triangleArray.swap(triangle_array);
	obj->vertexArray.swap(vertex_array);
	gameObject->mesh.push_back(obj);
	gameObject->meshCount += 1;
	ifs.close();
	return gameObject;
}

const char* getFileName(std::string filePath) {
	std::string s1(filePath.substr(filePath.find_last_of('\\') + 1));
	const char* r = (s1.substr(0, s1.rfind('.'))).c_str();
	return r;
}

#endif // !OBJLoader

