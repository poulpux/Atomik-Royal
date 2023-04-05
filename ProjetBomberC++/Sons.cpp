#include "Sons.h"
#include "Player.h"

SonMusique::SonMusique()
{
}

SonMusique::SonMusique(int _Son1, sf::Vector2f _positionSon, sf::Sound _soundExplosionClassic, sf::Sound _soundBombeNucleaire, sf::Sound _soundHit, sf::Sound _soundImpulsifExplosion, sf::Sound _soundBonusFlame, sf::Sound _soundBonusHeal, sf::Sound _soundKill, sf::Sound _soundRecupItem, sf::Sound _soundBonusShield, sf::Sound _soundBonusSpeed)
{
	Son1 = _Son1;
	positionSon = _positionSon;
	stopCreatSound = false;
	timerErase = 0.0f;
	IlfifeSound = 1;
	soundExplosionClassic = _soundExplosionClassic;
	soundBombeNucleaire = _soundBombeNucleaire;
	soundHit = _soundHit;
	soundImpulsifExplosion = _soundImpulsifExplosion;
	soundBonusFlame = _soundBonusFlame;
	soundBonusHeal = _soundBonusHeal;
	soundKill = _soundKill;
	soundRecupItem = _soundRecupItem;
	soundBonusShield = _soundBonusShield;
	soundBonusSpeed = _soundBonusSpeed;
}

SonMusique::~SonMusique()
{
}

void SonMusique::InitSon()
{
	bufferExplosionClassic.loadFromFile("..\\Ressources\\Sons\\BombClassicExplosion.wav");
	soundExplosionClassic.setBuffer(bufferExplosionClassic);

	bufferBombeNucleaire.loadFromFile("..\\Ressources\\Sons\\BombeNucleaire.wav");
	soundBombeNucleaire.setBuffer(bufferBombeNucleaire);

	bufferHit.loadFromFile("..\\Ressources\\Sons\\BombermanHit.wav");
	soundHit.setBuffer(bufferHit);

	bufferImpulsifExplosion.loadFromFile("..\\Ressources\\Sons\\BombImpulsifExplosion.wav");
	soundImpulsifExplosion.setBuffer(bufferImpulsifExplosion);

	bufferBonusFlame.loadFromFile("..\\Ressources\\Sons\\Flamme.wav");
	soundBonusFlame.setBuffer(bufferBonusFlame);

	bufferBonusHeal.loadFromFile("..\\Ressources\\Sons\\HealingBomberman.wav");
	soundBonusHeal.setBuffer(bufferBonusHeal);

	bufferKill.loadFromFile("..\\Ressources\\Sons\\KillBomberMan.wav");
	soundKill.setBuffer(bufferKill);

	bufferRecupItem.loadFromFile("..\\Ressources\\Sons\\RecupereItems.wav");
	soundRecupItem.setBuffer(bufferRecupItem);

	bufferBonusShield.loadFromFile("..\\Ressources\\Sons\\ShieldBomberman.wav");
	soundBonusShield.setBuffer(bufferBonusShield);

	bufferBonusSpeed.loadFromFile("..\\Ressources\\Sons\\SpeedBoost.wav");
	soundBonusSpeed.setBuffer(bufferBonusSpeed);
}

void SonMusique::SetVolume(sf::Music& _music)
{
	_music.setVolume(MusicVolume);
}

void SonMusique::SetSon(sf::Sound& _sound)
{
	_sound.setVolume(SonVolume);
}

