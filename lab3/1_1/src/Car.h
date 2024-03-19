#ifndef INC_1_1_CAR_H
#define INC_1_1_CAR_H

#include "stdafx.h"
#include "Engine.h"
#include "Transmission.h"

enum class DirectionMovement {
    FORWARD,
    BACKWARD,
};

class Car {
public:
    DirectionMovement GetDirection();

    bool IsTurnedOn();

    bool TurnOnEngine();

    bool TurnOffEngine();

    bool SetSpeed(int speed);

    int GetSpeed() const;

    bool SetGear(int gear);

    int GetGear() const;

private:
    Engine m_engine = {};
    const Transmission m_transmission = {};
};


#endif //INC_1_1_CAR_H
