#pragma once
#include "tools.h"
class Camera;
class Player;
class Bombe;
class Client;
class SonMusique;
class Bonus
{
public:

	Bonus();
	Bonus(sf::Sprite _spriteBonusFeu, sf::Vector2f _positionBonusFeu, int _frameXBonus);
	~Bonus();

	void InitBonus();
	void UpdateBonus(myWindow& _window, Camera* _cam, Player* _p, Bombe* _bomb, Client* _client, SonMusique* _son);
	void UpdateSetBonus();
	void DisplayBonus(myWindow* _window);

	//Bounus Feu
	std::vector<Bonus*> BONUSFEU;
	sf::Sprite spriteBonus;
	sf::Texture textureBonus;
	sf::Texture *textureBonusPOINT = &textureBonus;
	sf::Vector2f positionBonusFeu;
	sf::IntRect intrectBonus = {0,0,36,36};
	int frameXBonus = 0;
	int IlifeVitesse = 1;
	
	float timerkey = 0.0f;
private:
};

