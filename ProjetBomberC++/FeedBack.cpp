#include "FeedBack.h"

void FeedBack::initFeedBack()
{
	TExplo.loadFromFile(TEXTURE_PATH"explosion.png");
	SExplo.setTexture(TExplo);
	SExplo.setScale(ScaleExplo);
}

void FeedBack::updateFeedBack(Player& _player)
{
	if (i == 0)
	{
		if (_player.getPv() <= 0)
		{
			TimerBombe += tools::GetTimeDelta();
			if (TimerBombe >= 0.05f)
			{
				FrameExplo += 1;

				if (FrameExplo >= 10)
				{
					FrameExplo = 0;
					i = 1;
				}
				TimerBombe = 0.0f;
			}
			RectExplo.left = FrameExplo * RectExplo.width;
			SExplo.setTextureRect(RectExplo);
		}
	}
}

void FeedBack::displayFeedBack(myWindow& _window, Player& _player)
{
	SExplo.setOrigin(sf::Vector2f(32, 32));
	SExplo.setPosition(_player.getPos().x + 10, _player.getPos().y + 10);
	if (i == 0)
	{
		if (_player.getPv() <= 0)
		{
			_window.Draw(SExplo);
		}
	}
}