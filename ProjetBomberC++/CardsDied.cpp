#include "CardsDied.h"
#include "Player.h"
#include"Killfield.h"
#include"Client.h"
#include "Sons.h"
CardsDied::CardsDied(typeCard _type)
{
	type = _type;
	if (/*type ==BOMBGIFT||*/type==HEAL||type==GIVESPDBOOST)
	{
		cost = 2;
	}
	/*else if (type ==SMOKE||type==CHASE||type==BOMBRAIN||type==SUPPLYDROP)
	{
		cost = 3;
	}*/
	//else if (type == CLOSERING /*|| type == DAYORNIGHT*/ /*|| type == BLOODMOOD*/)
	//{
	//	cost = 4;
	//}
	else if (/*type == SUDDENDEATH ||*/ type == ATOMIK)
	{
		cost = 5;
	}
}

CardsDied::CardsDied(sf::Sprite _spriteBombeAtomic,  sf::RectangleShape _recBombeAtomic, sf::Vector2f _positionAttention)
{
	spriteBombeAtomic = _spriteBombeAtomic;
	positionBombeAtomic.x = _positionAttention.x;
	positionBombeAtomic.y = _positionAttention.y - 1000.f;
	recBombeAtomic = _recBombeAtomic;

	positionrecBombeAtomic = _positionAttention;
	positionAttention = _positionAttention;

	afficheAttention = false;
	timerAttention = 0.0f;
	spdFireBall = 0.1;
	tpsTombe = 4.f;
	stopson = false;
}

CardsDied::CardsDied(sf::Sprite _spriteExplosionAtomic, sf::Vector2f _positionExplosionAtomic)
{
	spriteExplosionAtomic = _spriteExplosionAtomic;
	positionExplosionAtomic = _positionExplosionAtomic;
	spdFireBall = 200.f;
	tpsTombe = 6.f;
}

CardsDied::CardsDied(sf::Sprite _spriteFireball, sf::Vector2f _positionFireball, float _angleDirection)
{
	spriteFireball = _spriteFireball;
	positionFireball = _positionFireball;
	IlifeFireball = 1;
	angleDirection = _angleDirection;
	frameXFireball = 0;
	timerFireball = 0.0f;
	transparence = 255.0f;
	timerTombe = 0.0f;
	spdFireBall = 200.f;
	tpsTombe = 3.f;
}

void CardsDied::Init()
{
	defaultTexture.loadFromFile(RACCOURCI"default.png");
	textureCloseRing.loadFromFile(RACCOURCI"cardCloseRing.png");
	textureAcceleration.loadFromFile(RACCOURCI"acceleration.png");
	textureHeal.loadFromFile(RACCOURCI"heal.png");
	textureAtomik.loadFromFile(RACCOURCI"bombeH.png");
	textureBloodMoon.loadFromFile(RACCOURCI"bloodMoon.png");

	textureBombeAtomic.loadFromFile(TEXTURE_PATH"BombAtomic.png");
	spriteBombeAtomic.setTexture(*textureBombeAtomicPOINT);
	spriteBombeAtomic.setTextureRect(intrectBombeAtomic);
	spriteBombeAtomic.setPosition(positionBombeAtomic);
	spriteBombeAtomic.setOrigin(48.0f / 2.0f, 32.0f / 2.0f);
	spriteBombeAtomic.setScale(sf::Vector2f(8.0f, 8.0f));
	recBombeAtomic.setSize(sf::Vector2f(4.0f, 4.0f));
	recBombeAtomic.setFillColor(sf::Color::Red);

	textureExplosionAtomic.loadFromFile(TEXTURE_PATH"Explosion2.png");
	spriteExplosionAtomic.setTexture(*textureExplosionAtomicPOINT);
	spriteExplosionAtomic.setTextureRect(intrectExplosionAtomic);
	spriteExplosionAtomic.setPosition(positionExplosionAtomic);
	spriteExplosionAtomic.setOrigin(128.0f / 2.0f, 128.0f / 2.0f);
	spriteExplosionAtomic.setScale(sf::Vector2f(8.0f, 8.0f));

	textureAttention.loadFromFile(TEXTURE_PATH"Attention.png");
	spriteAttention.setTexture(textureAttention);
	spriteAttention.setPosition(positionAttention);
	spriteAttention.setScale(sf::Vector2f(53.0f, 53.0f));
	spriteAttention.setOrigin(sf::Vector2f(14.0f / 2.0f, 14.0f / 2.0f));
	spriteAttention.setColor(sf::Color(255.0f, 255.0f, 255.0f, 150.0f));

	textureFireball.loadFromFile(TEXTURE_PATH"FireBall.png");
	spriteFireball.setTexture(*textureFireballPOINT);
	spriteFireball.setPosition(positionFireball);
	spriteFireball.setTextureRect(intrectFireball);
	spriteFireball.setScale(sf::Vector2f(1.5f, 2.0f));
	spriteFireball.setOrigin(sf::Vector2f(96.0f / 2.0f, 48.0f / 2.0f));

	texturePiece.loadFromFile(TEXTURE_PATH"piece.png");
	spritePiece.setTexture(texturePiece);
	spritePiece.setPosition(positionPiece);
	spritePiece.setScale(sf::Vector2f(2.0f, 2.0f));
	spritePiece.setOrigin(sf::Vector2f(64.0f / 2.0f, 42.0f / 2.0f));

	fontPiece.loadFromFile(FONT_PATH"Typewriter.ttf");
	textPiece.setFont(fontPiece);
	textPiece.setFillColor(sf::Color::Black);
	textPiece.setCharacterSize(55);
	textPiece.setString("x" + std::to_string(NBpiece));
	textPiece.setPosition(positiontextPiece);
	spdFireBall = 200.f;
	tpsTombe = 3.f;
}

