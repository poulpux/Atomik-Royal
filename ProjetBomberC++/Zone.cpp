#include "Zone.h"
#include"Player.h"
#include"Camera.h"
#include"Client.h"
Zone::Zone()
{
	//équilibrage

	//---------------------------------------------------------------------------------
	tpsForClos = 25;
	tpsForAnnonce = 10;
	delayTkDmg = 1.2f;
	//----------------------------------------------------------------------------------

	timer = 0.f;

	//Initialisation des 9 carrés
	A1G.close = false; A2G.close = false; A3G.close = false;
	B1G.close = false; B2G.close = false; B3G.close = false;
	C1G.close = false; C2G.close = false; C3G.close = false;

	A1G.pos = posCarte::A1; A1G.position = { 48.0f, 16.0f }; A2G.pos = posCarte::A2; A2G.position = { 1648.0f, 16.0f }; A3G.pos = posCarte::A3; A3G.position = { 3248.0f, 16.0f };
	B1G.pos = posCarte::B1; B1G.position = { 48.0f, 1616.0f }; B2G.pos = posCarte::B2; B2G.position = { 1648.0f, 1616.0f }; B3G.pos = posCarte::B3; B3G.position = { 3248.0f, 1616.0f };
	C1G.pos = posCarte::C1; C1G.position = { 48.0f, 3216.0f }; C2G.pos = posCarte::C2; C2G.position = { 1648.0f, 3216.0f }; C3G.pos = posCarte::C3; C3G.position = { 3248.0f, 3216.0f };
	rings.push_back(&A1G); rings.push_back(&A2G); rings.push_back(&A3G); 
	rings.push_back(&B1G); rings.push_back(&B2G); rings.push_back(&B3G);
	rings.push_back(&C1G); rings.push_back(&C2G); rings.push_back(&C3G);

	nbZoneOp = 8;
	Annonce = true;

	//La zone
	MaskZone.setFillColor(sf::Color(204, 0, 0, 100));
	MaskZone.setSize(sf::Vector2f(1920, 1080));

	recZone.setSize(sf::Vector2f(1600.0f, 1600.0f));
	recZone.setFillColor(sf::Color(255.0f, 0.0f, 0.0f, 150.0f));
}

void Zone::init()
{
	std::list<RingGestion*>a;
	rings = a;
	foireux = false;

	timer = 0.f;
	A1G.close = false; A2G.close = false; A3G.close = false;
	B1G.close = false; B2G.close = false; B3G.close = false;
	C1G.close = false; C2G.close = false; C3G.close = false;

	A1G.pos = posCarte::A1; A1G.position = { 48.0f, 16.0f }; A2G.pos = posCarte::A2; A2G.position = { 1648.0f, 16.0f }; A3G.pos = posCarte::A3; A3G.position = { 3248.0f, 16.0f };
	B1G.pos = posCarte::B1; B1G.position = { 48.0f, 1616.0f }; B2G.pos = posCarte::B2; B2G.position = { 1648.0f, 1616.0f }; B3G.pos = posCarte::B3; B3G.position = { 3248.0f, 1616.0f };
	C1G.pos = posCarte::C1; C1G.position = { 48.0f, 3216.0f }; C2G.pos = posCarte::C2; C2G.position = { 1648.0f, 3216.0f }; C3G.pos = posCarte::C3; C3G.position = { 3248.0f, 3216.0f };
	rings.push_back(&A1G); rings.push_back(&A2G); rings.push_back(&A3G);
	rings.push_back(&B1G); rings.push_back(&B2G); rings.push_back(&B3G);
	rings.push_back(&C1G); rings.push_back(&C2G); rings.push_back(&C3G);

	nbZoneOp = 8;
	Annonce = true;

	MaskZone.setFillColor(sf::Color(204, 0, 0, 100));
	MaskZone.setSize(sf::Vector2f(1920, 1080));

	recZone.setPosition(sf::Vector2f(-5000, -5000));
	recZone.setSize(sf::Vector2f(1600.0f, 1600.0f));
	recZone.setFillColor(sf::Color(255.0f, 0.0f, 0.0f, 150.0f));
}

