#ifndef INC_1_1_TRANSMISSION_H
#define INC_1_1_TRANSMISSION_H

#include "stdafx.h"

class Transmission {
public:
    bool SetGear(int gear);

    int GetGear() const;

    std::pair<int, int> GetPermissibleSpeedByGear(int gear) const;

private:
    int m_gear = 0;
    mutable std::map<int, std::pair<int, int>> m_permissibleSpeedByGear = {
            {-1, {0, 20}},
            {0, {0, 149}},
            {1, {0, 30}},
            {2, {20, 50}},
            {3, {30, 60}},
            {4, {40, 90}},
            {5, {50, 150}},
    };
};


#endif //INC_1_1_TRANSMISSION_H
