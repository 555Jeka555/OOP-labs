#ifndef INC_1_1_ENGINE_H
#define INC_1_1_ENGINE_H

#include "stdafx.h"

class Engine {
public:
    bool IsTurnedOn();

    bool TurnOnEngine();

    bool TurnOffEngine();

    bool SetSpeed(int speed);

    int GetSpeed() const;

private:
    bool m_isTurnedOn = false;
    int m_speed = 0;
};


#endif //INC_1_1_ENGINE_H
