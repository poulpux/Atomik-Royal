#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Network.hpp>
#include <string>

//#define WIN32_LEAN_AND_MEAN 
//#define _CRT_SECURE_NO_WARNINGS

class myWindow {
public:
	myWindow();
	myWindow(const std::string& l_title, const sf::Vector2u& l_size);
	~myWindow();
	void BeginDraw(); // Clear the window.
	void EndDraw(); // Display the changes.
	void Update();
	inline void SetIsDone(bool _isDone) { m_isDone = _isDone; }
	bool IsDone();
	bool IsFullscreen();
	sf::Vector2u GetWindowSize();
	sf::RenderWindow& getRenderWindow() { return m_window; };
	void ToggleFullscreen();
	void Draw(sf::Drawable& l_drawable);
	void Draw(sf::Drawable& l_drawable, sf::RenderStates _rs);
	sf::Texture UpdateTexture();
	inline sf::RenderWindow& getWindow() { return m_window; };
	void Destroy();
	inline sf::Event& GetEvent() { return event; }

private:
	void Setup(const std::string& l_title, const sf::Vector2u& l_size);
	void Create();
	sf::RenderWindow m_window;
	sf::Vector2u m_windowSize;
	std::string m_windowTitle;
	bool m_isDone;
	bool m_isFullscreen;
	sf::Event event;
};
