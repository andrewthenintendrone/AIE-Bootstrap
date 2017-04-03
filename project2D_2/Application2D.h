#pragma once

#include "Application.h"
#include "Renderer2D.h"
#include "Audio.h"
#include "Vector3.h"

class Application2D : public aie::Application {
public:

	Application2D();
	virtual ~Application2D();

	virtual bool startup();
	virtual void shutdown();

	virtual void update(float deltaTime);
	virtual void draw();

protected:

	aie::Renderer2D*	m_2dRenderer;

	aie::Font*			m_font;
	aie::Audio*			m_audio;

	float m_cameraX, m_cameraY;

	aie::Texture*		m_playerTexture;
	int numCharacters;
	Vector3 m_playerPos = { 640.0f, 360.0f, 0.0f };
	int m_playerDirection = 1;
	float m_playerTimer;
	float m_playerSpeed = 200.0f;
	int m_playerNumber;
    bool m_playerShiny = false;

	aie::Texture* map;

	float m_timer;
};