#pragma once
#include "tools.h"

class Map;
class Client;
class Player;
struct ClientH
{
	sf::TcpSocket* tcpSock;
	sf::UdpSocket* udpSock;
	std::string pseudo;
	int id;
	sf::Vector2f pos;
	int direct;
	float timeOut;
	bool chestSend;
};
//typedef struct Client Client;

class Host
{
protected:

	sf::UdpSocket udpSocket;
	sf::Packet receivePacket;
	sf::Packet sendPacket;
	sf::Vector2f receivePosition;
public:
	void init(Client& _client);
	void Update(Map& _map, Player& _player);
	void connect();
	void UDPPos();
	void TCPProtocol(Map& _map);
	void deconnect();

	sf::TcpListener listener;
	sf::SocketSelector selector;
	/*unsigned short int getPort() { return port; }
	int getNbClient() { return nbClient; }*/
	std::list<ClientH*>listClients;

	unsigned short int port = 6666;
	unsigned short int clientPort = 6666;
	int nbClient;
	sf::IpAddress ip = "127.0.0.1";
	sf::IpAddress clientIp = "127.0.0.1";
	std::list<Map*>listChest;
};