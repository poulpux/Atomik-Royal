#include "Player.h"
#include"Client.h"
#include "Bombe.h"
#include "Map.h"
#include"CardsDied.h"
#include "Camera.h"
#include "Bonus.h"
#include "Items.h"
#include "Sons.h"
#include"Particles.h"

Player::Player()
{
	//équilibrage 

	//-------------------------------------------
	spd.x = 200;
	spd.y = 200;
	spdSave = spd.x;
	spdBoost = spd.x / 8;
	spdBoost = spd.y / 8;
	spd2Touch = spd.x * 0.7;
	if (isHost)
	{
		spd.x = spd.x*1.2;
		spd.y = spd.y*1.2;
		spdSave = spd.x;
		spdBoost = spd.x / 8;
		spdBoost = spd.y / 8;
		spd2Touch = spd.x * 0.7;
	}
	spdDirector = 500.f;
	bombCdwn = 0.3f;
	bombDmg = 25.f;
	dmgBombLimit = 50;

	powSpdBonus = 2;
	dureSpdBonus = 10;
	cooldawnPc = 8.f;
	//-------------------------------------------
	pos = { 1000,1000 };
	life = 100;
	nbBombePosable = 1;
	stateP = state::PLAYER;
	rect = { 65,22,13,16 };
	sprite.setOrigin(1.f, 0.f);
	multiSpd = 1;
	armure = 0;

	nbBonusSpd = 0;
	nbBonusFeu = 0;
	nbBonusArmure = 0;
	nbBonusHeal = 0;
	nbBombeImpulsif = 0;
}

Player::~Player()
{
}

void Player::InitPlayer(Camera& _cam)
{
	texture.loadFromFile(TEXTURE_PATH"basic.png");
	sprite.setTexture(texture);
	sprite.setPosition(pos);
	sprite.setScale(sf::Vector2f(1.7f, 1.7f));
	totalCard = 2;

	rectShowCible.setSize(sf::Vector2f(600, 120));
	rectShowCible.setFillColor(sf::Color::White);
	font.loadFromFile("../Ressources/Fonts/Typewriter.ttf");
	nameEnnemy.setCharacterSize(45);
	nameEnnemy.setFillColor(sf::Color(20, 60, 18, 255));
	nameEnnemy.setFont(font);

	recBleuPlayer.setRadius(35.0f);
	recBleuPlayer.setPosition(positionrecBleuPlayer);
	recBleuPlayer.setFillColor(sf::Color::Blue);
	recBleuPlayer.setOrigin(sf::Vector2f(35.0f,35.0f));
  
    activeImpulsif = true;

	nbPiece = 0;
	texturecurseur.loadFromFile(TEXTURE_PATH"viseur.png");
	spritecurseur.setTexture(texturecurseur);
	spritecurseur.setPosition(positioncurseur);
	spritecurseur.setScale(sf::Vector2f(0.4f, 0.4f));
	spritecurseur.setOrigin(sf::Vector2f(81.0f / 2.0f, 81.0f / 2.0f));

	spd.x = 200;
	spd.y = 200;
	spdSave = spd.x;
	spdBoost = spd.x / 8;
	spdBoost = spd.y / 8;
	spd2Touch = spd.x * 0.7;
	if (isHost)
	{
		spd.x = spd.x * 1.2;
		spd.y = spd.y* 1.2;
		spdSave = spd.x;
		spdBoost = spd.x / 8;
		spdBoost = spd.y / 8;
		spd2Touch = spd.x * 0.7;
	}
	spdDirector = 500.f;
	bombCdwn = 0.3f;
	bombDmg = 25.f;
	dmgBombLimit = 50;

	powSpdBonus = 2;
	dureSpdBonus = 10;
	cooldawnPc = 7.f;
	//-------------------------------------------
	pos = { 1000,1000 };
	life = 100;
	nbBombePosable = 1;
	stateP = state::PLAYER;
	rect = { 65,22,13,18 };
	sprite.setOrigin(1.f, 0.f);
	multiSpd = 1;
	armure = 0;
	nbBonusSpd = 0;
	nbBonusFeu = 0;
	nbBonusArmure = 0;
	nbBonusHeal = 0;
	nbBombeImpulsif = 0;


	_cam.Init();

	std::list<CardsDied*>a;
	main = a;
}

void Player::UpdatePlayer(Bombe& _bomb, Map& _map, Client& _client, myWindow& _window, Camera& _view, CardsDied* _card, Bonus* _bonus, Items* _item, SonMusique* _son)
{
	TakeSpdBoost();
	/*if (isHost) life = 0;*/
	mousePosition = sf::Mouse::getPosition(_window.getRenderWindow());
	mapPixel = _window.getRenderWindow().mapPixelToCoords(mousePosition, _view.viewGame);
	moove(&_map);
	if (stateP == PLAYER)
	{
		posBomb(_bomb, _client, _window, _view, _card, _son);
		
	}
	else 
	{
		openCardMenu(_client,*_card,_son); 
		gainPiece();
	}
	isDead(_bomb, _bonus, _item, _view, _client);
	anim();
	positionZone();
	if (spdMenu) Spdlaunch( _client, *_card,_window);
	if (healMenu) Heallaunch(_client, *_card, _window);

	/*if (sf::Keyboard::isKeyPressed(sf::Keyboard::O) && timerBomb > 0.3f)
	{
		changePv(25);
		armure -= 25;
		timerBomb = 0.0f;
	}*/
	if(life>0) Parti.push_back(new Particles(_window, _view));
}

