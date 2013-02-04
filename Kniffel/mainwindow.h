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
    void initTable();
    void insertNamesDialog();
    int generateRandomNumbers();
    void rollDices();
    void setImages(int index, int random);
    void fillLeftTableWithModelData(vector<int> v, int column);
    void fillRightTableWithModelData(vector<int> v, int column);
    void deleteAllTableContent();
    Player::Player &getCurrentPlayer();
    ~MainWindow();

public slots:
    void showInstructionDialog();
    void changeCubes();
    void setCheckbox1Slot(bool);
    void setCheckbox2Slot(bool);
    void setCheckbox3Slot(bool);
    void setCheckbox4Slot(bool);
    void setCheckbox5Slot(bool);
    void leftTableCellClick(const QModelIndex &);
    void startNewGameClicked();
    void showInsertNamesDialog();
    
private:
    Ui::MainWindow *ui;
    vector<int> m_cubes;
    //if true cubes is fix
    vector<bool> m_fixedCubes;
    vector<int> m_test;
    QStandardItemModel *m_modelLeftTable;
    QStandardItemModel *m_modelRightTable;
    Player *m_player1;
    Player *m_player2;
    int m_counterThrow;
    int m_counterRounds;
    QCheckBox *m_box1;
    QCheckBox *m_box2;
    QCheckBox *m_box3;
    QCheckBox *m_box4;
    QCheckBox *m_box5;
};

#endif // MAINWINDOW_H
