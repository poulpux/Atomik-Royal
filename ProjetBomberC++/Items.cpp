#include "Items.h"
#include "Bonus.h"
#include "Camera.h"
#include "Player.h"
#include "Client.h"
#include "Sons.h"

Items::Items()
{
}

Items::Items(sf::Sprite _sprite, sf::Vector2f _pos, int _life)
{
	Scoffre = _sprite;
	PosCoffre = _pos;
	life = _life;
}

Items::Items(sf::Sprite _spriteItemExpulsif, sf::Vector2f _positionItemExpulsif, bool _plusOuMoin)
{
	spriteItemExpulsif = _spriteItemExpulsif;
	positionItemExpulsif = _positionItemExpulsif;
	IlifeItemExpulsif = 1;
	plusOuMoin = _plusOuMoin;
}

Items::~Items()
{
}

void Items::initItems()
{
	Tcoffre.loadFromFile(TEXTURE_PATH"Coffre.png");
	Scoffre.setTexture(Tcoffre);

	textureItemExpulsif.loadFromFile(TEXTURE_PATH"bombExpulsif.png");
	spriteItemExpulsif.setTexture(*textureItemExpulsifPOINT);
	spriteItemExpulsif.setPosition(positionItemExpulsif);
	spriteItemExpulsif.setOrigin(22.0f / 2.0f, 12.0f / 2.0f);
	spriteItemExpulsif.setScale(sf::Vector2f(1.5f, 1.5f));

	degaeItem = false;
}

void Items::updateItems(myWindow& window, Camera* _cam, Player* _p, Client* _client, SonMusique* _son)
{
	TimerItems += tools::GetTimeDelta();

	sf::Vector2i mousePosition = sf::Mouse::getPosition(window.getRenderWindow());
	sf::Vector2f mapPixel = window.getRenderWindow().mapPixelToCoords(mousePosition, _cam->viewGame);

	for (auto i : ITEMEXPULSIF) //Update des impulsive quand elles sont au sol, si le joueur va dessus, il les ramasse, si c'est un ennemi qui va dessus, elles disparaissent
	{
		auto u = _client->Ennemies.begin();
		auto n = _client->Ennemies.end();
		while (u != n)
		{
			if ((*u)->sprite.getGlobalBounds().intersects(i->spriteItemExpulsif.getGlobalBounds()))
			{
				if (!(*u)->dead)
				{
					i->IlifeItemExpulsif -= 1;
				}
			}
			u++;
		}
		if (_p->sprite.getGlobalBounds().intersects(i->spriteItemExpulsif.getGlobalBounds()))
		{
			if (_p->getPv() > 0 && _p->getState() == state::PLAYER)
			{
				_son->SEXPLOSIONCLASSIC.push_back(new SonMusique(7, _p->pos, _son->soundExplosionClassic, _son->soundBombeNucleaire, _son->soundHit, _son->soundImpulsifExplosion, _son->soundBonusFlame, _son->soundBonusHeal, _son->soundKill, _son->soundRecupItem, _son->soundBonusShield, _son->soundBonusSpeed));
				if (i->plusOuMoin == false)
				{
					_p->UpBombeImpulsif();
					i->IlifeItemExpulsif -= 1;
				}
				if (i->plusOuMoin == true)
				{
					_p->UpBombeImpulsif2();
					i->IlifeItemExpulsif -= 1;
				}
			}
		}
	}
}

void Items::displayItems(myWindow& window, Bonus* _bonus)
{
	//Display des impulsives
	for (auto i : ITEMEXPULSIF)
	{
		i->spriteItemExpulsif.setPosition(i->positionItemExpulsif);
		window.Draw(i->spriteItemExpulsif);
	}
	for (int i = 0; i < ITEMEXPULSIF.size(); i++)
	{
		if (ITEMEXPULSIF[i]->IlifeItemExpulsif <= 0) {
			ITEMEXPULSIF.erase(ITEMEXPULSIF.begin() + i);
		}
	}
}