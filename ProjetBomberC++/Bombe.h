#pragma once
#include "tools.h"
#include "myWindow.h"
#include<list>
class Player;
class Map;
class Items;
class Client;
class Killfield;
class SonMusique;
class Bombe
{
protected:
	float tpsForExplo;
	float tpsExplo;
	float dmgBombeClassic;

	float timerB;
	sf::RectangleShape modele;

	bool aExplo;
	bool arret;
	bool hasItPlayer;
	int id = -1;
	bool isEnclenched;
	bool exploPush;
public:
	Bombe();
	Bombe(sf::Vector2f _pos);
	Bombe(sf::Vector2f _pos, int& _id, int& _nbFlamme);
	Bombe(sf::Sprite _spriteBombeExpulsif, sf::Vector2f _positionBombeExpulsif, sf::RectangleShape _recExpulsif, sf::Vector2f _positionExpulsif, int& _id);
	Bombe(sf::Sprite _spriteExplosionExpulsif, sf::Vector2f _positionExplosionExpulsif, int _IlifeExplosionExpulsif, int _prout);
	void InitBomb();
	void Update(Map& _map,Items* _item,Client& _client, Player& _player, Killfield& _killou, SonMusique* _son);
	void avExplo(Map& _map, Items* _item, int _nbFlamme, Player& _player, Killfield& _killou, Client& _client, sf::Vector2f _pos, SonMusique* _son);
	void UpdateSetBombeExpulsif();
	void UpdateSetExplsionExpulsif();

	void Display(myWindow& _window, Client& _client, SonMusique* _son);
	std::list<Bombe*>listeBombe;
	std::list<sf::RectangleShape>listTouche;
	int IlifeBombe = 1;
	float timerBombe = 0.0f;

	int nbFlamme= 1;
	void bonusFlamme() { nbFlamme++; }
	//Bombe expulsif
	std::vector<Bombe*> BOMBEEXPULSIF;
	sf::Sprite spriteBombeExpulsif;
	sf::Texture textureBombeExpulsif;
	sf::Texture* textureBombeExpulsifPOINT = &textureBombeExpulsif;
	sf::Vector2f positionBombeExpulsif;
	sf::Vector2f vitesseBombeExpulsif;
	sf::IntRect intrectBombeExpulsif = { 0,0,22,12 };
	int frameXbombeExpulsif = 0;
	float timerBombeExpulsif = 0.0f;
	int IlifeBombeExpulsif = 1;
	sf::RectangleShape recExpulsif;
	sf::Vector2f positionExpulsif;

	//explosion expulsif
	std::vector<Bombe*> EXPLOSIONEXPULSIF;
	sf::Sprite spriteExplosionExpulsif;
	sf::Texture textureExplosionExpulsif;
	sf::Texture* textureExplosionExpulsifPOINT = &textureExplosionExpulsif;
	sf::Vector2f positionExplosionExpulsif;
	sf::IntRect intrectExplosionExpulsif = { 0,0,64,64 };
	int frameXExplosionExpulsif = 0;
	float timerExplosionExpulsif = 0.0f;
	int IlifeExplosionExpulsif = 1;
	int prout = 1;
	float timer;

	sf::Vector2f pos;

	bool stop = false;
};