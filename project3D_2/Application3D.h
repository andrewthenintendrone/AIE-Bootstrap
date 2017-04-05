#pragma once

#include "Application.h"
#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>
#include <vector>
#include "Vector3.h"

struct Face
{
    int x;
    int y;
    int z;
};

struct Model
{
    std::vector<glm::vec3>vertices;
    std::vector<Face>faces;

    void load(std::string fileName)
    {
        //open model
        FILE * file;
        fopen_s(&file, fileName.c_str(), "r");

        // break if the model doesn't exist
        if (file == NULL) {
            printf("Impossible to open the file !\n");
            return;
        }

        while (1)
        {
            char lineHeader[256];

            // read the first word of the line
            int res = fscanf_s(file, "%s", lineHeader, sizeof(lineHeader));

            if (res == EOF)
            {
                break; // EOF = End Of File. Quit the loop.
            }

            if (strcmp(lineHeader, "v") == 0)
            {
                float x, y, z;
                fscanf_s(file, "%f %f %f\n", &x, &y, &z);
                vertices.push_back(glm::vec3(x, y, z));
            }
            if (strcmp(lineHeader, "f") == 0)
            {
                unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
                int matches = fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2]);
                Face temp;
                temp.x = vertexIndex[0] - 1;
                temp.y = vertexIndex[1] - 1;
                temp.z = vertexIndex[2] - 1;
                faces.push_back(temp);
            }
        }
    }

    static Model generateRandom()
    {
        Model temp;
        for (int i = 0; i < 20; i++)
        {
            glm::vec3 vertex((rand() % 500 - 250) / 100.0f, (rand() % 500 - 250) / 100.0f, (rand() % 500 - 250) / 100.0f);
            temp.vertices.push_back(vertex);
        }
        for (int i = 0; i < 5; i++)
        {
            temp.faces.push_back(Face());
            temp.faces[i].x = rand() % 20;
            temp.faces[i].y = rand() % 20;
            temp.faces[i].z = rand() % 20;
        }
        return temp;
    }
};

class Application3D : public aie::Application {
public:

	Application3D();
	virtual ~Application3D();

	virtual bool startup();
	virtual void shutdown();

	virtual void update(float deltaTime);
	virtual void draw();

    std::vector<Model>models;
    Model currentModel;

    unsigned int upgrade = 0;

protected:

	glm::mat4	m_viewMatrix;
	glm::mat4	m_projectionMatrix;
};