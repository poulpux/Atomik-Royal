#include "menu.h"
#include"Player.h"
#include "Client.h"

menu::menu(StateMenu _stateMenu/*, SonMusique* _son*/) {
	//sonMusique = _son;
	stateMenu = _stateMenu;
	choixMenu = 0;
	choixOption = 0;
}

void menu::init(myWindow& _window, Player& _player, Client& clients) {
	initDial();
	viewMenu.setViewport(sf::FloatRect(0.0f, 0.0f, 1.0f, 1.0f));
	viewMenu.setSize(1920, 1080);

	sMenu = "Menu";
	sConnecter = "Rejoindre en tant qu'hote";
	sJouerInv = "Jouer en Invite";
	sOption = "Option";
	sQuitter = "Quitter";
	sMenuOption = "Menu Option";
	soSon = "Son Volume";
	soMusique = "Musique Volume";
	soPleineEcran = "Pleine Ecran";
	soCommande = "Commande";
	soRetour = "Retour";
	volSon = "Volume du son :";
	volMusic = "Volume de la musique :";

	stPseudo = "Pseudo";
	stIP = "IP";
	stPort = "Port";

	stHote = ("Hote");
	stJoueur2 = ("Joueur 2");
	stJoueur3 = ("Joueur 3");
	stJoueur4 = ("Joueur 4");
	stJoueur5 = ("Joueur 5");
	stJoueur6 = ("Joueur 6");
	stJoueur7 = ("Joueur 7");
	stJoueur8 = ("Joueur 8");

	posVolMu = sf::Vector2f(_window.GetWindowSize().x * 0.4, _window.GetWindowSize().y * 0.2);
	posValMu = sf::Vector2f(posVolMu.x + 400, posVolMu.y);
	posVolSon = sf::Vector2f(_window.GetWindowSize().x * 0.4, _window.GetWindowSize().y * 0.2);
	posValSon = sf::Vector2f(posVolSon.x + 300, posVolSon.y);;

	posMenu = sf::Vector2f(_window.GetWindowSize().x * 0.45, _window.GetWindowSize().y * 0.05);
	posConnect = sf::Vector2f(_window.GetWindowSize().x * 0.2, _window.GetWindowSize().y * 0.2);
	posJouerInv = sf::Vector2f(_window.GetWindowSize().x * 0.2, _window.GetWindowSize().y * 0.3);
	posOption = sf::Vector2f(_window.GetWindowSize().x * 0.2, _window.GetWindowSize().y * 0.4);
	posQuitter = sf::Vector2f(_window.GetWindowSize().x * 0.2, _window.GetWindowSize().y * 0.5);

	posOSon = sf::Vector2f(_window.GetWindowSize().x * 0.2, _window.GetWindowSize().y * 0.2);
	posOMusique = sf::Vector2f(_window.GetWindowSize().x * 0.2, _window.GetWindowSize().y * 0.3);
	posOPE = sf::Vector2f(_window.GetWindowSize().x * 0.2, _window.GetWindowSize().y * 0.4);
	posOCom = sf::Vector2f(_window.GetWindowSize().x * 0.2, _window.GetWindowSize().y * 0.5);
	posORetour = sf::Vector2f(_window.GetWindowSize().x * 0.2, _window.GetWindowSize().y * 0.6);

	posMoins = sf::Vector2f(_window.GetWindowSize().x * 0.45, _window.GetWindowSize().y * 0.3);
	posPlus = sf::Vector2f(_window.GetWindowSize().x * 0.50, _window.GetWindowSize().y * 0.3);

	posPseudo = sf::Vector2f(_window.GetWindowSize().x * 0.47, _window.GetWindowSize().y * 0.29);
	posIP = sf::Vector2f(_window.GetWindowSize().x * 0.47, _window.GetWindowSize().y * 0.43);
	posPort = sf::Vector2f(_window.GetWindowSize().x * 0.47, _window.GetWindowSize().y * 0.56);

	posHote = sf::Vector2f(_window.GetWindowSize().x * 0.55, _window.GetWindowSize().y * 0.20);
	posJoueur2 = sf::Vector2f(_window.GetWindowSize().x * 0.47, _window.GetWindowSize().y * 0.29);
	posJoueur3 = sf::Vector2f(_window.GetWindowSize().x * 0.47, _window.GetWindowSize().y * 0.343);
	posJoueur4 = sf::Vector2f(_window.GetWindowSize().x * 0.47, _window.GetWindowSize().y * 0.395);
	posJoueur5 = sf::Vector2f(_window.GetWindowSize().x * 0.47, _window.GetWindowSize().y * 0.45);
	posJoueur6 = sf::Vector2f(_window.GetWindowSize().x * 0.47, _window.GetWindowSize().y * 0.505);
	posJoueur7 = sf::Vector2f(_window.GetWindowSize().x * 0.47, _window.GetWindowSize().y * 0.56);
	posJoueur8 = sf::Vector2f(_window.GetWindowSize().x * 0.47, _window.GetWindowSize().y * 0.61);

	posConnection = sf::Vector2f(posMenu.x, posMenu.y + 150);

	menuGameFont.loadFromFile("../Ressources/Fonts/Typewriter.ttf");
	curseurTexture.loadFromFile("../Ressources/Textures/Curseur.png");

	moinsTexture.loadFromFile("../Ressources/Textures/Moins.png");
	moinsSprite.setTexture(moinsTexture);
	moinsSprite.setPosition(posMoins);
	plusTexture.loadFromFile("../Ressources/Textures/Plus.png");
	plusSprite.setTexture(plusTexture);
	plusSprite.setPosition(posPlus);

	tCursBombe.loadFromFile("../Ressources/Textures/bomb1.png");
	sCursBombe.setTexture(tCursBombe);
	sCursBombe.setTextureRect(rectBombeMenu);
	sCursBombe.setOrigin(16.0f / 2.0f, 16.0f / 2.0f);
	sCursBombe.setScale(sf::Vector2f(2.0f, 2.0f));

	tExploMenu.loadFromFile("../Ressources/Textures/explosion.png");
	sExploMenu.setTexture(tExploMenu);
	sExploMenu.setOrigin(64.0f / 2.0f, 64.0f / 2.0f);
	sExploMenu.setScale(sf::Vector2f(2.0f, 2.0f));

	tcmdManette.loadFromFile("../Ressources/Textures/manette.png");
	scmdManette.setTexture(tcmdManette);
	scmdManette.setScale(sf::Vector2f(1.0f, 1.0f));
	scmdManette.setPosition(posMenu.x, posMenu.y + 150);

	tcmdClavier.loadFromFile("../Ressources/Textures/Clavier.png");
	scmdClavier.setTexture(tcmdClavier);
	scmdClavier.setScale(sf::Vector2f(1.0f, 1.0f));
	scmdClavier.setPosition(posMenu.x, posMenu.y + 150);

	ttConnection.loadFromFile("../Ressources/Textures/Connection.png");
	spConnection.setTexture(ttConnection);
	spConnection.setScale(sf::Vector2f(1.0f, 1.0f));
	spConnection.setPosition(posConnection);
	spConnectionInv.setTexture(ttConnection);
	spConnectionInv.setScale(sf::Vector2f(1.0f, 1.0f));
	spConnectionInv.setPosition(posConnection);

	ttLoby.loadFromFile("../Ressources/Textures/Lobby.png");
	spLobby.setTexture(ttLoby);
	spLobby.setScale(sf::Vector2f(1.0f, 1.0f));
	spLobby.setPosition(posConnection);
	spLobbyInv.setTexture(ttLoby);
	spLobbyInv.setScale(sf::Vector2f(1.0f, 1.0f));
	spLobbyInv.setPosition(posConnection);

	tMenu.setFont(menuGameFont);
	tMenu.setString(sMenu);
	tMenu.setFillColor(sf::Color::Black);
	tMenu.setPosition(posMenu);

	tConnecter.setFont(menuGameFont);
	tConnecter.setString(sConnecter);
	tConnecter.setFillColor(sf::Color::Black);
	tConnecter.setPosition(posConnect);

	tJouerInv.setFont(menuGameFont);
	tJouerInv.setString(sJouerInv);
	tJouerInv.setFillColor(sf::Color::Black);
	tJouerInv.setPosition(posJouerInv);

	tOption.setFont(menuGameFont);
	tOption.setString(sOption);
	tOption.setFillColor(sf::Color::Black);
	tOption.setPosition(posOption);

	tQuitter.setFont(menuGameFont);
	tQuitter.setString(sQuitter);
	tQuitter.setFillColor(sf::Color::Black);
	tQuitter.setPosition(posQuitter);

	tMenuOption.setFont(menuGameFont);
	tMenuOption.setString(sMenuOption);
	tMenuOption.setFillColor(sf::Color::Black);
	tMenuOption.setPosition(posMenu);

	toSon.setFont(menuGameFont);
	toSon.setString(soSon);
	toSon.setFillColor(sf::Color::Black);
	toSon.setPosition(posOSon);

	toMusique.setFont(menuGameFont);
	toMusique.setString(soMusique);
	toMusique.setFillColor(sf::Color::Black);
	toMusique.setPosition(posOMusique);

	toPleineEcran.setFont(menuGameFont);
	toPleineEcran.setString(soPleineEcran);
	toPleineEcran.setFillColor(sf::Color::Black);
	toPleineEcran.setPosition(posOPE);

	toCommande.setFont(menuGameFont);
	toCommande.setString(soCommande);
	toCommande.setFillColor(sf::Color::Black);
	toCommande.setPosition(posOCom);

	toRetour.setFont(menuGameFont);
	toRetour.setString(soRetour);
	toRetour.setFillColor(sf::Color::Black);
	toRetour.setPosition(posORetour);

	curseurSprite.setTexture(curseurTexture);
	curseurSprite.setScale(-1, 1);

	SonMenuBuffer.loadFromFile("..\\Ressources\\Sons\\Whoosh3.wav");
	SonMenu.setBuffer(SonMenuBuffer);
	SonMenu.setPlayingOffset(sf::seconds(1.0f));

	menuMusique.openFromFile("..\\Ressources\\Sons\\Menu.ogg");
	menuMusique.setLoop(true);

	tVolMus.setFont(menuGameFont);
	tVolMus.setString(volMusic);
	tVolMus.setFillColor(sf::Color::Black);
	tVolMus.setPosition(posVolMu);

	tVolSon.setFont(menuGameFont);
	tVolSon.setString(volSon);
	tVolSon.setFillColor(sf::Color::Black);
	tVolSon.setPosition(posVolSon);

	txPseudo.setFont(menuGameFont);
	txPseudo.setString(stPseudo);
	txPseudo.setFillColor(sf::Color::Black);
	txPseudo.setPosition(posPseudo);

	txIP.setFont(menuGameFont);
	txIP.setString(stIP);
	txIP.setFillColor(sf::Color::Black);
	txIP.setPosition(posIP);

	txPort.setFont(menuGameFont);
	txPort.setString(stPort);
	txPort.setFillColor(sf::Color::Black);
	txPort.setPosition(posPort);

	txHote.setFont(menuGameFont);
	txHote.setFillColor(sf::Color::Black);
	txJoueur2.setFont(menuGameFont);
	txJoueur2.setFillColor(sf::Color::Black);
	txJoueur3.setFont(menuGameFont);
	txJoueur3.setFillColor(sf::Color::Black);
	txJoueur4.setFont(menuGameFont);
	txJoueur4.setFillColor(sf::Color::Black);
	txJoueur5.setFont(menuGameFont);
	txJoueur5.setFillColor(sf::Color::Black);
	txJoueur6.setFont(menuGameFont);
	txJoueur6.setFillColor(sf::Color::Black);
	txJoueur7.setFont(menuGameFont);
	txJoueur7.setFillColor(sf::Color::Black);
	txJoueur8.setFont(menuGameFont);
	txJoueur8.setFillColor(sf::Color::Black);

	txHote.setPosition(posHote);
	txJoueur2.setPosition(posJoueur2);
	txJoueur3.setPosition(posJoueur3);
	txJoueur4.setPosition(posJoueur4);
	txJoueur5.setPosition(posJoueur5);
	txJoueur6.setPosition(posJoueur6);
	txJoueur7.setPosition(posJoueur7);
	txJoueur8.setPosition(posJoueur8);

	opaciteMenu = 5.0f;
	opaciteTimer = 0.0f;

	affClavier = 0;
	affManette = 0;

	menuMusique.play();

	iChoixConnect = 0;
	iDepConnect = 0;
}

