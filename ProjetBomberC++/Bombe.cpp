#include"Bombe.h"
#include"Map.h"
#include "Items.h"
#include"Client.h"
#include"Player.h"
#include"Killfield.h"
#include "Sons.h"
Bombe::Bombe()
{
}

Bombe::Bombe(sf::Vector2f _pos)
{
	//équilibrage

	//------------------------------------------------------
	tpsForExplo = 1.5;
	tpsExplo = 0.3;
	dmgBombeClassic = 25.f;
	//------------------------------------------------------
	pos = _pos;

	modele.setFillColor(sf::Color::Black);
	modele.setSize(sf::Vector2f(32, 32));
	modele.setPosition(pos);
}

Bombe::Bombe(sf::Vector2f _pos, int& _id, int& _nbFlamme)
{
	//équilibrage

	//------------------------------------------------------
	tpsForExplo = 1.2;
	tpsExplo = 0.6;
	dmgBombeClassic = 25.f;
	//------------------------------------------------------
	pos = _pos;
	id = _id;
	modele.setFillColor(sf::Color::Black);
	modele.setSize(sf::Vector2f(32, 32));
	modele.setPosition(pos);

	nbFlamme = _nbFlamme;
	stop = false;
}

//bombe expulsif
Bombe::Bombe(sf::Sprite _spriteBombeExpulsif, sf::Vector2f _positionBombeExpulsif, sf::RectangleShape _recExpulsif, sf::Vector2f _positionExpulsif, int& _id)
{
	spriteBombeExpulsif = _spriteBombeExpulsif;
	positionBombeExpulsif = _positionBombeExpulsif;
	recExpulsif = _recExpulsif;
	positionExpulsif = _positionExpulsif;
	timer = 0.0f;
	id = _id;
}

Bombe::Bombe(sf::Sprite _spriteExplosionExpulsif, sf::Vector2f _positionExplosionExpulsif, int _IlifeExplosionExpulsif, int _prout)
{
	spriteExplosionExpulsif = _spriteExplosionExpulsif;
	positionExplosionExpulsif = _positionExplosionExpulsif;
	IlifeExplosionExpulsif = _IlifeExplosionExpulsif;
	prout = _prout;
}

void Bombe::InitBomb()
{
	textureBombeExpulsif.loadFromFile(TEXTURE_PATH"BombeExpulsif.png");
	spriteBombeExpulsif.setTexture(*textureBombeExpulsifPOINT);
	spriteBombeExpulsif.setTextureRect(intrectBombeExpulsif);
	spriteBombeExpulsif.setPosition(positionBombeExpulsif);
	spriteBombeExpulsif.setOrigin(22.0f / 2.0f, 12.0f / 2.0f);
	spriteBombeExpulsif.setScale(sf::Vector2f(1.5f, 1.5f));
	recExpulsif.setSize(sf::Vector2f(5.0f, 5.0f));
	recExpulsif.setFillColor(sf::Color::Red);

	textureExplosionExpulsif.loadFromFile(TEXTURE_PATH"Explosion3.png");
	spriteExplosionExpulsif.setTexture(*textureExplosionExpulsifPOINT);
	spriteExplosionExpulsif.setTextureRect(intrectExplosionExpulsif);
	spriteExplosionExpulsif.setPosition(positionExplosionExpulsif);
	spriteExplosionExpulsif.setScale(sf::Vector2f(1.6f, 1.6f));
	spriteExplosionExpulsif.setOrigin(64.0f / 2.0f, 64.0f / 2.0f);

	nbFlamme = 1;
}

