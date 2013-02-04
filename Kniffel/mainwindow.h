#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QModelIndex>
#include <QStandardItemModel>
#include <QLabel>
#include <player.h>
#include <QCheckBox>


using namespace std;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);

    ~MainWindow();

    /*This method inits the table and the whole rest of the UI Styles
     */
    void initTable();

    /*This method generates a random int value for the dice rolling
     */
    int generateRandomNumbers();

    /*This method is called, when the player rolls the dices
     *It contains a big part of the game logic
     */
    void rollDices();

    /*This method sets the images for the current dice values
     */
    void setImages(int index, int random);

    /*This method fills a certain column in the left point table
     */
    void fillLeftTableWithModelData(vector<int> v, int column);

    /*This method fills a certain column in the right point table
     */
    void fillRightTableWithModelData(vector<int> v, int column);

    /*This method deletes all content of a table. It can be used to start a new game
     */
    void deleteAllTableContent();

    /*This helper method returns the current player object, based on the round counter
     */
    Player::Player &getCurrentPlayer();

public slots:

    //This slot should be called, when the "roll dices" button is clicked.
    void changeCubes();

    //Slots for checkboxes to keep dices.
    void setCheckbox1Slot(bool);
    void setCheckbox2Slot(bool);
    void setCheckbox3Slot(bool);
    void setCheckbox4Slot(bool);
    void setCheckbox5Slot(bool);

    // This slot should be called, when the player clicks on the table to save a point value.
    void leftTableCellClick(const QModelIndex &);
    
private:
    Ui::MainWindow *ui;

    //the current values of the 5 dices
    vector<int> m_cubes;

    //if true cubes is fix
    vector<bool> m_fixedCubes;
    vector<int> m_test;

    // the two table for the points
    QStandardItemModel *m_modelLeftTable;
    QStandardItemModel *m_modelRightTable;

    // only in this current version: fixed amount of players
    Player *m_player1;
    Player *m_player2;

    // counter for the game logic
    int m_counterThrow;
    int m_counterRounds;

    // Checkboxes to keep dice values
    QCheckBox *m_box1;
    QCheckBox *m_box2;
    QCheckBox *m_box3;
    QCheckBox *m_box4;
    QCheckBox *m_box5;
};

#endif // MAINWINDOW_H
