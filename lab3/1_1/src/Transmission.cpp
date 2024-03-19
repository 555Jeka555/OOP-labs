#include "Transmission.h"

bool Transmission::SetGear(int gear)
{

}

int Transmission::GetGear() const
{

}

std::pair<int, int> Transmission::GetPermissibleSpeedByGear(int gear) const
{
    return Transmission::m_permissibleSpeedByGear[gear];
}
