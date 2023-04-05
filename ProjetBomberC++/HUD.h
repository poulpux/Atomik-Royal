#pragma once
#include "tools.h"

class Camera;
class Player;
class Client;
class HUD
{
private:

sf::Texture tBarreVie;
sf::Sprite sBarreVie;
sf::Vector2f posBarreVie;
sf::RectangleShape rBarreVie;
sf::RectangleShape rBarreShield;
sf::Text txVie;
std::string stVie;
sf::Font fVie;

sf::Sprite spriteHUDFeu;
sf::Sprite spriteHUDVitesse;
sf::Texture textureHUDItem;
sf::IntRect intrectHUDFeu = {72,0,36,36 };
sf::IntRect intrectHUDVitesse = { 36,0,36,36 };
sf::Text textHUDFeu;
sf::Text textHUDVitesse;

sf::Text KillAndCo;
sf::Sprite Kill;
sf::Sprite Survivant;
sf::Texture txtKill;
sf::Texture txtSurv;

sf::RectangleShape lobby;
sf::Vector2f mapPixelle;

sf::RectangleShape rfeedBack;
float tpsDefile;
int saveLife=4;
float longFeedbar;
float timer;
sf::Vector2f pos;
public:
	void InitHud() {
		lobby.setSize(sf::Vector2f(500, 120));
		lobby.setFillColor(sf::Color(20,210,235,255));

		fVie.loadFromFile("../Ressources/Fonts/Typewriter.ttf");
		tBarreVie.loadFromFile("../Ressources/Textures/BarHPBomber.png");
		sBarreVie.setTexture(tBarreVie);
		sBarreVie.setScale(sf::Vector2f(2.0f,2.0f));
		sBarreVie.setColor(sf::Color(255.0f, 255.0f, 255.0f, 200.0f));


		rfeedBack.setFillColor(sf::Color(156.f, 0.f, 0.f, 225.0f));
		txVie.setFont(fVie);

		textureHUDItem.loadFromFile(TEXTURE_PATH"BonusSpriteSheet.png");
		spriteHUDFeu.setTexture(textureHUDItem);
		spriteHUDFeu.setTextureRect(intrectHUDFeu);
		spriteHUDFeu.setScale(sf::Vector2f(2.0f,2.0f));
		spriteHUDVitesse.setTexture(textureHUDItem);
		spriteHUDVitesse.setTextureRect(intrectHUDVitesse);
		spriteHUDVitesse.setScale(sf::Vector2f(2.0f, 2.0f));
		textHUDFeu.setFont(fVie);
		textHUDFeu.setCharacterSize(40);
		textHUDFeu.setFillColor(sf::Color::Green);
		textHUDVitesse.setFont(fVie);
		textHUDVitesse.setCharacterSize(40);
		textHUDVitesse.setFillColor(sf::Color::Green);
		KillAndCo.setFont(fVie);

		txtKill.loadFromFile(TEXTURE_PATH"nbKill.png");
		txtSurv.loadFromFile(TEXTURE_PATH"total-survivant.png");

		Kill.setTexture(txtKill);
		Survivant.setTexture(txtSurv);
		KillAndCo.setCharacterSize(45);
		KillAndCo.setFillColor(sf::Color::Black);
		KillAndCo.setString("Appuie sur S");

		tpsDefile = 75.f;
	}
	void UpdateHud(Camera& _cam, Player& player, myWindow& _window,Client& _client);
	void calculEtc(Client& _client, Player& _player);
	void DisplayHud(myWindow& _window, Player& player, Client& _client, Camera& _cam);
};