void Player::posBomb(Bombe& _bomb, Client& _client, myWindow& _window, Camera& _view, CardsDied* _card, SonMusique* _son)
{
	timerBomb += tools::GetTimeDelta();
	float LT, RT;
	gp::Gamepad::getTriggers(0, LT, RT);
	if ((sf::Keyboard::isKeyPressed(sf::Keyboard::E) || RT > 0.5) && timerBomb > bombCdwn && NBSwitchItem == 1 )
	{
		bool okPos =  false;
		auto i = _bomb.listeBombe.begin(); auto n = _bomb.listeBombe.end();
		while (i != n)
		{
			if ((*i)->pos == sf::Vector2f((int)((pos.x - 5) / 32) * 32 + 16, (int)((pos.y + 3) / 32) * 32 + 16))
			{
				okPos = true;
			}
			i++;
		}

		auto j = _client.Ennemies.begin(); auto q = _client.Ennemies.end();
		while (j != q)
		{
			auto y = (*j)->ennemyBomb.begin(); auto w = (*j)->ennemyBomb.end();
			while (y!=w)
			{
				if ((*y)->pos == sf::Vector2f((int)((pos.x - 5) / 32) * 32 + 16, (int)((pos.y + 3) / 32) * 32 + 16))
				{
					okPos = true;
				}
				y++;
			}
			j++;
		}

		if (!okPos)
		{
			_client.throw_Bomb(sf::Vector2f((int)((pos.x - 5) / 32) * 32 + 16, (int)((pos.y + 3) / 32) * 32 + 16), _bomb.nbFlamme);
			_bomb.listeBombe.push_back(new Bombe(sf::Vector2f((int)((pos.x - 5) / 32) * 32 + 16, (int)((pos.y + 3) / 32) * 32 + 16)));
			timerBomb = 0.0f;
		}
	}

	if ((sf::Keyboard::isKeyPressed(sf::Keyboard::E)|| RT > 0.5) && timerBomb > bombCdwn*2 && getBombeImpulsif() > 0 && NBSwitchItem == 2 )
	{
		int a = -1;
		_bomb.BOMBEEXPULSIF.push_back(new Bombe(_bomb.spriteBombeExpulsif, sf::Vector2f(pos.x + 5, pos.y + 5), _bomb.recExpulsif, mapPixel,a));
		_client.throw_Impuls(sf::Vector2f(pos.x + 5, pos.y + 5), mapPixel);
		SuppBombeImpulsif();
		timerBomb = 0.0f;
	}
	/*if (sf::Keyboard::isKeyPressed(sf::Keyboard::R) && timerBomb > bombCdwn)
	{
		_client.throw_Atomik(mapPixel);
		_card->BOMBEATOMIC.push_back(new CardsDied(_card->spriteBombeAtomic, _card->recBombeAtomic, mapPixel));
		
		timerBomb = 0.0f;
	}*/
	if ((sf::Keyboard::isKeyPressed(sf::Keyboard::E)|| RT>0.5) && timerBomb > bombCdwn && getBonusHeal() > 0 && NBSwitchItem == 5 && getPv() < 100 )
	{
		_son->SEXPLOSIONCLASSIC.push_back(new SonMusique(10, pos,_son->soundExplosionClassic, _son->soundBombeNucleaire, _son->soundHit, _son->soundImpulsifExplosion, _son->soundBonusFlame, _son->soundBonusHeal,_son->soundKill, _son->soundRecupItem, _son->soundBonusShield, _son->soundBonusSpeed));
		bandageBonus();
		SuppbonusHeal();
		healParti = true;
		registerPos = { pos.x + 7.5f,pos.y + 9.f };
		timerBomb = 0.0f;
	}
	if ((sf::Keyboard::isKeyPressed(sf::Keyboard::E)|| RT>0.5) && timerBomb > bombCdwn && getBonusArmure() > 0 && NBSwitchItem == 4 && getArmure() < 100)
	{
		_son->SEXPLOSIONCLASSIC.push_back(new SonMusique(8, pos,_son->soundExplosionClassic, _son->soundBombeNucleaire, _son->soundHit, _son->soundImpulsifExplosion, _son->soundBonusFlame, _son->soundBonusHeal, _son->soundKill, _son->soundRecupItem, _son->soundBonusShield, _son->soundBonusSpeed));
		armureBonus();
		SuppbonusArmure();
		shieldParti = true;
		registerPos = { pos.x + 7.5f,pos.y + 9.f };
		timerBomb = 0.0f;
	}
	if (healParti)
	{
		int a = 0;
		timerParti += tools::GetTimeDelta();
		if (timerParti < 0.2)
		{
			Parti.push_back(new Particles(registerPos, a));
		}
		else
		{
			healParti = false;
			timerParti = 0;
		}
	}

	if (shieldParti)
	{
		int a = 1;
		timerPartieS += tools::GetTimeDelta();
		if (timerPartieS < 0.2)
		{
			Parti.push_back(new Particles(registerPos, a));
		}
		else
		{
			shieldParti = false;
			timerPartieS = 0;
		}
	}
}

