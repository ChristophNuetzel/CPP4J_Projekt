#include <player.h>
#include <iostream>

using namespace std;

// creates and fills the map initially with -1 values.
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

// constructor
Player::Player(QString playerName, int columnNumber)
{
    this->m_playerName = playerName;
    this->m_columnNumber = columnNumber;
    this->m_pointValues = createPointMap();
}

void Player::setPointValue(int orderIndex, int pointValue)
{
    if (orderIndex < 0 || orderIndex > 12) {
        cout << "The given orderIndex is out of bounds!" << endl;
    }
    this->m_pointValues[orderIndex] = pointValue;
}

vector<int> Player::getPointList()
{
    vector<int> resultList = vector<int>(13);

    for (int i = 0; i < 13; i++)
    {
        resultList[i] = this->m_pointValues[i];
    }

    return resultList;
}



std::vector<int> Player::getSumPointList(){

    vector<int> resultList = vector<int>(5);

    //Initalize all with 0
    for(uint i = 0; i < resultList.size(); i++){
        resultList[i] = 0;
    }

    //Sum top (0)
    for(int i = 0; i < 6; i++ ){
        resultList[0] += this->m_pointValues[i];
    }

    //Bonus? (1)
    if(resultList[0] >= 63 ){
        resultList[1] = 35;
    }

    //Total top (2)
    resultList[2] = resultList[0] + resultList[1];

    //Total bottom (3)
    for(int i = 6; i < 13; i++){
        resultList[3] += this->m_pointValues[i];
    }

    //Total All
    resultList[4] = resultList[2] + resultList[3];

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
