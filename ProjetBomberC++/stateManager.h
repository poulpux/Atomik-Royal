#pragma once
#include "myWindow.h"
#include "tools.h"
#include <iostream>
class Player;
class Client;
class stateManager;

class State
{
protected:
    stateManager* stateManager_;
public:
    virtual ~State()
    {

    }

    void set_stateManager(stateManager* _stateManager)
    {
        this->stateManager_ = _stateManager;
    }

    virtual void init(myWindow& _window, Player& _player, Client& clients) = 0;
    virtual void update(myWindow& _window,Player& _player, Client& clients) = 0;
    virtual void updateEvent(myWindow& _window) = 0;
    virtual void draw(myWindow& _window, Player& _player, Client& clients) = 0;
    virtual void destroy() = 0;
};

class stateManager {

    /**
     * @var State A reference to the current state of the stateManager.
     **/

private:
    State* state_;

public:
    stateManager(State* state, myWindow& _window, Player& _player, Client& clients) : state_(nullptr) {
        this->TransitionTo(state, _window, _player, clients);
    }
    ~stateManager() {
        delete state_;
    }
    /**
     * The stateManager allows changing the State object at runtime.
     */
    void TransitionTo(State* state, myWindow& _window, Player& _player, Client& clients) {
        std::cout << "Context: Transition to " << typeid(*state).name() << ".\n";
        if (this->state_ != nullptr)
            delete this->state_;
        this->state_ = state;
        this->state_->set_stateManager(this);
        this->RequestInit(_window,_player,clients);
    }
    /**
     * The stateManager delegates part of its behavior to the current State object.
     */
    void RequestInit(myWindow& _window, Player& _player, Client& clients)
    {
        this->state_->init(_window, _player,clients);
    }
    void RequestUpdate(myWindow& _window,Player& _player, Client& clients)
    {
        this->state_->update(_window,_player, clients);
    }
    void RequestUpdateEvent(myWindow& _window)
    {
        while (_window.getRenderWindow().pollEvent(_window.GetEvent()))
        {
            if (_window.GetEvent().type == sf::Event::Closed)
            {
                _window.SetIsDone(true);
            }
            else if (_window.GetEvent().type == sf::Event::KeyPressed && _window.GetEvent().key.code == sf::Keyboard::F5)
            {
                _window.ToggleFullscreen();
            }
            this->state_->updateEvent(_window);
        }
    }
    void RequestDraw(myWindow& _window, Player& _player, Client& clients)
    {
        this->state_->draw(_window, _player, clients);
    }
    void RequestDestroy()
    {
        this->state_->destroy();
    }
};