void Player::moove(Map* _map)
{
	checkOne = false;
	checkTwo = false;
	sf::FloatRect FRPlayer = sprite.getGlobalBounds();
	sf::Vector2f gamepadG, gamepadD;
	gp::Gamepad::getSticksPosition(0, gamepadG, gamepadD);
	sf::Vector2f MovSpeed;
	tools::direction(pos, sf::Vector2f(pos.x + gamepadG.x * 100, pos.y + gamepadG.y * 100), MovSpeed);
	//Control mouvement
	if (stateP == GAMEDIRECTOR)
	{
		if ((sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Q) || gamepadG.x != 0))
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && pos.x < 4875)
			{
				pos.x += spd.x * tools::GetTimeDelta();
				sendSpd.x = spd.x;
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q) && pos.x > 50)
			{
				pos.x -= spd.x * tools::GetTimeDelta();
				sendSpd.x = spd.x;
			}
			else
			{
				pos.x += spd.x * tools::GetTimeDelta() * MovSpeed.x;
				sendSpd.x = spd.x*abs(MovSpeed.x) * 1.3;
			}

		}
		else
		{
			checkOne = true;
		}

		if ((sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Z) || gamepadG.y != 0))
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && pos.y < 4800)
			{
				pos.y += spd.y * tools::GetTimeDelta();
				sendSpd.y = spd.y;
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z) && pos.y > 25)
			{
				pos.y -= spd.y * tools::GetTimeDelta();
				sendSpd.y = spd.y;
			}
			else
			{
				pos.y -= spd.y * tools::GetTimeDelta() * MovSpeed.y;
				sendSpd.y = spd.y * abs(MovSpeed.y) * 1.3;
			}
		}
		else
		{
			checkTwo = true;
		}
	}
	else
	{
		if (((sf::Keyboard::isKeyPressed(sf::Keyboard::D) && !(_map->collisionPlayer(FRPlayer, DROITE, spd))) || ((sf::Keyboard::isKeyPressed(sf::Keyboard::Q) && !(_map->collisionPlayer(FRPlayer, GAUCHE, spd))) || gamepadG.x != 0)))
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && !(_map->collisionPlayer(FRPlayer, DROITE, spd)) && pos.x <= 4725 + 100)
			{
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Z)&&pos.y> 20 &&pos.y< 4785)
				{
					pos.x += spd2Touch * tools::GetTimeDelta() * multiSpd;
					sendSpd.x = spd2Touch * multiSpd /** 1.4*/;
				}
				else
				{
					pos.x += spd.x * tools::GetTimeDelta() * multiSpd;
					sendSpd.x = spd.x * multiSpd;
				}

			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q) && !(_map->collisionPlayer(FRPlayer, GAUCHE, spd)) && pos.x > 50)
			{
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Z) && pos.y > 20 && pos.y < 4785)
				{
					pos.x -= spd2Touch * tools::GetTimeDelta() * multiSpd;
					sendSpd.x = spd2Touch * multiSpd /** 1.4*/;
				}
				else
				{
					pos.x -= spd.x * tools::GetTimeDelta() * multiSpd;
					sendSpd.x = spd.x * multiSpd;
				}
			}
			else if (gamepadG.x > 0 && !(_map->collisionPlayer(FRPlayer, DROITE, spd)) && pos.x <= 4725 + 100)
			{
				pos.x += spd.x * tools::GetTimeDelta() * MovSpeed.x * multiSpd;
				sendSpd.x = spd.x * multiSpd * abs(MovSpeed.x) * 1.3;
			}
			else if (gamepadG.x < 0 && !(_map->collisionPlayer(FRPlayer, GAUCHE, spd)) && pos.x>50)
			{
				pos.x += spd.x * tools::GetTimeDelta() * MovSpeed.x * multiSpd;
				sendSpd.x = spd.x * multiSpd * abs(MovSpeed.x) * 1.3;
			}
		}
		else
		{
			checkOne = true;
		}
		

		if ((((sf::Keyboard::isKeyPressed(sf::Keyboard::S) && !(_map->collisionPlayer(FRPlayer, BAS, spd)))) || ((sf::Keyboard::isKeyPressed(sf::Keyboard::Z) && !(_map->collisionPlayer(FRPlayer, HAUT, spd))))) || gamepadG.y != 0)
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && !(_map->collisionPlayer(FRPlayer, BAS, spd))&&pos.y< 4785)
			{
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q) || sf::Keyboard::isKeyPressed(sf::Keyboard::D) && pos.x > 50 && pos.x < 4725 + 100)
				{
					pos.y += spd2Touch * tools::GetTimeDelta() * multiSpd;
					sendSpd.y = spd2Touch * multiSpd/* * 1.4*/;
				}
				else
				{
					pos.y += spd.y * tools::GetTimeDelta() * multiSpd;
					sendSpd.y = spd.y * multiSpd;
				}
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z) && !(_map->collisionPlayer(FRPlayer, HAUT, spd)) && pos.y> 20)
			{
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q) || sf::Keyboard::isKeyPressed(sf::Keyboard::D) && pos.x > 50 && pos.x < 4725 + 100)
				{
					pos.y -= spd2Touch * tools::GetTimeDelta() * multiSpd;
					sendSpd.y = spd2Touch * multiSpd /** 1.4*/;
				}
				else
				{
					pos.y -= spd.y * tools::GetTimeDelta() * multiSpd;
					sendSpd.y = spd.y * multiSpd ;
				}
			}
			else if (gamepadG.y < 0 && !(_map->collisionPlayer(FRPlayer, BAS, spd))&&pos.y>20)
			{
				pos.y -= spd.y * tools::GetTimeDelta() * MovSpeed.y * multiSpd;
				sendSpd.y = spd.y * multiSpd * abs(MovSpeed.y) * 1.3;
			}
			else if (gamepadG.y > 0 && !(_map->collisionPlayer(FRPlayer, HAUT, spd)) && pos.y < 4785)
			{
				pos.y -= spd.y * tools::GetTimeDelta() * MovSpeed.y * multiSpd;
				sendSpd.y = spd.y * multiSpd * abs(MovSpeed.y)*1.3;
			}
		}
		else
		{
			checkTwo = true;
		}
	}
	sprite.setPosition(pos);


}