void menu::update(myWindow& _window, Player& _player, Client& clients) {

	valMusic = std::to_string((int)sonMusique.GetVolumeMusique());
	valSon = std::to_string((int)sonMusique.GetVolumeSon());

	tValMus.setFont(menuGameFont);
	tValMus.setString(valMusic);
	tValMus.setFillColor(sf::Color::Black);
	tValMus.setPosition(posValMu);

	tValSon.setFont(menuGameFont);
	tValSon.setString(valSon);
	tValSon.setFillColor(sf::Color::Black);
	tValSon.setPosition(posValSon);

	sonMusique.SetVolume(menuMusique);
	sonMusique.SetSon(SonMenu);

	stValide = { "Validation" };
	txValide.setFont(menuGameFont);
	txValide.setString(stValide);
	txValide.setFillColor(sf::Color::Black);
	txValide.setPosition(sf::Vector2f(posConnection.x + 350, posConnection.y + 500));

	opaciteTimer += tools::GetTimeDelta();
	if (opaciteMenu < 255.0f && opaciteTimer > 0.01f)
	{
		opaciteMenu++;
		opaciteTimer = 0.0f;
	}

	menuTimer += tools::GetTimeDelta();
	timerBombeMenu += tools::GetTimeDelta();
	if (stateMenu == StateMenu::MENU && iChoixOptionState == 0) {
		if (iChoixConnect == 0 && iChoixConnectInv == 0 && iLobby == 0 && iLobbyInv == 0) {
			TextePseudo.erase();
			TexteIP.erase();
			TextePort.erase();
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && choixMenu > 0 && menuTimer > 0.2f) {
				SonMenu.play();
				choixMenu -= 1;
				menuTimer = 0.0f;
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && choixMenu < 3 && menuTimer > 0.2f) {
				SonMenu.play();
				choixMenu += 1;
				menuTimer = 0.0f;
			}
			switch (choixMenu)
			{
			case 0:
				posCusreur = sf::Vector2f(posConnect.x - 50, posConnect.y + 10);
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) && menuTimer > 0.2f || bombeMoving == true) {
					bombeMoving = true;
					exploCurs();
					if (bombeMoving == false) {
						iChoixConnect = 1;
					}
				}
				break;
			case 1:
				posCusreur = sf::Vector2f(posJouerInv.x - 50, posJouerInv.y + 10);
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) && menuTimer > 0.2f || bombeMoving == true) {
					bombeMoving = true;
					exploCurs();
					if (bombeMoving == false) {
						iChoixConnectInv = 1;
					}
				}
				break;
			case 2:
				posCusreur = sf::Vector2f(posOption.x - 50, posOption.y + 10);
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) && menuTimer > 0.2f || bombeMoving == true) {
					bombeMoving = true;
					exploCurs();
					if (bombeMoving == false) {
						iChoixOptionState = 1;
						//this->stateManager_->TransitionTo(new menu(StateMenu::OPTION), _window, _player, clients);
						menuTimer = 0.0f;
					}
				}
				break;
			case 3:
				posCusreur = sf::Vector2f(posQuitter.x - 50, posQuitter.y + 10);
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) && menuTimer > 0.2f || bombeMoving == true) {
					bombeMoving = true;
					exploCurs();
					if (bombeMoving == false) {
						_window.SetIsDone(true);
						menuTimer = 0.0f;
					}
				}
				break;
			default:
				break;
			}
		}
		else if (iChoixConnect == 1) {
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && iDepConnect > 1 && menuTimer > 0.2f) {
				SonMenu.play();
				iDepConnect -= 1;
				menuTimer = 0.0f;
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && iDepConnect < 5 && menuTimer > 0.2f) {
				SonMenu.play();
				iDepConnect += 1;
				menuTimer = 0.0f;
			}
			switch (iDepConnect)
			{
			case 1:
				posCusreur = sf::Vector2f(posConnection.x, posConnection.y + 50);
				break;
			case 2:
				posCusreur = sf::Vector2f(posConnection.x, posConnection.y + 220);
				break;
			case 3:
				posCusreur = sf::Vector2f(posConnection.x, posConnection.y + 370);
				break;
			case 4:
				posCusreur = sf::Vector2f(posConnection.x, posConnection.y + 530); if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) && menuTimer > 0.2f) {
					iChoixConnect = 0;
					menuTimer = 0.0f;
				}
				break;
			case 5:
				posCusreur = sf::Vector2f(posConnection.x + 340, posConnection.y + 530);
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) && menuTimer > 0.2f) {
					/*_player.InitPlayer();*/
					//sf::TcpSocket newSock;
					//// ...
					//clients.tcpSock = std::move(newSock); // Ou clients.tcpSock = newSock;
					///*(clients.tcpSock) = new sf::TcpSocket;*/
					clients.reset();
					
					si_port = std::stoi(TextePort);
					std::cout << "AAAAAAA" << std::endl;
					clients.zoneToClose = 0;
					clients.port = si_port;
					clients.ip = TexteIP;
					_player.isHost = true;
					clients.pseudo = TextePseudo;
					/*std::list<player*>a;
					clients.Ennemies = a;*/
					std::cout << clients.port << std::endl;
					std::cout << clients.pseudo << std::endl;
					posCusreur = sf::Vector2f(posConnection.x + 400, posConnection.y + 550);
					this->stateManager_->TransitionTo(new game, _window, _player, clients);
					menuTimer = 0.0f;
				}
				break;
			default:
				break;
			}
		}
		else if (iChoixConnectInv == 1) {
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && iDepConnect > 1 && menuTimer > 0.2f) {
				SonMenu.play();
				iDepConnect -= 1;
				menuTimer = 0.0f;
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && iDepConnect < 5 && menuTimer > 0.2f) {
				SonMenu.play();
				iDepConnect += 1;
				menuTimer = 0.0f;
			}
			switch (iDepConnect)
			{
			case 1:
				posCusreur = sf::Vector2f(posConnection.x, posConnection.y + 50);
				break;
			case 2:
				posCusreur = sf::Vector2f(posConnection.x, posConnection.y + 220);
				break;
			case 3:
				posCusreur = sf::Vector2f(posConnection.x, posConnection.y + 370);
				break;
			case 4:
				posCusreur = sf::Vector2f(posConnection.x, posConnection.y + 530); if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) && menuTimer > 0.2f) {
					iChoixConnectInv = 0;
					menuTimer = 0.0f;
				}
				break;
			case 5:
				posCusreur = sf::Vector2f(posConnection.x + 340, posConnection.y + 530);
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) && menuTimer > 0.2f) {
					si_port = std::stoi(TextePort);
					clients.port = si_port;
					clients.ip = TexteIP;
					clients.pseudo = TextePseudo;
					posCusreur = sf::Vector2f(posConnection.x + 400, posConnection.y + 550);
					this->stateManager_->TransitionTo(new game, _window, _player, clients);
					menuTimer = 0.0f;
				}
				break;
			default:
				break;
			}
		}
	}
	if (iChoixOptionState == 1) {
		if (choixSon == 0 && choixMusique == 0 && affManette == 0 && iLobby == 0 && iLobbyInv == 0) {
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && choixOption > 0 && menuTimer > 0.2f) {
				SonMenu.play();
				choixOption -= 1;
				menuTimer = 0.0f;
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && choixOption < 4 && menuTimer > 0.2f) {
				SonMenu.play();
				choixOption += 1;
				menuTimer = 0.0f;
			}
			switch (choixOption)
			{
			case 0:
				posCusreur = sf::Vector2f(posOSon.x - 50, posOSon.y + 10);
				if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) && menuTimer > 0.2f) || bombeMoving == true) {
					bombeMoving = true;
					exploCurs();
					if (bombeMoving == false) {
						choixSon = 1;
						menuTimer = 0.0f;
					}
				}
				break;
			case 1:
				posCusreur = sf::Vector2f(posOMusique.x - 50, posOMusique.y + 10);
				if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) && menuTimer > 0.2f) || bombeMoving == true) {
					bombeMoving = true;
					exploCurs();
					if (bombeMoving == false) {
						choixMusique = 1;
						menuTimer = 0.0f;
					}
				}
				break;
			case 2:
				posCusreur = sf::Vector2f(posOPE.x - 50, posOPE.y + 10);
				if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) && menuTimer > 0.2f) || bombeMoving == true) {
					bombeMoving = true;
					exploCurs();
					if (bombeMoving == false) {
						_window.ToggleFullscreen();
						menuTimer = 0.0f;
					}
				}
				break;
			case 3:
				posCusreur = sf::Vector2f(posOCom.x - 50, posOCom.y + 10);
				if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) && menuTimer > 0.2f) || bombeMoving == true) {
					bombeMoving = true;
					exploCurs();
					if (bombeMoving == false) {
						affManette = 1;
						menuTimer = 0.0f;
					}
				}
				break;
			case 4:
				posCusreur = sf::Vector2f(posORetour.x - 50, posORetour.y);
				if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) && menuTimer > 0.2f) || bombeMoving == true) {
					bombeMoving = true;
					exploCurs();
					if (bombeMoving == false) {
						iChoixOptionState = 0;
						//this->stateManager_->TransitionTo(new menu(StateMenu::MENU), _window, _player, clients);
						menuTimer = 0.0f;
					}
				}
				break;
			default:
				break;
			}
		}
		else if (choixSon == 1) {
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && sonMusique.GetVolumeSon() > 0 && menuTimer > 0.2f) {
				SonMenu.play();
				sonMusique.AddVolumeSon(-5);
				menuTimer = 0.0f;
				moinsSprite.setScale(2, 2);
				plusSprite.setScale(1, 1);
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && sonMusique.GetVolumeSon() < 100 && menuTimer > 0.2f) {
				SonMenu.play();
				sonMusique.AddVolumeSon(5);
				menuTimer = 0.0f;
				plusSprite.setScale(2, 2);
				moinsSprite.setScale(1, 1);
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) && menuTimer > 0.2f) {
				choixSon = 0;
				menuTimer = 0.0f;
				plusSprite.setScale(1, 1);
				moinsSprite.setScale(1, 1);
			}
		}
		else if (choixMusique == 1) {
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && sonMusique.GetVolumeMusique() > 0 && menuTimer > 0.2f) {
				sonMusique.AddVolumeMusique(-5);
				menuTimer = 0.0f;
				moinsSprite.setScale(2, 2);
				plusSprite.setScale(1, 1);
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && sonMusique.GetVolumeMusique() < 100 && menuTimer > 0.2f) {
				sonMusique.AddVolumeMusique(5);
				menuTimer = 0.0f;
				plusSprite.setScale(2, 2);
				moinsSprite.setScale(1, 1);
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) && menuTimer > 0.2f) {
				choixMusique = 0;
				menuTimer = 0.0f;
				plusSprite.setScale(1, 1);
				moinsSprite.setScale(1, 1);
			}
		}
		else if (affManette == 1) {
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) && menuTimer > 0.2f) {
				affManette = 0;
				affClavier = 0;
				menuTimer = 0.0f;
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && menuTimer > 0.2f) {
				affClavier = 1;
				menuTimer = 0.0f;
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && menuTimer > 0.2f) {
				affClavier = 0;
				menuTimer = 0.0f;
			}
		}
	}
}


