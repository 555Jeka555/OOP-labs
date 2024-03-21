#include "Car.h"

std::string Car::GetDirection() const
{
    return this->m_directionMovementToString[this->m_directionMovement];
}

bool Car::IsTurnedOn() const
{
    return this->m_engine.IsTurnedOn();
}

bool Car::TurnOnEngine()
{
    this->m_engine.TurnOnEngine();

    return this->m_engine.IsTurnedOn();
}

bool Car::TurnOffEngine()
{
    if (this->m_engine.IsTurnedOn()
        && this->m_transmission.GetGear() == 0
        && this->m_speed == 0)
    {
        this->m_engine.TurnOffEngine();
    }

    return !this->m_engine.IsTurnedOn();
}

bool Car::SetSpeed(int speed)
{
    bool isInvalidSpeed = speed < m_min_speed;

    if (isInvalidSpeed
        || !this->m_engine.IsTurnedOn())
    {
        return false;
    }

    int currentGear = this->m_transmission.GetGear();

    std::pair<int, int> permissibleSpeedByCurrentGear =
            this->m_transmission.GetPermissibleSpeedByGear(currentGear);
    int minSpeed = permissibleSpeedByCurrentGear.first;
    int maxSpeed = permissibleSpeedByCurrentGear.second;

    bool isSpeedUpOnNeutralGear = currentGear == 0 && speed > this->m_speed;
    if (isSpeedUpOnNeutralGear)
    {
        return false;
    }

    bool isSpeedExceededAllowedSpeedLimit = speed < minSpeed || speed > maxSpeed;
    if (isSpeedExceededAllowedSpeedLimit)
    {
        return false;
    }

    if (speed == 0)
    {
        this->m_directionMovement = DirectionMovement::STANDING_STILL;
    }
    else if (currentGear == -1)
    {
        this->m_directionMovement = DirectionMovement::BACKWARD;
    }
    else if (currentGear > 0)
    {
        this->m_directionMovement = DirectionMovement::FORWARD;
    }

    this->m_speed = speed;
    return true;
}

int Car::GetSpeed() const
{
    return this->m_speed;
}

bool Car::SetGear(int gear)
{
    bool isSwitchGearOnNotAllowedBeforeTurnedOn = !this->m_engine.IsTurnedOn() && gear != 0;

    bool isSwitchBackwardWithSpeed = gear == -1 && this->m_speed != 0;

    bool isSwitchHighGearFromBackwardGearWithSpeed =
            this->m_transmission.GetGear() == -1 && gear > 0 && this->m_speed != 0;

    bool isSwitchGearUpWhenBackward =
            this->m_transmission.GetGear() == 0
            && this->m_directionMovement == DirectionMovement::BACKWARD;

    if (isSwitchGearOnNotAllowedBeforeTurnedOn
        || isSwitchBackwardWithSpeed
        || isSwitchHighGearFromBackwardGearWithSpeed
        || isSwitchGearUpWhenBackward
        || this->m_transmission.IsGearExist(gear))
    {
        return false;
    }

    std::pair<int, int> permissibleSpeedByNewGear =
            this->m_transmission.GetPermissibleSpeedByGear(gear);
    int minSpeed = permissibleSpeedByNewGear.first;
    int maxSpeed = permissibleSpeedByNewGear.second;

    bool isSpeedNotAllowedToSwitchGear =
            this->m_speed < minSpeed || this->m_speed > maxSpeed;
    if (isSpeedNotAllowedToSwitchGear)
    {
        return false;
    }

    this->m_transmission.SetGear(gear);
    return true;
}

int Car::GetGear() const
{
    return this->m_transmission.GetGear();
}
