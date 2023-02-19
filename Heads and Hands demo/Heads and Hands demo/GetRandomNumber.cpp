/*!
    \file
    \brief File with the implementation of the GetRandomNumber functions
 */
#include "GetRandomNumber.hpp"

/*!
    Function simulates character attack
    \param[in] min Left border of the range
    \param[in] max Right border of the range
    \return Random value from the range from 0 to the character's maximum damage
 */
int GetRandomNumber(int min, int max) {
    if (min < 0 || min >= max) {
        min = 0;
    }
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<>dist(min, max);
    int num = dist(gen);
    return num;
}

/*!
    Function simulates a dice roll
    \return Random value of the face of the cube
 */
int GetRandomNumber() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<>dist(1, 6);
    int num = dist(gen);
    return num;
}
