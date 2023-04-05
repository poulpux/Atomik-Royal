#include "Map.h"
#include "Camera.h"
#include "Map.h"
#include "Items.h"
#include "Bonus.h"
#include "Player.h"
#include"Client.h"
Map::Map()
{
}

Map::Map(sf::Sprite _SpriteTile, sf::Vector2f _positionTile)
{
	//contructeur collision
	positionTile = _positionTile;
	SpriteTile = _SpriteTile;
}

Map::Map(sf::Sprite _SpriteTileCoffre, sf::Vector2f _positionTileCoffre, int _IlifeTileCoffre, int _randdo, int _randoarme)
{
	//contructeur coffre
	SpriteTileCoffre = _SpriteTileCoffre;
	positionTileCoffre = _positionTileCoffre;
	IlifeTileCoffre = _IlifeTileCoffre;
	randdo = _randdo;
	randoarme = _randoarme;
}

Map::~Map()
{
}

void Map::InitMap(Items* _items, Player& _player, Client& _client)
{
	textureMap.loadFromFile(TEXTURE_PATH"CarrerMapPasFinis.png");
	spriteMap.setTexture(textureMap);
	spriteMap.setPosition(positionMap);
	spriteMap.setScale(sf::Vector2f(1.0f, 1.0f));

	TextureTile.loadFromFile(TEXTURE_PATH"hitbox.png");
	SpriteTile.setTexture(*TextureTilePoint);
	SpriteTile.setPosition(positionTile);

	TextureTileCoffre.loadFromFile(TEXTURE_PATH"CoffreMap.png");
	SpriteTileCoffre.setTexture(*TextureTileCoffrePoint);
	SpriteTileCoffre.setPosition(positionTileCoffre);

	if(_player.isHost) loadMapCoffre(_items, _client);
	loadMap();



	//on met toutes les collisions dans un tableau de bool
	float min = 0;
	for (auto& _m : MAP)
	{
		sf::Vector2i test;
		test.x = (int)((_m->positionTile.x + 32) / 32);
		test.y = (int)((_m->positionTile.y + 32) / 32);
		tab[test.y][test.x] = true;
	}
}


void Map::DisplayMap(myWindow& _window)
{
	_window.Draw(spriteMap);
}

void Map::DisplayMapHITBOX(myWindow& _window, Bonus* _bonus, Items* _items)
{
	//Display des coffres et item/bonus au sol
	for (auto& _m : MAP)
	{
		_m->SpriteTile.setPosition(_m->positionTile);
	}

	for (auto c : MAPCOFFRE)
	{
		c->SpriteTileCoffre.setPosition(c->positionTileCoffre);
		_window.Draw(c->SpriteTileCoffre);
	}

	for (int i = 0; i < MAPCOFFRE.size(); i++)
	{
		if (MAPCOFFRE[i]->IlifeTileCoffre <= 0)
		{
			if (MAPCOFFRE[i]->randdo == 1)
				_bonus->BONUSFEU.push_back(new Bonus(_bonus->spriteBonus, sf::Vector2f(MAPCOFFRE[i]->positionTileCoffre.x + 16.0f, MAPCOFFRE[i]->positionTileCoffre.y + 16.0f), 0));

			if (MAPCOFFRE[i]->randdo == 2)
				_bonus->BONUSFEU.push_back(new Bonus(_bonus->spriteBonus, sf::Vector2f(MAPCOFFRE[i]->positionTileCoffre.x + 16.0f, MAPCOFFRE[i]->positionTileCoffre.y + 16.0f), 1));

			if (MAPCOFFRE[i]->randdo == 3)
				_bonus->BONUSFEU.push_back(new Bonus(_bonus->spriteBonus, sf::Vector2f(MAPCOFFRE[i]->positionTileCoffre.x + 16.0f, MAPCOFFRE[i]->positionTileCoffre.y + 16.0f), 2));
				
			if (MAPCOFFRE[i]->randdo == 4)
				_bonus->BONUSFEU.push_back(new Bonus(_bonus->spriteBonus, sf::Vector2f(MAPCOFFRE[i]->positionTileCoffre.x + 16.0f, MAPCOFFRE[i]->positionTileCoffre.y + 16.0f), 3));

			if (MAPCOFFRE[i]->randoarme == 3)
				_items->ITEMEXPULSIF.push_back(new Items(_items->spriteItemExpulsif, sf::Vector2f(MAPCOFFRE[i]->positionTileCoffre.x + 16.0f, MAPCOFFRE[i]->positionTileCoffre.y + 16.0f), false));

			MAPCOFFRE.erase(MAPCOFFRE.begin() + i);
		}
	}
}

