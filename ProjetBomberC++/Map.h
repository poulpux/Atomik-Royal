#pragma once
#include "tools.h"
class Camera;
class Items;
class Bonus;
class Player;
class Client;
class Map
{
public:

	enum direction {
		NORTH = 1, EAST, SOUTH, WEST
	};

	Map();
	Map(sf::Sprite _SpriteTile, sf::Vector2f _positionTile);
	Map(sf::Sprite _SpriteTileCoffre, sf::Vector2f _positionTileCoffre, int _IlifeTileCoffre, int _randdo, int _randoarme);
	~Map();

	void InitMap(Items* _items,Player& _player, Client& _client);
	void DisplayMap(myWindow& _window);
	void DisplayMapHITBOX(myWindow& _window, Bonus* _bonus, Items* _items);
	
	bool collisionPlayer(sf::FloatRect sprite, Direction _dir, sf::Vector2f vitesse);
	bool collisionBombe(sf::Vector2f);

	void loadMap();
	void saveMap();

	void loadMapCoffre(Items* _items,Client& _client);
	void saveMapCoffre(Items* _items);

	std::vector<Map*> MAP;	
	sf::Sprite SpriteTile;
	
	sf::Sprite SpriteTileCoffre;
	std::vector<Map*> MAPCOFFRE;
	sf::Texture TextureTileCoffre;
	sf::Texture* TextureTileCoffrePoint = &TextureTileCoffre;
	sf::Vector2f positionTileCoffre;
	int IlifeTileCoffre = 1;
	int randdo = 0;
	int randoarme = 0;

	bool stopcreat = false;
	bool stopcreat2 = false;
protected:

	sf::Sprite spriteMap;
	sf::Texture textureMap;
	sf::Vector2f positionMap = {48.0f, 16.0f};
	
	sf::Texture TextureTile;
	sf::Texture* TextureTilePoint = &TextureTile;
	sf::Vector2f positionTile;
	sf::Vector2i intTile;

	sf::Vector2i mousePosition;
	bool tab[150][150];
	float keytimer = 0.0f;
};