void Player::isDead(Bombe& _bomb, Bonus* _bonus, Items* _item, Camera& _cam, Client& _client)
{

	if (life <= 0 && stateP == PLAYER)
	{
		int a = 0;
		for (int i = 0; i < getBonusArmure(); i++)
		{
			a = 0;
			_bonus->BONUSFEU.push_back(new Bonus(_bonus->spriteBonus, pos, 0));
			_client.sendBonus(pos, a);

		}
		for (int i = 0; i < getBonusSpd(); i++)
		{
			a = 1;
			_bonus->BONUSFEU.push_back(new Bonus(_bonus->spriteBonus, pos, 1));
			_client.sendBonus(pos, a);
		}
		for (int i = 0; i < getBonusFeu(); i++)
		{
			a = 2;
			_bonus->BONUSFEU.push_back(new Bonus(_bonus->spriteBonus, pos, 2));
			_client.sendBonus(pos, a);
		}
		for (int i = 0; i < getBonusHeal(); i++)
		{
			a = 3;
			_bonus->BONUSFEU.push_back(new Bonus(_bonus->spriteBonus, pos, 3));
			_client.sendBonus(pos, a);
		}
		for (int i = 0; i < getBombeImpulsif(); i++)
		{
			_item->ITEMEXPULSIF.push_back(new Items(_item->spriteItemExpulsif, pos, true));
			_client.sendGre(pos);
		}
		_cam.setZoom(1.429);
		for (size_t j = 0; j < 3; j++)
		{
			int randomN = 0;
			randomN = tools::iRand2(0, totalCard);
			main.push_back(new CardsDied(typeCard(j)));
		}
		spd.x = spdDirector;
		spd.y = spdDirector;
		stateP = GAMEDIRECTOR;
	}
}

void Player::DisplayPlayer(myWindow& _window, CardsDied& _deck, Client& _client)
{
	if (stateP == PLAYER)
	{
		_window.Draw(sprite);
	}

	auto i = Parti.begin(); auto n = Parti.end();
	while (i!=n)
	{
		if(inzone) (*i)->IncreasColor();
		else (*i)->DecreasColor();

		(*i)->update(_window);
		if((*i)->transparence>25) (*i)->draw(_window);
		if ((*i)->timer > 2&& ((*i)->type ==0||(*i)->type == 1))
		{
			delete(*i);
			i = Parti.erase(i);
		}
		else if ((*i)->type == 2 && (*i)->timer > 10)
		{
			std::cout << std::endl;
			delete(*i);
			i = Parti.erase(i);
		}
		else
		{
			i++;
		}
	}
}

void Player::DisplayCarte2(myWindow& _window, CardsDied& _deck, Client& _client)
{
	if (stateP == GAMEDIRECTOR)
	{
		if (isCardMenuOpen)
		{
			int a = 0;
			auto i = main.begin();
			auto n = main.end();
			while (i != n)
			{
				typeCard h = (*i)->getType();
				spriteC.setTexture(*_deck.getTextureCloseR(h));
				positionC = _window.getRenderWindow().mapPixelToCoords(sf::Vector2i(380 + (400 * a), 250));
				spriteC.setPosition(positionC);
				_window.Draw(spriteC);
				a++;
				i++;
			}
		}
		if (cardUsingOpen)
		{
			DisplayCarte(_window, _client);
		}
	}
}

