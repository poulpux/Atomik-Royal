#include "Bonus.h"
#include "Camera.h"
#include "Player.h"
#include "Bombe.h"
#include "Client.h"
#include "Sons.h"

Bonus::Bonus()
{
}

Bonus::Bonus(sf::Sprite _spriteBonusFeu, sf::Vector2f _positionBonusFeu, int _frameXBonus)
{
	spriteBonus = _spriteBonusFeu;
	positionBonusFeu = _positionBonusFeu;
	frameXBonus = _frameXBonus;
}

Bonus::~Bonus()
{
}

void Bonus::InitBonus()
{
	//Bonus feu
	textureBonus.loadFromFile(TEXTURE_PATH"BonusSpriteSheet.png");
	spriteBonus.setTexture(*textureBonusPOINT);
	spriteBonus.setTextureRect(intrectBonus);
	spriteBonus.setPosition(positionBonusFeu);
	spriteBonus.setScale(sf::Vector2f(0.8f,0.8f));
	spriteBonus.setOrigin(sf::Vector2f(36.0f / 2.0f, 36.0f / 2.0f));
}

void Bonus::UpdateBonus(myWindow& _window, Camera* _cam, Player* _p, Bombe* _bomb, Client* _client, SonMusique* _son)
{
	timerkey += tools::GetTimeDelta();
	sf::Vector2i mousePosition = sf::Mouse::getPosition(_window.getRenderWindow());
	sf::Vector2f mapPixel = _window.getRenderWindow().mapPixelToCoords(mousePosition, _cam->viewGame);
	/*if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad0) && timerkey > 0.2f)
	{
		BONUSFEU.push_back(new Bonus(spriteBonus, mapPixel,0));
		timerkey = 0.0f;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad1) && timerkey > 0.2f)
	{
		BONUSFEU.push_back(new Bonus(spriteBonus, mapPixel, 1));
		timerkey = 0.0f;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad2) && timerkey > 0.2f)
	{
		BONUSFEU.push_back(new Bonus(spriteBonus, mapPixel, 2));
		timerkey = 0.0f;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad3) && timerkey > 0.2f)
	{
		BONUSFEU.push_back(new Bonus(spriteBonus, mapPixel, 3));
		timerkey = 0.0f;
	}*/
	for (auto b : BONUSFEU)
	{
		b->UpdateSetBonus();

		auto i = _client->Ennemies.begin();
		auto n = _client->Ennemies.end();
		while (i != n)
		{
			if ((*i)->sprite.getGlobalBounds().intersects(b->spriteBonus.getGlobalBounds()) && b->frameXBonus == 0)
			{
				//_son->SEXPLOSIONCLASSIC.push_back(new SonMusique(7, b->positionBonusFeu, _son->soundExplosionClassic, _son->soundBombeNucleaire, _son->soundHit, _son->soundImpulsifExplosion, _son->soundBonusFlame, _son->soundBonusHeal, _son->soundKill, _son->soundRecupItem, _son->soundBonusShield, _son->soundBonusSpeed));
				b->IlifeVitesse -= 1;
			}
			if ((*i)->sprite.getGlobalBounds().intersects(b->spriteBonus.getGlobalBounds()) && b->frameXBonus == 1)
			{
				//_son->SEXPLOSIONCLASSIC.push_back(new SonMusique(7, b->positionBonusFeu, _son->soundExplosionClassic, _son->soundBombeNucleaire, _son->soundHit, _son->soundImpulsifExplosion, _son->soundBonusFlame, _son->soundBonusHeal, _son->soundKill, _son->soundRecupItem, _son->soundBonusShield, _son->soundBonusSpeed));
				b->IlifeVitesse -= 1;
			}
			if ((*i)->sprite.getGlobalBounds().intersects(b->spriteBonus.getGlobalBounds()) && b->frameXBonus == 2)
			{
				//_son->SEXPLOSIONCLASSIC.push_back(new SonMusique(7, b->positionBonusFeu, _son->soundExplosionClassic, _son->soundBombeNucleaire, _son->soundHit, _son->soundImpulsifExplosion, _son->soundBonusFlame, _son->soundBonusHeal, _son->soundKill, _son->soundRecupItem, _son->soundBonusShield, _son->soundBonusSpeed));
				b->IlifeVitesse -= 1;
			}
			if ((*i)->sprite.getGlobalBounds().intersects(b->spriteBonus.getGlobalBounds()) && b->frameXBonus == 3)
			{
				//_son->SEXPLOSIONCLASSIC.push_back(new SonMusique(7, b->positionBonusFeu, _son->soundExplosionClassic, _son->soundBombeNucleaire, _son->soundHit, _son->soundImpulsifExplosion, _son->soundBonusFlame, _son->soundBonusHeal, _son->soundKill, _son->soundRecupItem, _son->soundBonusShield, _son->soundBonusSpeed));
				b->IlifeVitesse -= 1;
			}
			i++;
		}

		if (_p->getPv() > 0)
		{
			if (_p->getBonusArmure() < 2)
			{
				if (_p->sprite.getGlobalBounds().intersects(b->spriteBonus.getGlobalBounds()) && b->frameXBonus == 0)
				{
					_p->UpbonusArmure();
					_son->SEXPLOSIONCLASSIC.push_back(new SonMusique(7, b->positionBonusFeu, _son->soundExplosionClassic, _son->soundBombeNucleaire, _son->soundHit, _son->soundImpulsifExplosion, _son->soundBonusFlame, _son->soundBonusHeal,_son->soundKill, _son->soundRecupItem, _son->soundBonusShield, _son->soundBonusSpeed));
					//std::cout << "Bouclier";
					b->IlifeVitesse -= 1;
				}
			}
			
			if (_p->sprite.getGlobalBounds().intersects(b->spriteBonus.getGlobalBounds()) && b->frameXBonus == 1)
			{
				_p->UpbonusSpd();
				_p->spdBonus();
				_son->SEXPLOSIONCLASSIC.push_back(new SonMusique(7, b->positionBonusFeu, _son->soundExplosionClassic, _son->soundBombeNucleaire, _son->soundHit, _son->soundImpulsifExplosion, _son->soundBonusFlame, _son->soundBonusHeal,_son->soundKill, _son->soundRecupItem, _son->soundBonusShield, _son->soundBonusSpeed));
				_son->SEXPLOSIONCLASSIC.push_back(new SonMusique(9, b->positionBonusFeu, _son->soundExplosionClassic, _son->soundBombeNucleaire, _son->soundHit, _son->soundImpulsifExplosion, _son->soundBonusFlame, _son->soundBonusHeal,_son->soundKill, _son->soundRecupItem, _son->soundBonusShield, _son->soundBonusSpeed));
				//std::cout << "Vitesse";
				b->IlifeVitesse -= 1;
			}
			if (_p->sprite.getGlobalBounds().intersects(b->spriteBonus.getGlobalBounds()) && b->frameXBonus == 2)
			{
				_bomb->bonusFlamme();
				_p->UpbonusFeu();
				_son->SEXPLOSIONCLASSIC.push_back(new SonMusique(7, b->positionBonusFeu, _son->soundExplosionClassic, _son->soundBombeNucleaire, _son->soundHit, _son->soundImpulsifExplosion, _son->soundBonusFlame, _son->soundBonusHeal,_son->soundKill, _son->soundRecupItem, _son->soundBonusShield, _son->soundBonusSpeed));
				_son->SEXPLOSIONCLASSIC.push_back(new SonMusique(5, b->positionBonusFeu, _son->soundExplosionClassic, _son->soundBombeNucleaire, _son->soundHit, _son->soundImpulsifExplosion, _son->soundBonusFlame, _son->soundBonusHeal,_son->soundKill, _son->soundRecupItem, _son->soundBonusShield, _son->soundBonusSpeed));
				//std::cout << "Feu";
				b->IlifeVitesse -= 1;
			}
			if (_p->getBonusHeal() < 3)
			{
				if (_p->sprite.getGlobalBounds().intersects(b->spriteBonus.getGlobalBounds()) && b->frameXBonus == 3)
				{
					_son->SEXPLOSIONCLASSIC.push_back(new SonMusique(7, b->positionBonusFeu, _son->soundExplosionClassic, _son->soundBombeNucleaire, _son->soundHit, _son->soundImpulsifExplosion, _son->soundBonusFlame, _son->soundBonusHeal,_son->soundKill, _son->soundRecupItem, _son->soundBonusShield, _son->soundBonusSpeed));
					_p->UpbonusHeal();
					//std::cout << "Vie";
					b->IlifeVitesse -= 1;
				}
			}
		}
	}
}

