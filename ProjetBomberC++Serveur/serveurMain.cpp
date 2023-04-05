#include <iostream>
#include <string>
#include <sstream>
#include <SFML\Graphics.hpp>
#include <SFML/Network.hpp>
#include"tools.h"
#include "Serveur.h"
Serveur serv;

int main()
{
	serv.init();
	while (true)
	{
		tools::restartClock();
		serv.Update();
	}
	return 0;
}