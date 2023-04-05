#pragma once
#include "tools.h"

class Player;
class Bombe;
class Zone;
class Killfield;
class Map;
class CardsDied;
class Bonus;
class Items;
class Camera;

enum packetType
{
	NEW_CONNECTION,
	ON_CONNECTION_ADD_OTHER_PLAYER,
	UPDATE_POSITION,
	CLIENT_DISCONNECTED,
	THROW_BOMB,
	THROW_IMPULSIVE,
	CLOSE_RING,
	NOTIFZONE,
	SPD_BOOST,
	HEALL,
	ID_ASSIGN,
	DEATH,
	SENDCHEST,
	SENDATOMIK,
	START,
	SENDBONUS,
	SENDARM,
	INITPOS
};
typedef enum packetType packetType;



struct player
{
	int id;
	sf::Vector2f position;
	std::string username;
	sf::Sprite sprite;
	std::list<Bombe*>ennemyBomb;
	std::list<Bombe*>ennemyImpuls;
	std::list<Bombe*>ennemyExploImpuls;
	sf::IntRect rect;
	int direc;
	bool dead;
};
typedef struct player player;
class Client
{
protected:
	sf::UdpSocket udpSocket;
	float sendTimer = 0.0f;
	float timeOut = 0.0f;

	sf::Texture texture;
	player defaultP;

	sf::IntRect rect;

public:
	unsigned short int port = 6666;
	sf::IpAddress ip = "127.0.0.1";
	std::string pseudo;

	void reset();
	void initClient();
	void updateClient(Player& _player, Bombe& _bomb, Zone& _zone, Killfield& _kill, Map& _map, CardsDied& _card, Bonus& _bonus, Items& _item, Camera& _cam);
	void UDPPos(Player& _player);
	void sendPos(Player& _player);
	void sendDisconnect();
	void initPos(sf::Vector2f& pos, int& id);
	void throw_Impuls(sf::Vector2f _pos, sf::Vector2f _distination);
	void throw_Bomb(sf::Vector2f _pos, int& _nbFlamme);
	void throw_Atomik(sf::Vector2f _pos);
	void sendSPDBoost(int& id);
	void sendBonus(sf::Vector2f& pos, int& type);
	void sendGre(sf::Vector2f& pos);
	void sendHeal(int& id);
	void sendDeath(std::string& _tueur, std::string& _tuee);
	void zoneAuto(int& _ring, bool _close);
	void sendChess(sf::Vector2f& _pos, int& rngBonus, int& rngArme);
	void lunchGame();
	void draw(myWindow& _window);

	void TCPTransactions(Player& _player, Bombe& _bomb, Zone& _zone, Killfield& _kill, Map& _map, CardsDied& _card, Bonus& _bonus, Items& _item, Camera& _cam);
	void connectVerif();

	int zoneToClose;
	int GetZoneToClose() { return zoneToClose; }
	std::list<player*>Ennemies;
	int iid;

	int nbKill;
	int nbSurvivant;

	sf::TcpSocket tcpSock;
};