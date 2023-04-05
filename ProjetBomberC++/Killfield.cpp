#include "Killfield.h"
#include"Player.h"
#include"Client.h"
Killfield::Killfield()
{
	font.loadFromFile("../Ressources/Fonts/Typewriter.ttf");
	text.loadFromFile("../Ressources/Textures/kill.png");
	kill.setTexture(text);
	txt.setFont(font);
	txt.setFillColor(sf::Color::Black);
	TAffich = 8.f;
}

Killfield::Killfield(std::string& _tueur, std::string& _tue)
{
	tueur = _tueur;
	tuee = _tue;
}

void Killfield::Init()
{
	std::list<Killfield*>a;
	killList = a;
}

void Killfield::Update()
{
	auto i = killList.begin(); auto n = killList.end();
	while (i!=n)
	{
		(*i)->timer += tools::GetTimeDelta();
		if ((*i)->timer > TAffich)
		{
			delete (*i);
			i = killList.erase(i);
		}
		else	i++;
	}
}

void Killfield::ouiiiii()
{

}


void Killfield::Display(myWindow& _window,Player& _player, Client& _client)
{
	int a = 0;
	auto i = killList.begin(); auto n = killList.end();
	while (i != n)
	{
		if (_player.getPv() > 0)
		{
			txt.setScale(0.5, 0.5);
			kill.setScale(0.5, 0.5);
		}
		else
		{
			txt.setScale(1,1);
			kill.setScale(1,1);
		}
		if ((*i)->tueur == _client.pseudo) txt.setFillColor(sf::Color::Yellow);
		else txt.setFillColor(sf::Color::White);
		txt.setString((*i)->tueur);
		txt.setPosition(_window.getRenderWindow().mapPixelToCoords(sf::Vector2i(1575, 348+70*a)));
		_window.Draw(txt);
		
		kill.setPosition(_window.getRenderWindow().mapPixelToCoords(sf::Vector2i(1725, 348 + 70 * a)));
		_window.Draw(kill);

		if ((*i)->tuee == _client.pseudo) txt.setFillColor(sf::Color::Yellow);
		else txt.setFillColor(sf::Color::White);

		txt.setString((*i)->tuee);
		txt.setPosition(_window.getRenderWindow().mapPixelToCoords(sf::Vector2i(1775, 348 + 70 * a)));
		_window.Draw(txt);
		a++;
		i++;
	}
}

