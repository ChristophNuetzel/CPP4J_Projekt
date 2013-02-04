#ifndef PLAYER_H
#define PLAYER_H

#include <QString>
#include <vector>
#include <map>

/* This class represents a single player in the kniffel program.
 * @brief The player class
 */
class Player
{
public:
    /*This constructor creates a new player.
     *The given QString becomes the player's name.
     *The given int columnNumber is the index of the column in the GUI.
     */
    Player(QString playerName, int columnNumber);
    
    /*This method returns a vector containing all the current point values for this player.
     *If a point value hasn't been set at the moment the value is -1.
     *
     *The order of the values is as follows:
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
     */
    std::vector<int> getPointList();


    /*This method stores a point value for this player.
     *The given int-vaue orderIndex matches the point category as seen in the getPointList-method!
     */
    void setPointValue(int orderIndex, int pointValue);

    /*This method returns this player's name as a QString.
     */
    QString getPlayerName();

    /*This method returns the player's column index.
     */
    int getColumnNumber();

    /*The order of the values is as follows:
    * Sum top      (Index 0)
    * Bonus?       (1)
    * Total top    (2)
    * Total bottom (3)
    * Total All    (4)
    */
    std::vector<int> getSumPointList();

private:

    // the name of the player
    QString m_playerName;

    // this map contains the points of the player
    std::map<int,int> m_pointValues;

    // the column index in the point table
    int m_columnNumber;
};

#endif // PLAYER_H
