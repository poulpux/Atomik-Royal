#include "Client.h"
#include"Player.h"
#include<thread>
#include"Bombe.h"
#include"Zone.h"
#include"Killfield.h"
#include"Map.h"
#include"CardsDied.h"
#include"Bonus.h"
#include"Items.h"
#include"Camera.h"
void Client::connectVerif()
{

}

void Client::reset()
{
	sendTimer = 0.0f;
	timeOut = 0.0f;
	port = 6666;
	ip = "127.0.0.1";
	pseudo = "";
	zoneToClose = 0;
	std::list<player*>a;
	std::list<player*>Ennemies = a;
	iid = 0;

	nbKill = 0;
	nbSurvivant = 2;
	tcpSock.disconnect();
	tcpSock.setBlocking(true);
}

void Client::initClient()
{
	/*if (udpSocket.bind(port) != sf::Socket::Done)
		std::cerr << "Erreur de bind" << std::endl;*/
	

	/*sf::TcpSocket tcpSock;*/
	if (tcpSock.connect(ip, port) == sf::Socket::Done)
	{
		std::cout << "Connecte au serveur" << std::endl;

		tcpSock.setBlocking(false);
		sf::Packet sendPacket;
		sendPacket << pseudo;
		tcpSock.send(sendPacket);
	}
	else // sinon on quitte
	{
		std::cout << "Echec connection au serveur : "<<"ip = "<<ip<<" pseudo = "<<pseudo << std::endl;
	}
	texture.loadFromFile("../Ressources/Textures/basic.png");
	rect = { 65,22,13,16 };
	
}

void Client::updateClient(Player& _player, Bombe& _bomb, Zone& _zone, Killfield& _kill, Map& _map, CardsDied& _card, Bonus& _bonus, Items& _item, Camera& _cam)
{
	/*UDPPos(_player);*/
	sendPos(_player);
	TCPTransactions(_player,_bomb, _zone, _kill,_map, _card, _bonus, _item, _cam);
}

void Client::UDPPos(Player& _player)
{
	sf::Packet sendPacket;
	sendPacket  << _player.getPos().x << _player.getPos().y;
	if (udpSocket.send(sendPacket, ip, port) != sf::Socket::Done)
		std::cerr << "Erreur d'envoi" << std::endl;

	sf::Packet receivedPacket;
	if (udpSocket.receive(receivedPacket, ip, port) != sf::Socket::Done)
		std::cerr << "Erreur de reception" << std::endl;
	else
	{
		timeOut = 0;
		sf::Vector2f receivedPos;
		int id;
		receivedPacket >>id>> receivedPos.x >> receivedPos.y;
		if (receivedPos.x != 0 && receivedPos.y != 0)
		{
			auto i = Ennemies.begin();
			auto n = Ennemies.end();
			while (i != n)
			{
				if (id == (*i)->id)
				{
					(*i)->position.x = receivedPos.x;
					(*i)->position.y = receivedPos.y;
					(*i)->direc = 1;
				}
				i++;
			}
		}
		/*std::cout << "Position du joueur (Client) : " << receivedPos.x << " , " << receivedPos.y << std::endl;*/
	}
}

void Client::sendPos(Player& _player)
{
	sendTimer += tools::GetTimeDelta();
	timeOut += tools::GetTimeDelta();
	float time;
	//if (_player.isHost)time = 0.007;
	//else time = 0.015;
	if (sendTimer >0.06)
	{
		sf::Packet sendPacket;
		sf::Vector2f position;
		position.x = _player.getPos().x; position.y = _player.getPos().y;
		int rect = _player.rect.top;
		if (tcpSock.send(sendPacket) == sf::Socket::Done)
		{
			sendPacket << UPDATE_POSITION<<pseudo << _player.getDir()<< position.x << position.y<<rect;
			tcpSock.send(sendPacket);
			timeOut = 0.0f;
		}

		sendTimer = 0.0f;
	}
}

void Client::sendDisconnect()
{
	std::cout << "Disconnated" << std::endl;
	sf::Packet sendPacket;
	if (tcpSock.send(sendPacket) == sf::Socket::Done)
	{
		sendPacket << CLIENT_DISCONNECTED;
		tcpSock.send(sendPacket);
		timeOut = 0.0f;
	}
}