void Player::DisplayCarte(myWindow& _window, Client& _client)
{
	auto a = main.begin(); auto b = a; b++; auto c = b; c++;
	auto card = a;
	if (laquelle == 1) auto card = a;
	else if (laquelle == 2) auto card = b;
	else  if (laquelle == 3) auto card = c;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::E) && timerClicked > 0.2)
	{
		cardUsingOpen = false;
	}
	if ((*card)->getType() == GIVESPDBOOST || (*card)->getType() == HEAL)
	{
		auto i = _client.Ennemies.begin(); auto n = _client.Ennemies.end();
		int a = 0;
		while (i != n)
		{
			if (!(*i)->dead)
			{
				if (a >= 4)
				{
					a -= 4;
					rectShowCible.setPosition(sf::Vector2f(pos.x - 600 + 700, pos.y - 400 + (a * 150)));
					_window.Draw(rectShowCible);

					nameEnnemy.setPosition(sf::Vector2f(pos.x - 600 + 5 + 700, pos.y - 400 + 25 + (a * 150)));
					nameEnnemy.setString((*i)->username);
					_window.Draw(nameEnnemy);
				}
				else
				{
					rectShowCible.setPosition(sf::Vector2f(pos.x - 600, pos.y - 400 + (a * 150)));
					_window.Draw(rectShowCible);

					nameEnnemy.setPosition(sf::Vector2f(pos.x - 600 + 5, pos.y - 400 + 25 + (a * 150)));
					nameEnnemy.setString((*i)->username);
					_window.Draw(nameEnnemy);
				}
				a++;
			}
			i++;
		}
	}
}

void Player::DisplayRondBleu(myWindow* _window)
{
	positionrecBleuPlayer.x = pos.x;
	positionrecBleuPlayer.y = pos.y;
	recBleuPlayer.setPosition(positionrecBleuPlayer);
	_window->Draw(recBleuPlayer);
}

void Player::DisplayCurseur(myWindow& _window)
{
	sf::Vector2f gamepadG, gamepadD;
	gp::Gamepad::getSticksPosition(0, gamepadG, gamepadD);
	sf::Vector2f MovSpeed;
	tools::direction(pos, sf::Vector2f(pos.x + gamepadD.x * 100, pos.y + gamepadD.y * 100), MovSpeed);
	if (gamepadD.y != 0)
	{
		/*if(positioncurseur.y< _window.getRenderWindow().mapPixelToCoords(sf::Vector2i(0,0).y))*/
		positioncurseur.y -= 1200.0f * tools::GetTimeDelta() * MovSpeed.y;
		sf::Mouse::setPosition(sf::Vector2i(positioncurseur.x + 1000, positioncurseur.y + 700));
	}
	if (gamepadD.x != 0)
	{
		positioncurseur.x += 1200.0f * tools::GetTimeDelta() * MovSpeed.x;
		sf::Mouse::setPosition(sf::Vector2i(positioncurseur.x + 1000, positioncurseur.y + 700));
	}

	spritecurseur.setPosition(mapPixel);
	_window.Draw(spritecurseur);

}

void Player::anim()
{
	if(getDontMove()==false) timerCourse += tools::GetTimeDelta();
	playerDir = getDirection();
	sprite.setPosition(pos);
	sprite.setTextureRect(rect);

	sprite.setTexture(texture);
	if (playerDir == NORTH_WEST) { rect.left = 113; }
	else if (playerDir == NORTH_EAST) { rect.left = 17; }
	else if (playerDir == SOUTH_WEST) { rect.left = 81; }
	else if (playerDir == SOUTH_EAST) { rect.left = 49; }
	else if (playerDir == EAST) { rect.left = 33; }
	else if (playerDir == WEST) { rect.left = 97; }
	else if (playerDir == NORTH) { rect.left = 1; }
	else if (playerDir == SOUTH) { rect.left = 65; }

	if (timerCourse < 0.2) { rect.top = 22; }
	else if (timerCourse < 0.2 * 2) { rect.top = 46; }
	else if (timerCourse < 0.2 * 3) { rect.top = 71; }
	else timerCourse = 0;
}

void Player::openCardMenu(Client& _client, CardsDied& cardd, SonMusique* _son)
{
	timerClicked += tools::GetTimeDelta();
	timerCardMenu += tools::GetTimeDelta();
	if (((sf::Keyboard::isKeyPressed(sf::Keyboard::E) || gp::Gamepad::isButtonPressed(0, gp::Gamepad::X)) && timerCardMenu > 0.2 && !isCardMenuOpen) && !cardUsingOpen)
	{
		isCardMenuOpen = true;
		timerCardMenu = 0;
	}
	if ((sf::Keyboard::isKeyPressed(sf::Keyboard::E) || gp::Gamepad::isButtonPressed(0, gp::Gamepad::X)) && timerCardMenu > 0.2 && isCardMenuOpen)
	{
		isCardMenuOpen = false;
		timerCardMenu = 0;
	}

	if (isCardMenuOpen)
	{
		activatCard(_client,cardd,_son);
	}
}

