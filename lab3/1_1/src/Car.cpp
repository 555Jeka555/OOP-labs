#include "Car.h"

DirectionMovement Car::GetDirection()
{
    // Implement logic to return the current direction of the car
}

bool Car::IsTurnedOn()
{
    return Car::m_engine.IsTurnedOn();
}

bool Car::TurnOnEngine()
{
    Car::m_engine.TurnOnEngine();

    return Car::m_engine.IsTurnedOn();
}

bool Car::TurnOffEngine()
{
    if (Car::m_engine.IsTurnedOn()
        && Car::m_transmission.GetGear() == 0
        && Car::m_engine.GetSpeed() == 0)
    {
        Car::m_engine.TurnOffEngine();
    }

    return !Car::m_engine.IsTurnedOn();
}

bool Car::SetSpeed(int speed)
{
    int currentGear = Car::m_transmission.GetGear();
    int currenSpeed = Car::m_engine.GetSpeed();

    std::pair<int, int> permissibleSpeedByCurrentGear =
            Car::m_transmission.GetPermissibleSpeedByGear(currentGear);
    int minSpeed = permissibleSpeedByCurrentGear.first;
    int maxSpeed = permissibleSpeedByCurrentGear.second;

    if (currentGear == 0 && speed >= currenSpeed)
    {
        return false;
    }

    if (speed < minSpeed || minSpeed > maxSpeed)
    {
        return false;
    }

    return Car::m_engine.SetSpeed(speed);
}

int Car::GetSpeed() const
{
    return Car::m_engine.GetSpeed();
}

bool Car::SetGear(int gear)
{
    int currentGear = Car::m_transmission.GetGear();
    int currenSpeed = Car::m_engine.GetSpeed();

    std::pair<int, int> permissibleSpeedByNewGear =
            Car::m_transmission.GetPermissibleSpeedByGear(gear);
    int minSpeed = permissibleSpeedByNewGear.first;
    int maxSpeed = permissibleSpeedByNewGear.second;

    if (currenSpeed <= minSpeed || currenSpeed >= maxSpeed)
    {
        return false;
    }

    return SetGear(gear);
}

int Car::GetGear() const
{
    return Car::m_transmission.GetGear();
}