void CardsDied::UpdateDied(Player* _p, Killfield& _killou, Client& _client, SonMusique* _son)
{
	for (auto ba : BOMBEATOMIC)
	{
		ba->UpdateSetBombAtomic();
		if (ba->stopson == false)
		{
			_son->SEXPLOSIONCLASSIC.push_back(new SonMusique(2, ba->positionAttention, _son->soundExplosionClassic, _son->soundBombeNucleaire, _son->soundHit, _son->soundImpulsifExplosion, _son->soundBonusFlame, _son->soundBonusHeal, _son->soundKill, _son->soundRecupItem, _son->soundBonusShield, _son->soundBonusSpeed));
			ba->stopson = true;
		}		
	}
	for (auto ea : EXPLOSIONATOMIC)
	{
		ea->UpdateSetExplosionAtomic();
	}
	for (auto f : FIREBALL)
	{
		f->UpdateSetFireBall();
		if (f->spriteFireball.getGlobalBounds().intersects(_p->sprite.getGlobalBounds())&&_p->getPv()>0)
		{
			_son->SEXPLOSIONCLASSIC.push_back(new SonMusique(3, _p->pos, _son->soundExplosionClassic, _son->soundBombeNucleaire, _son->soundHit, _son->soundImpulsifExplosion, _son->soundBonusFlame, _son->soundBonusHeal, _son->soundKill, _son->soundRecupItem, _son->soundBonusShield, _son->soundBonusSpeed));
			_p->takeDmg(100);
			if (_p->getPv() < 1)
			{
				std::string a = "";
				_killou.killList.push_back(new Killfield(a, _client.pseudo));
				_client.sendDeath(a, _client.pseudo);
			}
		}
	}
}

void CardsDied::UpdateSetBombAtomic()
{
	timer += tools::GetTimeDelta();
	timerBombeAtomic += tools::GetTimeDelta();
	timerAttention += tools::GetTimeDelta();
	timerTombe += tools::GetTimeDelta();
	if (timerBombeAtomic >= 0.1f)
	{
		frameXbombeAtomic += 1;
		if (frameXbombeAtomic > 11)
		{
			frameXbombeAtomic = 0;
		}
		timerBombeAtomic = 0.0f;
	}
	intrectBombeAtomic.left = frameXbombeAtomic * intrectBombeAtomic.width;
	spriteBombeAtomic.setTextureRect(intrectBombeAtomic);
	if (timerTombe > 3.0f)
	{
		vitesseBombeAtomic.y += gravityBombeAtomic.y * tools::GetTimeDelta();
		positionBombeAtomic.y += vitesseBombeAtomic.y * tools::GetTimeDelta();
	}
	if (timer > 0.1f)
	{
		if (recBombeAtomic.getGlobalBounds().intersects(spriteBombeAtomic.getGlobalBounds()))
		{
			IlifeBombeAtomic -= 1;
		}
	}
	if (timerAttention > tpsTombe/10)
	{
		afficheAttention = !afficheAttention;
		timerAttention = 0.0f;
	}
}

void CardsDied::UpdateSetExplosionAtomic()
{
	timerExplosionAtomic += tools::GetTimeDelta();
	if (timerExplosionAtomic >= 0.065f)
	{
		frameXExplosionAtomic += 1;
		if (frameXExplosionAtomic > 12)
		{
			IlifeExplosionAtomic -= 1;
		}
		timerExplosionAtomic = 0.0f;
	}
	intrectExplosionAtomic.left = frameXExplosionAtomic * intrectExplosionAtomic.width;
	spriteExplosionAtomic.setTextureRect(intrectExplosionAtomic);
}

