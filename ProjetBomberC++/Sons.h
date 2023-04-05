#pragma once
#include "tools.h"
#include "stateManager.h"

extern float SonVolume;
extern float MusicVolume;
class Player;
class SonMusique {

public:

	SonMusique();
	SonMusique(int _Son1, sf::Vector2f _positionSon, sf::Sound _soundExplosionClassic, sf::Sound _soundBombeNucleaire, sf::Sound _soundHit, sf::Sound _soundImpulsifExplosion, sf::Sound _soundBonusFlame, sf::Sound _soundBonusHeal, sf::Sound _soundKill, sf::Sound _soundRecupItem, sf::Sound _soundBonusShield, sf::Sound _soundBonusSpeed);
	~SonMusique();

	void InitSon();
	void SetVolume(sf::Music& _music);
	void SetSon(sf::Sound& _sound);

	float GetVolumeSon() { return SonVolume; }
	void AddVolumeSon(float _Volume) { SonVolume += _Volume; }

	float GetVolumeMusique() { return MusicVolume; }
	void AddVolumeMusique(float _Volume) { MusicVolume += _Volume; }

	void UpdateSound(Player* _player);

	//explosion bombe classic
	sf::SoundBuffer bufferExplosionClassic;
	sf::Sound soundExplosionClassic;
	//bombe nucléaire
	sf::SoundBuffer bufferBombeNucleaire;
	sf::Sound soundBombeNucleaire;
	//bomberman hit
	sf::SoundBuffer bufferHit;
	sf::Sound soundHit;
	//bombe impulsif explo
	sf::SoundBuffer bufferImpulsifExplosion;
	sf::Sound soundImpulsifExplosion;
	//bonus flamme
	sf::SoundBuffer bufferBonusFlame;
	sf::Sound soundBonusFlame;
	//bonus healing
	sf::SoundBuffer bufferBonusHeal;
	sf::Sound soundBonusHeal;
	//kill
	sf::SoundBuffer bufferKill;
	sf::Sound soundKill;
	//recupe item
	sf::SoundBuffer bufferRecupItem;
	sf::Sound soundRecupItem;
	//bonusshield
	sf::SoundBuffer bufferBonusShield;
	sf::Sound soundBonusShield;
	//speedboost
	sf::SoundBuffer bufferBonusSpeed;
	sf::Sound soundBonusSpeed;

	std::vector<SonMusique*> SEXPLOSIONCLASSIC;
	int Son1;
	bool stopCreatSound = false;
	float timerErase = 0.0f;
	int IlfifeSound = 1;

	sf::Vector2f positionSon;
};

