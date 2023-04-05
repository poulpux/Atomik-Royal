#include "HUD.h"
#include "Camera.h"
#include "Player.h"
#include"Client.h"

void HUD::UpdateHud(Camera& _cam, Player& player, myWindow& _window, Client& _client) {
	if (player.gamelaunch)
	{
		timer += tools::GetTimeDelta();

		calculEtc(_client, player);
		if (player.getPv() > 76) {
			rBarreVie.setSize(sf::Vector2f(288, 36));
			rBarreVie.setFillColor(sf::Color(0.0f, 128.0f, 0.0f, 200.0f));
			txVie.setFillColor(sf::Color(0.0f, 128.0f, 0.0f, 200.0f));
		}
		else if (player.getPv() > 50 && player.getPv() <= 75) {
			rBarreVie.setSize(sf::Vector2f(217, 36));
			rBarreVie.setFillColor(sf::Color(255.0f, 255.0f, 0.0f, 200.0f));
			txVie.setFillColor(sf::Color(255.0f, 255.0f, 0.0f, 200.0f));
		}
		else if (player.getPv() > 25 && player.getPv() <= 50) {
			rBarreVie.setSize(sf::Vector2f(144, 36));
			rBarreVie.setFillColor(sf::Color(255.0f, 140.0f, 0.0f, 200.0f));
			txVie.setFillColor(sf::Color(255.0f, 140.0f, 0.0f, 200.0f));
		}
		else if (player.getPv() > 0 && player.getPv() <= 25) {
			rBarreVie.setSize(sf::Vector2f(73, 36));
			rBarreVie.setFillColor(sf::Color(255.0f, 0.0f, 0.0f, 200.0f));
			txVie.setFillColor(sf::Color(255.0f, 0.0f, 0.0f, 200.0f));
		}
		stVie = std::to_string((int)player.getPv());
		txVie.setString(stVie);
		posBarreVie = sf::Vector2f(_cam.getPosViewgame().x - 850, _cam.getPosViewgame().y + 400);
		sBarreVie.setPosition(posBarreVie);

		rBarreShield.setFillColor(sf::Color(0.0f, 200.0f, 255.0f, 200.0f));
		if (player.getArmure() > 76) {
			rBarreShield.setSize(sf::Vector2f(288, 19));
		}
		else if (player.getArmure() > 50 && player.getArmure() <= 75) {
			rBarreShield.setSize(sf::Vector2f(217, 19));
		}
		else if (player.getArmure() > 25 && player.getArmure() <= 50) {
			rBarreShield.setSize(sf::Vector2f(144, 19));
		}
		else if (player.getArmure() > 0 && player.getArmure() <= 25) {
			rBarreShield.setSize(sf::Vector2f(73, 19));
		}
		//calculEtc(_client, player);
	}
	else
	{
		if (mapPixelle.x > 560 && mapPixelle.x < 912 && mapPixelle.y>690 && mapPixelle.y < 765 && sf::Mouse::isButtonPressed(sf::Mouse::Left)&&player.isHost)
		{
			_client.lunchGame();
			player.gamelaunch = true;
		}
	}
}

void HUD::calculEtc(Client& _client, Player& _player)
{
	_client.nbSurvivant = 0;
	if (_player.getPv() > 0) _client.nbSurvivant ++;

	auto i = _client.Ennemies.begin(); auto n = _client.Ennemies.end();
	while (i!=n)
	{
		if (!(*i)->dead) _client.nbSurvivant++;
		i++;
	}
}