void Client::initPos(sf::Vector2f& pos, int& id)
{
	sf::Packet sendPacket;
	if (tcpSock.send(sendPacket) == sf::Socket::Done)
	{
		std::cout << "Send : " << pos.x << ", " << pos.y << " id : " << id << std::endl;
		sendPacket << INITPOS << pos.x << pos.y<<id;
		tcpSock.send(sendPacket);
		timeOut = 0.0f;
	}
}

void Client::throw_Impuls(sf::Vector2f _pos, sf::Vector2f _destination)
{
	sf::Packet sendPacket;
	if (tcpSock.send(sendPacket) == sf::Socket::Done)
	{
		sendPacket << THROW_IMPULSIVE << iid << _pos.x << _pos.y << _destination.x << _destination.y;
		tcpSock.send(sendPacket);
		timeOut = 0.0f;
	}
}


void Client::throw_Bomb(sf::Vector2f _pos, int& _nbFlamme)
{
	sf::Packet sendPacket;
	if (tcpSock.send(sendPacket) == sf::Socket::Done)
	{
		sendPacket << THROW_BOMB << pseudo << _pos.x << _pos.y << _nbFlamme;
		tcpSock.send(sendPacket);
		timeOut = 0.0f;
	}
}

void Client::throw_Atomik(sf::Vector2f _pos)
{
	sf::Packet sendPacket;
	if (tcpSock.send(sendPacket) == sf::Socket::Done)
	{
		sendPacket << SENDATOMIK << _pos.x << _pos.y;
		tcpSock.send(sendPacket);
		timeOut = 0.0f;
	}
}

void Client::sendSPDBoost(int& id)
{
	sf::Packet sendPacket;

	if (tcpSock.send(sendPacket) == sf::Socket::Done)
	{
		sendPacket << SPD_BOOST << id;
		tcpSock.send(sendPacket);
		timeOut = 0.0f;
	}
}

void Client::sendBonus(sf::Vector2f& pos, int& type)
{
	sf::Packet sendPacket;

	if (tcpSock.send(sendPacket) == sf::Socket::Done)
	{
		sendPacket << SENDBONUS << pos.x << pos.y << type;
		tcpSock.send(sendPacket);
		timeOut = 0.0f;
	}
}

void Client::sendGre(sf::Vector2f& pos)
{
	sf::Packet sendPacket;

	if (tcpSock.send(sendPacket) == sf::Socket::Done)
	{
		sendPacket << SENDARM << pos.x << pos.y ;
		tcpSock.send(sendPacket);
		timeOut = 0.0f;
	}
}

void Client::sendHeal(int& id)
{
	sf::Packet sendPacket;

	if (tcpSock.send(sendPacket) == sf::Socket::Done)
	{
		sendPacket << HEALL << id;
		tcpSock.send(sendPacket);
		timeOut = 0.0f;
	}
}
void Client::sendDeath(std::string& _tueur, std::string& _tuee)
{
	sf::Packet sendPacket;

	if (tcpSock.send(sendPacket) == sf::Socket::Done)
	{
		sendPacket << DEATH << iid<< _tueur << _tuee;
		tcpSock.send(sendPacket);
		timeOut = 0.0f;
	}
}
void Client::zoneAuto(int& _ring, bool _close)
{
	sf::Packet sendPacket;

	if (tcpSock.send(sendPacket) == sf::Socket::Done)
	{
		pseudo = std::to_string( _close);
		std::cout << pseudo << std::endl;
		sendPacket << CLOSE_RING << pseudo << _ring;
		tcpSock.send(sendPacket);
		timeOut = 0.0f;
	}
}

void Client::sendChess(sf::Vector2f& _pos, int& rngBonus, int& rngArme)
{
	sf::Packet sendPacket;
	if (tcpSock.send(sendPacket) == sf::Socket::Done)
	{
		sendPacket << SENDCHEST << _pos.x << _pos.y << rngBonus << rngArme;
		tcpSock.send(sendPacket);
		timeOut = 0.0f;
	}
}

void Client::lunchGame()
{
	sf::Packet sendPacket;
	if (tcpSock.send(sendPacket) == sf::Socket::Done)
	{
		sendPacket << START;
		tcpSock.send(sendPacket);
		timeOut = 0.0f;
	}
}


