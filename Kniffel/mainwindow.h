#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QModelIndex>
#include <QStandardItemModel>

using namespace std;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    void initTable(QStandardItemModel *modelLeftTable, QStandardItemModel *modelRightTable);
    void fillTableWithStuff(QStandardItemModel *modelLeftTable, QStandardItemModel *modelRightTable);
    void insertNamesDialog();
    int generateRandomNumbers();
    void rollDices();
    ~MainWindow();

public slots:
    void showInstructionDialog();
    void changeCubes();
    
private:
    Ui::MainWindow *ui;
    vector<int> m_cubes;
    //if true cubes is fix
    vector<bool> m_fixedCubes;
};

#endif // MAINWINDOW_H
