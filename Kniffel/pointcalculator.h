#ifndef POINTCALCULATOR_H
#define POINTCALCULATOR_H

#include <QObject>
#include <vector>

using namespace std;

class PointCalculator
{

public:

    /*This static method returns a vector<int> with 13 values, each one for the point values calculated
     *by the given dices.
     *
     *The order is as followed:
     * Ones     (Index 0)
     * Twos     (1)
     * Threes   (2)
     * Fours    (3)
     * Fives    (4)
     * sixes    (5)
     *
     * three-of-a-kind  (6)
     * four-of-a-kind   (7)
     * full house       (8)
     * small straight   (9)
     * large straight   (10)
     * yahtzee          (11)
     * chance           (12)
     *
     *The given vector<int> must have the length of 6!
     */
    static vector<int> calculatePointValues(vector<int> dices);
};

#endif // POINTCALCULATOR_H
