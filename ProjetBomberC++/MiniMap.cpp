#include "MiniMap.h"
#include "Player.h"

MiniMap::MiniMap()
{
}

MiniMap::~MiniMap()
{
}

void MiniMap::InitMiniMap()
{
	FRMiniMap = { 0.86f, 0, 0.2 * 0.56f, 0.2f };
	positionMiniMap = { 843.0f, 810.0f };

	viewMiniMap.setViewport(FRMiniMap);
	viewMiniMap.setCenter(positionMiniMap);
	if (stopminimap == false)
	{
		viewMiniMap.zoom(1.59);
		stopminimap = true;
	}

	joueur.setFillColor(sf::Color::Blue);
	joueur.setOrigin(20, 20);
	joueur.setRadius(20);
	
	contour.setFillColor(sf::Color(20, 60, 18, 255));
	contour.setSize(sf::Vector2f(170, 170));

	textureGM.loadFromFile(TEXTURE_PATH"CarrerMapZONE.png");
	spriteGM.setTexture(textureGM);
	spriteGM.setPosition(positionGM);
	spriteGM.setScale(sf::Vector2f(0.13f, 0.13f));
	spriteGM.setOrigin(sf::Vector2f(5200.0f / 2.0f, 5200.0f / 2.0f));

}

void MiniMap::UpdateMiniMap(Player* _p)
{
	timerKey += tools::GetTimeDelta();
	//zone descent 1
	joueur.setPosition(_p->getPos());
	if (_p->getPos().y > 16.0f && _p->getPos().y < 1616.0f)
		positionMiniMap.y = 810.0f;
	
	//zone descent 2
	if (_p->getPos().y > 1616.0f && _p->getPos().y < 3216.0f)
		positionMiniMap.y = 2410.0f;
	
	//zone descent 3
	if (_p->getPos().y > 3216.0f && _p->getPos().y < 4816)
		positionMiniMap.y = 4010;
	

	//zone A
	if (_p->getPos().x > 48.0f && _p->getPos().x < 1648.0f)
		positionMiniMap.x = 843.0f;
	
	//zone B
	if (_p->getPos().x > 1648.0f && _p->getPos().x < 3248.0f)
		positionMiniMap.x = 2443.0f;
	
	//zone C
	if (_p->getPos().x > 3248.0f && _p->getPos().x < 4848)
		positionMiniMap.x = 4043;
	

	viewMiniMap.setCenter(positionMiniMap);

	//affiche la carte avec M
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::M) && timerKey > 0.2f)
	{
		aficheGM = !aficheGM;
		timerKey = 0.0f;
	}
}

void MiniMap::DisplayGrandMap(myWindow* _window)
{
	positionGM = _window->getRenderWindow().mapPixelToCoords(sf::Vector2i(960, 540));
	spriteGM.setPosition(positionGM);
	if (aficheGM == true)
		_window->Draw(spriteGM);
	
}

void MiniMap::DisplayMiniMap(myWindow& _window)
{
	contour.setPosition(_window.getRenderWindow().mapPixelToCoords(sf::Vector2i(1638, -10)));
	_window.Draw(contour);
	_window.getRenderWindow().setView(viewMiniMap);
}
