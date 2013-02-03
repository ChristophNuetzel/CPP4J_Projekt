#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QModelIndex>
#include <QStandardItemModel>
#include <QLabel>
#include <player.h>

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
    void deleteAllTableContent();
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
    void rightTableCellClick(const QModelIndex &);
    void changeNamesClicked();
    void startNewGameClicked();
    void showInsertNamesDialog();
    
private:
    Ui::MainWindow *ui;
    QString m_namePlayer1;
    QString m_namePlayer2;
    vector<int> m_cubes;
    //if true cubes is fix
    vector<bool> m_fixedCubes;
    vector<int> m_test;
    QStandardItemModel *m_modelLeftTable;
    QStandardItemModel *m_modelRightTable;
    Player *m_player1;
    Player *m_player2;

};

#endif // MAINWINDOW_H