void Client::draw(myWindow& _window)
{
	auto i = Ennemies.begin();
	auto n = Ennemies.end();
	while (i!=n)
	{
		if (!(*i)->dead)
		{
			(*i)->sprite.setPosition((*i)->position);
			(*i)->sprite.setTextureRect(rect);
			(*i)->sprite.setColor(sf::Color(255, 0, 0, 200));
			(*i)->sprite.setTexture(texture);
			if ((*i)->direc == NORTH_WEST) { (*i)->rect.left = 113; }
			else if ((*i)->direc == NORTH_EAST) { (*i)->rect.left = 17; }
			else if ((*i)->direc == SOUTH_WEST) { (*i)->rect.left = 81; }
			else if ((*i)->direc == SOUTH_EAST) { (*i)->rect.left = 49; }
			else if ((*i)->direc == EAST) { (*i)->rect.left = 33; }
			else if ((*i)->direc == WEST) { (*i)->rect.left = 97; }
			else if ((*i)->direc == NORTH) { (*i)->rect.left = 1; }
			else if ((*i)->direc == SOUTH) { (*i)->rect.left = 65; }
			(*i)->sprite.setTextureRect((*i)->rect);
			_window.Draw((*i)->sprite);
		}
		i++;
	}
}

void Client::TCPTransactions(Player& _player, Bombe& _bomb, Zone& _zone, Killfield& _kill, Map& _map, CardsDied& _card, Bonus& _bonus, Items& _item, Camera& _cam)
{
	sf::Packet receivePacket;
	std::string username;
	sf::Vector2f pos; sf::Vector2f posAtteri;
	int direc;
	int id;

	if (tcpSock.receive(receivePacket) == sf::Socket::Done)
	{
		timeOut = 0.0f;
		int pType;
		receivePacket >> pType;
		if (pType == NEW_CONNECTION)		// Nouvelle connection sur le serveur, on instancie le nouveau player
		{
			receivePacket >> username >> id;
			std::cout << "Player : " << id << " has join the game." << std::endl;

			player* ennemy = new player();
			ennemy->id = id;
			ennemy->position.x = 500.0f;
			ennemy->position.y = 300.0f;
			ennemy->username = username;
			ennemy->sprite.setTexture(texture); 
			ennemy->sprite.setScale(1.8f, 1.8f);
			ennemy->rect = { 65,22,13,16 };
			Ennemies.push_back(ennemy);
		}
		else if (pType == ON_CONNECTION_ADD_OTHER_PLAYER)	// Quand on se connecte on récupére les autres players déjà connectés
		{
			
			receivePacket >> username >> id >> pos.x >> pos.y;

			player* ennemy = new player();
			ennemy->id = id;
			ennemy->position.x = pos.x;
			ennemy->position.y = pos.y;
			ennemy->username = username;
			ennemy->sprite.setTexture(texture);
			ennemy->sprite.setScale(1.8f, 1.8f);
			ennemy->rect = { 65,22,13,16 };
			std::cout << "Player : " << id << " is in the game." << std::endl;
			Ennemies.push_back(ennemy);
		}
		else if (pType == UPDATE_POSITION)		// Mise à jour des position de chaque joueur
		{
			int rect;
			receivePacket >> id >> username >> direc >> pos.x >> pos.y>> rect;
			if (pos.x != 0 && pos.y != 0)
			{
				auto i = Ennemies.begin();
				auto n = Ennemies.end();
				while (i != n)
				{
					if (id == (*i)->id)
					{
						(*i)->position.x = pos.x;
						(*i)->position.y = pos.y;
						(*i)->direc = direc;
						(*i)->rect.top = rect;
					}
					i++;
				}
			}
		}
		else if (pType == CLIENT_DISCONNECTED)	// Lorsqu'un joueur se déconnecte du serveur on l'enléve du client
		{
			receivePacket >> id;
			auto i = Ennemies.begin();
			auto n = Ennemies.end();
			while (i != n)
			{
				if ((*i)->id == id)
				{
					std::cout << (*i)->username << " is disconnected" << std::endl;
					(*i)->sprite.setPosition(sf::Vector2f(-5000, -5000));
					delete(*i);
					i = Ennemies.erase(i);
				}
				else
				{
					i++;
				}
			}
		}
		else if (pType == THROW_BOMB)
		{
			int nbFlamme;
			receivePacket >> id >> username >> pos.x >> pos.y >> nbFlamme ;
			if (pos.x != 0 && pos.y != 0)
			{
				auto i = Ennemies.begin(); auto n = Ennemies.end();
				while (i!=n)
				{
					if ((*i)->id == id)
					{
						(*i)->ennemyBomb.push_back(new Bombe(pos,(*i)->id,nbFlamme));
						/*_bomb.listeBombe.push_back(new Bombe(pos));*/
					}
					i++;
				}
			}
		}
		else if (pType == THROW_IMPULSIVE)
		{
			receivePacket >> id >> pos.x >> pos.y>>posAtteri.x>>posAtteri.y;
			if (pos.x != 0 && pos.y != 0)
			{
				auto i = Ennemies.begin(); auto n = Ennemies.end();
				while (i != n)
				{
					if ((*i)->id == id)
					{
						(*i)->ennemyImpuls.push_back(new Bombe(_bomb.spriteBombeExpulsif, pos, _bomb.recExpulsif, posAtteri,id));
						/*_bomb.BOMBEEXPULSIF.push_back(new Bombe(_bomb.spriteBombeExpulsif, pos, _bomb.recExpulsif, posAtteri));*/
					}
					i++;
				}
			}
		}
		else if (pType == CLOSE_RING)
		{
			int ring;
			receivePacket >> username >> ring;
			if (username == "1")
			{
				_zone.saveRand = ring;
				_zone.timer = 0;
				_zone.ringClose(RANDOM);
			}
			else
			{
				_zone.foireux = true;
				int compt = 0;
				auto i = _zone.rings.begin();
				auto n = _zone.rings.end();
				while (i != n)
				{
					if (ring == compt && (*i)->close == 0)
					{
						_zone.nomNotif = (*i)->pos;
						compt++;
					}
					if((*i)->close == 0) compt++;
					i++;
				}
				_zone.timer = 0;
			}
			
		}
		else if (pType == SPD_BOOST)
		{
			receivePacket >> id;
			_player.setMultSpd();
			std::cout << "met la fonction spdBoost" << std::endl;
		}
		else if (pType == HEALL)
		{
			receivePacket >> id;
			_player.bandageBonus();
			std::cout << "HEAL !" << std::endl;
		}
		else if (pType == ID_ASSIGN)
		{
			receivePacket >> id;
			iid = id;
		}
		else if (pType == DEATH)
		{
			int iidd;
			std::string tueur, tuee;
			receivePacket >> iidd>>tueur >> tuee;
			auto i = Ennemies.begin(); auto n = Ennemies.end();
			while (i!=n)
			{
				if ((*i)->id == iidd && !(*i)->dead)
				{
					if(tueur == pseudo) nbKill++;
					_kill.killList.push_back(new Killfield(tueur, tuee));
					(*i)->dead = true;
				}
				i++;
			}
		}
		else if (pType == SENDCHEST)
		{
			sf::Vector2f pos;
			int bonus, arme;
			receivePacket >> pos.x >> pos.y >> bonus >> arme;
			_map.MAPCOFFRE.push_back(new Map(_map.SpriteTileCoffre, pos, 1, bonus, arme));
		}
		else if (pType == SENDATOMIK)
		{
			sf::Vector2f pos;
			receivePacket >> pos.x >> pos.y ;
			_card.BOMBEATOMIC.push_back(new CardsDied(_card.spriteBombeAtomic, _card.recBombeAtomic, pos));
		}
		else if (pType == START)
		{
			_player.gamelaunch = true;
		}
		else if (pType == SENDBONUS)
		{
			sf::Vector2f pos;
			int typeB;
			receivePacket >> pos.x >> pos.y >> typeB;
			_bonus.BONUSFEU.push_back(new Bonus(_bonus.spriteBonus, pos, typeB));
		}
		else if (pType == SENDARM)
		{
			sf::Vector2f pos;
			receivePacket >> pos.x >> pos.y;
			_item.ITEMEXPULSIF.push_back(new Items(_item.spriteItemExpulsif, pos, true));
		}
		else if (pType == INITPOS)
		{
			sf::Vector2f pos;
			receivePacket >> pos.x >> pos.y;
			std::cout << "Client : " << pos.x << " , " << pos.y << std::endl;
			_player.setPos(pos);
			_cam.positionView = { pos };
		}
	}
}
