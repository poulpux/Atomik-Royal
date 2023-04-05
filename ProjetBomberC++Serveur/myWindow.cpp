#include "myWindow.h"


myWindow::myWindow() {
	Setup("Window", sf::Vector2u(1920, 1080));
}

myWindow::myWindow(const std::string& l_title, const sf::Vector2u& l_size)
{
	Setup(l_title, l_size);
}

myWindow::~myWindow()
{
	Destroy();
}

void myWindow::Setup(const std::string& l_title, const sf::Vector2u& l_size)
{
	m_windowTitle = l_title;
	m_windowSize = l_size;
	m_isFullscreen = false;
	m_isDone = false;
	Create();
}

void myWindow::Create()
{
	auto style = (m_isFullscreen ? sf::Style::Fullscreen : sf::Style::Default);
	m_window.create({ m_windowSize.x, m_windowSize.y, 32 }, m_windowTitle, style);
}
void myWindow::Destroy()
{
	m_window.close();
}

void myWindow::Update()
{

}

void myWindow::ToggleFullscreen()
{
	m_isFullscreen = !m_isFullscreen;
	Destroy();
	Create();
}

void myWindow::BeginDraw()
{
	m_window.clear(sf::Color::White);
}
void myWindow::EndDraw()
{
	m_window.display();
}

bool myWindow::IsDone()
{
	return m_isDone;

}
bool myWindow::IsFullscreen()
{
	return m_isFullscreen;
}
sf::Vector2u myWindow::GetWindowSize()
{
	return m_windowSize;
}

void myWindow::Draw(sf::Drawable& l_drawable)
{
	m_window.draw(l_drawable);
}

void myWindow::Draw(sf::Drawable& l_drawable, sf::RenderStates _rs)
{
	m_window.draw(l_drawable, _rs);
}

sf::Texture myWindow::UpdateTexture()
{
	sf::Texture tmp;
	tmp.create((int)GetWindowSize().x, (int)GetWindowSize().y);
	tmp.update(m_window);
	return tmp;
}