void Bonus::UpdateSetBonus()
{
	intrectBonus.left = frameXBonus * intrectBonus.width;
	spriteBonus.setTextureRect(intrectBonus);
}

void Bonus::DisplayBonus(myWindow* _window)
{
	for (auto b : BONUSFEU)
	{
		b->spriteBonus.setPosition(b->positionBonusFeu);
		_window->Draw(b->spriteBonus);
	}
	for (int i = 0; i < BONUSFEU.size(); i++)
	{
		if (BONUSFEU[i]->IlifeVitesse <= 0)
		{
			BONUSFEU.erase(BONUSFEU.begin() + i);
		}
	}

	/*for (unsigned int i = 0; i < BONUSFEU.size(); i++)
	{
		for (unsigned int j = 0; j < BONUSFEU.size(); j++)
		{
			if (BONUSFEU[i] != BONUSFEU[j]) {
				if (tools::Circle_Collision(BONUSFEU[i]->positionBonusFeu, BONUSFEU[j]->positionBonusFeu, 16, 16))
				{
					BONUSFEU[i]->positionBonusFeu.x += (BONUSFEU[i]->positionBonusFeu.x, BONUSFEU[j]->positionBonusFeu.y) - 250.0f;
					BONUSFEU[i]->positionBonusFeu.y += (BONUSFEU[i]->positionBonusFeu.x, BONUSFEU[j]->positionBonusFeu.y) - 250.0f;
				}
			}
		}
	}*/
}