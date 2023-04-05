#include "tools.h"

sf::Clock sfclock;
sf::Time sfTime;

namespace tools
{
	int iRand(int _min, int _max)
	{
		return rand() % (_max - _min) + _min;
	}

	int iRand2(int _min, int _max)
	{
		return rand() % ((_max + 1) - _min) + _min;
	}

	double frand(float _min, float _max)
	{
		return ((rand() / (double)RAND_MAX) * ((double)_max - (double)_min) + (double)_min);
	}
	//FDZFijijij
	void restartClock()
	{
		sfTime = sfclock.restart();
	}

	float GetTimeDelta()
	{
		return sfTime.asSeconds();
	}

	float lerp(float v0, float v1, float t)
	{
		return (1 - t) * v0 + t * v1;
	}


	sf::Vector2f vec2f_lerp(sf::Vector2f v0, sf::Vector2f v1, float t)
	{
		sf::Vector2f tmp;
		tmp.x = (1 - t) * v0.x + t * v1.x;
		tmp.y = (1 - t) * v0.y + t * v1.y;
		return tmp;
	}


	sf::Vector3f vec3f_lerp(sf::Vector3f v0, sf::Vector3f v1, float t)
	{
		sf::Vector3f tmp;
		tmp.x = (1 - t) * v0.x + t * v1.x;
		tmp.y = (1 - t) * v0.y + t * v1.y;
		tmp.z = (1 - t) * v0.z + t * v1.z;
		return tmp;
	}


	sf::Color color_lerp(sf::Color v0, sf::Color v1, float t)
	{
		sf::Color tmp;
		tmp.r = (1 - t) * v0.r + t * v1.r;
		tmp.g = (1 - t) * v0.g + t * v1.g;
		tmp.b = (1 - t) * v0.b + t * v1.b;
		tmp.a = (1 - t) * v0.a + t * v1.a;
		return tmp;
	}

	bool Circle_Collision(sf::Vector2f _pos1, sf::Vector2f _pos2, float _rayon1, float _rayon2)
	{
		// if (sqrt(pow(_pos1.x - _pos2.x, 2) + pow(_pos1.y - _pos2.y, 2)) < _rayon1 + _rayon2) // Version non optimisé
		// Version Optimisé
		if ((_pos1.x - _pos2.x) * (_pos1.x - _pos2.x) + (_pos1.y - _pos2.y) * (_pos1.y - _pos2.y) < (_rayon1 + _rayon2) * (_rayon1 + _rayon2))
		{
			return true;
		}
		else return false;
	}

	bool rectRect(float r1x, float r1y, float r1w, float r1h, float r2x, float r2y, float r2w, float r2h)
	{

		// are the sides of one rectangle touching the other?

		if (r1x + r1w >= r2x &&    // r1 right edge past r2 left
			r1x <= r2x + r2w &&    // r1 left edge past r2 right
			r1y + r1h >= r2y &&    // r1 top edge past r2 bottom
			r1y <= r2y + r2h) {    // r1 bottom edge past r2 top
			return true;
		}
		return false;
	}

	bool Rectangle_Collision(sf::FloatRect _box1, sf::FloatRect _box2)
	{
		if ((_box2.left >= _box1.left + _box1.width)      // trop à droite
			|| (_box2.left + _box2.width <= _box1.left) // trop à gauche
			|| (_box2.top >= _box1.top + _box1.height) // trop en bas
			|| (_box2.top + _box2.height <= _box1.top))  // trop en haut
			return false;
		else
			return true;
	}

	bool mouseCollisionWithRectangle(sf::Vector2f _positionMouse, sf::Vector2f _positionRectangle, sf::Vector2f _sizeRectangle) {
		if (_positionMouse.x > _positionRectangle.x
			&& _positionMouse.x < _positionRectangle.x + _sizeRectangle.x
			&& _positionMouse.y > _positionRectangle.y
			&& _positionMouse.y < _positionRectangle.y + _sizeRectangle.y)
			return true;
		else { return false; }
	}
	float distance(sf::Vector2f _point1, sf::Vector2f _point2)
	{
		return sqrt((_point1.x - _point2.x) * (_point1.x - _point2.x) + (_point1.y - _point2.y) * (_point1.y - _point2.y));;
	}
	bool circleRect(sf::Vector2f _circlePosition, sf::Vector2f _rectanglePosition, float rayon, sf::Vector2f _rectangleSize) {

		// cx et cy position du cercle
		 //



		 // temporarectanglePosition.y variables to set edges for testing
		float testX = _circlePosition.x;
		float testY = _circlePosition.y;


		// which edge is closest?
		if (_circlePosition.x < _rectanglePosition.x)         testX = _rectanglePosition.x;      // test left edge
		else if (_circlePosition.x > _rectanglePosition.x + _rectangleSize.x) testX = _rectanglePosition.x + _rectangleSize.x;   // right edge
		if (_circlePosition.y < _rectanglePosition.y)         testY = _rectanglePosition.y;      // top edge
		else if (_circlePosition.y > _rectanglePosition.y + _rectangleSize.y) testY = _rectanglePosition.y + _rectangleSize.y;   // bottom edge

		// get distance from closest edges
		float distX = _circlePosition.x - testX;
		float distY = _circlePosition.y - testY;
		float distance = sqrt((distX * distX) + (distY * distY));

		// if the distance is less than the radius, collision!
		if (distance <= rayon) {
			return true;
		}
		return false;
	}

	void direction(sf::Vector2f _playerCenter, sf::Vector2f _mousePos, sf::Vector2f& _cosSin)
	{
		if (tools::distance(_mousePos, _playerCenter) != 0) {
			_cosSin.x = (_mousePos.x - _playerCenter.x) / tools::distance(_mousePos, _playerCenter);
			_cosSin.y = (_mousePos.y - _playerCenter.y) / tools::distance(_mousePos, _playerCenter);
		}
	}


	float calculSin(float _cos)
	{
		if (_cos == -1) { _cos = -0.99; }
		return sqrt(1 - (pow(_cos, 2)));
	}


};