void Player::activatCard(Client& _client, CardsDied& cardd, SonMusique* _son)
{
	auto a = main.begin(); auto b = a; b++; auto c = b; c++;
	if (mapPixel.x >= pos.x - 600 && mapPixel.x <= pos.x - 225 && mapPixel.y >= pos.y - 325 && mapPixel.y <= pos.y + 237 && nbPiece >= (*a)->getCost() && (sf::Mouse::isButtonPressed(sf::Mouse::Left) || gp::Gamepad::isButtonPressed(0, gp::Gamepad::A)) && timerClicked > 0.2)
	{
		spdMenu = true;
		isCardMenuOpen = false;
		cardUsingOpen = true;
		timerClicked = 0;
	}
	else if (mapPixel.x >= pos.x - 600 + 400 && mapPixel.x <= pos.x - 225 + 400 && mapPixel.y >= pos.y - 325 && mapPixel.y <= pos.y + 237 && nbPiece >= (*b)->getCost() && (sf::Mouse::isButtonPressed(sf::Mouse::Left) ||gp::Gamepad::isButtonPressed(0,gp::Gamepad::A)) && timerClicked > 0.2)
	{
		healMenu = true;
		isCardMenuOpen = false;
		cardUsingOpen = true;
		timerClicked = 0;
	}
	else if (mapPixel.x >= pos.x - 600 + 800 && mapPixel.x <= pos.x - 225 + 800 && mapPixel.y >= pos.y - 325 && mapPixel.y <= pos.y + 237 && nbPiece >= (*c)->getCost() && (sf::Mouse::isButtonPressed(sf::Mouse::Left) || gp::Gamepad::isButtonPressed(0, gp::Gamepad::A))&& timerClicked > 0.2)
	{
		timerClicked = 0;
		_client.throw_Atomik(pos);
		cardd.BOMBEATOMIC.push_back(new CardsDied(cardd.spriteBombeAtomic, cardd.recBombeAtomic, pos));
		nbPiece -= (*c)->getCost();
		pasRepAtomik = true;
		isCardMenuOpen = false;
	}

}

void Player::Spdlaunch(Client& _client, CardsDied& cardd, myWindow& _window)
{
	auto i = _client.Ennemies.begin(); auto n = _client.Ennemies.end();
	int a = 0;
	while (i != n)
	{
		if (!(*i)->dead)
		{
			if (a >= 4)
			{
				if (mapPixel.x >= pos.x - 600 + 700 && mapPixel.x <= pos.x - 600 + 700 + 600 && mapPixel.y >= pos.y - 400 + 25 + (a * 150) && mapPixel.y <= pos.y - 400 + 25 + (a * 150) + 120 && timerClicked > 0.2 && (sf::Mouse::isButtonPressed(sf::Mouse::Left) /*|| gp::Gamepad::isButtonPressed(0, gp::Gamepad::A)*/))
				{
					timerClicked = 0;
					nbPiece -= 3;
					_client.sendSPDBoost((*i)->id);
					spdMenu = false;
					cardUsingOpen = false;
				}
			}
			else
			{
				if (mapPixel.x >= pos.x - 600 && mapPixel.x <= pos.x - 600 + 600 && mapPixel.y >= pos.y - 400 + 25 + (a * 150) && mapPixel.y <= pos.y - 400 + 25 + (a * 150) + 120 && timerClicked > 0.2 && (sf::Mouse::isButtonPressed(sf::Mouse::Left) /*|| gp::Gamepad::isButtonPressed(0, gp::Gamepad::A)*/))
				{
					timerClicked = 0;
					nbPiece -= 3;
					_client.sendSPDBoost((*i)->id);
					spdMenu = false;
					cardUsingOpen = false;
				}
			}

			a++;
		}
		i++;
	}
}

void Player::Heallaunch(Client& _client, CardsDied& cardd, myWindow& _window)
{
	auto i = _client.Ennemies.begin(); auto n = _client.Ennemies.end();
	int a = 0;
	while (i != n)
	{
		if (!(*i)->dead)
		{
			if (a >= 4)
			{
				if (mapPixel.x >= pos.x - 600 + 700 && mapPixel.x <= pos.x - 600 + 700 + 600 && mapPixel.y >= pos.y - 400 + 25 + (a * 150) && mapPixel.y <= pos.y - 400 + 25 + (a * 150) + 120 && timerClicked > 0.2 && (sf::Mouse::isButtonPressed(sf::Mouse::Left) || gp::Gamepad::isButtonPressed(0, gp::Gamepad::A)))
				{
					timerClicked = 0;
					nbPiece -= 3;
					_client.sendHeal((*i)->id);
					healMenu = false;
					cardUsingOpen = false;
				}
			}
			else
			{
				if (mapPixel.x >= pos.x - 600 && mapPixel.x <= pos.x - 600 + 600 && mapPixel.y >= pos.y - 400 + 25 + (a * 150) && mapPixel.y <= pos.y - 400 + 25 + (a * 150) + 120 && timerClicked > 0.2 && (sf::Mouse::isButtonPressed(sf::Mouse::Left) || gp::Gamepad::isButtonPressed(0, gp::Gamepad::A)))
				{
					timerClicked = 0;
					nbPiece -= 3;
					_client.sendHeal((*i)->id);
					healMenu = false;
					cardUsingOpen = false;
				}
			}

			a++;
		}
		i++;
	}
}

