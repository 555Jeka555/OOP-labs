#ifndef INC_1_1_ENGINE_H
#define INC_1_1_ENGINE_H

#include "stdafx.h"

class Engine {
public:
    bool IsTurnedOn() const;

    void TurnOnEngine();

    void TurnOffEngine();

private:
    bool m_isTurnedOn = false;
};


#endif //INC_1_1_ENGINE_H
