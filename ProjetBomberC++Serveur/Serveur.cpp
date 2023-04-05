//#include "Serveur.h"
//
//void Serveur::init()
//{
//	if (listener.listen(port) == sf::Socket::Done)
//	{
//		selector.add(listener);
//		std::cout << "Serveur en ligne" << std::endl;
//	}
//	else
//	{
//		exit(0);
//	}
//}
//
//void Serveur::Update()
//{
//	//Si nouvelle connection
//	if (selector.wait())
//	{
//		tools::restartClock();
//		if (selector.isReady(listener))
//		{
//			connect();
//		}
//		else
//		{
//			ReceiveMess();
//		}
//		deconnect();
//	}
//}
//
//void Serveur::connect()
//{
//	sf::Packet receivePacket;
//	std::string pseudo;
//
//	Client* client = new Client();
//	client->tcpSock = new sf::TcpSocket();
//	client->udpSock = new sf::UdpSocket();
//	listener.accept(*client->tcpSock);
//	selector.add(*client->tcpSock);
//	client->id = nbClient;
//
//	if (client->tcpSock->receive(receivePacket) == sf::Socket::Done)
//	{
//		receivePacket >> pseudo;
//	}
//	std::cout << pseudo << " : " << client->id << std::endl;
//	client->pseudo = pseudo;
//	listClients.push_back(client);
//	nbClient++;
//
//	auto i = listClients.begin();
//	auto n = listClients.end();
//	while (i!=n)
//	{
//		//Envoie que t'existe aux autres 
//		if ((*i)->id != client->id)
//		{
//			sf::Packet sendPacket;
//			sendPacket << packetType::NEW_CONNECTION << pseudo << client->id;
//			(*i)->tcpSock->send(sendPacket);
//		}
//		else //Repere les autres
//		{
//			auto j = listClients.begin();
//			auto q = listClients.end();
//			while (j != q)
//			{
//
//				sf::Packet sendPacket;
//				sendPacket << packetType::ON_CONNECTION_ADD_OTHER_PLAYER << (*j)->pseudo << (*j)->id << (*j)->pos.x << (*j)->pos.y;
//				if ((*j)->id != client->id)
//				{
//					(*i)->tcpSock->send(sendPacket);
//				}
//				j++;
//			}
//		}
//		i++;
//	}
//}
//
//void Serveur::ReceiveMess()
//{
//	int a = 0;
//	sf::Packet receivePacket;
//	auto i = listClients.begin();
//	auto n = listClients.end();
//	while (i!=n)
//	{
//		if (selector.isReady(*(*i)->tcpSock))
//		{
//			if ((*i)->tcpSock->receive(receivePacket) == sf::Socket::Done)
//			{
//				int pType;
//				receivePacket >> pType;
//				if (pType == UPDATE_POSITION)
//				{
//					(*i)->timeOut = 0.0f;
//					std::string pseudo;
//					sf::Vector2f position;
//					int direc;
//					receivePacket >> pseudo >> direc >>position.x >> position.y;
//					std::string ip = (*i)->tcpSock->getRemoteAddress().toString();
//
//					//cout << "Recu du client " << pseudo << " ip: " << ip << " x: " << position.x << " y: " << position.y << endl;
//
//					sf::Packet sendPacket;
//					sendPacket << packetType::UPDATE_POSITION << (*i)->id << pseudo << direc<<position.x << position.y;
//
//					auto j = listClients.begin();
//					auto q = listClients.end();
//					while (j != q)
//					{
//						if ((*j)->id != (*i)->id)
//						{
//							(*j)->tcpSock->send(sendPacket);
//						}
//						j++;
//					}
//				}
//				else if (pType == THROW_BOMB)
//				{
//					(*i)->timeOut = 0.0f;
//					std::string pseudo;
//					sf::Vector2f position;
//					receivePacket >> pseudo >> position.x >> position.y;
//					std::string ip = (*i)->tcpSock->getRemoteAddress().toString();
//
//					//cout << "Recu du client " << pseudo << " ip: " << ip << " x: " << position.x << " y: " << position.y << endl;
//
//					sf::Packet sendPacket;
//					sendPacket << packetType::THROW_BOMB << (*i)->id << pseudo << position.x << position.y;
//
//					auto j = listClients.begin();
//					auto q = listClients.end();
//					while (j != q)
//					{
//						if ((*j)->id != (*i)->id)
//						{
//							(*j)->tcpSock->send(sendPacket);
//						}
//						j++;
//					}
//				}
//			}
//		}
//
//		a++;
//		i++;
//	}
//}
//
//void Serveur::deconnect()
//{
//	auto i = listClients.begin();
//	auto n = listClients.end();
//	while(i!=n)
//	{
//		if (tools::GetTimeDelta() < 1.0f)
//			(*i)->timeOut += tools::GetTimeDelta();
//		if ((*i)->timeOut > 1.0f)
//		{
//			std::cout << (*i)->pseudo << " is disconnected" << std::endl;
//
//			sf::Packet sendPacket;
//			sendPacket << packetType::CLIENT_DISCONNECTED << (*i)->id;
//			auto j = listClients.begin();
//			auto q = listClients.end();
//			while (j != q)
//			{
//				(*j)->tcpSock->send(sendPacket);
//				j++;
//			}
//			selector.remove(*(*i)->tcpSock);
//			delete(*i);
//			i = listClients.erase(i);
//
//		}
//		else
//		{
//			i++;
//		}
//	}
//}