void Player::TakeSpdBoost()
{
	if (timerSpdBoost < dureSpdBonus && multiSpd != 1)
	{
		timerSpdBoost += tools::GetTimeDelta();
	}
	else
	{
		timerSpdBoost = 0;
		multiSpd = 1;
	}
}

Dir Player::getDirection()
{
	sf::Vector2f gamepadG{ 0,0 }; sf::Vector2f gamepadD{ 0,0 };
	gp::Gamepad::getSticksPosition(0, gamepadG, gamepadD);

	if (gamepadD.x < -50 && gamepadD.y>50) { return Dir::NORTH_WEST; }
	else if (gamepadD.x > 50 && gamepadD.y > 50) { return Dir::NORTH_EAST; }
	else if (gamepadD.x < -50 && gamepadD.y < -50) { return Dir::SOUTH_WEST; }
	else if (gamepadD.x > 50 && gamepadD.y < -50) { return Dir::SOUTH_EAST; }
	else if (gamepadD.x > 50) { return Dir::EAST; }
	else if (gamepadD.x < -50) { return Dir::WEST; }
	else if (gamepadD.y > 50) { return Dir::NORTH; }
	else if (gamepadD.y < -50) { return Dir::SOUTH; }
	else if (gamepadG.x < -50 && gamepadG.y>50) { return Dir::NORTH_WEST; }
	else if (gamepadG.x > 50 && gamepadG.y > 50) { return Dir::NORTH_EAST; }
	else if (gamepadG.x < -50 && gamepadG.y < -50) { return Dir::SOUTH_WEST; }
	else if (gamepadG.x > 50 && gamepadG.y < -50) { return Dir::SOUTH_EAST; }
	else if (gamepadG.x > 50) { return Dir::EAST; }
	else if (gamepadG.x < -50) { return Dir::WEST; }
	else if (gamepadG.y > 50) { return Dir::NORTH; }
	else if (gamepadG.y < -50) { return Dir::SOUTH; }
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z) && sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) { return Dir::NORTH_WEST; }
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z) && sf::Keyboard::isKeyPressed(sf::Keyboard::D)) { return Dir::NORTH_EAST; }
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z)) { return Dir::NORTH; }
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) { return Dir::SOUTH_WEST; }
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && sf::Keyboard::isKeyPressed(sf::Keyboard::D)) { return Dir::SOUTH_EAST; }
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) { return Dir::SOUTH; }
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) { return Dir::WEST; }
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) { return Dir::EAST; }
	else return playerDir;
}

void Player::powerActivation(CardsDied& _deck)
{
	/*if (_deck.getType() == CLOSERING)
	{

	}*/
}

void Player::initInventaire() {
	ttInventaire.loadFromFile("../Ressources/Textures/Inventaire.png");
	ssInventaire.setTexture(ttInventaire);
	ssInventaire.setScale(sf::Vector2f(0.80f, 0.80f));
	ssInventaire.setColor(sf::Color(255.0f, 255.0f, 255.0f, 225.0f));

	rInv.setPosition(positionrecBleuPlayer);
	rInv.setFillColor(sf::Color(255.0f, 255.0f, 255.0f, 225.0f));

	textureCaseInv.loadFromFile(TEXTURE_PATH"selectItem.png");
	spriteCaseInv.setTexture(textureCaseInv);
	spriteCaseInv.setPosition(positionCaseInv);
	spriteCaseInv.setScale(sf::Vector2f(0.8f, 0.8f));
	spriteCaseInv.setOrigin(sf::Vector2f(61.0f / 2.0f, 59.0f / 2.0f));

	textNbBombeImpulsif.setFont(font);
	textNbBombeImpulsif.setCharacterSize(20);
	textNbBombeImpulsif.setString("x" + std::to_string(nbBombeImpulsif));
	textNbBombeImpulsif.setFillColor(sf::Color::Green);

	textNbBombeArmure.setFont(font);
	textNbBombeArmure.setCharacterSize(20);
	textNbBombeArmure.setString("x" + std::to_string(nbBonusArmure));
	textNbBombeArmure.setFillColor(sf::Color::Green);

	textNbBombeHeal.setFont(font);
	textNbBombeHeal.setCharacterSize(20);
	textNbBombeHeal.setString("x" + std::to_string(nbBonusHeal));
	textNbBombeHeal.setFillColor(sf::Color::Green);

}

