#include "Camera.h"
#include"Player.h"
#include "Zone.h"

Camera::Camera()
{
    viewGame.setViewport(sf::FloatRect(0, 0, 1, 1));
    viewGame.setSize(1920, 1080);
    viewGame.zoom(0.7f);
    
}

Camera::~Camera()
{
}

void Camera::Init()
{
    viewGame.setViewport(sf::FloatRect(0, 0, 1, 1));
    viewGame.setSize(1920, 1080);
    viewGame.zoom(0.7f);
}

void Camera::draw(myWindow& _window, Player& _player)
{
    Quality(_player, _window);
    viewGame.setCenter(positionView);
    _window.getRenderWindow().setView(viewGame);
}

void Camera::Quality(Player& _player, myWindow& _window)
{
   /* if (_player.isHost) boosHost = 1.5f;*/
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) positionView = _player.pos;
    sf::Vector2f dir;
    tools::direction(positionView, _player.pos, dir);
    if (_player.getPv() <= 0)
    {
        if (_player.getPos().x <= 4800 + 50 - (1920 / 2) && _player.getPos().x >= (1920 / 2) + 50)
        {
            positionView.x = _player.getPos().x;
        }
        else if (_player.getPos().x > 4800 + 50 - (1920 / 2))
        {
            _player.pos.x = 4800 + 50 - (1920 / 2);
            positionView.x = _player.getPos().x;
        }
        else
        {
            _player.pos.x = (1920 / 2) + 50;
            positionView.x = _player.getPos().x;
        }

        if (_player.getPos().y <= 4800 - (1080 / 2) + 15 && _player.getPos().y >= (1080 / 2) + 15)
        {

            positionView.y = _player.getPos().y;
        }
        else if (_player.getPos().y > 4800 - (1080 / 2) + 15)
        {
            _player.pos.y = 4800 - (1080 / 2) + 15;
            positionView.y = _player.getPos().y;
        }
        else
        {
            _player.pos.y = (1080 / 2) + 15;
            positionView.y = _player.getPos().y;
        }
    }
    if (_player.getPv() > 0)
    { 
        sf::Vector2f screen = _window.getRenderWindow().mapPixelToCoords(sf::Vector2i(1920/2,1080/2), viewGame);
        if (_player.pos.x<= 4800 +48 - (1920 / 2)+400-16-16 && _player.pos.x >= (1920 / 2) - 307&&tools::distance(positionView, _player.pos) > 50/*((_player.pos.x-screen.x>75|| _player.pos.x - screen.x < 75)*/)
        {
            positionView.x += tools::GetTimeDelta()*_player.getSpeed().x * dir.x * boosHost;
        }

        if (_player.pos.y <= 4800 - (1080 / 2) -16+ 300+32 && _player.pos.y >= (1080 / 2) - 190-64 && tools::distance(positionView, _player.pos) > 50/*((_player.pos.y - screen.y > 75 || _player.pos.y - screen.y < 75))*/)
        {
            positionView.y += tools::GetTimeDelta() * _player.getSpeed().y * dir.y * boosHost;
        }
    }

    if (_player.getDontMove() == true&&_player.getPv()>0&&_player.pos.y <= 4800 - (1080 / 2) + 16 + 300-32 && _player.pos.y >= (1080 / 2) - 215+32&& _player.pos.x <= 4800 + 48 - (1920 / 2) + 400 - 64 - 16-32 && _player.pos.x >= (1920 / 2) - 307+32 + 16)
    {
        timer += tools::GetTimeDelta();
        if (tools::distance(positionView, _player.pos) > 5)
        {
            if (smooth < 50)
                smooth += tools::GetTimeDelta();
            positionView.x += tools::GetTimeDelta() *smooth * dir.x * boosHost;
            positionView.y += tools::GetTimeDelta() * smooth * dir.y * boosHost;
        }
        else
        {
            smooth = 0;
        }
    }
    if (_player.getDontMove() == false) smooth = 0;
}

sf::Vector2f Camera::getPosViewgame()
{
    return positionView;
}


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