void SonMusique::UpdateSound(Player* _player)
{
	for (auto enemi2TIR = SEXPLOSIONCLASSIC.begin(); enemi2TIR != SEXPLOSIONCLASSIC.end();)
	{
		(*enemi2TIR)->timerErase += tools::GetTimeDelta();
		if ((*enemi2TIR)->stopCreatSound == false)
		{
			if ((*enemi2TIR)->Son1 == 1)
			{
				(*enemi2TIR)->soundExplosionClassic.play();
				(*enemi2TIR)->stopCreatSound = true;
			}
			if ((*enemi2TIR)->Son1 == 2)
			{
				(*enemi2TIR)->soundBombeNucleaire.play();
				(*enemi2TIR)->stopCreatSound = true;
			}
			if ((*enemi2TIR)->Son1 == 3)
			{
				(*enemi2TIR)->soundHit.play();
				(*enemi2TIR)->stopCreatSound = true;
			}
			if ((*enemi2TIR)->Son1 == 4)
			{
				(*enemi2TIR)->soundImpulsifExplosion.play();
				(*enemi2TIR)->stopCreatSound = true;
			}
			if ((*enemi2TIR)->Son1 == 5)
			{
				(*enemi2TIR)->soundBonusFlame.play();
				(*enemi2TIR)->stopCreatSound = true;
			}
			if ((*enemi2TIR)->Son1 == 6)
			{
				(*enemi2TIR)->soundKill.play();
				(*enemi2TIR)->stopCreatSound = true;
			}
			if ((*enemi2TIR)->Son1 == 7)
			{
				(*enemi2TIR)->soundRecupItem.play();
				(*enemi2TIR)->stopCreatSound = true;
			}
			if ((*enemi2TIR)->Son1 == 8)
			{
				(*enemi2TIR)->soundBonusShield.play();
				(*enemi2TIR)->stopCreatSound = true;
			}
			if ((*enemi2TIR)->Son1 == 9)
			{
				(*enemi2TIR)->soundBonusSpeed.play();
				(*enemi2TIR)->stopCreatSound = true;
			}
			if ((*enemi2TIR)->Son1 == 10)
			{
				(*enemi2TIR)->soundBonusHeal.play();
				(*enemi2TIR)->stopCreatSound = true;
			}
		}
		if ((*enemi2TIR)->timerErase > 11.0f)
		{
			(*enemi2TIR)->IlfifeSound -= 1;
			(*enemi2TIR)->timerErase = 0.0f;
		}
		if (tools::distance((*enemi2TIR)->positionSon, _player->pos) < 500)
		{
			(*enemi2TIR)->soundExplosionClassic.setVolume(100 * (SonVolume / 100));
			(*enemi2TIR)->soundBombeNucleaire.setVolume(100 * (SonVolume / 100));
			(*enemi2TIR)->soundHit.setVolume(100* (SonVolume / 100));
			(*enemi2TIR)->soundImpulsifExplosion.setVolume(100 * (SonVolume / 100));
			(*enemi2TIR)->soundBonusFlame.setVolume(100 * (SonVolume / 100));
			(*enemi2TIR)->soundKill.setVolume(100 * (SonVolume / 100));
			(*enemi2TIR)->soundRecupItem.setVolume(100 * (SonVolume / 100));
			(*enemi2TIR)->soundBonusShield.setVolume(100 * (SonVolume / 100));
			(*enemi2TIR)->soundBonusSpeed.setVolume(100 * (SonVolume / 100));
			(*enemi2TIR)->soundBonusHeal.setVolume(100 * (SonVolume / 100));
		}
		else if (tools::distance((*enemi2TIR)->positionSon, _player->pos) < 2000)
		{
			(*enemi2TIR)->soundExplosionClassic.setVolume(100 * ((1 - abs(tools::distance((*enemi2TIR)->positionSon, _player->pos) / 1200))) * (SonVolume / 100));
			(*enemi2TIR)->soundBombeNucleaire.setVolume(100 * (1 - abs(tools::distance((*enemi2TIR)->positionSon, _player->pos) / 1600)) * (SonVolume / 100));
			(*enemi2TIR)->soundHit.setVolume(100 * (1 - abs(tools::distance((*enemi2TIR)->positionSon, _player->pos) / 1200)) * (SonVolume / 100));
			(*enemi2TIR)->soundImpulsifExplosion.setVolume(100 * (1 - abs(tools::distance((*enemi2TIR)->positionSon, _player->pos) / 1200)) * (SonVolume / 100));
			(*enemi2TIR)->soundBonusFlame.setVolume(100 * (1 - abs(tools::distance((*enemi2TIR)->positionSon, _player->pos) / 1200)) * (SonVolume / 100));
			(*enemi2TIR)->soundKill.setVolume(100 * (1 - abs(tools::distance((*enemi2TIR)->positionSon, _player->pos) / 1200)) * (SonVolume / 100));
			(*enemi2TIR)->soundRecupItem.setVolume(100 * (1 - abs(tools::distance((*enemi2TIR)->positionSon, _player->pos) / 1200)) * (SonVolume / 100));
			(*enemi2TIR)->soundBonusShield.setVolume(100 * (1 - abs(tools::distance((*enemi2TIR)->positionSon, _player->pos) / 1200)) * (SonVolume / 100));
			(*enemi2TIR)->soundBonusSpeed.setVolume(100 * (1 - abs(tools::distance((*enemi2TIR)->positionSon, _player->pos) / 1200)) * (SonVolume / 100));
			(*enemi2TIR)->soundBonusHeal.setVolume(100 * (1 - abs(tools::distance((*enemi2TIR)->positionSon, _player->pos) / 1200)) * (SonVolume / 100));
		}
		if (tools::distance((*enemi2TIR)->positionSon, _player->pos) > 1200)
		{
			(*enemi2TIR)->soundExplosionClassic.setVolume(0);
			(*enemi2TIR)->soundBombeNucleaire.setVolume(0);
			(*enemi2TIR)->soundHit.setVolume(0);
			(*enemi2TIR)->soundImpulsifExplosion.setVolume(0);
			(*enemi2TIR)->soundBonusFlame.setVolume(0);
			(*enemi2TIR)->soundKill.setVolume(0);
			(*enemi2TIR)->soundRecupItem.setVolume(0);
			(*enemi2TIR)->soundBonusShield.setVolume(0);
			(*enemi2TIR)->soundBonusSpeed.setVolume(0);
			(*enemi2TIR)->soundBonusHeal.setVolume(0);
		}

		if ((*enemi2TIR)->IlfifeSound <= 0)
		{
			delete* enemi2TIR;
			enemi2TIR = SEXPLOSIONCLASSIC.erase(enemi2TIR);
		}
		else
		{
			++enemi2TIR;
		}
	}
	/*for (auto& s : SEXPLOSIONCLASSIC)
	{
		if (s->stopCreatSound == false)
		{
			if (s->Son1 == 1)
			{
				s->soundExplosionClassic.play();
				s->stopCreatSound = true;
			}
			if (s->Son1 == 2)
			{
				s->soundBombeNucleaire.play();
				s->stopCreatSound = true;
			}
			if (s->Son1 == 3)
			{
				s->soundHit.play();
				s->stopCreatSound = true;
			}
			if (s->Son1 == 4)
			{
				s->soundImpulsifExplosion.play();
				s->stopCreatSound = true;
			}
			if (s->Son1 == 5)
			{
				s->soundBonusFlame.play();
				s->stopCreatSound = true;
			}
			if (s->Son1 == 6)
			{
				s->soundKill.play();
				s->stopCreatSound = true;
			}
			if (s->Son1 == 7)
			{
				s->soundRecupItem.play();
				s->stopCreatSound = true;
			}
			if (s->Son1 == 8)
			{
				s->soundBonusShield.play();
				s->stopCreatSound = true;
			}
			if (s->Son1 == 9)
			{
				s->soundBonusSpeed.play();
				s->stopCreatSound = true;
			}
			if (s->Son1 == 10)
			{
				s->soundBonusHeal.play();
				s->stopCreatSound = true;
			}			
		}
		s->timerErase += tools::GetTimeDelta();
		if (s->timerErase > 13.0f)
		{
			s->IlfifeSound -= 1;
			s->timerErase = 0.0f;
		}
	}
	for (int i = 0; i < SEXPLOSIONCLASSIC.size(); i++) 
	{
		if (SEXPLOSIONCLASSIC[i]->IlfifeSound <= 0) 
		{
			SEXPLOSIONCLASSIC.erase(SEXPLOSIONCLASSIC.begin() + i);
		}
	}
	if (SEXPLOSIONCLASSIC.size() > 0)
	{
		std::cout << SEXPLOSIONCLASSIC.size() << std::endl;
	}*/
	
}