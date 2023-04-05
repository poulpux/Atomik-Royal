#pragma once
#include "tools.h"
class Player;
class MiniMap
{
public:

	MiniMap();
	~MiniMap();

	void InitMiniMap();
	void UpdateMiniMap(Player* _p);
	void DisplayGrandMap(myWindow* _window);
	void DisplayMiniMap(myWindow& _window);

	sf::FloatRect FRMiniMap = { 0.86f, 0, 0.2*0.56f, 0.2f };
	sf::View viewMiniMap;
	sf::Vector2f positionMiniMap = { 843.0f, 810.0f };
	
	sf::Texture textureGM;
	sf::Sprite spriteGM;
	sf::Vector2f positionGM;

	float timerKey = 0.0f;
	bool aficheGM = false;

	bool stopminimap = false;

protected:
	sf::CircleShape joueur;
	sf::RectangleShape contour;
};

