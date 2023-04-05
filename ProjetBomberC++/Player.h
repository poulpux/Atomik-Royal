#pragma once
#include "tools.h"
#include "myWindow.h"
#include"gamepadx.hpp"
#include<list>

class Bombe;
class Client;
class Camera;
class Map;
class Bonus;
class CardsDied;
class Items;
class SonMusique;
class Particles;
enum Dir
{
	SOUTH,
	NORTH,
	EAST,
	WEST,
	SOUTH_EAST,
	SOUTH_WEST,
	NORTH_EAST,
	NORTH_WEST,
	NO
};

enum state
{
	PLAYER,
	GAMEDIRECTOR
};

class Player
{
public:
	Player();
	~Player();

	void InitPlayer(Camera& _cam);

	void UpdatePlayer(Bombe& _bomb, Map& _map, Client& _client, myWindow& _window, Camera& _view, CardsDied* _card, Bonus* _bonus, Items* _item, SonMusique* _son);
	void posBomb(Bombe& _bomb, Client& _client, myWindow& _window, Camera& _view, CardsDied* _card, SonMusique* _son);
	void moove(Map* _map);
	int getPv() { return life; };
	int getArmure() { return armure; };
	void changePv(int _healOrDmg) { life -= _healOrDmg; }
	void spdBonus() { spd.x += spdBoost; spd.y += spdBoost; spd2Touch += spdBoost * 0.7; };
	void isDead(Bombe& _bomb, Bonus* _bonus, Items* _item, Camera& _cam, Client& _client);
	void DisplayPlayer(myWindow& _window, CardsDied& _deck, Client& _client);
	void DisplayCarte2(myWindow& _window, CardsDied& _deck, Client& _client);
	void DisplayCarte(myWindow& _window, Client& _client);
	void DisplayRondBleu(myWindow* _window);
	void DisplayCurseur(myWindow& _window);

	void anim();
	void openCardMenu(Client& _client, CardsDied& cardd, SonMusique* _son);
	void activatCard(Client& _client, CardsDied& cardd, SonMusique* _son);
	void Spdlaunch( Client& _client, CardsDied& cardd, myWindow& _window);
	void Heallaunch(Client& _client, CardsDied& cardd, myWindow& _window);

	void TakeSpdBoost();

	int getFlamme() { return bombaPower; }
	state getState() { return stateP; }

	void takeDmg(int _dmg)
	{
		int a = _dmg;
		if (armure < _dmg)
		{
			a -= armure;
			armure = 0;
			life -= a;

		}
		else
			armure -= _dmg;
	}
	void dmgBonus() { if (bombDmg < dmgBombLimit)bombDmg += 12.5; }
	void bandageBonus() { if (life < 76) { life += 25; } else { life = 100; } }
	void armureBonus() { if (armure < 76) { armure += 25; } else { armure = 100; } }
	void nbBombeBonus() { nbBombePosable++; }
	void bombaPowBonus() { bombaPower++; }
	void setMultSpd() { multiSpd = powSpdBonus; }

	int getBonusSpd() { return nbBonusSpd; };
	int getBonusFeu() { return nbBonusFeu; };
	int getBonusArmure() { return nbBonusArmure; };
	int getBonusHeal() { return nbBonusHeal; };
	int getBombeImpulsif() { return nbBombeImpulsif; };

	void UpbonusSpd() { nbBonusSpd += 1; };
	void UpbonusFeu() { nbBonusFeu += 1; };
	void UpbonusArmure() { nbBonusArmure += 1; };
	void UpbonusHeal() { nbBonusHeal += 1; };
	void UpBombeImpulsif() { nbBombeImpulsif += 2; };
	void UpBombeImpulsif2() { nbBombeImpulsif += 1; };

	void SuppbonusArmure() { nbBonusArmure -= 1; };
	void SuppbonusHeal() { nbBonusHeal -= 1; };
	void SuppBombeImpulsif() { nbBombeImpulsif -= 1; };
	void setPos(sf::Vector2f _pos) { pos = _pos; };
	Dir getDirection();
	void powerActivation(CardsDied& _deck);
	sf::Vector2f getPos() { return pos; };
	sf::Texture getTexture() { return texture; }
	Dir getDir() { return playerDir; }
	sf::Sprite sprite;
	bool isHost;
	bool gamelaunch;
	void initInventaire();
	void updateInventaire();
	void DisplayInventaire(myWindow& _window);
	void gainPiece();
	bool activeImpulsif = false;