void Bombe::Update(Map& _map, Items* _item, Client& _client, Player& _player, Killfield& _killou, SonMusique* _son)
{
	auto i = listeBombe.begin(); auto n = listeBombe.end();
	while (i!=n)
	{
		(*i)->timerB += tools::GetTimeDelta();
		(*i)->avExplo(_map, _item, nbFlamme,_player, _killou, _client, (*i)->pos,_son);
		
		//Collisions entre les bombes
		auto j = listeBombe.begin(); auto q = listeBombe.end();
		while (j!=q)
		{
			auto ii = (*j)->listTouche.begin(); auto nn = (*j)->listTouche.end();
			while (ii != nn)
			{
				if ((*i)->modele.getPosition() == (*ii).getPosition() &&!(*i)->isEnclenched)
				{
					(*i)->timerB = (*i)->tpsForExplo;
					(*i)->isEnclenched = true;
				}
				ii++;
			}
			j++;
		}
		auto i2 = _client.Ennemies.begin(); auto n2 = _client.Ennemies.end();
		while (i2!=n2)
		{
			auto j2 = (*i2)->ennemyBomb.begin(); auto q2 = (*i2)->ennemyBomb.end();
			while (j2 != q2)
			{
				auto ii2 = (*j2)->listTouche.begin(); auto nn2 = (*j2)->listTouche.end();
				while (ii2 != nn2)
				{
					if ((*j2)->modele.getPosition() == (*ii2).getPosition() && !(*j2)->isEnclenched)
					{
						(*j2)->timerB = (*j2)->tpsForExplo;
						(*j2)->isEnclenched = true;
					}
					ii2++;
				}
				j2++;
			}
			i2++;
		}

		if ((*i)->aExplo)
		{
			delete (*i);
			i = listeBombe.erase(i);
		}
		else
		{
			i++;
		}
	}

	auto j = _client.Ennemies.begin(); auto q = _client.Ennemies.end();
	while (j!=q)
	{
		auto r = (*j)->ennemyBomb.begin(); auto l = (*j)->ennemyBomb.end();
		while (r!=l)
		{
			(*r)->timerB += tools::GetTimeDelta();
			(*r)->avExplo(_map, _item, (*r)->nbFlamme, _player, _killou, _client,(*r)->pos, _son);
			if ((*r)->aExplo)
			{
				delete (*r);
				r = listeBombe.erase(r);
			}
			else
			{
				r++;
			}
		}

		for (auto be : (*j)->ennemyImpuls)
		{
			be->UpdateSetBombeExpulsif();
			if (be->timer > 0.1f)
			{
				for (auto m : _map.MAP)
				{
					if ((be->recExpulsif.getGlobalBounds().intersects(be->spriteBombeExpulsif.getGlobalBounds())) || m->SpriteTile.getGlobalBounds().intersects(be->spriteBombeExpulsif.getGlobalBounds()))
					{
						be->IlifeBombeExpulsif -= 1;
					}
				}
			}
		}
		for (auto ee : (*j)->ennemyExploImpuls)
		{
			ee->UpdateSetExplsionExpulsif();
			if (ee->spriteExplosionExpulsif.getGlobalBounds().intersects(_player.sprite.getGlobalBounds()) && !ee->hasItPlayer && _player.getPv() > 0)
			{
				_son->SEXPLOSIONCLASSIC.push_back(new SonMusique(3, ee->positionExplosionExpulsif, _son->soundExplosionClassic, _son->soundBombeNucleaire, _son->soundHit, _son->soundImpulsifExplosion, _son->soundBonusFlame, _son->soundBonusHeal, _son->soundKill, _son->soundRecupItem, _son->soundBonusShield, _son->soundBonusSpeed));
				_player.takeDmg(25);
				ee->hasItPlayer = true;
				if (_player.getPv() < 1)
				{
					std::string a = "";
					
					a = (*j)->username;
					_killou.killList.push_back(new Killfield(a, _client.pseudo));
					_client.sendDeath(a, _client.pseudo);
				}
			}
		}




		j++;
	}
	for (auto be : BOMBEEXPULSIF)
	{
		be->UpdateSetBombeExpulsif();
		if (be->timer > 0.1f)
		{
			for (auto m : _map.MAP)
			{
				if ((be->recExpulsif.getGlobalBounds().intersects(be->spriteBombeExpulsif.getGlobalBounds())) || m->SpriteTile.getGlobalBounds().intersects(be->spriteBombeExpulsif.getGlobalBounds()))
				{
					be->IlifeBombeExpulsif -= 1;
				}
			}
		}
	}
	for (auto ee : EXPLOSIONEXPULSIF)
	{
		ee->UpdateSetExplsionExpulsif();
		if (ee->spriteExplosionExpulsif.getGlobalBounds().intersects(_player.sprite.getGlobalBounds()) && !ee->hasItPlayer&&_player.getPv()>0)
		{
			_son->SEXPLOSIONCLASSIC.push_back(new SonMusique(3, ee->positionExplosionExpulsif, _son->soundExplosionClassic, _son->soundBombeNucleaire, _son->soundHit, _son->soundImpulsifExplosion, _son->soundBonusFlame, _son->soundBonusHeal, _son->soundKill, _son->soundRecupItem, _son->soundBonusShield, _son->soundBonusSpeed));
			_player.takeDmg(25);
			ee->hasItPlayer = true;
			if (_player.getPv() < 1)
			{
				std::string a = "";
				if (id != -1)
				{
					auto i = _client.Ennemies.begin(); auto n = _client.Ennemies.end();
					while (i != n)
					{
						if ((*i)->id == id)
						{
							a = (*i)->username;
						}
						i++;
					}
				}
				_killou.killList.push_back(new Killfield(a, _client.pseudo));
				_client.sendDeath(a, _client.pseudo);
			}
		}
	}
}

