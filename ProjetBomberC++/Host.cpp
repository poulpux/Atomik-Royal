#include "Host.h"
#include"Client.h"
#include<thread>
#include<mutex>
#include"Map.h"
#include"Player.h"
void Host::init(Client& _client)
{
	/*if (udpSocket.bind(clientPort) != sf::Socket::Done)
		std::cerr << "Erreur de bind" << std::endl;*/
	port = _client.port;
	clientPort = _client.port;
	nbClient = 0;
	ip = _client.ip;
	clientIp = _client.ip;

	if (listener.listen(port) == sf::Socket::Done)
	{
		selector.add(listener);
		std::cout << "Serveur en ligne" << std::endl;
	}
	else
	{
		exit(0);
	}
}

void Host::Update(Map& _map, Player& _player)
{
	if (selector.wait())
	{
		tools::restartClock();
		if (selector.isReady(listener))
		{
			if(!_player.gamelaunch) connect();
		}
		else 
		{

			TCPProtocol(_map);
		}
		/*deconnect();*/
	}
	/*UDPPos();*/
}

void Host::connect()
{
	sf::Packet receivePacket;
	std::string pseudo;

	ClientH* client = new ClientH();
	client->tcpSock = new sf::TcpSocket();
	client->udpSock = new sf::UdpSocket();
	listener.accept(*client->tcpSock);
	selector.add(*client->tcpSock);
	selector.add(*client->udpSock);
	client->id = nbClient;

	if (client->tcpSock->receive(receivePacket) == sf::Socket::Done)
	{
		receivePacket >> pseudo;
	}
	std::cout << pseudo << " : " << client->id << std::endl;
	client->pseudo = pseudo;
	listClients.push_back(client);
	nbClient++;

	auto i = listClients.begin();
	auto n = listClients.end();
	while (i != n)
	{
		//Envoie que t'existe aux autres 
		if ((*i)->id != client->id)
		{
			sf::Packet sendPacket;
			sendPacket << packetType::NEW_CONNECTION << pseudo << client->id;
			(*i)->tcpSock->send(sendPacket);
		}
		else //Repere les autres
		{
			auto g = listChest.begin(); auto l = listChest.end();
			while (g!=l)
			{
				sf::Packet sendPacket;
				int bonus = (*g)->randdo, arme = (*g)->randoarme;
				sf::Vector2f pos = (*g)->positionTileCoffre;
				sendPacket << packetType::SENDCHEST << pos.x << pos.y << bonus << arme;
				client->tcpSock->send(sendPacket);
				g++;
			}
			auto j = listClients.begin();
			auto q = listClients.end();
			while (j != q)
			{

				sf::Packet sendPacket;
				if ((*j)->id != client->id)
				{
					sendPacket << packetType::ON_CONNECTION_ADD_OTHER_PLAYER << (*j)->pseudo << (*j)->id << (*j)->pos.x << (*j)->pos.y;
					(*i)->tcpSock->send(sendPacket);
				}
				else
				{
					sendPacket << packetType::ID_ASSIGN << (*i)->id;
					(*i)->tcpSock->send(sendPacket);
				}
				j++;
			}
		}
		i++;
	}
}

void Host::UDPPos()
{
	if (udpSocket.receive(receivePacket,clientIp, clientPort) != sf::Socket::Done)
		std::cerr << "Erreur de reception" << std::endl;
	else
	{
		int id;
		receivePacket >> id>>receivePosition.x >> receivePosition.y;
		sendPacket.clear();
		sendPacket <<receivePosition.x << receivePosition.y;
		udpSocket.send(sendPacket,clientIp, clientPort);
	}
}

