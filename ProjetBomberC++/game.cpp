#include "game.h"
#include "menu.h"
#include "Player.h"
#include"Camera.h"
#include"Zone.h"
#include "Bombe.h"
#include "Map.h"
#include "MiniMap.h"
#include"Client.h"
#include"CardsDied.h"
#include "MenuInGame.h"
#include"Host.h"
#include "Bonus.h"
#include "Items.h"
#include "HUD.h"
#include "Client.h"
#include "Killfield.h"
#include"Lobby.h"
#include "Victory.h"
#include"PlayerLaunch.h"
#include "FeedBack.h"
#include "Sons.h"
#include "menu.h"

Killfield killfield;
Bombe bombe;
Camera cam;
Map map;
MiniMap minimap;
Zone zone;
CardsDied deck;
MenuInGame _menu;
Host host;
HUD hud;
Bonus bonus;
Items items;
Lobby lobby;
Victory vict;
PlayerLaunch launch;
FeedBack feed;
SonMusique son;
menu _Menu;

float timer = 0.0f;
float timerThread = 0.0f;
bool isHost;
int test;

void game::init(myWindow& _window, Player& _player, Client& clients)
{
	//réinitialisation de toutes les valeurs au début de la partie

	srand(time(NULL));
	map.InitMap(&items, _player, clients);
	son.InitSon();
	zone.InitNotif();
	zone.init();
	_player.InitPlayer(cam);
	vict.init();
	minimap.InitMiniMap();
	deck.Init();
	_menu.initMenuGame(_window, &cam,&_Menu);
	initQuitter();
	clients.initClient();
	deck.Init();
	hud.InitHud();
	bonus.InitBonus();
	bombe.InitBomb();
	items.initItems();
	_player.initInventaire();
	killfield.Init();
	zone.init();
	vict.initFin(_window);
	host.clientIp = clients.ip;
	host.ip = clients.ip;
	host.port = clients.port;
	host.clientPort = clients.port;

	//technique pour que les client envoient moins de données à l'hôte et qu'il puisse s'en sortir
	if (_player.isHost == true)
	{
		host.init(clients);
		clients.initClient();
		_window.getRenderWindow().setFramerateLimit(600);
	}
	else
	{
		_window.getRenderWindow().setFramerateLimit(100);
	}
	map.InitMap(&items, _player, clients);
	feed.initFeedBack();
}

void game::update(myWindow& _window, Player& _player, Client& clients)
{
	if (_player.gamelaunch) //Si tu n'es plus dans le lobby et que la game a été lancée
	{
		_window.getRenderWindow().setMouseCursorVisible(false);

		//efface les items
		if (items.degaeItem == false)
		{
			for (int i = 0; i < items.ITEMEXPULSIF.size(); i++)
			{
				items.ITEMEXPULSIF.erase(items.ITEMEXPULSIF.begin() + i);
			}
			for (int i = 0; i < bonus.BONUSFEU.size(); i++)
			{
				bonus.BONUSFEU.erase(bonus.BONUSFEU.begin() + i);
			}
			if (items.ITEMEXPULSIF.size() <= 0 && bonus.BONUSFEU.size() <= 0)
			{
				items.degaeItem = true;
			}
		}

		timer += tools::GetTimeDelta();

		//Chargement et envoie des coffres aux autres joueurs, on donne une position aléatoire à chaque joueur
		if (_player.isHost && !loadChess)
		{
			map.loadMapCoffre(&items, clients);
			loadChess = true;
		}
		if (!loadPos)
		{
			srand(time(NULL));
			launch.initposPlayer(host, clients);
			cam.setPos(_player.getPos());
			loadPos = true;
		}
		
		//Echap pour quitter
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) && timer > 0.2f && _menu.GetOption() == 0) {

			bQuit = true;
			timer = 0.0f;
		}

		//Role du serveur
		if (_player.isHost == true)
		{
			clients.updateClient(_player, bombe, zone, killfield, map, deck,bonus,items,cam);
			host.Update(map,_player);
			vict.Update(clients, _player, _window);
		}
		hud.UpdateHud(cam,_player, _window, clients);
		killfield.Update();
		bombe.Update(map, &items, clients, _player, killfield,&son);
		_player.UpdatePlayer(bombe, map, clients, _window, cam, &deck, &bonus, &items,&son);
		zone.Update(_player, clients, cam);
		_player.updateInventaire();
		bonus.UpdateBonus(_window, &cam, &_player, &bombe, &clients,&son);
		clients.updateClient(_player, bombe, zone, killfield, map, deck, bonus, items,cam);
		deck.UpdateDied(&_player,killfield, clients,&son);
		vict.Update(clients, _player, _window);
		minimap.UpdateMiniMap(&_player);

		_menu.updateMG(_window, cam,&_Menu);
		items.updateItems(_window, &cam, &_player,&clients,&son);
		feed.updateFeedBack(_player);

		//Tout le reset si la partie et fini ou si on quitte avec esc
		if (vict.bReset == true) {
			if (_window.getRenderWindow().hasFocus())
			{
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
					_menu.menuMusique.stop();
					std::cout << "efface" << std::endl;
					clients.sendDisconnect();
					clients.tcpSock.disconnect();
					cam.Init();
					std::list<player*>a;
					clients.Ennemies = a;
					_player.isHost = false;
					_player.gamelaunch = false;
					host.nbClient = 0;
					std::cout << "efface" << std::endl;
					auto i = host.listClients.begin(); auto n = host.listClients.end();
					while (i!=n)
					{
						host.selector.remove(*(*i)->tcpSock);
						delete(*i);
						i = host.listClients.erase(i);
						std::cout << "efface" << std::endl;
					}
					this->stateManager_->TransitionTo(new menu(StateMenu::MENU), _window, _player, clients);
					vict.bReset = false;
					clients.reset();
				}
			}
		}
		if (bQuit == true) {
			updateQuitter(_window, _player);
			if (iQuit == 1) {
				_menu.menuMusique.stop();
				std::cout << "efface" << std::endl;
				clients.sendDisconnect();
				clients.tcpSock.disconnect();
				cam.Init();
				std::list<player*>a;
				clients.Ennemies = a;
				_player.isHost = false;
				_player.gamelaunch = false;
				host.nbClient = 0;
				std::cout << "efface" << std::endl;
				auto i = host.listClients.begin(); auto n = host.listClients.end();
				while (i != n)
				{
					host.selector.remove(*(*i)->tcpSock);
					delete(*i);
					i = host.listClients.erase(i);
					std::cout << "efface" << std::endl;
				}
				this->stateManager_->TransitionTo(new menu(StateMenu::MENU), _window, _player, clients);
				vict.bReset = false;
				clients.reset();


				bQuit = false;
				iQuit = 0;
			}
			else if (iQuit == 2) {
				bQuit = false;
				iQuit = 0;
			}
		}
		son.UpdateSound(&_player);
	}
	else //si dans le lobby il y a que l'update du client et del'hote qui sont joué
	{
		if (_player.isHost && !loadChess)
		{
			map.loadMapCoffre(&items, clients);
			loadChess = true;
		}
		if (_player.isHost == true)
		{
			hud.UpdateHud(cam, _player, _window, clients);
			clients.updateClient(_player, bombe, zone, killfield, map, deck,bonus, items, cam);
			host.Update(map, _player);
			_player.UpdatePlayer(bombe, map, clients, _window, cam, &deck, &bonus, &items,&son);
		}
		clients.updateClient(_player, bombe, zone, killfield, map, deck, bonus, items,cam);
	}
	_window.getRenderWindow().clear(sf::Color(110.0f, 164.0f, 0.0f)); //Coleur du fond sur mesure
}