bool Map::collisionPlayer(sf::FloatRect sprite, Direction _dir, sf::Vector2f vitesse)
{
	sf::Vector2i persosprite;
	sf::Vector2i persosprite2;

	//Collision du joueur

	if (_dir == HAUT)
	{
		persosprite.x = (int)(sprite.left + 16) / 32.0f;
		persosprite.y = (int)(sprite.top - vitesse.y * tools::GetTimeDelta() + 16) / 32.0f;
		persosprite2.x = (int)(sprite.left + sprite.width + 16) / 32.0f;
		persosprite2.y = (int)(sprite.top - vitesse.y * tools::GetTimeDelta() + 16) / 32.0f;
		if (tab[persosprite.y][persosprite.x] == 1 || tab[persosprite2.y][persosprite2.x] == 1) return true;

	}
	if (_dir == BAS)
	{

		persosprite.x = (int)(sprite.left + 16) / 32.0f;
		persosprite.y = (int)(sprite.top + sprite.height + vitesse.y * tools::GetTimeDelta() + 14) / 32.0f;
		persosprite2.x = (int)(sprite.left + sprite.width + 16) / 32.0f;
		persosprite2.y = (int)(sprite.top + sprite.height + vitesse.y * tools::GetTimeDelta() + 14) / 32.0f;

		if (tab[persosprite.y][persosprite.x] == 1 || tab[persosprite2.y][persosprite2.x] == 1) return true;

	}
	if (_dir == GAUCHE)
	{
		persosprite.x = (int)(sprite.left - vitesse.x * tools::GetTimeDelta() + 16) / 32.0f;
		persosprite.y = (int)(sprite.top + 18) / 32.0f;
		persosprite2.x = (int)(sprite.left - vitesse.x * tools::GetTimeDelta() + 16) / 32.0f;
		persosprite2.y = (int)(sprite.top + sprite.height + 14) / 32.0f;

		if (tab[persosprite.y][persosprite.x] == 1 || tab[persosprite2.y][persosprite2.x] == 1) return true;

	}
	if (_dir == DROITE)
	{
		persosprite.x = (int)(sprite.left + sprite.width + vitesse.x * tools::GetTimeDelta() + 16) / 32.0f;
		persosprite.y = (int)(sprite.top + 18) / 32.0f;
		persosprite2.x = (int)(sprite.left + sprite.width + vitesse.x * tools::GetTimeDelta() + 16) / 32.0f;
		persosprite2.y = (int)(sprite.top + sprite.height + 14) / 32.0f;

		if (tab[persosprite.y][persosprite.x] == 1 || tab[persosprite2.y][persosprite2.x] == 1) return true;

	}
	return false;
}

bool Map::collisionBombe(sf::Vector2f _pos)
{
	//Collision pour la flamme des bombes
	sf::Vector2i pos;
	pos.x = (int)(_pos.x / 32);
	pos.y = (int)(_pos.y / 32);
	if (tab[pos.y][pos.x] == true) { return true; }
}

void Map::loadMap()
{
	//Va chercher les collisions
	std::ifstream mapFile("..\\Ressources\\Maps\\Map1.map");

	sf::Vector2f posTemp;
	int typeTemp;
	while (!mapFile.eof())
	{
		mapFile >> posTemp.x;
		mapFile >> posTemp.y;

		MAP.push_back(new Map(SpriteTile, posTemp));
	}
	mapFile.close();

}

void Map::saveMap()
{
	std::ofstream mapFile("..\\Ressources\\Maps\\Map1.map");
	for (auto _o : MAP)
	{
		mapFile << _o->positionTile.x;
		mapFile << ' ';
		mapFile << _o->positionTile.y;
		mapFile << std::endl;
	}
	mapFile.close();

}

void Map::loadMapCoffre(Items* _items, Client& _client)
{
	//Pose les coffres aléatoirement sur la carte
	std::ifstream mapFile("..\\Ressources\\Maps\\MapCoffre.map");
	sf::Vector2f posTemp;

	while (!mapFile.eof())
	{
		int rngC = 0;
		int rngBonus = 0;
		int rngArme = 0;
		mapFile >> posTemp.x;
		mapFile >> posTemp.y;

		rngC = tools::iRand(1, 3);
		rngBonus = tools::iRand(1, 5);
		rngArme = tools::iRand(1, 4);
		if (rngC == 1)
		{
			_client.sendChess(posTemp, rngBonus, rngArme);
			MAPCOFFRE.push_back(new Map(SpriteTileCoffre, posTemp, 1, rngBonus, rngArme));
		}
	}

	mapFile.close();
}

void Map::saveMapCoffre(Items* _items)
{
	std::ofstream mapFile("..\\Ressources\\Maps\\MapCoffre.map");
	for (auto _o : MAPCOFFRE)
	{
		mapFile << _o->positionTileCoffre.x;
		mapFile << ' ';
		mapFile << _o->positionTileCoffre.y;
		mapFile << std::endl;
	}
	mapFile.close();
}
