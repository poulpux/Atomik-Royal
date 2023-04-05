#pragma once
#include"tools.h"
#include<list>
class Player;
class Camera;
class Client;
#define RingDmgCalcul ((int)(1 + (8 - nbZoneOp) * 0.6))

enum posCarte { A1, A2, A3, B1, B2, B3, C1, C2, C3, RANDOM };
struct RingGestion
{
	posCarte pos;
	bool close;
	sf::Vector2f position;

};
class Zone
{
protected:
	float dmgTimer;
	float delayTkDmg;
	float tpsForAnnonce;
	float tpsForClos;
	bool Annonce;
	int nbZoneOp;
	bool inZone = false;
	sf::RectangleShape MaskZone;
	std::string tNomZone;

	RingGestion* saveDecompt;
	sf::RectangleShape recZone;
public:
	int saveRand;
	bool foireux;
	posCarte nomNotif;
	Zone();
	void init();
	void Update(Player& _player, Client& _client, Camera& cam);
	void ringManagment(Client& _client, Player& _player);
	void ringClose(posCarte _pos);
	void playerTakeDmg(Player& _player);
	void draw(myWindow& _window, Player* _p);

	float timer;
	std::list<RingGestion*>rings;

	sf::Text tNotif;
	sf::Font fNotif;
	std::string sDebutNotif, sTpsRestant, sTimerTps;
	sf::RectangleShape rNotif;
	sf::Vector2f posNotif;

	float tpsRestantTimer = 0.0f;
	void InitNotif() {
		fNotif.loadFromFile("../Ressources/Fonts/Typewriter.ttf");
		tNotif.setFont(fNotif);
		tNotif.setFillColor(sf::Color::Black);
		sDebutNotif = { "Destruction de la zone : " };
		sTpsRestant = { " Temps restant : " };

		rNotif.setFillColor(sf::Color::White);
		rNotif.setFillColor(sf::Color(255.0f, 255.0f, 255.0f, 100.0f));
		rNotif.setSize(sf::Vector2f(850, 50));

	}
	RingGestion A1G, A2G, A3G, B1G, B2G, B3G, C1G, C2G, C3G;
	std::string GetNomZone() { return tNomZone; }
	void getZone(posCarte _ring) {
		switch (_ring)
		{
		case A1:
			tNomZone = (" Zone A1 ");
			break;
		case A2:
			tNomZone = (" Zone B1 ");
			break;
		case A3:
			tNomZone = (" Zone C1 ");
			break;
		case B1:
			tNomZone = (" Zone A2 ");
			break;
		case B2:
			tNomZone = (" Zone B2 ");
			break;
		case B3:
			tNomZone = (" Zone C2 ");
			break;
		case C1:
			tNomZone = (" Zone A3 ");
			break;
		case C2:
			tNomZone = (" Zone B3 ");
			break;
		case C3:
			tNomZone = (" Zone C3 ");
			break;
		case RANDOM:
			break;
		default:
			break;
		}
	}
};


//
//                $$$$$$$
//            $$$$$$$$$$$$$$
//         $$$$$$$$$$$$$$$$$$
//        $$$$$$$$$$$$$$$$$$$$
//       $$$$$$$$$$$$$$$? $$$$    $$$$$$
//       $$$$$$$ ?$$$$$$$$$$$$   $$$  $$$
//       $$$$$$$$$$$$$$v$$$$$  $$$$    $$
//        $$$$$$$$$$$$$$$$$$$$$$$$
//         $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
// $$$$$$     $$$$$$$$$$$$$$$$$$        $$
//$$   $$$$$$$$$$$$$$$$$$$$$$$         $$
// $$$    $$$$$$$$$$$$$$$$$$$$$$$$$$$$
//     $$$$$$$$  $$$ $$$$$$          $$
//   $$$$       $$$  $$$ $$$      $$$$
//  $$$       $$$$   $$$  $$$
//   $$$$$   $$$     $$$   $$$$    $$
//    $$$    $$$$$$  $$$    $$$$$$$$
//            $$$     $$$$$   $$$$



