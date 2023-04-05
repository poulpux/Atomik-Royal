//#pragma once
//#include "tools.h"
//#include"SFML/Network.hpp"
//#include<list>
//
//enum packetType
//{
//	NEW_CONNECTION,
//	ON_CONNECTION_ADD_OTHER_PLAYER,
//	UPDATE_POSITION,
//	CLIENT_DISCONNECTED,
//	THROW_BOMB
//};
//typedef enum packetType packetType;
//
//struct ClientH
//{
//	sf::TcpSocket* tcpSock;
//	sf::UdpSocket* udpSock;
//	std::string pseudo;
//	int id;
//	sf::Vector2f pos;
//	int direct;
//	float timeOut;
//};
//
//
//class Serveur
//{
//protected:
//	unsigned short int port = 6666;
//	int nbClient;
//
//	sf::TcpListener listener;
//	sf::SocketSelector selector;
//	sf::Packet receivePacket;
//
//public:
//	void init();
//	void Update();
//	void connect();
//	void ReceiveMess();
//	void deconnect();
//
//
//	/*unsigned short int getPort() { return port; }
//	int getNbClient() { return nbClient; }*/
//	std::list<ClientH*>listClients;
//};