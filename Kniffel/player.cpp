#include "player.h"
#include "iostream.h"

using namespace std;

map<int,int> createPointMap()
{
    map<int,int> pointValueMap;
    pointValueMap[0] = -1;
    pointValueMap[1] = -1;
    pointValueMap[2] = -1;
    pointValueMap[3] = -1;
    pointValueMap[4] = -1;
    pointValueMap[5] = -1;
    pointValueMap[6] = -1;
    pointValueMap[7] = -1;
    pointValueMap[8] = -1;
    pointValueMap[9] = -1;
    pointValueMap[10] = -1;
    pointValueMap[11] = -1;
    pointValueMap[12] = -1;

    return pointValueMap;
}

player::player(QString playerName)
{
    this->m_playerName = playerName;
    this->m_pointValues = createPointMap();
}

void player::setPointValue(int orderIndex, int pointValue)
{
    if (orderIndex < 0 || orderIndex > 12) {
        cout << "The given orderIndex is out of bounds!" << endl;
    }
    this->m_pointValues[orderIndex] = pointValue;
}

vector<int> player::getPointList()
{
    vector<int> resultList = vector<int>(13);

    for (int i = 0; i < 13; i++)
    {
        resultList[i] = this->m_pointValues[i];
    }

    return resultList;
}
