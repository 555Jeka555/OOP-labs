#include "Car.h"

std::string Car::GetDirection() const
{
    return m_directionMovementToString.at(m_directionMovement);
}

bool Car::IsTurnedOn() const
{
    return m_engine.IsTurnedOn();
}

bool Car::TurnOnEngine()
{
    m_engine.TurnOnEngine();

    return m_engine.IsTurnedOn();
}

bool Car::TurnOffEngine()
{
    if (m_engine.IsTurnedOn()
        && m_transmission.GetGear() == 0
        && m_speed == 0)
    {
        m_engine.TurnOffEngine();
    }

    return !m_engine.IsTurnedOn();
}

bool Car::SetSpeed(int speed)
{
    bool isInvalidSpeed = speed < m_minSpeed;

    if (isInvalidSpeed
        || !m_engine.IsTurnedOn())
    {
        return false;
    }

    int currentGear = m_transmission.GetGear();

    std::pair<int, int> permissibleSpeedByCurrentGear =
            m_transmission.GetPermissibleSpeedByGear(currentGear);
    int minSpeed = permissibleSpeedByCurrentGear.first;
    int maxSpeed = permissibleSpeedByCurrentGear.second;

    bool isSpeedUpOnNeutralGear = currentGear == 0 && speed > m_speed;
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
        m_directionMovement = DirectionMovement::STANDING_STILL;
    }
    else if (currentGear == -1)
    {
        m_directionMovement = DirectionMovement::BACKWARD;
    }
    else if (currentGear > 0)
    {
        m_directionMovement = DirectionMovement::FORWARD;
    }

    m_speed = speed;
    return true;
}

int Car::GetSpeed() const
{
    return m_speed;
}

bool Car::SetGear(int gear)
{
    bool isSwitchGearNotAllowedBeforeTurnedOnEngine = !m_engine.IsTurnedOn() && gear != 0;

    bool isSwitchBackwardWithSpeed = gear == -1 && m_speed != 0;

    bool isSwitchHighGearFromBackwardGearWithSpeed =
            m_transmission.GetGear() == -1 && gear > 0 && m_speed != 0;

    bool isSwitchGearUpWhenBackward =
            gear != 0
            && m_transmission.GetGear() == 0
            && m_directionMovement == DirectionMovement::BACKWARD;

    if (isSwitchGearNotAllowedBeforeTurnedOnEngine
        || isSwitchBackwardWithSpeed
        || isSwitchHighGearFromBackwardGearWithSpeed
        || isSwitchGearUpWhenBackward
        || m_transmission.IsGearExist(gear))
    {
        return false;
    }

    std::pair<int, int> permissibleSpeedByNewGear =
            m_transmission.GetPermissibleSpeedByGear(gear);
    int minSpeed = permissibleSpeedByNewGear.first;
    int maxSpeed = permissibleSpeedByNewGear.second;

    bool isSpeedNotAllowedToSwitchGear =
            m_speed < minSpeed || m_speed > maxSpeed;
    if (isSpeedNotAllowedToSwitchGear)
    {
        return false;
    }

    m_transmission.SetGear(gear);
    return true;
}

int Car::GetGear() const
{
    return m_transmission.GetGear();
}
