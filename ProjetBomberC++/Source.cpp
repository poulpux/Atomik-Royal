#include "tools.h"
#include "stateManager.h"
#include "game.h"
#include "menu.h"
#include <clocale>
#include"Player.h"
#include"Client.h"
float SonVolume;
float MusicVolume;
Player player;
Client cli;
int main()
{
	setlocale(LC_ALL, "fr_FR.UTF-8");
	myWindow window("ProjetBomber", sf::Vector2u(1920, 1080));
	stateManager* State = new stateManager(new menu(StateMenu::MENU), window, player, cli);
	while (!window.IsDone())
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::F11))
		{
			window.ToggleFullscreen();
		}
		tools::restartClock();
		//update and request
		window.Update();
		State->RequestUpdate(window,player, cli);
		State->RequestUpdateEvent(window);

		//draw and request
		window.BeginDraw();
		State->RequestDraw(window,player,cli);

		//end
		window.EndDraw();

	}
	return 0;
}