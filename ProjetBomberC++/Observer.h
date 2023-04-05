//#pragma once
//#include "zone.h"
//
//class Observer
//{
//};
//
//class ClientAbstrait
//{
//public:
//	ClientAbstrait();
//	virtual ~ClientAbstrait();
//	virtual void update() = 0;
//};
//
//class HostAbstrait
//{
//protected:
//	std::vector<ClientAbstrait*>  clients;
//public:
//	HostAbstrait();
//	virtual ~HostAbstrait();
//	void attacher(ClientAbstrait* o);
//	void detacher(ClientAbstrait* o);
//	void avertir();
//};
//
//
//class HostNotif : public HostAbstrait // Sujet concret
//{
//protected:
//	sf::Text NotifZoneDetruite;
//	unsigned int numZone;
//	float tempsRestant;
//public:
//	HostNotif();
//	virtual ~HostNotif();
//	unsigned int getNumZone();
//	float getTpsRestant();
//	void postTpsRestant();
//	void postZone();
//};
//
//
//class ClientNotif : public ClientAbstrait // Observeur concret
//{
//protected:
//	HostNotif* notifDestruct;
//	sf::Text NotifZoneDetruite;
//	unsigned int numZone;
//	unsigned int tempsRestant;
//	std::string nom;
//public:
//	ClientNotif(HostNotif* s, std::string n);
//	virtual ~ClientNotif();
//	virtual void update();
//};
//
//
//// Implémentation
//HostAbstrait::HostAbstrait() :clients() {}
//HostAbstrait::~HostAbstrait() {}
//void HostAbstrait::attacher(ClientAbstrait* o) {
//	clients.push_back(o);
//}
//void HostAbstrait::detacher(ClientAbstrait* o) {
//	std::vector<ClientAbstrait*> ::iterator it;
//	for (it = clients.begin(); it != clients.end() && *it != o; it++) {}
//	if (it != clients.end()) {
//		clients.erase(it);
//	}
//}
//void HostAbstrait::avertir() {
//	std::vector<ClientAbstrait*> ::iterator it;
//	for (it = clients.begin(); it != clients.end(); it++) {
//		(*it)->update();
//	}
//}
//ClientAbstrait::ClientAbstrait() {}
//ClientAbstrait::~ClientAbstrait() {}
//HostNotif::HostNotif() {
//	tempsRestant = 0;
//	numZone = 0;
//}
//HostNotif::~HostNotif() {}
//float HostNotif::getTpsRestant() {
//	return numZone;
//}
//unsigned int HostNotif::getNumZone() {
//	return tempsRestant;
//}
//void HostNotif::postZone() {
//	++numZone;
//	//avertir();
//}
//void HostNotif::postTpsRestant() {
//	++tempsRestant;
//	//avertir();
//}
//ClientNotif::ClientNotif(HostNotif* s, std::string n) :notifDestruct(s), nom(n) {
//	numZone = notifDestruct->getTpsRestant();
//	tempsRestant = notifDestruct->getNumZone();
//}
//ClientNotif::~ClientNotif() {}
//void ClientNotif::update()
//{
//	unsigned int nbpi = notifDestruct->getTpsRestant();
//	unsigned int nbpr = notifDestruct->getNumZone();
//	if (nbpi != numZone) {
//		std::cout << nom << " prevenu\n";
//		std::cout << " Temps restant avant destruction de la zone : "<< nbpr << " : " << nbpi << " seconde" << std::endl;
//	}
//	std::cout << std::endl;
//	numZone = nbpi;
//	tempsRestant = nbpr;
//}

