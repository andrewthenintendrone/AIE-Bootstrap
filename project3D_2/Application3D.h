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
                int x, y, z;
                fscanf_s(file, "%d %d %d\n", &x, &y, &z);
                faces.push_back(Face{ x - 1, y - 1, z - 1 });
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

    int upgrade = 0;

protected:

	glm::mat4	m_viewMatrix;
	glm::mat4	m_projectionMatrix;
};