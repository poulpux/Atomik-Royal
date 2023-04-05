#pragma once
#include "tools.h"
#include "Bombe.h"
class Camera;
class Bonus;
class Player;
class Client;
class SonMusique;
class Items : public Bombe
{
private:
	sf::Texture Tcoffre;

	sf::Vector2i PosMouse;

	float TimerItems = 0.0f;

public:

	Items();
	Items(sf::Sprite _sprite,sf::Vector2f _pos,int _life);
	Items(sf::Sprite _spriteItemExpulsif, sf::Vector2f _positionItemExpulsif, bool _plusOuMoin);
	~Items();

	void initItems();
	void updateItems(myWindow& window, Camera* _cam, Player* _p, Client* _client, SonMusique* _son);
	void displayItems(myWindow& window, Bonus* _bonus);

	std::vector<Items*>coffre;

	sf::Sprite Scoffre;
	sf::Vector2f PosCoffre;
	int life = 0;
	int random = 0;

	std::vector<Items*> ITEMEXPULSIF;
	sf::Sprite spriteItemExpulsif;
	sf::Texture textureItemExpulsif;
	sf::Texture* textureItemExpulsifPOINT = &textureItemExpulsif;
	sf::Vector2f positionItemExpulsif;
	int IlifeItemExpulsif = 1;
	bool plusOuMoin = false;

	bool degaeItem = false;
};