void game::updateEvent(myWindow& _window)
{

}

void game::draw(myWindow& _window, Player& _player, Client& clients)
{
	if (_player.gamelaunch)
	{
		cam.draw(_window, _player);
		map.DisplayMap(_window);
		bombe.Display(_window, clients,&son);
		map.DisplayMapHITBOX(_window, &bonus, &items);
		bonus.DisplayBonus(&_window);
		deck.DisplayBombeAtomic(&_window);
		items.displayItems(_window, &bonus);
		clients.draw(_window);
		_player.DisplayPlayer(_window, deck, clients);
				
		_menu.displayMenuGame(_window);
		displayQuitter(_window);
		zone.draw(_window,&_player);
		killfield.Display(_window, _player, clients);
		minimap.DisplayGrandMap(&_window);
		feed.displayFeedBack(_window, _player);

		if (_player.getState() == state::PLAYER) //Si le joueur est vivant
		{
			_player.DisplayInventaire(_window);
			hud.DisplayHud(_window, _player, clients,cam);
			_player.DisplayCurseur(_window);

			minimap.DisplayMiniMap(_window);
			map.DisplayMap(_window);
			_player.DisplayRondBleu(&_window);
			bombe.Display(_window, clients,&son);
			deck.DisplayBombeAtomic(&_window);
		}
		else 
		{
			_player.DisplayCarte2(_window, deck, clients);
			feed.displayFeedBack(_window, _player);
			deck.DisplayPiece(&_window, _player);
			_player.DisplayCurseur(_window);

		}
	}
	else //Si dans le lobby
	{
		lobby.draw(clients, _window, _player);

		hud.DisplayHud(_window,_player, clients, cam);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && _player.isHost) //Permet à l'hote de lancer la partie
		{
			clients.lunchGame();
			_player.gamelaunch = true;
		}
	}
		if (vict.bReset == true) {
			vict.draw(_window);
		}
}
void game::initQuitter() {
	ttQuit.loadFromFile("../Ressources/Textures/Quitter.png");
	spQuit.setTexture(ttQuit);
	spQuit.setColor(sf::Color(255.0f, 255.0f, 255.0f, 200.0f));
}

void game::updateQuitter(myWindow& _window, Player& _player) {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && timer > 0.2f) {
		iQuit = 1;
		timer = 0.0f;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && timer > 0.2f) {
		iQuit = 2;
		timer = 0.0f;
	}
}

void game::displayQuitter(myWindow& _window) {
	if (bQuit == true) {
		posQuit = sf::Vector2f(cam.getPosViewgame().x - 200, cam.getPosViewgame().y);
		spQuit.setPosition(posQuit);
		_window.Draw(spQuit);
	}
}
void game::destroy()
{

}