#include "MenuInGame.h"
#include "game.h"
#include "Camera.h"
#include "menu.h"
#include "Sons.h"
#include "menu.h"

void MenuInGame::initMenuGame(myWindow& _window, Camera* _cam, menu* _menu) {
	sMenu = "Menu Option";
	sOption = "Option";
	soSon = "Son Volume";
	soMusique = "Musique Volume";
	soPleineEcran = "Pleine Ecran";
	soCommande = "Commande";
	volSon = "Volume du son :";
	volMusic = "Volume de la musique :";

	menuGameFont.loadFromFile("../Ressources/Fonts/Typewriter.ttf");
	tCurseur.loadFromFile("../Ressources/Textures/Curseur.png");
	tMenu.setFont(menuGameFont);
	tMenu.setString(sMenu);
	tMenu.setFillColor(sf::Color::Black);

	tcmdManette.loadFromFile("../Ressources/Textures/manette.png");
	scmdManette.setTexture(tcmdManette);
	scmdManette.setScale(sf::Vector2f(1.0f, 1.0f));
	scmdManette.setColor(sf::Color(255.0f, 255.0f, 255.0f, 225.0f));
	scmdManette.setPosition(posMenu.x - 200, posMenu.y + 150);

	tcmdClavier.loadFromFile("../Ressources/Textures/Clavier.png");
	scmdClavier.setTexture(tcmdClavier);
	scmdClavier.setScale(sf::Vector2f(1.0f, 1.0f));
	scmdClavier.setColor(sf::Color(255.0f, 255.0f, 255.0f, 225.0f));
	scmdClavier.setPosition(posMenu.x - 200, posMenu.y + 150);

	tMenuOption.setFont(menuGameFont);
	tMenuOption.setString(sMenu);
	tMenuOption.setFillColor(sf::Color::Black);

	toSon.setFont(menuGameFont);
	toSon.setString(soSon);
	toSon.setFillColor(sf::Color::Black);

	toMusique.setFont(menuGameFont);
	toMusique.setString(soMusique);
	toMusique.setFillColor(sf::Color::Black);

	toPleineEcran.setFont(menuGameFont);
	toPleineEcran.setString(soPleineEcran);
	toPleineEcran.setFillColor(sf::Color::Black);

	toCommande.setFont(menuGameFont);
	toCommande.setString(soCommande);
	toCommande.setFillColor(sf::Color::Black);

	sCurseur.setTexture(tCurseur);

	SonMenuBuffer.loadFromFile("..\\Ressources\\Sons\\Whoosh3.wav");
	SonMenu.setBuffer(SonMenuBuffer);
	SonMenu.setPlayingOffset(sf::seconds(1.0f));

	menuMusique.openFromFile("..\\Ressources\\Sons\\MainMario35.ogg"); 
	menuMusique.setLoop(true);

	tVolMus.setFont(menuGameFont);
	tVolMus.setString(volMusic);
	tVolMus.setFillColor(sf::Color::Black);
	tVolMus.setPosition(posVolMu);

	tVolSon.setFont(menuGameFont);
	tVolSon.setString(volSon);
	tVolSon.setFillColor(sf::Color::Black);
	tVolSon.setPosition(posVolSon);

	rOption.setFillColor(sf::Color::White);
	rOption.setFillColor(sf::Color(255.0f, 255.0f, 255.0f, 100.0f));
	rOption.setSize(sf::Vector2f(200, 50));

	rSon.setFillColor(sf::Color::White);
	rSon.setFillColor(sf::Color(255.0f, 255.0f, 255.0f, 100.0f));
	rSon.setSize(sf::Vector2f(250, 50));

	rMusic.setFillColor(sf::Color::White);
	rMusic.setFillColor(sf::Color(255.0f, 255.0f, 255.0f, 100.0f));
	rMusic.setSize(sf::Vector2f(300, 50));

	rPE.setFillColor(sf::Color::White);
	rPE.setFillColor(sf::Color(255.0f, 255.0f, 255.0f, 100.0f));
	rPE.setSize(sf::Vector2f(220, 50));

	rCommande.setFillColor(sf::Color::White);
	rCommande.setFillColor(sf::Color(255.0f, 255.0f, 255.0f, 100.0f));
	rCommande.setSize(sf::Vector2f(200, 50));

	_menu->sonMusique.SetVolume(menuMusique);
	_menu->sonMusique.SetSon(SonMenu);
	menuMusique.play();
}

