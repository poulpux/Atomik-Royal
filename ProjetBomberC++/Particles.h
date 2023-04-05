#include"myWindow.h"
#include"tools.h"
#include"Camera.h"
class Particles {
public:
    Particles(sf::Vector2f pos, int& _type) {
        // Set the position of the particle
        type = _type;
        if (_type == 0)
        {
            shape[0].setPosition(pos);
            shape[1].setPosition(pos);
            // Set the size of the rectangles
            shape[0].setFillColor(sf::Color(0, 255, 0));
            shape[1].setFillColor(sf::Color(0, 255, 0));
            // Set the rotation of the particle to a random direction
            shape[0].setSize(sf::Vector2f(8.f, 3.f));
            shape[1].setSize(sf::Vector2f(3.f, 8.f));

            shape[0].setOrigin(4.f, 1.5f);
            shape[1].setOrigin(1.5f, 4.f);
            // Set the velocity of the particle to a random direction and speed
            float direction = static_cast<float>(std::rand() % 360) * 3.14159f / 180.f;
            float speed = static_cast<float>(std::rand() % 5 + 20);
            velocity.x = speed * std::cos(direction);
            velocity.y = speed * std::sin(direction);
        }
        else if (_type == 1)
        {
            shape[0].setPosition(pos);
            shape[0].setSize(sf::Vector2f(9.f, 9.f));
            

            shape[0].setOrigin(4.5f, 4.5f);
            
           shape[0].setFillColor(sf::Color(13, 233, 250));
           
      
           float direction = static_cast<float>(std::rand() % 360) * 3.14159f / 180.f;
           float speed = static_cast<float>(std::rand() % 5 + 20);
           velocity.x = speed * std::cos(direction);
           velocity.y = speed * std::sin(direction);
        }
       
    }

    Particles(myWindow& _window, Camera& _cam) {
        type = 2;
       
        pipos.x = tools::iRand2(0, 960);
        int b = tools::iRand2(0, 1);
        int c = tools::iRand2(0, 18);
        int d = tools::iRand2(0, 2);
        int e = tools::iRand2(0, pipos.x / 960 * 1000);

       
        //plus l'algorithme se répète, plus les particules iront vers le bord
        for (size_t i = 0; i < 3; i++)
        {
            int e = tools::iRand2(0, pipos.x / 960 * 1000);
            if (e > 500)  pipos.x = tools::iRand2(0, 960);
        }
       

        if (b == 1)
        {
            pipos.x = 1920 - pipos.x;
        }
        velocity.x = 0;
        velocity.y = -500;
       /* sf::Vector2f pos = { a, 756 };*/
        shape[0].setPosition(_window.getRenderWindow().mapPixelToCoords(sf::Vector2i(pipos.x, 1200),_cam.viewGame));
        pipos.y = 1080;
        shape[0].setSize(sf::Vector2f(4.f+d, 12.f + c));
        shape[0].setFillColor(sf::Color(255, 0, 0, 200));
    }
    void update(myWindow& _window) {
        timer += tools::GetTimeDelta();
        // Update the position based on the velocity vector
        if (type == 2)
        {
            sf::Vector2f pos = _window.getRenderWindow().mapPixelToCoords(sf::Vector2i(pipos.x, pipos.y));
            
           pipos.y +=(velocity.y * tools::GetTimeDelta());
           shape[0].setPosition(pos);

           shape->setFillColor(sf::Color(255, 0, 0, transparence));
        }
        else
        {
            shape[0].move(velocity * tools::GetTimeDelta());
            shape[1].move(velocity * tools::GetTimeDelta());
        }

    }

    void IncreasColor()
    {
        if(transparence<240)   transparence += 100 * tools::GetTimeDelta();
    }

    void DecreasColor()
    {
        if (transparence >1)
        transparence -= 200 * tools::GetTimeDelta();
    }
    void draw(myWindow& _window) {
        _window.Draw(shape[0]);
        _window.Draw(shape[1]);
    }
    float timer = 0.f;
    sf::RectangleShape shape[2];
    int type;
    sf::Vector2f pipos;
    float transparence;
private:
   sf::CircleShape circle;
   sf::Vector2f velocity;
};