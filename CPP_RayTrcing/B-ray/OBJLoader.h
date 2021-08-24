#ifndef OBJLoader_H
#define OBJLoader_H

#include "Mesh.h"
#include "GameObject.h"
#include "Triangle.h"
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
	GameObject* gameObject = new GameObject();
	Mesh* obj = new Mesh();
	vector<Vector3> normal, texcoord;
	vector<Triangle> triangle_array;
	vector<Vertex> vertex_array;
	char charDes[10]{ '\0' };
	unsigned count(0), meshCount(0), vetrexCount(0), vertexIndex_offest(1);

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
			if (buff_line[2] == 'o'&& meshCount != 0)
			{
				obj = new Mesh();
				vertexIndex_offest += vetrexCount;
			}

			sscanf(buff_line, "# %i %s", &count, &charDes);
			if (!strcmp(charDes, "vertices"))
			{
				obj->vertexArray = new Vertex[count];
				vetrexCount = count;
				copy(vertex_array.begin(), vertex_array.end(), obj->vertexArray);
				vector<Vertex>().swap(vertex_array);
				obj->setVertexCount(count);
				memset(charDes, '\0', sizeof(charDes));
			}

			if (!strcmp(charDes, "faces")) {
				obj->triangleArray = new Triangle[count];
				copy(triangle_array.begin(), triangle_array.end(), obj->triangleArray);
				vector<Triangle>().swap(triangle_array);
				obj->setFaceCount(count);
				gameObject->mesh[meshCount] = obj;
				++meshCount;
				memset(charDes, '\0', sizeof(charDes));
			}

			break;
		case 'v':

			if (buff_line[1] == ' ')
			{
				sscanf(buff_line, "v %f %f %f", &x, &y, &z);
				Vertex vert(Vector3(x, y, z), Vector3(0), Vector3(0));
				vertex_array.push_back(vert);
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
				obj->vertexArray[vertexIndex[i] - vertexIndex_offest].normal = normal.at(normalIndex[i] - 1);
				obj->vertexArray[vertexIndex[i] - vertexIndex_offest].texcoord = texcoord.at(uvIndex[i] - 1);
			}

			Triangle tri(&(obj->vertexArray[vertexIndex[0] - vertexIndex_offest]),
				&(obj->vertexArray[vertexIndex[1] - vertexIndex_offest]),
				&(obj->vertexArray[vertexIndex[2] - vertexIndex_offest]));
			triangle_array.push_back(tri);
			break;
		}
	}
	gameObject->meshCount = meshCount;
	ifs.close();
	return gameObject;
}

const char* getFileName(std::string filePath) {
	std::string s1(filePath.substr(filePath.find_last_of('\\') + 1));
	const char* r = (s1.substr(0, s1.rfind('.'))).c_str();
	return r;
}

#endif // !OBJLoader

