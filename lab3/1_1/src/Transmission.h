#ifndef INC_1_1_TRANSMISSION_H
#define INC_1_1_TRANSMISSION_H

#include "stdafx.h"

class Transmission {
public:
    void SetGear(int gear);

    int GetGear() const;

    bool IsGearExist(int gear) const;

    std::pair<int, int> GetPermissibleSpeedByGear(int gear) const;

private:
    const int m_minGear = -1;
    const int m_maxGear = 5;
    int m_gear = 0;
    const std::map<int, std::pair<int, int>> m_permissibleSpeedByGear = {
            {-1, {0, 20}},
            {0, {0, 150}},
            {1, {0, 30}},
            {2, {20, 50}},
            {3, {30, 60}},
            {4, {40, 90}},
            {5, {50, 150}},
    };
};


#endif //INC_1_1_TRANSMISSION_H