void HUD::DisplayHud(myWindow& _window, Player& player, Client& _client, Camera& _cam){
	if (player.gamelaunch)
	{
		if (player.getPv() > 0) {
			posBarreVie = _window.getRenderWindow().mapPixelToCoords(sf::Vector2i(100, 900));
			sBarreVie.setPosition(posBarreVie);
			rBarreVie.setPosition(sf::Vector2f(posBarreVie.x + 3, posBarreVie.y + 24));
			txVie.setPosition(sf::Vector2f(posBarreVie.x - 50, posBarreVie.y));

			/*if (sf::Keyboard::isKeyPressed(sf::Keyboard::X)&&timer>0.2)
			{
				player.takeDmg(25);
				timer = 0;
			}*/
			if (saveLife == 4 && player.getPv() >= 76)
			{
				longFeedbar = 73;
				rfeedBack.setPosition(sf::Vector2f(posBarreVie.x + 3 + 73, posBarreVie.y + 24 - 5000));
			}
			else if (saveLife == 4 && player.getPv() < 76 && player.getPv() >=51 && longFeedbar > 0)
			{
				longFeedbar -= tools::GetTimeDelta() * tpsDefile;
				rfeedBack.setPosition(sf::Vector2f(posBarreVie.x + 3 + 217, posBarreVie.y + 24));
			}
			else if (saveLife == 4 and player.getPv() < 51)
			{
				longFeedbar = 73;
				saveLife = 3;
			}

			if (saveLife == 3 && player.getPv() >= 51)
			{
				longFeedbar = 73;
				rfeedBack.setPosition(sf::Vector2f(posBarreVie.x + 3 + 73, posBarreVie.y + 24 - 5000));
			}
			else if (saveLife == 3 && player.getPv() < 51 && longFeedbar > 0 && player.getPv() >= 26)
			{
				longFeedbar -= tools::GetTimeDelta() * tpsDefile;
				rfeedBack.setPosition(sf::Vector2f(posBarreVie.x + 3 + 144, posBarreVie.y + 24));
			}
			else if (saveLife == 3 and player.getPv() < 26 )
			{
				longFeedbar = 73;
				saveLife = 2;
			}

			if (saveLife == 2 && player.getPv() >= 26)
			{
				longFeedbar = 73;
				rfeedBack.setPosition(sf::Vector2f(posBarreVie.x + 3 + 73, posBarreVie.y + 24 - 5000));
			}
			else if (saveLife == 2 && player.getPv() < 26 && longFeedbar > 0)
			{
				longFeedbar -= tools::GetTimeDelta() * tpsDefile;
				rfeedBack.setPosition(sf::Vector2f(posBarreVie.x + 3 + 73, posBarreVie.y + 24));
			}


			rfeedBack.setSize(sf::Vector2f(longFeedbar, 36));

			if (longFeedbar < 0.1 || longFeedbar == 73) rfeedBack.setPosition(sf::Vector2f(posBarreVie.x + 3 + 73, posBarreVie.y + 24 - 5000));


			_window.Draw(sBarreVie);
			_window.Draw(rBarreVie);
			_window.Draw(rfeedBack);
			_window.Draw(txVie);

			spriteHUDVitesse.setPosition(_window.getRenderWindow().mapPixelToCoords(sf::Vector2i(10, 700)));
			_window.Draw(spriteHUDVitesse);
			spriteHUDFeu.setPosition(_window.getRenderWindow().mapPixelToCoords(sf::Vector2i(10, 790)));
			_window.Draw(spriteHUDFeu);

			textHUDFeu.setString("x" + std::to_string(player.getBonusFeu()));
			textHUDFeu.setPosition(_window.getRenderWindow().mapPixelToCoords(sf::Vector2i(120, 790)));
			_window.Draw(textHUDFeu);
			textHUDVitesse.setString("x" + std::to_string(player.getBonusSpd()));
			textHUDVitesse.setPosition(_window.getRenderWindow().mapPixelToCoords(sf::Vector2i(120, 700)));
			_window.Draw(textHUDVitesse);

			KillAndCo.setCharacterSize(20);
			Survivant.setPosition(_window.getRenderWindow().mapPixelToCoords(sf::Vector2i(1750 - 120, 250)));
			KillAndCo.setString(std::to_string(_client.nbSurvivant));
			KillAndCo.setPosition(_window.getRenderWindow().mapPixelToCoords(sf::Vector2i(1825 - 120, 250)));

			_window.Draw(Survivant);
			_window.Draw(KillAndCo);

			Kill.setPosition(_window.getRenderWindow().mapPixelToCoords(sf::Vector2i(1835 - 95, 250)));
			KillAndCo.setString(std::to_string(_client.nbKill));
			KillAndCo.setPosition(_window.getRenderWindow().mapPixelToCoords(sf::Vector2i(1900 - 95, 250)));

			_window.Draw(Kill);
			_window.Draw(KillAndCo);

			KillAndCo.setCharacterSize(30);
			KillAndCo.setString(player.posZone);
			KillAndCo.setPosition(_window.getRenderWindow().mapPixelToCoords(sf::Vector2i(1550, 150)));

			_window.Draw(KillAndCo);

		}
		if (player.getArmure() > 0)
		{
			rBarreShield.setPosition(sf::Vector2f(posBarreVie.x + 3, posBarreVie.y + 2));
			_window.Draw(rBarreShield);
		}
	}
	else
	{
		if (player.isHost)
		{
			lobby.setPosition(_window.getRenderWindow().mapPixelToCoords(sf::Vector2i(1050, 800)));
			_window.Draw(lobby);
			sf::Vector2i mousePosition = sf::Mouse::getPosition(_window.getRenderWindow());
			mapPixelle = _window.getRenderWindow().mapPixelToCoords(mousePosition, _cam.viewGame);
			KillAndCo.setPosition(_window.getRenderWindow().mapPixelToCoords(sf::Vector2i(1100, 830)));
			_window.Draw(KillAndCo);
		}
	}
}
