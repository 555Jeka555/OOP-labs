#include "Engine.h"

bool Engine::IsTurnedOn() const
{
    return this->m_isTurnedOn;
}

void Engine::TurnOnEngine()
{
    this->m_isTurnedOn = true;
}

void Engine::TurnOffEngine()
{
    this->m_isTurnedOn = false;
}
