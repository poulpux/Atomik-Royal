#include "Lobby.h"
#include"Client.h"
#include"Player.h"
Lobby::Lobby()
{
	text.loadFromFile("../Ressources/Textures/Retenter_le_lobby.png");
	sprite.setTexture(text);
	font.loadFromFile("../Ressources/Fonts/Typewriter.ttf");
	txt.setFont(font);
	txt.setFillColor(sf::Color::Black);
}

void Lobby::draw(Client& _client, myWindow& _window, Player& _player)
{
	_window.Draw(sprite);
	for (size_t j = 0; j < _client.Ennemies.size() + 1; j++)
	{
		auto i = _client.Ennemies.begin(); auto n = _client.Ennemies.end();
		while (i != n)
		{
			if ((*i)->id == j)
			{
				if (j != 0)
				{
					txt.setString((*i)->username);
					txt.setPosition(sf::Vector2f(_window.GetWindowSize().x * 0.47, _window.GetWindowSize().y * 0.2 + (((*i)->id+1) * 55)));
					_window.Draw(txt);
				}
				else
				{
					txt.setString((*i)->username);
					txt.setPosition(sf::Vector2f(_window.GetWindowSize().x * 0.55, _window.GetWindowSize().y * 0.2));
					_window.Draw(txt);
				}
			}
			if (_client.iid == j)
			{
				if (j != 0)
				{
					txt.setString(_client.pseudo);
					txt.setPosition(sf::Vector2f(_window.GetWindowSize().x * 0.47, _window.GetWindowSize().y * 0.2 + ((_client.iid + 1) * 55)));
					_window.Draw(txt);
				}
				else
				{
					txt.setString(_client.pseudo);
					txt.setPosition(sf::Vector2f(_window.GetWindowSize().x * 0.55, _window.GetWindowSize().y * 0.2));
					_window.Draw(txt);
				}
			}

			i++;
		}
	}
}
