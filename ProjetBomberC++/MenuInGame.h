#pragma once
#include "tools.h"
#include "Sons.h"
#include "stateManager.h"

class game;
class Camera;
class menu;
class MenuInGame
{
	sf::Text tMenu, tMenuOption, toSon, toMusique, toPleineEcran, toCommande, tVolSon, tVolMus, tValSon, tValMus;

	sf::String sMenu, sOption, soSon, soMusique, soPleineEcran, soCommande, volSon, volMusic, valSon, valMusic;
	
	sf::Vector2f posCusreur, posMenu, posOSon, posOMusique, posOPE, posOCom, posVolMu, posVolSon, posValMu, posValSon;

	sf::Font menuGameFont;

	sf::Texture tCurseur, tcmdManette, tcmdClavier;

	sf::Sprite sCurseur, scmdManette, scmdClavier;

	float timeMenuOption = 0.0f, opaciteTimerG = 0.0f;

	int option = 0, choixSon = 0, choixMusique = 0, choixOptionG = 0, affClavier = 0, affManette = 0;


	sf::SoundBuffer SonMenuBuffer;

	sf::Sound SonMenu;

	sf::Uint8 opaciteMenuG;

	sf::RectangleShape rOption, rSon, rMusic, rPE, rCommande;

public:

	sf::Music menuMusique;
	int GetOption() { return option; }
	SonMusique sonMusiqueG;

	void initMenuGame(myWindow& _window, Camera* _cam, menu* _menu);
	void updateMG(myWindow& _window, Camera& _cam, menu* _menu);
	void displayMenuGame(myWindow& _window);

};