void Player::updateInventaire(){

	timerManette += tools::GetTimeDelta();
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1))
	{
		positionCaseInv.x = 1445.0f;
		NBSwitchItem = 1;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2))
	{
		positionCaseInv.x = 1529.0f;
		NBSwitchItem = 2;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3))
	{
		positionCaseInv.x = 1613.0f;
		NBSwitchItem = 3;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num4))
	{
		positionCaseInv.x = 1697.0f;
		NBSwitchItem = 4;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num5))
	{
		positionCaseInv.x = 1781.0f;
		NBSwitchItem = 5;
	}
	//manette bouton droit
	if(gp::Gamepad::isButtonPressed(0, gp::Gamepad::RB) && NBSwitchItem == 1 && timerManette > 0.3f)
	{
		positionCaseInv.x = 1529.0f;
		NBSwitchItem = 2;
		timerManette = 0.0f;
	}
	if (gp::Gamepad::isButtonPressed(0, gp::Gamepad::RB) && NBSwitchItem == 2 && timerManette > 0.3f)
	{
		positionCaseInv.x = 1613.0f;
		NBSwitchItem = 3;
		timerManette = 0.0f;
	}
	if (gp::Gamepad::isButtonPressed(0, gp::Gamepad::RB) && NBSwitchItem == 3 && timerManette > 0.3f)
	{
		positionCaseInv.x = 1697.0f;
		NBSwitchItem = 4;
		timerManette = 0.0f;
	}
	if (gp::Gamepad::isButtonPressed(0, gp::Gamepad::RB) && NBSwitchItem == 4 && timerManette > 0.3f)
	{
		positionCaseInv.x = 1781.0f;
		NBSwitchItem = 5;
		timerManette = 0.0f;
	}
	if (gp::Gamepad::isButtonPressed(0, gp::Gamepad::RB) && NBSwitchItem == 5 && timerManette > 0.3f)
	{
		positionCaseInv.x = 1445.0f;
		NBSwitchItem = 1;
		timerManette = 0.0f;
	}
	//manette bouton droit
	if (gp::Gamepad::isButtonPressed(0, gp::Gamepad::LB) && NBSwitchItem == 5 && timerManette > 0.3f)
	{
		positionCaseInv.x = 1697.0f;
		NBSwitchItem = 4;
		timerManette = 0.0f;
	}
	if (gp::Gamepad::isButtonPressed(0, gp::Gamepad::LB) && NBSwitchItem == 4 && timerManette > 0.3f)
	{
		positionCaseInv.x = 1613.0f;
		NBSwitchItem = 3;
		timerManette = 0.0f;
	}
	if (gp::Gamepad::isButtonPressed(0, gp::Gamepad::LB) && NBSwitchItem == 3 && timerManette > 0.3f)
	{
		positionCaseInv.x = 1529.0f;
		NBSwitchItem = 2;
		timerManette = 0.0f;
	}
	if (gp::Gamepad::isButtonPressed(0, gp::Gamepad::LB) && NBSwitchItem == 2 && timerManette > 0.3f)
	{
		positionCaseInv.x = 1445.0f;
		NBSwitchItem = 1;
		timerManette = 0.0f;
	}
	if (gp::Gamepad::isButtonPressed(0, gp::Gamepad::LB) && NBSwitchItem == 1 && timerManette > 0.3f)
	{
		positionCaseInv.x = 1781.0f;
		NBSwitchItem = 5;
		timerManette = 0.0f;
	}
}

void Player::DisplayInventaire(myWindow& _window) {
	posInv = _window.getRenderWindow().mapPixelToCoords(sf::Vector2i(1400, 900));
	//updateInventaire(_window);
	ssInventaire.setPosition(posInv);
	//rChoixObjet.setPosition(posChoixBombe);
	_window.Draw(ssInventaire);

	spriteCaseInv.setPosition(_window.getRenderWindow().mapPixelToCoords(sf::Vector2i(positionCaseInv.x, positionCaseInv.y)));
	_window.Draw(spriteCaseInv);

	//nb item

	textNbBombeImpulsif.setPosition(_window.getRenderWindow().mapPixelToCoords(sf::Vector2i(1519.0f, 946.0f)));
	_window.Draw(textNbBombeImpulsif);
	textNbBombeImpulsif.setString("x" + std::to_string(nbBombeImpulsif));

	textNbBombeArmure.setPosition(_window.getRenderWindow().mapPixelToCoords(sf::Vector2i(1687.0f, 946.0f)));
	_window.Draw(textNbBombeArmure);
	textNbBombeArmure.setString("x" + std::to_string(nbBonusArmure));

	textNbBombeHeal.setPosition(_window.getRenderWindow().mapPixelToCoords(sf::Vector2i(1771.0f, 946.0f)));
	_window.Draw(textNbBombeHeal);
	textNbBombeHeal.setString("x" + std::to_string(nbBonusHeal));

}

void Player::gainPiece()
{
	timerPc += tools::GetTimeDelta();
	if (timerPc > cooldawnPc)
	{
		nbPiece += 1;
		timerPc = 0;
	}
	if (nbPiece < 0)
	{
		nbPiece = 0;
		timerPc = 0.0f;
	}
}
