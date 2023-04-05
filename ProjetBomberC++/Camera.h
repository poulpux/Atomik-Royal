#pragma once
#include<iostream>
#include"SFML/Graphics.hpp"
#include"myWindow.h"
class Player;
class Zone;
class Camera
{
protected:
	float timer;
	float smooth;
	sf::Vector2f avance;
	float boosHost = 1.f;
public: 
	sf::Vector2f positionView;
	sf::Vector2f getPosViewgame();

	Camera();
	~Camera();
	sf::View viewGame;
	void Init();
	void draw(myWindow& _window, Player& _player);
	void setPos(sf::Vector2f pos) { viewGame.setCenter(pos); };
	void Quality(Player& _player, myWindow& _window);
	void setZoom(float _zoom) { viewGame.zoom(_zoom); std::cout << "aa" << std::endl; }

	bool mortView = false;
};


//
//                $$$$$$$
//            $$$$$$$$$$$$$$
//         $$$$$$$$$$$$$$$$$$
//        $$$$$$$$$$$$$$$$$$$$
//       $$$$$$$$$$$$$$$? $$$$    $$$$$$
//       $$$$$$$ ?$$$$$$$$$$$$   $$$  $$$
//       $$$$$$$$$$$$$$v$$$$$  $$$$    $$
//        $$$$$$$$$$$$$$$$$$$$$$$$
//         $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
// $$$$$$     $$$$$$$$$$$$$$$$$$        $$
//$$   $$$$$$$$$$$$$$$$$$$$$$$         $$
// $$$    $$$$$$$$$$$$$$$$$$$$$$$$$$$$
//     $$$$$$$$  $$$ $$$$$$          $$
//   $$$$       $$$  $$$ $$$      $$$$
//  $$$       $$$$   $$$  $$$
//   $$$$$   $$$     $$$   $$$$    $$
//    $$$    $$$$$$  $$$    $$$$$$$$
//            $$$     $$$$$   $$$$

