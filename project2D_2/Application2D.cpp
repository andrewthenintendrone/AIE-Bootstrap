#include "Application2D.h"
#include "Texture.h"
#include "Font.h"
#include "Input.h"
#include <string>
#include <math.h>
#include <time.h>

Application2D::Application2D() {

}

Application2D::~Application2D() {

}

bool Application2D::startup() {
	
	m_2dRenderer = new aie::Renderer2D();

    srand((int)time(NULL));
    m_playerTexture = new aie::Texture("./textures/pokemon/front/1.png");
	numCharacters = 493;
	m_playerNumber = 1;



	m_font = new aie::Font("./font/consolas.ttf", 32);

	m_audio = new aie::Audio("./audio/powerup.wav");

	m_cameraX = 0;
	m_cameraY = 0;
	m_timer = 0;
	m_playerTimer = 0;

	map = new aie::Texture("./textures/map.jpg");

	return true;
}

void Application2D::shutdown() {
	
	delete m_audio;
	delete m_font;
	delete m_2dRenderer;
}

void Application2D::update(float deltaTime) {

	m_timer += deltaTime;
	m_playerTimer += 10 * deltaTime;

	// input example
	aie::Input* input = aie::Input::getInstance();

	/*########################################
	use arrow keys to move player
	########################################*/
	if (input->isKeyDown(aie::INPUT_KEY_UP))
	{
        m_playerDirection = 0;
		m_playerPos.y += m_playerSpeed * deltaTime;
	}

	else if (input->isKeyDown(aie::INPUT_KEY_DOWN))
	{
        m_playerDirection = 1;
		m_playerPos.y -= m_playerSpeed * deltaTime;
	}

	else if (input->isKeyDown(aie::INPUT_KEY_LEFT))
	{
        m_playerDirection = 2;
		m_playerPos.x -= m_playerSpeed * deltaTime;
	}

	else if (input->isKeyDown(aie::INPUT_KEY_RIGHT))
	{
		m_playerDirection = 3;
		m_playerPos.x += m_playerSpeed * deltaTime;
	}

	else
	{
		m_playerTimer = 0;
	}

	/*########################################
	speed up the player if they hold shift
	########################################*/
    if (input->isKeyDown(aie::INPUT_KEY_LEFT_SHIFT))
    {
        m_playerSpeed = 400.0f;
    }
    else
    {
        m_playerSpeed = 200.0f;
    }

	/*########################################
	get path to relevant path and assign it to m_playerTexture
	########################################*/
    std::string spritePath = "./textures/pokemon/";

    if (m_playerShiny)
    {
        spritePath += "shiny_";
    }

	switch (m_playerDirection)
	{
	case 0:
		spritePath += "back";
		break;
	case 1:
		spritePath += "front";
		break;
	case 2:
		spritePath += "left";
		break;
	case 3:
		spritePath += "right";
		break;
	}

    if ((int)m_playerTimer % 4 >= 2)
    {
        spritePath += "f2";
    }

    spritePath += "/" + std::to_string(m_playerNumber) + ".png";
    m_playerTexture->load(spritePath.c_str());


	if (input->wasKeyPressed(aie::INPUT_KEY_SPACE))
	{
        if (rand() % 8192 == 0)
        {
            m_playerShiny = true;
        }
        else
        {
            m_playerShiny = false;
        }
        m_playerNumber = rand() % numCharacters + 1;
	}

	if (input->isKeyDown(aie::INPUT_KEY_ESCAPE))
		quit();
}

void Application2D::draw() {

	// wipe the screen to the background colour
	clearScreen();

	// set the camera position before we begin rendering
	m_2dRenderer->setCameraPos(m_cameraX, m_cameraY);

	// begin drawing sprites
	m_2dRenderer->begin();

	// draw character
	m_2dRenderer->setUVRect(0.0f, 0.0f, 1.0f, 1.0f);
    m_2dRenderer->drawSprite(m_playerTexture, m_playerPos.x, m_playerPos.y, m_playerTexture->getWidth() * 4.0f, m_playerTexture->getHeight() * 4.0f, 0.0f, 0.0f, 0.5f, 0.5f);

	// done drawing sprites
	m_2dRenderer->end();
}