void menu::updateEvent(myWindow& _window) {
	if (_window.GetEvent().type == sf::Event::TextEntered) {
		if (_window.GetEvent().text.unicode >= 33 && _window.GetEvent().text.unicode <= 126) {
			if (iDepConnect == 1)
				TextePseudo += (char)(_window.GetEvent().text.unicode);
			else if (iDepConnect == 2)
				TexteIP += (char)(_window.GetEvent().text.unicode);
			else if (iDepConnect == 3)
				TextePort += (char)(_window.GetEvent().text.unicode);
		}
		if (_window.GetEvent().text.unicode == 8) {
			if (iDepConnect == 1 && TextePseudo.size() > 0)
				TextePseudo.pop_back();
			else if (iDepConnect == 2 && TexteIP.size() > 0)
				TexteIP.pop_back();
			else if (iDepConnect == 3 && TextePort.size() > 0)
				TextePort.pop_back();
		}
		if (_window.GetEvent().text.unicode == 32) {
			if (iDepConnect == 1)
				TextePseudo += (char)(_window.GetEvent().text.unicode);
			else if (iDepConnect == 2)
				TexteIP += (char)(_window.GetEvent().text.unicode);
			else if (iDepConnect == 3)
				TextePort += (char)(_window.GetEvent().text.unicode);
		}
		if (iDepConnect == 1)
			TXpseudo.setString(TextePseudo);
		else if (iDepConnect == 2)
			TXip.setString(TexteIP);
		else if (iDepConnect == 3)
			TXport.setString(TextePort);
	}
}

