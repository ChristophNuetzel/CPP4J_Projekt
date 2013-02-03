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
     */
    Player(QString playerName);
    
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
    QString getPlayerName();

private:

    QString m_playerName;
    std::map<int,int> m_pointValues;
};

#endif // PLAYER_H
