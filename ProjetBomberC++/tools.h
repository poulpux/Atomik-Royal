#pragma once
#include "myWindow.h"
#include <utility>
#include <thread>
#include <mutex>
#include <chrono>
#include <map>
#include <fstream>
#include <iostream>
#include <sstream>
#include <list>
#include <string>
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include"SFML/Network.hpp"

#define TEXTURE_PATH "../Ressources/Textures/"
#define TEXTURE_PATH_BACKGROUND "../Ressources/Textures/Background/"
#define TEXTURE_PATH_CREDIT "../Ressources/Textures/Credits/"
#define FONT_PATH "../Ressources/Fonts/"

//DEFINE DES COULEUR UI
#define BROWN_COLOR sf::Color(138,86,63)
#define BEIGE_COLOR sf::Color(255,220,138)
#define LIGHTBROWN_COLOR sf::Color(193,122,88)
#define WHITE_COLOR sf::Color(255,246,245)

enum Ability {
	NONE = 1, KAME, POULP, DUMB
};

typedef enum Direction { BAS, DROITE, GAUCHE, HAUT, IDLE } Direction;

//using namespace sf;

namespace tools
{

	int iRand(int _min, int _max);

	int iRand2(int _min, int _max);

	double frand(float _min, float _max);

	void restartClock();

	float GetTimeDelta();

	float lerp(float v0, float v1, float t);

	sf::Vector2f vec2f_lerp(sf::Vector2f v0, sf::Vector2f v1, float t);

	sf::Vector3f vec3f_lerp(sf::Vector3f v0, sf::Vector3f v1, float t);

	sf::Color color_lerp(sf::Color v0, sf::Color v1, float t);

	bool Circle_Collision(sf::Vector2f _pos1, sf::Vector2f _pos2, float _rayon1, float _rayon2);

	bool Rectangle_Collision(sf::FloatRect _box1, sf::FloatRect _box2);

	bool rectRect(float r1x, float r1y, float r1w, float r1h, float r2x, float r2y, float r2w, float r2h);

	bool mouseCollisionWithRectangle(sf::Vector2f _positionMouse, sf::Vector2f _positionRectangle, sf::Vector2f _sizeRectangle);

	sf::Vector2f VsmoothstepPingPongLerp(sf::Vector2f start, sf::Vector2f end, float t);

	float FsmoothstepPingPongLerp(float start, float end, float t);

	float distance(sf::Vector2f _point1, sf::Vector2f _point2);

	bool circleRect(sf::Vector2f _circlePosition, sf::Vector2f _rectanglePosition, float rayon, sf::Vector2f _rectangleSize);

	void direction(sf::Vector2f _playerCenter, sf::Vector2f _mousePos, sf::Vector2f& _cosSin);

	float calculSin(float _cos);


};