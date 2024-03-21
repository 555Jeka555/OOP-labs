#ifndef INC_1_1_CAR_H
#define INC_1_1_CAR_H

#include "stdafx.h"
#include "Engine.h"
#include "Transmission.h"

enum class DirectionMovement
{
    FORWARD,
    BACKWARD,
    STANDING_STILL,
};

class Car {
public:
    std::string GetDirection() const;

    bool IsTurnedOn() const;

    bool TurnOnEngine();

    bool TurnOffEngine();

    bool SetSpeed(int speed);

    int GetSpeed() const;

    bool SetGear(int gear);

    int GetGear() const;

private:
    const int m_minSpeed = 0;
    Engine m_engine = {};
    Transmission m_transmission = {};
    int m_speed = 0;
    DirectionMovement m_directionMovement = DirectionMovement::STANDING_STILL;
    const std::map<DirectionMovement, std::string> m_directionMovementToString = {
            {DirectionMovement::STANDING_STILL, "standing still"},
            {DirectionMovement::BACKWARD, "backward"},
            {DirectionMovement::FORWARD, "forward"},
    };
};


#endif //INC_1_1_CAR_H