void CardsDied::UpdateSetFireBall()
{
	timerFireball += tools::GetTimeDelta();
	if (timerFireball >= 0.09f)
	{
		frameXFireball += 1;
		if (frameXFireball > 11)
		{
			frameXFireball = 0;
		}
		timerFireball = 0.0f;
	}
	intrectFireball.left = frameXFireball * intrectFireball.width;
	spriteFireball.setTextureRect(intrectFireball);

	positionFireball.x += cos((3.1416 / 180) * -angleDirection) * spdFireBall * tools::GetTimeDelta();
	positionFireball.y += sin((3.1416 / 180) * -angleDirection) * spdFireBall * tools::GetTimeDelta();

	if (transparence > 0.0f)
	{
		transparence -= 90.f * tools::GetTimeDelta();
	}	
	if (transparence <= 0.0f)
	{
		IlifeFireball -= 1;
	}
	spriteFireball.setColor(sf::Color(255.0f, 255.0f, 255.0f, transparence));
}

void CardsDied::DisplayBombeAtomic(myWindow* _window)
{
	for (auto ba : BOMBEATOMIC)
	{
		if (ba->afficheAttention == false)
		{
			spriteAttention.setPosition(ba->positionAttention);
			_window->Draw(spriteAttention);
		}		
		ba->spriteBombeAtomic.setRotation(90);
		ba->recBombeAtomic.setPosition(ba->positionrecBombeAtomic);
		ba->spriteBombeAtomic.setPosition(ba->positionBombeAtomic);
		if (ba->timerTombe > 3)
		{
			_window->Draw(ba->spriteBombeAtomic);
		}		
	}
	for (int i = 0; i < BOMBEATOMIC.size(); i++)
	{
		if (BOMBEATOMIC[i]->IlifeBombeAtomic <= 0)
		{
			EXPLOSIONATOMIC.push_back(new CardsDied(spriteExplosionAtomic, sf::Vector2f(BOMBEATOMIC[i]->positionBombeAtomic.x, BOMBEATOMIC[i]->positionBombeAtomic.y - 200.0f)));
			float angle = 0.0f;
			for (int p = 0; p < 20; p++)
			{
				FIREBALL.push_back(new CardsDied(spriteFireball, sf::Vector2f(BOMBEATOMIC[i]->positionBombeAtomic.x, BOMBEATOMIC[i]->positionBombeAtomic.y + 170.0f), angle));
				angle = angle + 20.0f;
			}
			

			BOMBEATOMIC.erase(BOMBEATOMIC.begin() + i);
		}
	}
	for (auto f : FIREBALL)
	{
		f->spriteFireball.setRotation(-f->angleDirection);
		f->spriteFireball.setPosition(f->positionFireball);
		_window->Draw(f->spriteFireball);
	}
	for (int i = 0; i < FIREBALL.size(); i++)
	{
		if (FIREBALL[i]->IlifeFireball <= 0)
		{
			FIREBALL.erase(FIREBALL.begin() + i);
		}
	}
	for (auto ea : EXPLOSIONATOMIC)
	{
		ea->spriteExplosionAtomic.setPosition(ea->positionExplosionAtomic);
		_window->Draw(ea->spriteExplosionAtomic);
	}
	for (int i = 0; i < EXPLOSIONATOMIC.size(); i++)
	{
		if (EXPLOSIONATOMIC[i]->IlifeExplosionAtomic <= 0)
		{
			EXPLOSIONATOMIC.erase(EXPLOSIONATOMIC.begin() + i);
		}
	}
}

void CardsDied::DisplayPiece(myWindow* _window, Player& _player)
{
	positiontextPiece = _window->getRenderWindow().mapPixelToCoords(sf::Vector2i(1800, 970));

	textPiece.setString("x" + std::to_string(_player.nbPiece));
	textPiece.setPosition(positiontextPiece);
	_window->Draw(textPiece);

	positionPiece = _window->getRenderWindow().mapPixelToCoords(sf::Vector2i(1720, 1000));
	spritePiece.setPosition(positionPiece);
	_window->Draw(spritePiece);
}

sf::Texture* CardsDied::getTextureCloseR(typeCard& _type)
{
	/*if (_type == CLOSERING) { return &textureCloseRing; }
	else */if (_type == GIVESPDBOOST) { return &textureAcceleration; }
	else if (_type == HEAL) { return &textureHeal; }
	//else if (_type == SUDDENDEATH) { return &textureSuddenDeath; }
	//else if (_type == BOMBGIFT) { return &textureBombGift; }
	//else if (_type == DAYORNIGHT) { return &textureDayOrNight; }
	//else if (_type == SMOKE) { return &textureSmoke; }
	else if (_type == ATOMIK) { return &textureAtomik; }
	//else if (_type == CHASE) { return &textureChase; }
	//else if (_type == BOMBRAIN) { return &textureBombRain; }
	//else if (_type == SUPPLYDROP) { return &textureSupplyDrop; }
	/*else if (_type == BLOODMOOD) { return &textureBloodMoon; }*/
	else
	{
		return &defaultTexture;
	}
}