void MenuInGame::updateMG(myWindow& _window, Camera& _cam, menu* _menu) {

	valMusic = std::to_string((int)sonMusiqueG.GetVolumeMusique());
	valSon = std::to_string((int)sonMusiqueG.GetVolumeSon());

	tValMus.setFont(menuGameFont);
	tValMus.setString(valMusic);
	tValMus.setFillColor(sf::Color::Black);
	tValMus.setPosition(posValMu);

	tValSon.setFont(menuGameFont);
	tValSon.setString(valSon);
	tValSon.setFillColor(sf::Color::Black);
	tValSon.setPosition(posValSon);

	_menu->sonMusique.SetVolume(menuMusique);
	_menu->sonMusique.SetSon(SonMenu);


	opaciteTimerG += tools::GetTimeDelta();
	if (opaciteMenuG < 255.0f && opaciteTimerG > 0.01f)
	{
		opaciteMenuG++;
		opaciteTimerG = 0.0f;
	}
	timeMenuOption += tools::GetTimeDelta();
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) && timeMenuOption > 0.3f && GetOption() == 0) {
		option = 1;
		timeMenuOption = 0.0f;
	}
	if (GetOption() == 1) {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) && timeMenuOption > 0.3f) {
			option = 0;
			timeMenuOption = 0.0f;
		}
		posMenu = sf::Vector2f(_cam.getPosViewgame().x, _cam.getPosViewgame().y - 450);
		posOMusique = sf::Vector2f(_cam.getPosViewgame().x - 200, _cam.getPosViewgame().y - 250);
		posVolMu = sf::Vector2f(_cam.getPosViewgame().x - 200, _cam.getPosViewgame().y - 250);
		posValMu = sf::Vector2f(posVolMu.x + 270, posVolMu.y);
		posOSon = sf::Vector2f(_cam.getPosViewgame().x - 200, _cam.getPosViewgame().y - 150);
		posVolSon = sf::Vector2f(_cam.getPosViewgame().x - 200, _cam.getPosViewgame().y - 150);
		posValSon = sf::Vector2f(posVolSon.x + 200, posVolSon.y);
		posOPE = sf::Vector2f(_cam.getPosViewgame().x - 200, _cam.getPosViewgame().y - 50);
		posOCom = sf::Vector2f(_cam.getPosViewgame().x - 200, _cam.getPosViewgame().y + 50);
		scmdManette.setPosition(posMenu.x - 400, posMenu.y + 150);
		scmdClavier.setPosition(posMenu.x - 500, posMenu.y + 150);

		if (choixSon == 0 && choixMusique == 0) {
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && choixOptionG > 0 && timeMenuOption > 0.3f) {
				SonMenu.play();
				choixOptionG -= 1;
				timeMenuOption = 0.0f;
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && choixOptionG < 3 && timeMenuOption > 0.3f) {
				SonMenu.play();
				choixOptionG += 1;
				timeMenuOption = 0.0f;
			}
			switch (choixOptionG)
			{
			case 0:
				posCusreur = sf::Vector2f(posOMusique.x - 50, posOMusique.y + 10);
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && sonMusiqueG.GetVolumeMusique() > 0 && timeMenuOption > 0.3f) {
					sonMusiqueG.AddVolumeMusique(-5);
					timeMenuOption = 0.0f;
				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && sonMusiqueG.GetVolumeMusique() < 100 && timeMenuOption > 0.3f) {
					sonMusiqueG.AddVolumeMusique(5);
					timeMenuOption = 0.0f;
				}
				break;
			case 1:
				posCusreur = sf::Vector2f(posOSon.x - 50, posOSon.y + 10);
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && sonMusiqueG.GetVolumeSon() > 0 && timeMenuOption > 0.3f) {
					sonMusiqueG.AddVolumeSon(-5);
					timeMenuOption = 0.0f;
				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && sonMusiqueG.GetVolumeSon() < 100 && timeMenuOption > 0.3f) {
					sonMusiqueG.AddVolumeSon(5);
					timeMenuOption = 0.0f;
				}
				break;
			case 2:
				posCusreur = sf::Vector2f(posOPE.x - 50, posOPE.y + 10);
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && timeMenuOption > 0.3f) {
					_window.ToggleFullscreen();
					timeMenuOption = 0.0f;
				}
				break;
			case 3:
				posCusreur = sf::Vector2f(posOCom.x - 50, posOCom.y + 10);
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
					affClavier = 1;
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
					affManette = 1;
				else {
					affClavier = 0;
					affManette = 0;
				}

				break;
			default:
				break;
			}
		}


		rOption.setPosition(posMenu);
		rOption.setScale(0.8, 0.8);
		rSon.setPosition(posOSon);
		rSon.setScale(0.8, 0.8);
		rMusic.setPosition(posOMusique);
		rMusic.setScale(0.8, 0.8);
		rPE.setPosition(posOPE);
		rPE.setScale(0.8, 0.8);
		rCommande.setPosition(posOCom);
		rCommande.setScale(0.8, 0.8);
		sCurseur.setPosition(posCusreur);
		sCurseur.setScale(-0.8, 0.8);

		tMenuOption.setPosition(posMenu);
		tMenuOption.setScale(0.8, 0.8);
		toSon.setPosition(posOSon);
		toSon.setScale(0.8, 0.8);
		toMusique.setPosition(posOMusique);
		toMusique.setScale(0.8, 0.8);
		toPleineEcran.setPosition(posOPE);
		toPleineEcran.setScale(0.8, 0.8);
		toCommande.setPosition(posOCom);
		toCommande.setScale(0.8, 0.8);
	}
}

void MenuInGame::displayMenuGame(myWindow& _window) {
	if (GetOption() == 1) {
		sCurseur.setPosition(posCusreur);

		_window.Draw(rOption);
		_window.Draw(rSon);
		_window.Draw(rMusic);
		_window.Draw(rPE);
		_window.Draw(rCommande);
		_window.Draw(tMenuOption);
		_window.Draw(toSon);
		_window.Draw(toMusique);
		_window.Draw(toPleineEcran);
		_window.Draw(toCommande);
		_window.Draw(tValMus);
		_window.Draw(tValSon);
		_window.Draw(sCurseur);

		if (affManette == 1)
			_window.Draw(scmdManette);
		if (affClavier == 1)
			_window.Draw(scmdClavier);

	}
}
