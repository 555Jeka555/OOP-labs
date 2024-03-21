#include "Transmission.h"

void Transmission::SetGear(int gear)
{
    this->m_gear = gear;
}

int Transmission::GetGear() const
{
    return this->m_gear;
}

bool Transmission::IsGearExist(int gear) const
{
    return gear < this->m_min_gear || gear > this->m_max_gear;
}

std::pair<int, int> Transmission::GetPermissibleSpeedByGear(int gear) const
{
    return this->m_permissibleSpeedByGear[gear];
}