void Bombe::avExplo(Map& _map, Items* _item, int _nbFlamme,Player& _player, Killfield& _killou, Client& _client, sf::Vector2f _pos, SonMusique* _son)
{
	auto u = _client.Ennemies.begin();
	auto n = _client.Ennemies.end();
	if (timerB < tpsForExplo)
	{
		modele.setFillColor(sf::Color::Black);
	}
	else if (timerB >= tpsForExplo&&timerB<tpsForExplo+tpsExplo&& !exploPush)
	{
		modele.setFillColor(sf::Color::Red);
		
		for (size_t i = 0; i < 4; i++)
		{
			for (size_t j = 1; j < _nbFlamme + 1; j++)
			{
				sf::Vector2f posTemps;
				if (i == 0)
				{
					posTemps = sf::Vector2f(pos.x - 32 * j + 16, pos.y + 16);     //colonne de gauche
					if (stop == false)
					{
						_son->SEXPLOSIONCLASSIC.push_back(new SonMusique(1, posTemps, _son->soundExplosionClassic, _son->soundBombeNucleaire, _son->soundHit, _son->soundImpulsifExplosion, _son->soundBonusFlame, _son->soundBonusHeal, _son->soundKill, _son->soundRecupItem, _son->soundBonusShield, _son->soundBonusSpeed));
						stop = true;
					}
					if (_map.collisionBombe(posTemps) == true) arret = true;
					if (!arret)
					{
						sf::RectangleShape a = modele;
						a.setPosition(posTemps.x - 16, posTemps.y - 16);
						listTouche.push_back(a);
					}
				}
				else if (i == 1)
				{
					posTemps = sf::Vector2f(pos.x + 16, pos.y - 32 * j + 16);       //colonne du haut
					if (_map.collisionBombe(posTemps) == true) arret = true;
					if (!arret)
					{
						sf::RectangleShape a = modele;
						a.setPosition(posTemps.x - 16, posTemps.y - 16);
						listTouche.push_back(a);
						/*for (int i = 0; i < _map.MAPCOFFRE.size(); i++)
						{
							if (a.getGlobalBounds().intersects(_map.MAPCOFFRE[i]->SpriteTileCoffre.getGlobalBounds()))
							{
								_map.MAPCOFFRE[i]->IlifeTileCoffre -= 1;
							}
						}
						if (a.getGlobalBounds().intersects(_player.sprite.getGlobalBounds()) && !hasItPlayer && _player.getPv() >= 1)
						{
							_son->SEXPLOSIONCLASSIC.push_back(new SonMusique(3, posTemps, _son->soundExplosionClassic, _son->soundBombeNucleaire, _son->soundHit, _son->soundImpulsifExplosion, _son->soundBonusFlame, _son->soundBonusHeal, _son->soundKill, _son->soundRecupItem, _son->soundBonusShield, _son->soundBonusSpeed));
							_player.takeDmg(dmgBombeClassic);
							if (_player.getPv() < 1)
							{
								std::string a = "";
								if (id != -1)
								{
									auto i = _client.Ennemies.begin(); auto n = _client.Ennemies.end();
									while (i != n)
									{
										if ((*i)->id == id)
										{
											a = (*i)->username;
										}
										i++;
									}
								}
								_killou.killList.push_back(new Killfield(a, _client.pseudo));
								_client.sendDeath(a, _client.pseudo);
								_son->SEXPLOSIONCLASSIC.push_back(new SonMusique(6, posTemps, _son->soundExplosionClassic, _son->soundBombeNucleaire, _son->soundHit, _son->soundImpulsifExplosion, _son->soundBonusFlame, _son->soundBonusHeal, _son->soundKill, _son->soundRecupItem, _son->soundBonusShield, _son->soundBonusSpeed));
							}
							hasItPlayer = true;
						}
						while (u != n)
						{
							if ((*u)->sprite.getGlobalBounds().intersects(a.getGlobalBounds()) && !hasItPlayer)
							{
								_son->SEXPLOSIONCLASSIC.push_back(new SonMusique(3, posTemps, _son->soundExplosionClassic, _son->soundBombeNucleaire, _son->soundHit, _son->soundImpulsifExplosion, _son->soundBonusFlame, _son->soundBonusHeal, _son->soundKill, _son->soundRecupItem, _son->soundBonusShield, _son->soundBonusSpeed));
								hasItPlayer = true;
							}
							u++;
						}*/
					}
				}
				else if (i == 2)
				{
					posTemps = sf::Vector2f(pos.x + 16, pos.y + 32 * j + 16);    //colonne de gauche
					if (_map.collisionBombe(posTemps) == true) arret = true;
					if (!arret)
					{
						sf::RectangleShape a = modele;
						a.setPosition(posTemps.x - 16, posTemps.y - 16);
						listTouche.push_back(a);
						/*for (int i = 0; i < _map.MAPCOFFRE.size(); i++)
						{
							if (a.getGlobalBounds().intersects(_map.MAPCOFFRE[i]->SpriteTileCoffre.getGlobalBounds()))
							{
								_map.MAPCOFFRE[i]->IlifeTileCoffre -= 1;
							}
							if (a.getGlobalBounds().intersects(_player.sprite.getGlobalBounds()) && !hasItPlayer && _player.getPv() >= 1)
							{
								_son->SEXPLOSIONCLASSIC.push_back(new SonMusique(3, posTemps, _son->soundExplosionClassic, _son->soundBombeNucleaire, _son->soundHit, _son->soundImpulsifExplosion, _son->soundBonusFlame, _son->soundBonusHeal, _son->soundKill, _son->soundRecupItem, _son->soundBonusShield, _son->soundBonusSpeed));
								_player.takeDmg(dmgBombeClassic);
								if (_player.getPv() < 1)
								{
									std::string a = "";
									if (id != -1)
									{
										auto i = _client.Ennemies.begin(); auto n = _client.Ennemies.end();
										while (i != n)
										{
											if ((*i)->id == id)
											{
												a = (*i)->username;
											}
											i++;
										}
									}
									_killou.killList.push_back(new Killfield(a, _client.pseudo));
									_client.sendDeath(a, _client.pseudo);
									_son->SEXPLOSIONCLASSIC.push_back(new SonMusique(6, posTemps, _son->soundExplosionClassic, _son->soundBombeNucleaire, _son->soundHit, _son->soundImpulsifExplosion, _son->soundBonusFlame, _son->soundBonusHeal, _son->soundKill, _son->soundRecupItem, _son->soundBonusShield, _son->soundBonusSpeed));
								}
								hasItPlayer = true;
							}
							while (u != n)
							{
								if ((*u)->sprite.getGlobalBounds().intersects(a.getGlobalBounds()) && !hasItPlayer)
								{
									_son->SEXPLOSIONCLASSIC.push_back(new SonMusique(3, posTemps, _son->soundExplosionClassic, _son->soundBombeNucleaire, _son->soundHit, _son->soundImpulsifExplosion, _son->soundBonusFlame, _son->soundBonusHeal, _son->soundKill, _son->soundRecupItem, _son->soundBonusShield, _son->soundBonusSpeed));
									hasItPlayer = true;
								}
								u++;
							}
						}*/
					}
				}
				else if (i == 3)
				{
					posTemps = sf::Vector2f(pos.x + 16 + 32 * j, pos.y + 16);     //colonne de gauche
					if (_map.collisionBombe(posTemps) == true) arret = true;
					if (!arret)
					{
						sf::RectangleShape a = modele;
						a.setPosition(posTemps.x - 16, posTemps.y - 16);
						listTouche.push_back(a);
						/*for (int i = 0; i < _map.MAPCOFFRE.size(); i++)
						{
							if (a.getGlobalBounds().intersects(_map.MAPCOFFRE[i]->SpriteTileCoffre.getGlobalBounds()))
							{
								_map.MAPCOFFRE[i]->IlifeTileCoffre -= 1;
							}
							if (a.getGlobalBounds().intersects(_player.sprite.getGlobalBounds()) && !hasItPlayer &&_player.getPv() >= 1)
							{
								_son->SEXPLOSIONCLASSIC.push_back(new SonMusique(3, posTemps,_son->soundExplosionClassic, _son->soundBombeNucleaire, _son->soundHit, _son->soundImpulsifExplosion, _son->soundBonusFlame, _son->soundBonusHeal, _son->soundKill, _son->soundRecupItem, _son->soundBonusShield, _son->soundBonusSpeed));
								_player.takeDmg(dmgBombeClassic);
								if (_player.getPv() < 1)
								{
									std::string a = "";
									if (id != -1)
									{
										auto i = _client.Ennemies.begin(); auto n = _client.Ennemies.end();
										while (i != n)
										{
											if ((*i)->id == id)
											{
												a = (*i)->username;
											}
											i++;
										}
									}
									_killou.killList.push_back(new Killfield(a, _client.pseudo));
									_client.sendDeath(a, _client.pseudo);
									_son->SEXPLOSIONCLASSIC.push_back(new SonMusique(6, posTemps, _son->soundExplosionClassic, _son->soundBombeNucleaire, _son->soundHit, _son->soundImpulsifExplosion, _son->soundBonusFlame, _son->soundBonusHeal, _son->soundKill, _son->soundRecupItem, _son->soundBonusShield, _son->soundBonusSpeed));
								}
								hasItPlayer = true;
							}
							while (u != n)
							{
								if ((*u)->sprite.getGlobalBounds().intersects(a.getGlobalBounds()) && !hasItPlayer)
								{
									_son->SEXPLOSIONCLASSIC.push_back(new SonMusique(3, posTemps, _son->soundExplosionClassic, _son->soundBombeNucleaire, _son->soundHit, _son->soundImpulsifExplosion, _son->soundBonusFlame, _son->soundBonusHeal, _son->soundKill, _son->soundRecupItem, _son->soundBonusShield, _son->soundBonusSpeed));
									hasItPlayer = true;
								}
								u++;
							}
						}		*/			
					}
				}
				arret = false;
			}
			exploPush = true;
		}
	}
	else if (timerB > tpsForExplo + tpsExplo)
	{
		aExplo = true;
	}

	auto p = listTouche.begin(); auto m = listTouche.end();
	while (p!=m)
	{
		if (stop == false)
		{
			_son->SEXPLOSIONCLASSIC.push_back(new SonMusique(1, pos, _son->soundExplosionClassic, _son->soundBombeNucleaire, _son->soundHit, _son->soundImpulsifExplosion, _son->soundBonusFlame, _son->soundBonusHeal, _son->soundKill, _son->soundRecupItem, _son->soundBonusShield, _son->soundBonusSpeed));
			stop = true;
		}
		
		for (int i = 0; i < _map.MAPCOFFRE.size(); i++)
		{
			if ((*p).getGlobalBounds().intersects(_map.MAPCOFFRE[i]->SpriteTileCoffre.getGlobalBounds()))
			{
				_map.MAPCOFFRE[i]->IlifeTileCoffre -= 1;
			}
		}
		if ((*p).getGlobalBounds().intersects(_player.sprite.getGlobalBounds()) && !hasItPlayer && _player.getPv() >= 1)
		{
			_son->SEXPLOSIONCLASSIC.push_back(new SonMusique(3, pos, _son->soundExplosionClassic, _son->soundBombeNucleaire, _son->soundHit, _son->soundImpulsifExplosion, _son->soundBonusFlame, _son->soundBonusHeal, _son->soundKill, _son->soundRecupItem, _son->soundBonusShield, _son->soundBonusSpeed));
			_player.takeDmg(dmgBombeClassic);
			if (_player.getPv() < 1)
			{
				std::string a = "";
				if (id != -1)
				{
					auto i = _client.Ennemies.begin(); auto n = _client.Ennemies.end();
					while (i != n)
					{
						if ((*i)->id == id)
						{
							a = (*i)->username;
						}
						i++;
					}
				}
				_killou.killList.push_back(new Killfield(a, _client.pseudo));
				_client.sendDeath(a, _client.pseudo);
				_son->SEXPLOSIONCLASSIC.push_back(new SonMusique(6, pos, _son->soundExplosionClassic, _son->soundBombeNucleaire, _son->soundHit, _son->soundImpulsifExplosion, _son->soundBonusFlame, _son->soundBonusHeal, _son->soundKill, _son->soundRecupItem, _son->soundBonusShield, _son->soundBonusSpeed));
			}
			hasItPlayer = true;
		}
		while (u != n)
		{
			if ((*u)->sprite.getGlobalBounds().intersects((*p).getGlobalBounds()) && !hasItPlayer)
			{
				_son->SEXPLOSIONCLASSIC.push_back(new SonMusique(3, pos, _son->soundExplosionClassic, _son->soundBombeNucleaire, _son->soundHit, _son->soundImpulsifExplosion, _son->soundBonusFlame, _son->soundBonusHeal, _son->soundKill, _son->soundRecupItem, _son->soundBonusShield, _son->soundBonusSpeed));
				hasItPlayer = true;
			}
			u++;
		}
		
		p++;
	}
}

