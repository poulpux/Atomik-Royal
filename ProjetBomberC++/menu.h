#pragma once
#include "tools.h"
#include "myWindow.h"
#include "stateManager.h"
#include "game.h"
#include "Sons.h"
#include "MiniMap.h"
#include<thread>

class Client;
class Player;
enum class StateMenu {
	MENU,
	OPTION
};

class menu : public State
{
private:
	StateMenu stateMenu;

	sf::View viewMenu;

	sf::Texture menuTexture, curseurTexture, moinsTexture, plusTexture, tCursBombe, tExploMenu, tcmdManette, tcmdClavier, ttConnection, ttLoby;

	sf::Sprite menuSprite, curseurSprite, moinsSprite, plusSprite, sCursBombe, sExploMenu, scmdManette, scmdClavier, spConnection, spConnectionInv, spLobby, spLobbyInv;

	sf::Vector2f posCusreur, posMenu, posConnect, posJouerInv, posOption, posQuitter, posOSon, posOMusique, posOPE, posOCom, posORetour, posMoins, posPlus, posVolMu, posVolSon, posValMu, posValSon, posConnection, posValide, posPseudo, posIP, posPort, posLobby, posHote, posJoueur2, posJoueur3, posJoueur4, posJoueur5, posJoueur6, posJoueur7, posJoueur8;

	sf::Font menuGameFont;

	int choixMenu, choixOption, choixSon, choixMusique, volumeSon, volumeMusique, frameXbombeMenu, affClavier, affManette, iChoixConnect, iChoixConnectInv, iDepConnect, iLobby, iLobbyInv, iLancement, iChoixOptionState;

	float menuTimer, opaciteTimer;

	sf::Text tMenu, tConnecter, tJouerInv, tOption, tQuitter, tMenuOption, toSon, toMusique, toPleineEcran, toCommande, toRetour, tVolSon, tVolMus, tValSon, tValMus, txPseudo, txIP, txPort, txValide, txHote, txJoueur2, txJoueur3, txJoueur4, txJoueur5, txJoueur6, txJoueur7, txJoueur8;
	
	sf::String sMenu, sConnecter, sJouerInv, sOption, sQuitter, sMenuOption, soSon, soMusique, soPleineEcran, soCommande, soRetour, volSon, volMusic, valSon, valMusic, stPseudo, stIP, stPort, stValide, stHote, stJoueur2, stJoueur3, stJoueur4, stJoueur5, stJoueur6, stJoueur7, stJoueur8;

	sf::Uint8 opaciteMenu;

	sf::IntRect rectBombeMenu = { 0,0,16,16 };

	sf::IntRect rectExploMenu = { 0,0,64,64 };

	bool premierePass, bombeMoving;

	float timerBombeMenu;

	sf::Texture boiteDial;
	sf::Sprite boiteD;

public:
	SonMusique sonMusique;

	std::string boiteSt, TextePseudo, TexteIP, TextePort;
	sf::Text boiteT, boiteTN, TXpseudo,TXip, TXport, dialogue;
	sf::Font fontA;
	std::string pseudo;
	std::string s_ip;

	short int si_port;
	sf::IpAddress si_IP;

	menu() = default;
	menu(StateMenu _stateMenu/*, SonMusique* _son*/);
	void init(myWindow& _window, Player& _player, Client& clients) override;
	void update(myWindow& _window, Player& _player, Client& clients) override;
	void updateEvent(myWindow& _window) override;
	void draw(myWindow& _window, Player& _player, Client& clients) override;
	void destroy() override;

	sf::SoundBuffer SonMenuBuffer, SonLevelBuffer;

	sf::Sound SonMenu;

	sf::Music menuMusique;

	sf::TcpSocket socket;

	void exploCurs();

	void initDial() {
		fontA.loadFromFile("../Ressources/Fonts/Typewriter.ttf");
		boiteSt = pseudo;
		boiteT.setString("Name : ");
		boiteTN.setString(boiteSt);
		boiteT.setFont(fontA);
		boiteTN.setFont(fontA);
		//boiteT.setColor(sf::Color::Red);
		//boiteTN.setColor(sf::Color::Red);

		TXpseudo.setFont(fontA);
		TXip.setFont(fontA);
		TXport.setFont(fontA);
		//texteD.setCharacterSize(10);
		//dialogue.setFillColor(sf::Color::Red);

		boiteT.setPosition(posPseudo);
		boiteTN.setPosition(posIP);
		dialogue.setPosition(posPort);

	};

	void updateDial(myWindow& _window, std::string _message) {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
			sf::Packet sendPacket;
			sendPacket << pseudo << _message;
			socket.send(sendPacket);
			_message = "";
		}
	}

};