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

/*Checks if 3 values of the vector are equal.
 *Returns the value of the number which exists three times.
 *Returns 0 if there isn't a Three-Of-A-Kind in the vector.
 **/
int containsThreeOfAKind(vector<int>& dices)
{
    int counter;
    for (vector<int>::iterator itOuter = dices.begin(); itOuter != dices.end(); ++itOuter) {
        counter = 0;
        for (vector<int>::iterator itInner = dices.begin(); itInner != dices.end(); ++itInner) {
            if (*itInner == *itOuter) {
                counter++;
            }
        }
        if (counter >= 3)
        {
            return *itOuter;
        }
    }

    return 0;
}

/*Checks if 4 values of the vector are equal.
 *Returns the value of the number which exists four times.
 *Returns 0 if there isn't a Four-Of-A-Kind in the vector.
 **/
int containsFourOfAKind(vector<int>& dices)
{
    int counter;
    for (vector<int>::iterator itOuter = dices.begin(); itOuter != dices.end(); ++itOuter) {
        counter = 0;
        for (vector<int>::iterator itInner = dices.begin(); itInner != dices.end(); ++itInner) {
            if (*itInner == *itOuter) {
                counter++;
            }
        }
        if (counter >= 4)
        {
            return *itOuter;
        }
    }

    return 0;
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
    int result = 0;
    if (containsThreeOfAKind(dices) != 0) {
        for (vector<int>::iterator it = dices.begin(); it != dices.end(); ++it) {
                result += *it;
        }
        return result;
    } else {
        return result;
    }
}

int fourOfAKindValue(vector<int>& dices)
{
    int result = 0;
    if (containsFourOfAKind(dices) != 0) {
        for (vector<int>::iterator it = dices.begin(); it != dices.end(); ++it) {
                result += *it;
        }
        return result;
    } else {
        return result;
    }
}

int fullHouseValue(vector<int>& dices)
{
    return 0;
}

int smallStraightValue(vector<int>& dices)
{
    vector<int>::iterator finder1;
    vector<int>::iterator finder2;
    vector<int>::iterator finder3;
    vector<int>::iterator finder4;
    vector<int>::iterator finder5;
    vector<int>::iterator finder6;

    finder1 = find(dices.begin(), dices.end(), 1);
    finder2 = find(dices.begin(), dices.end(), 2);
    finder3 = find(dices.begin(), dices.end(), 3);
    finder4 = find(dices.begin(), dices.end(), 4);
    finder5 = find(dices.begin(), dices.end(), 5);
    finder6 = find(dices.begin(), dices.end(), 6);

    if (finder1 != dices.end() && finder2 !=dices.end() && finder3 !=dices.end() && finder4 !=dices.end()){
        return 30;
    } else if (finder2 !=dices.end() && finder3 !=dices.end() && finder4 !=dices.end() && finder5 != dices.end()) {
        return 30;
    } else if(finder3 !=dices.end() && finder4 !=dices.end() && finder5 !=dices.end() && finder6 != dices.end()) {
        return 30;
    } else{
        return 0;
    }
}

int largeStraightValue(vector<int>& dices)
{
    return 0;
}

int yahtzeeValue(vector<int>& dices)
{
    if (dices[0] == dices[1] && dices[0] == dices[2] && dices[0] == dices[3] && dices[0] == dices[4]) {
        return 50;
    } else {
        return 0;
    }
}

int chanceValue(vector<int>& dices)
{
    int result = 0;

    for (vector<int>::iterator it = dices.begin(); it != dices.end(); ++it) {
            result += *it;
    }
    return result;
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
    result[7] = fourOfAKindValue(dices);
    result[8] = fullHouseValue(dices);
    result[9] = smallStraightValue(dices);
    result[10] = largeStraightValue(dices);
    result[11] = yahtzeeValue(dices);
    result[12] = chanceValue(dices);


    return result;
}