void Host::TCPProtocol(Map& _map)
{
	int a = 0;
	sf::Packet receivePacket;
	auto i = listClients.begin();
	auto n = listClients.end();
	while (i != n)
	{
		if (selector.isReady(*(*i)->tcpSock)||selector.isReady(*(*i)->udpSock))
		{
			if ((*i)->udpSock->receive(receivePacket, clientIp, clientPort) == sf::Socket::Done)
			{
				int id;
				receivePacket >> id >> receivePosition.x >> receivePosition.y;
				sendPacket.clear();
				sendPacket << id << receivePosition.x << receivePosition.y;
				auto j = listClients.begin();
				auto q = listClients.end();
				while (j != q)
				{
					if ((*j)->id != (*i)->id)
					{
						udpSocket.send(sendPacket, clientIp, clientPort);
					}
					j++;
				}
			}
			if ((*i)->tcpSock->receive(receivePacket) == sf::Socket::Done)
			{
				int pType;
				receivePacket >> pType;


				if (pType == UPDATE_POSITION)
				{
					(*i)->timeOut = 0.0f;
					std::string pseudo;
					sf::Vector2f position;
					int direc, rect;
					receivePacket >> pseudo >> direc >> position.x >> position.y>> rect;
					std::string ip = (*i)->tcpSock->getRemoteAddress().toString();

					sf::Packet sendPacket;
					sendPacket << packetType::UPDATE_POSITION << (*i)->id << pseudo << direc << position.x << position.y << rect;

					auto j = listClients.begin();
					auto q = listClients.end();
					while (j != q)
					{
						if ((*j)->id != (*i)->id)
						{
							(*j)->tcpSock->send(sendPacket);
						}
						j++;
					}
				}
				else if (pType == THROW_BOMB)
				{
					(*i)->timeOut = 0.0f;
					std::string pseudo;
					sf::Vector2f position;
					int nbFlamme;
					receivePacket >> pseudo >> position.x >> position.y >> nbFlamme;
					std::string ip = (*i)->tcpSock->getRemoteAddress().toString();

					sf::Packet sendPacket;
					sendPacket << packetType::THROW_BOMB << (*i)->id << pseudo << position.x << position.y<< nbFlamme ;

					auto j = listClients.begin();
					auto q = listClients.end();
					while (j != q)
					{
						if ((*j)->id != (*i)->id)
						{
							(*j)->tcpSock->send(sendPacket);
						}
						j++;
					}
				}
				else if (pType == THROW_IMPULSIVE)
				{
					(*i)->timeOut = 0.0f;
					int id;
					sf::Vector2f position, dir;
					receivePacket >> id >> position.x >> position.y>>dir.x>>dir.y;
					std::string ip = (*i)->tcpSock->getRemoteAddress().toString();

					sf::Packet sendPacket;
					sendPacket << packetType::THROW_IMPULSIVE << (*i)->id  << position.x << position.y<<dir.x<<dir.y;

					auto j = listClients.begin();
					auto q = listClients.end();
					while (j != q)
					while (j != q)
					{
						if ((*j)->id != (*i)->id)
						{
							(*j)->tcpSock->send(sendPacket);
						}
						j++;
					}
				}
				else if (pType == CLOSE_RING)
				{
					(*i)->timeOut = 0.0f;
					std::string pseudo;
					int ring;
					receivePacket >> pseudo >> ring;
					std::string ip = (*i)->tcpSock->getRemoteAddress().toString();

					sf::Packet sendPacket;
					sendPacket << packetType::CLOSE_RING << pseudo << ring;

					auto j = listClients.begin();
					auto q = listClients.end();
					while (j != q)
					{
						if ((*j)->id != (*i)->id)
						{
							(*j)->tcpSock->send(sendPacket);
						}
						j++;
					}
				}
				else if (pType == SPD_BOOST)
				{
					(*i)->timeOut = 0.0f;
					int id;
					receivePacket >> id;

					sf::Packet sendPacket;
					sendPacket << packetType::SPD_BOOST << id;

					auto j = listClients.begin();
					auto q = listClients.end();
					while (j != q)
					{
						if (id == (*j)->id)
						{
							(*j)->tcpSock->send(sendPacket);
						}
						j++;
					}
				}
				else if (pType == HEALL)
				{
					(*i)->timeOut = 0.0f;
					int id;
					receivePacket >> id;

					sf::Packet sendPacket;
					sendPacket << packetType::HEALL<< id;

					auto j = listClients.begin();
					auto q = listClients.end();
					while (j != q)
					{
						if (id == (*j)->id)
						{
							(*j)->tcpSock->send(sendPacket);
						}
						j++;
					}
				}
				else if (pType == DEATH)
				{
					(*i)->timeOut = 0.0f;
					int id;
					std::string tueur, tuee;
					receivePacket >> id >> tueur >> tuee ;

					sf::Packet sendPacket;
					sendPacket << packetType::DEATH << id << tueur << tuee;
					auto j = listClients.begin();
					auto q = listClients.end();
					while (j != q)
					{
						if (id != (*j)->id)
						{
							(*j)->tcpSock->send(sendPacket);
						}
						j++;
					}
				}
				else if (pType == SENDCHEST)
				{
					(*i)->timeOut = 0.0f;
					int bonus, arme;
					sf::Vector2f pos;
					receivePacket >>pos.x >> pos.y>>bonus>>arme;
					listChest.push_back(new Map(_map.SpriteTileCoffre, pos, 1, bonus, arme));
				}
				else if (pType == SENDATOMIK)
				{
					(*i)->timeOut = 0.0f;
					sf::Vector2f pos;
					receivePacket >> pos.x >> pos.y;

					sf::Packet sendPacket;
					sendPacket << packetType::SENDATOMIK << pos.x << pos.y;
					auto j = listClients.begin();
					auto q = listClients.end();
					while (j != q)
					{
						if ((*i)->id != (*j)->id)
						{
							(*j)->tcpSock->send(sendPacket);
						}
						j++;
					}
				}
				else if (pType == START)
				{
					sf::Packet sendPacket;
					sendPacket << packetType::START;
					auto j = listClients.begin();
					auto q = listClients.end();
					while (j != q)
					{
						if ((*i)->id != (*j)->id)
						{
							(*j)->tcpSock->send(sendPacket);
						}
						j++;
					}
				}
				else if (pType == SENDBONUS)
				{
					sf::Packet sendPacket;
					sf::Vector2f pos;
					int typeB = 0;
					sendPacket << packetType::SENDBONUS << pos.x << pos.y << typeB;
					auto j = listClients.begin();
					auto q = listClients.end();
					while (j != q)
					{
						if ((*i)->id != (*j)->id)
						{
							(*j)->tcpSock->send(sendPacket);
						}
						j++;
					}
				}
				else if (pType == SENDARM)
				{
					sf::Vector2f pos;
					receivePacket >> pos.x >> pos.y;
					sendPacket << packetType::SENDARM << pos.x << pos.y ;
					auto j = listClients.begin();
					auto q = listClients.end();
					while (j != q)
					{
						if ((*i)->id != (*j)->id)
						{
							(*j)->tcpSock->send(sendPacket);
						}
						j++;
					}
				}
				else if (pType == INITPOS)
				{
					/*sf::Vector2f pos;
					int id = 0;
					receivePacket >> pos.x >> pos.y >> id;
					sendPacket << packetType::INITPOS << pos.x << pos.y;
					auto j = listClients.begin();
					auto q = listClients.end();
					while (j != q)
					{
						if (id == (*j)->id)
						{
							std::cout << "pos : " << pos.x << ", " << pos.y << " id : " << id << std::endl; 
							(*j)->tcpSock->send(sendPacket);
						}
						j++;
					}*/
					sf::Packet sendPacket;
					sf::Vector2f pos;
					int _id = 0;
					receivePacket >> pos.x >> pos.y >> _id;
					sendPacket << packetType::INITPOS << pos.x << pos.y;
					auto j = listClients.begin();
					auto q = listClients.end();
					while (j != q)
					{
						if (_id == (*j)->id&&pos.x!=0)
						{
							std::cout << (*j)->id << std::endl;
							std::cout << "Serveur : " << pos.x << ", " << pos.y << " id : " << _id << std::endl;
							(*j)->tcpSock->send(sendPacket);
						}
						j++;
					}
				}
				else if (pType == CLIENT_DISCONNECTED)
				{
					selector.remove(*(*i)->tcpSock);
					delete(*i);
					i = listClients.erase(i);
					nbClient--;
				}
			}
		}

		a++;
		i++;
	}
}

void Host::deconnect()
{
	auto i = listClients.begin();
	auto n = listClients.end();
	while (i != n)
	{
		if (tools::GetTimeDelta() < 0.05f)
			(*i)->timeOut += tools::GetTimeDelta();
		if ((*i)->timeOut > 1.0f)
		{
			std::cout << (*i)->pseudo << " is disconnected" << std::endl;

			sf::Packet sendPacket;
			sendPacket << packetType::CLIENT_DISCONNECTED << (*i)->id;
			auto j = listClients.begin();
			auto q = listClients.end();
			while (j != q)
			{
				(*j)->tcpSock->send(sendPacket);
				j++;
			}
			selector.remove(*(*i)->tcpSock);
			delete(*i);
			i = listClients.erase(i);
			nbClient--;

		}
		else
		{
			i++;
		}
	}
}
