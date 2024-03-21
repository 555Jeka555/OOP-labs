#include "Transmission.h"

void Transmission::SetGear(int gear)
{
    m_gear = gear;
}

int Transmission::GetGear() const
{
    return m_gear;
}

bool Transmission::IsGearExist(int gear) const
{
    return gear < m_minGear || gear > m_maxGear;
}

std::pair<int, int> Transmission::GetPermissibleSpeedByGear(int gear) const
{
    return m_permissibleSpeedByGear.at(gear);
}
