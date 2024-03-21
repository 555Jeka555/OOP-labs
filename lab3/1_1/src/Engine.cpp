#include "Engine.h"

bool Engine::IsTurnedOn() const
{
    return m_isTurnedOn;
}

void Engine::TurnOnEngine()
{
    m_isTurnedOn = true;
}

void Engine::TurnOffEngine()
{
    m_isTurnedOn = false;
}