void Zone::Update(Player& _player, Client& _client, Camera& cam)
{
	ringManagment(_client, _player);
	playerTakeDmg(_player);
	getZone(posCarte(nomNotif));

	//Affiche la notification de zone
	if (foireux)
	{
		tpsRestantTimer = (tpsForClos - timer);
		if (tpsRestantTimer < 0) tpsRestantTimer = 0;
		sTimerTps = std::to_string((int)tpsRestantTimer);
		tNotif.setString(sDebutNotif + GetNomZone() + sTpsRestant + sTimerTps);
		if(_player.getPv()>0) posNotif = sf::Vector2f(cam.getPosViewgame().x - 400, cam.getPosViewgame().y - 350);
		else posNotif = sf::Vector2f(cam.getPosViewgame().x - 450, cam.getPosViewgame().y - 500);
		tNotif.setPosition(posNotif);
		rNotif.setPosition(posNotif);
	}
}

void Zone::ringManagment(Client& _client, Player& _player)
{
	timer += tools::GetTimeDelta();
	
	if (Annonce && timer > tpsForAnnonce && nbZoneOp > 0 && _player.isHost)
	{
		foireux = true;
		Annonce = false;

		//C'est l'hote qui va définir les zone qui se ferment aux joueurs, attention, il ne fermera jamais la dernière zone
		if (_player.isHost)
		{
			//Tire un nombre aléatoire entre 0 et le nombre de case encore ouverte
			saveRand = tools::iRand2(0, nbZoneOp);
			_client.zoneAuto(saveRand, false);
			int compt = 0;
			auto i =rings.begin();
			auto n = rings.end();
			while (i != n)
			{
				if (saveRand == compt && (*i)->close == 0)
				{
					nomNotif = (*i)->pos;
					compt++;
				}
				if ((*i)->close == 0) compt++;
				i++;
			}
		}

		timer = 0;
	}
	else if (!Annonce && timer > tpsForClos && _player.isHost)
	{
		//Envoie la requête pour fermer une zone aux clients
		_client.zoneAuto(saveRand, true);
		ringClose(RANDOM);
		foireux = false;
		Annonce = true;
		timer = 0;
	}
}

void Zone::ringClose(posCarte _pos)
{
	if (_pos == posCarte::RANDOM) //ferme une zone aléatoire
	{
		int compt = 0;
		auto i = rings.begin();
		auto n = rings.end();
		while (i != n)
		{
			if (saveRand == compt && (*i)->close == 0)
			{
				(*i)->close = true;

				compt++;
			}
			if ((*i)->close == false) compt++;

			i++;
		}
		foireux = false;
		nbZoneOp--;
	}
	else //Fonction pour fermer manuellement une zone, ça devais être une carte post-mortem, mais on a pas eu le temps
	{
		auto i = rings.begin();
		auto n = rings.end();
		while (i != n)
		{
			if ((*i)->pos == _pos)
			{

				(*i)->close = true;
			}
			i++;
		}
		nbZoneOp--;
	}
}

void Zone::playerTakeDmg(Player& _player)
{
	//Inflige des dommages après un certain temps dans la zone
	if (dmgTimer > delayTkDmg)
	{
		_player.changePv(RingDmgCalcul);
		dmgTimer = 0;
	}
}

void Zone::draw(myWindow& _window, Player* _p)
{
	//Affiche une notif
	if (foireux == true)
	{
		_window.Draw(rNotif);
		_window.Draw(tNotif);
	}
	_p->inzone = false;
	
	//Ca te dis si t'es dans la zone et ça va faire en sorte d'augmenter le timer des dgm zone
	auto i = rings.begin(); auto n = rings.end();
	while (i != n)
	{
		if ((*i)->close)
		{
			if (_p->sprite.getGlobalBounds().intersects(recZone.getGlobalBounds()))
			{
				dmgTimer += tools::GetTimeDelta();
				_p->inzone = true;
			}
			recZone.setPosition((*i)->position);
			_window.Draw(recZone);
		}
		i++;
	}
	
	if (!_p->inzone) dmgTimer = 0;
}