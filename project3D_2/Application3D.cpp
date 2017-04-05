#include "Application3D.h"
#include "Gizmos.h"
#include "Input.h"
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include "Vector3.h"

using glm::vec3;
using glm::vec4;
using glm::mat4;
using aie::Gizmos;

Application3D::Application3D() {

}

Application3D::~Application3D() {

}

bool Application3D::startup() {
	
    // set RNG seed
    srand((int)time(NULL));

    setBackgroundColour(30.0f / 255.0f, 30.0f / 255.0f, 30.0f / 255.0f, 1);

	// initialise gizmo primitive counts
	Gizmos::create(20000, 20000, 20000, 20000);

	// create simple camera transforms
	m_viewMatrix = glm::lookAt(vec3(10), vec3(0), vec3(0, 1, 0));
	m_projectionMatrix = glm::perspective(glm::pi<float>() * 0.25f,
										  getWindowWidth() / (float)getWindowHeight(),
										  0.1f, 1000.f);

    // load models
    models.push_back(Model());
    models.push_back(Model());
    models.push_back(Model());
    models.push_back(Model());
    models.push_back(Model());
    models.push_back(Model());

    models[0].load("./models/PorygonObj.obj");
    models[1].load("./models/Porygon2Obj.obj");
    models[2].load("./models/Porygon-ZObj.obj");
    models[3] = Model::generateRandom();
    models[4].load("./models/triforce.obj");
    models[5].load("./models/pikachu.obj");
    for (unsigned int i = 0; i < models.size(); i++)
    {
        for (unsigned int j = 0; j < models[i].vertices.size(); j++)
        {
            models[i].vertices[j] = Vector3::openGLnormalise(models[i].vertices[j]);
        }
    }

	return true;
}

void Application3D::shutdown() {

	Gizmos::destroy();
}

void Application3D::update(float deltaTime) {

	// query time since application started
	float time = getTime();

	// rotate camera
	m_viewMatrix = glm::lookAt(vec3(glm::sin(time * 2) * 10, 0, glm::cos(time * 2) * 10),
							   vec3(0), vec3(0, 1, 0));

	// wipe the gizmos clean for this frame
	Gizmos::clear();

	// draw a simple grid with gizmos
    vec4 black(0, 0, 0, 1);
	vec4 white(1);
    vec4 red(1, 0, 0, 1);
    vec4 orange(1, 0.5f, 0, 1);
    vec4 yellow(1, 1, 0, 1);
    vec4 green(0, 0.5f, 0, 1);
    vec4 blue(0, 0, 0.5f, 1);
    vec4 purple(0.5f, 0, 1, 1);
    vec4 flesh(1, 203.0f / 255.0f, 164.0f / 255.0f, 1);
	/*for (int i = 0; i < 21; ++i) {
		Gizmos::addLine(vec3(-10 + i, 0, 10),
						vec3(-10 + i, 0, -10),
						i == 10 ? white : black);
		Gizmos::addLine(vec3(10, 0, -10 + i),
						vec3(-10, 0, -10 + i),
						i == 10 ? white : black);
	}*/

	// add a transform so that we can see the axis
	//Gizmos::addTransform(mat4(1));

	// demonstrate a few shapes
	/*Gizmos::addAABBFilled(vec3(0), vec3(1), vec4(0, 0.5f, 1, 0.25f));
	Gizmos::addSphere(vec3(5, 0, 5), 1, 8, 8, vec4(1, 0, 0, 0.5f));
	Gizmos::addRing(vec3(5, 0, -5), 1, 1.5f, 8, vec4(0, 1, 0, 1));
	Gizmos::addDisk(vec3(-5, 0, 5), 1, 16, vec4(1, 1, 0, 1));
	Gizmos::addArc(vec3(-5, 0, -5), 0, 2, 1, 8, vec4(1, 0, 1, 1));*/

	/*mat4 t = glm::rotate(time, glm::normalize(vec3(1, 1, 1)));
	t[3] = vec4(-2, 0, 0, 1);
	Gizmos::addCylinderFilled(vec3(0), 0.5f, 1, 5, vec4(0, 1, 1, 1), &t);*/

    if (upgrade == 3)
    {
        models[3] = Model::generateRandom();
    }

	// quit if we press escape
	aie::Input* input = aie::Input::getInstance();

	if (input->isKeyDown(aie::INPUT_KEY_ESCAPE))
		quit();

    if (input->wasKeyPressed(aie::INPUT_KEY_SPACE))
    {
        if (upgrade < models.size() - 1)
        {
            upgrade++;
        }
        else
        {
            upgrade = 0;
        }
    }
    currentModel = models[upgrade];

    for (unsigned int i = 0; i < currentModel.faces.size(); i++)
    {
        //vec4 color(rand() % 256 / 255.0f, rand() % 256 / 255.0f, rand() % 256 / 255.0f, 1);
        Gizmos::addTri(currentModel.vertices[currentModel.faces[i].x], currentModel.vertices[currentModel.faces[i].y], currentModel.vertices[currentModel.faces[i].z], black);
        Gizmos::addLine(currentModel.vertices[currentModel.faces[i].x], currentModel.vertices[currentModel.faces[i].y], purple);
        Gizmos::addLine(currentModel.vertices[currentModel.faces[i].y], currentModel.vertices[currentModel.faces[i].z], purple);
        Gizmos::addLine(currentModel.vertices[currentModel.faces[i].z], currentModel.vertices[currentModel.faces[i].x], purple);
    }
}

void Application3D::draw() {

	// wipe the screen to the background colour
	clearScreen();

	// update perspective in case window resized
	m_projectionMatrix = glm::perspective(glm::pi<float>() * 0.25f,
										  getWindowWidth() / (float)getWindowHeight(),
										  0.1f, 1000.f);

	Gizmos::draw(m_projectionMatrix * m_viewMatrix);
}