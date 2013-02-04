#include <player.h>
#include <iostream>

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

Player::Player(QString playerName, int columnNumber)
{
    this->m_playerName = playerName;
    this->m_columnNumber = columnNumber;
    this->m_pointValues = createPointMap();
}

void Player::setPointValue(int orderIndex, int pointValue)
{
    cout << "orderIndex ist in Player: " << orderIndex << endl;
    cout << "pointValue ist in player: " << pointValue<< endl;


    if (orderIndex < 0 || orderIndex > 12) {
        cout << "The given orderIndex is out of bounds!" << endl;
    }
    this->m_pointValues[orderIndex] = pointValue;

    cout << "this->m_pointValues[orderIndex] ausgegeben nach der Zuweisung: " << this->m_pointValues[orderIndex] << endl;

}

vector<int> Player::getPointList()
{
    vector<int> resultList = vector<int>(13);

    cout << "in Player::getPointList" << m_pointValues[0] << endl;

    for (int i = 0; i < 13; i++)
    {
        resultList[i] = this->m_pointValues[i];
    }

    return resultList;
}

QString Player::getPlayerName()
{
    return m_playerName;
}

int Player::getColumnNumber()
{
    return m_columnNumber;
}
