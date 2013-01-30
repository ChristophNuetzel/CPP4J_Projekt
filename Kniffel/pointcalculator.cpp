#include "pointcalculator.h"

using namespace std;

PointCalculator::PointCalculator(QObject *parent) :
    QObject(parent)
{
}

int onesValue(vector<int>& dices)
{
    return 0;
}

int twosValue(vector<int>& dices)
{
    return 0;
}

int threesValue(vector<int>& dices)
{
    return 0;
}

int foursValue(vector<int>& dices)
{
    return 0;
}

int fivesValue(vector<int>& dices)
{
    return 0;
}

int sixesValue(vector<int>& dices)
{
    return 0;
}

int threeOfAKindValue(vector<int>& dices)
{
    return 0;
}

int FourOfAKindValue(vector<int>& dices)
{
    return 0;
}

int fullHouseValue(vector<int>& dices)
{
    return 0;
}

int smallStraightValue(vector<int>& dices)
{
    return 0;
}

int largeStraightValue(vector<int>& dices)
{
    return 0;
}

int yahtzeeValue(vector<int>& dices)
{
    return 0;
}

int chanceValue(vector<int>& dices)
{
    return 0;
}

vector<int> calculatePointValues(vector<int> dices)
{
    vector<int> result = vector<int>(13);

    result[0] = onesValue(dices);
    result[1] = twosValue(dices);
    result[2] = threesValue(dices);
    result[3] = foursValue(dices);
    result[4] = fivesValue(dices);
    result[5] = sixesValue(dices);

    result[6] = threeOfAKindValue(dices);
    result[7] = FourOfAKindValue(dices);
    result[8] = fullHouseValue(dices);
    result[9] = smallStraightValue(dices);
    result[10] = largeStraightValue(dices);
    result[11] = yahtzeeValue(dices);
    result[12] = chanceValue(dices);


    return result;
}

