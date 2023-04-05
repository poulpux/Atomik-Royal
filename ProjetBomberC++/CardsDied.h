#pragma once
#include "tools.h"
#include<list>
class Killfield;
class Client;

#define RACCOURCI "../Ressources/Textures/Cards/"

class Player;
class SonMusique;
enum typeCard
{
	/*CLOSERING,*/
	GIVESPDBOOST,
	HEAL,
	/*SUDDENDEATH,
	BOMBGIFT,
	DAYORNIGHT,
	SMOKE,*/
	ATOMIK,
	/*CHASE,
	BOMBRAIN,
	SUPPLYDROP,*/
	/*BLOODMOOD*/
};
class Player;
class CardsDied
{
protected:
	int cost;
	typeCard type;
	float spdFireBall;
	float tpsTombe;
public:
	sf::Texture defaultTexture;
	sf::Texture textureCloseRing;
	sf::Texture textureAcceleration;
	sf::Texture textureHeal;
	sf::Texture textureSuddenDeath;
	sf::Texture textureBombGift;
	sf::Texture textureDayOrNight;
	sf::Texture textureSmoke;
	sf::Texture textureAtomik;
	sf::Texture textureChase;
	sf::Texture textureBombRain;
	sf::Texture textureSupplyDrop;
	sf::Texture textureBloodMoon;


	CardsDied() {};
	CardsDied(typeCard _type);
	CardsDied(sf::Sprite _spriteBombeAtomic, sf::RectangleShape _recBombeAtomic, sf::Vector2f _positionAttention);
	CardsDied(sf::Sprite _spriteExplosionAtomic, sf::Vector2f _positionExplosionAtomic);
	CardsDied(sf::Sprite _spriteFireball, sf::Vector2f _positionFireball, float _angleDirection);
	void Init();
	void UpdateDied(Player* _p, Killfield& _killou, Client& _client, SonMusique* _son);
	void UpdateSetBombAtomic();
	void UpdateSetExplosionAtomic();
	void UpdateSetFireBall();
	void DisplayBombeAtomic(myWindow* _window);
	void DisplayPiece(myWindow* _window, Player& _player);

	int getCost() { return cost; }
	typeCard getType() { return type; }
	sf::Texture* getTextureCloseR(typeCard& _type);

	//Bomb atomic
	std::vector<CardsDied*> BOMBEATOMIC;
	sf::Sprite spriteBombeAtomic;
	sf::Texture textureBombeAtomic;
	sf::Texture* textureBombeAtomicPOINT = &textureBombeAtomic;
	sf::Vector2f positionBombeAtomic;
	sf::Vector2f vitesseBombeAtomic = { 0.0f, 100.0f };
	sf::Vector2f gravityBombeAtomic = { 0.0f, 200.0f };
	sf::IntRect intrectBombeAtomic = { 0,0,48,32 };
	int frameXbombeAtomic = 0;
	float timerBombeAtomic = 0.0f;
	int IlifeBombeAtomic = 1;
	bool stopson = false;

	sf::RectangleShape recBombeAtomic;
	sf::Vector2f positionrecBombeAtomic;
	float timer = 0.0f;

	//Bomb atomic
	std::vector<CardsDied*> EXPLOSIONATOMIC;
	sf::Sprite spriteExplosionAtomic;
	sf::Texture textureExplosionAtomic;
	sf::Texture* textureExplosionAtomicPOINT = &textureExplosionAtomic;
	sf::Vector2f positionExplosionAtomic;
	sf::IntRect intrectExplosionAtomic = { 0,0,128,128 };
	int frameXExplosionAtomic = 0;
	float timerExplosionAtomic = 0.0f;
	int IlifeExplosionAtomic = 1;

	sf::Sprite spriteAttention;
	sf::Texture textureAttention;
	sf::Vector2f positionAttention;
	bool afficheAttention = false;
	float timerAttention = 0.0f;

	std::vector<CardsDied*> FIREBALL;
	sf::Sprite spriteFireball;
	sf::Texture textureFireball;
	sf::Texture* textureFireballPOINT = &textureFireball;
	sf::Vector2f positionFireball;
	sf::IntRect intrectFireball = { 0,0,96,48 };
	int frameXFireball = 0;
	float timerFireball = 0.0f;
	int IlifeFireball = 1;
	float angleDirection = 0.0f;
	float transparence = 255.0f;
	float timerTombe = 0.0f;

	sf::Sprite spritePiece;
	sf::Texture texturePiece;
	sf::Vector2f positionPiece;
	sf::Text textPiece;
	sf::Font fontPiece;
	sf::Vector2f positiontextPiece;
	float timerGetPiece = 0.0f;
	int NBpiece = 0;
	float cooldowpiece = 15.0f;

};