	int nbBonusSpd = 0;
	int nbBonusFeu = 0;
	int nbBonusArmure = 0;
	int nbBonusHeal = 0;
	int nbBombeImpulsif = 0;

	sf::Vector2f getSpeed() { return sendSpd; };
	bool getDontMove() { if (checkOne && checkTwo)return true; else return false; }
	sf::Vector2f mapPixel;

	sf::Vector2f pos;
	int nbPiece;
	
	std::string posZone;

	void positionZone() {
		if (pos.x > 48.0f && pos.x < 1648.0f)
		{
			if (pos.y > 16 && pos.y < 1616)posZone = "A1";
			else if (pos.y > 1616.0f && pos.y < 3216.0f)posZone = "A2";
			else posZone = "A3";
		}
		else if (pos.x > 1648.0f && pos.x < 3248.0f)
		{
			if (pos.y > 16.0f && pos.y < 1616.0f)posZone = "B1";
			else if (pos.y > 1616.0f && pos.y < 3216.0f)posZone = "B2";
			else posZone = "B3";
		}
		else
		{
			if (pos.y > 16.0f && pos.y < 1616.0f)posZone = "C1";
			else if (pos.y > 1616.0f && pos.y < 3216.0f)posZone = "C2";
			else posZone = "C3";
		}
	}
	float cooldawnPc;
	float timerPc;
	sf::Vector2i mousePosition;
	sf::FloatRect rect2;
	state stateP;
	sf::Texture texture;

	bool checkOne;
	bool checkTwo;
	sf::Vector2f sendSpd;
	float spd2Touch;
	sf::Vector2f spd;
	sf::IntRect rect;
	float spdDirector;
	float spdBoost;
	float bombCdwn;
	float bombDmg;
	float timerBomb;
	float dmgBombLimit;
	sf::Vector2f hitBox;
	sf::Vector2f positionHitBox;

	int nbBombePosable;
	int bombaPower;
	int life;
	int armure;
	float spdSave;
	int totalCard;
	float timerCardMenu;
	bool isCardMenuOpen = false;
	sf::Sprite spriteC;
	sf::Vector2f positionC;
	float timerClicked;
	bool cardUsingOpen;
	bool spdMenu;
	bool healMenu;
	int laquelle;
	sf::RectangleShape rectShowCible;
	sf::Text nameEnnemy;
	sf::Font font;

	float timerSpdBoost;
	float dureSpdBonus;
	float powSpdBonus;
	float multiSpd;
	float timerCourse;
	std::list<CardsDied*>allCards;
	std::list<CardsDied*>main;

	Dir playerDir;

	//inv
	sf::Texture ttInventaire;
	sf::Sprite ssInventaire;
	sf::RectangleShape rInv, rChoixObjet;
	sf::Vector2f posInv, posChoixBombe;
	int iChoixBombe;
	float timerChoixBombe{ 0 };
	//case inv
	sf::Texture textureCaseInv;
	sf::Sprite spriteCaseInv;
	sf::Vector2f positionCaseInv = { 1445.0f, 942.0f };
	int NBSwitchItem = 1;
	//nbItem dans inventaire
	sf::Text textNbBombeImpulsif;

	sf::Text textNbBombeEnPLus;
	int NBBombeEnPlus = 0;
	sf::Text textNbBombeArmure;
	int NBBombeArmure = 0;
	sf::Text textNbBombeHeal;
	int NBBombeHeal = 0;

	float timerManette = 0.0f, timerParti, timerPartieS;

	sf::CircleShape recBleuPlayer;
	sf::Vector2f positionrecBleuPlayer;

	sf::Sprite spritecurseur;
	sf::Texture texturecurseur;
	sf::Vector2f positioncurseur = { 0.0f, 0.0f }, registerPos;
	sf::Vector2i positionMouse;

	bool pasRepAtomik, healParti, shieldParti;
	bool inzone;
private:
	std::list<Particles*>Parti;
};

