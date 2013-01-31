#include "pointcalculator.h"

using namespace std;

PointCalculator::PointCalculator(QObject *parent) :
    QObject(parent)
{
}

int calculatePointsForGivenNumber(int number, vector<int>& dices)
{
    int result = 0;

    for (vector<int>::iterator it = dices.begin(); it != dices.end(); ++it) {
        if (*it == number) {
            result += number;
        }
    }
    return result;
}

int onesValue(vector<int>& dices)
{
    return calculatePointsForGivenNumber(1, dices);
}

int twosValue(vector<int>& dices)
{
    return calculatePointsForGivenNumber(2, dices);
}

int threesValue(vector<int>& dices)
{
    return calculatePointsForGivenNumber(3, dices);
}

int foursValue(vector<int>& dices)
{
    return calculatePointsForGivenNumber(4, dices);
}

int fivesValue(vector<int>& dices)
{
    return calculatePointsForGivenNumber(5, dices);
}

int sixesValue(vector<int>& dices)
{
    return calculatePointsForGivenNumber(6, dices);
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