void Bombe::UpdateSetBombeExpulsif()
{
	timer += tools::GetTimeDelta();
	timerBombeExpulsif += tools::GetTimeDelta();
	if (timerBombeExpulsif > 0.09f)
	{
		frameXbombeExpulsif += 1;
		if (frameXbombeExpulsif > 11)
		{
			frameXbombeExpulsif = 0;
		}
		timerBombeExpulsif = 0.0f;
	}
	intrectBombeExpulsif.left = frameXbombeExpulsif * intrectBombeExpulsif.width;
	spriteBombeExpulsif.setTextureRect(intrectBombeExpulsif);

	sf::Vector2f vector;
	float norme;
	vector.x = positionExpulsif.x - positionBombeExpulsif.x;
	vector.y = positionExpulsif.y - positionBombeExpulsif.y;
	norme = sqrt(vector.x * vector.x + vector.y * vector.y);
	vitesseBombeExpulsif.x = 800 * (vector.x / norme);
	vitesseBombeExpulsif.y = 800 * (vector.y / norme);
	positionBombeExpulsif.x += vitesseBombeExpulsif.x * tools::GetTimeDelta();
	positionBombeExpulsif.y += vitesseBombeExpulsif.y * tools::GetTimeDelta();
}

void Bombe::UpdateSetExplsionExpulsif()
{
	timerExplosionExpulsif += tools::GetTimeDelta();
	if (timerExplosionExpulsif >= 0.07)
	{
		frameXExplosionExpulsif += 1;
		if (frameXExplosionExpulsif > 15)
		{
			IlifeExplosionExpulsif -= 1;
		}
		timerExplosionExpulsif = 0.0f;
	}
	intrectExplosionExpulsif.left = frameXExplosionExpulsif * intrectExplosionExpulsif.width;
	spriteExplosionExpulsif.setTextureRect(intrectExplosionExpulsif);
}

