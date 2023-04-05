#pragma once
#include "tools.h"
#include "myWindow.h"
#include "stateManager.h"

class Client;
class Player;
class game : public State
{
public:

	game() {};
	~game() {};

	void init(myWindow& _window, Player& _player, Client& clients) override;
	void update(myWindow& _window, Player& _player, Client& clients) override;
	void updateEvent(myWindow& _window) override;
	void draw(myWindow& _window, Player& _player, Client& clients) override;
	void destroy() override;

	void initQuitter();
	void updateQuitter(myWindow& _window, Player& _player);
	void displayQuitter(myWindow& _window);
private:
	int iQuit;
	bool bQuit;
	sf::Vector2f posQuit;
	sf::Texture ttQuit;
	sf::Sprite spQuit;

	bool loadChess;
	bool inithost;
	bool loadPos;
};