void menu::draw(myWindow& _window, Player& _player, Client& clients) {
	_window.getRenderWindow().clear(sf::Color::White);
	viewMenu.setCenter(_window.GetWindowSize().x / 2, _window.GetWindowSize().y / 2);
	_window.getRenderWindow().setView(viewMenu);
	if (stateMenu == StateMenu::MENU && iChoixOptionState == 0) {
		_window.Draw(tMenu);
		_window.Draw(tConnecter);
		_window.Draw(tJouerInv);
		_window.Draw(tOption);
		_window.Draw(tQuitter);
		if (iChoixConnect == 1) {
			_window.Draw(spConnection);
			TXpseudo.setPosition(posPseudo);
			TXip.setPosition(posIP);
			TXport.setPosition(posPort);
			_window.Draw(TXpseudo);
			_window.Draw(TXip);
			_window.Draw(TXport);
			_window.Draw(txValide);
		}
		if (iChoixConnectInv == 1) {
			_window.Draw(spConnection);
			TXpseudo.setPosition(posPseudo);
			TXip.setPosition(posIP);
			TXport.setPosition(posPort);
			_window.Draw(TXpseudo);
			_window.Draw(TXip);
			_window.Draw(TXport);
			_window.Draw(txValide);
		}
	}
	if (iChoixOptionState == 1) {
		_window.Draw(tMenuOption);
		_window.Draw(toSon);
		_window.Draw(toMusique);
		_window.Draw(toPleineEcran);
		_window.Draw(toCommande);
		_window.Draw(toRetour);
		if (affManette == 1) {
			if (affClavier == 1)
				_window.Draw(scmdClavier);
			else
				_window.Draw(scmdManette);
		}
		if (choixSon == 1) {
			_window.Draw(moinsSprite);
			_window.Draw(plusSprite);
			_window.Draw(tVolSon);
			_window.Draw(tValSon);
		}
		if (choixMusique == 1) {
			_window.Draw(moinsSprite);
			_window.Draw(plusSprite);
			_window.Draw(tVolMus);
			_window.Draw(tValMus);
		}
	}
	sCursBombe.setPosition(posCusreur);
	sExploMenu.setPosition(posCusreur);
	if (bombeMoving == false) {
		_window.Draw(sCursBombe);
	}
	else {
		_window.Draw(sExploMenu);
	}
}

void menu::destroy() {

}

void menu::exploCurs() {
	if (bombeMoving == true) {
		if (timerBombeMenu >= 0.05f) {
			frameXbombeMenu += 1;
			if (frameXbombeMenu > 10) {
				frameXbombeMenu = 0;
				bombeMoving = false;
			}
			timerBombeMenu = 0.0f;
		}
		rectExploMenu.left = frameXbombeMenu * rectExploMenu.width;
		sExploMenu.setTextureRect(rectExploMenu);
	}
}