void Bombe::Display(myWindow& _window, Client& _client, SonMusique* _son)
{
	auto i = listeBombe.begin(); auto n = listeBombe.end();
	while (i!=n)
	{
		_window.Draw((*i)->modele);
		auto j = (*i)->listTouche.begin(); auto q = (*i)->listTouche.end();
		while (j!=q)
		{
			_window.Draw((*j));
			j++;
		}
		i++;
	}
	auto w = _client.Ennemies.begin(); auto z = _client.Ennemies.end();
	while (w != z)
	{
		auto r = (*w)->ennemyBomb.begin(); auto l = (*w)->ennemyBomb.end();
		while (r != l)
		{
			_window.Draw((*r)->modele);
			for ( auto k : (*r)->listTouche)
			{
				_window.Draw(k);
			}
			r++;
		}
		for (auto h : (*w)->ennemyImpuls)
		{
			h->recExpulsif.setPosition(h->positionExpulsif);
			h->spriteBombeExpulsif.setPosition(h->positionBombeExpulsif);
			_window.Draw(h->spriteBombeExpulsif);
		}
		auto ii = (*w)->ennemyImpuls.begin(); auto nn = (*w)->ennemyImpuls.end();
		while (ii!=nn)
		{
			(*ii)->recExpulsif.setPosition((*ii)->positionExpulsif);
			(*ii)->spriteBombeExpulsif.setPosition((*ii)->positionBombeExpulsif);
			_window.Draw((*ii)->spriteBombeExpulsif);
			if ((*ii)->IlifeBombeExpulsif <= 0)
			{
				(*w)->ennemyExploImpuls.push_back(new Bombe(spriteExplosionExpulsif, (*ii)->positionBombeExpulsif, 1, 1));
				delete (*ii);
				ii = (*w)->ennemyImpuls.erase(ii);
			}
			ii++;
		}

		auto jj = (*w)->ennemyExploImpuls.begin(); auto qq = (*w)->ennemyExploImpuls.end();
		while (jj!=qq)
		{
			(*jj)->spriteExplosionExpulsif.setPosition((*jj)->positionExplosionExpulsif);
			_window.Draw((*jj)->spriteExplosionExpulsif);
			if ((*jj)->IlifeExplosionExpulsif <= 0) 
			{
				delete (*jj);
				jj = (*w)->ennemyExploImpuls.erase(jj);
			}
			jj++;
		}
		for (auto ee : (*w)->ennemyExploImpuls) {
			ee->spriteExplosionExpulsif.setPosition(ee->positionExplosionExpulsif);
			_window.Draw(ee->spriteExplosionExpulsif);
		}
		for (auto g :(*w)->ennemyExploImpuls) {
			if (g->IlifeExplosionExpulsif <= 0) {
				delete g;
			}
		}
		w++;
	}
	for (auto be : BOMBEEXPULSIF) {
		be->recExpulsif.setPosition(be->positionExpulsif);
		be->spriteBombeExpulsif.setPosition(be->positionBombeExpulsif);
		_window.Draw(be->spriteBombeExpulsif);
	}
	for (int i = 0; i < BOMBEEXPULSIF.size(); i++) {
		if (BOMBEEXPULSIF[i]->IlifeBombeExpulsif <= 0) {
			EXPLOSIONEXPULSIF.push_back(new Bombe(spriteExplosionExpulsif, BOMBEEXPULSIF[i]->positionBombeExpulsif, 1, 1));
			_son->SEXPLOSIONCLASSIC.push_back(new SonMusique(4, BOMBEEXPULSIF[i]->positionBombeExpulsif,_son->soundExplosionClassic, _son->soundBombeNucleaire, _son->soundHit, _son->soundImpulsifExplosion, _son->soundBonusFlame, _son->soundBonusHeal,_son->soundKill, _son->soundRecupItem, _son->soundBonusShield, _son->soundBonusSpeed));
			BOMBEEXPULSIF.erase(BOMBEEXPULSIF.begin() + i);
		}
	}
	for (auto ee : EXPLOSIONEXPULSIF) {
		ee->spriteExplosionExpulsif.setPosition(ee->positionExplosionExpulsif);
		_window.Draw(ee->spriteExplosionExpulsif);
	}
	for (int i = 0; i < EXPLOSIONEXPULSIF.size(); i++) {
		if (EXPLOSIONEXPULSIF[i]->IlifeExplosionExpulsif <= 0) {
			EXPLOSIONEXPULSIF.erase(EXPLOSIONEXPULSIF.begin() + i);
		}
	}
}
