#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QModelIndex>
#include <QStandardItemModel>
#include <QLabel>

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
    void setImages(int index, int random);
    ~MainWindow();

public slots:
    void showInstructionDialogSlot();
    void changeCubesSlot();
    void setCheckbox1Slot(bool);
    void setCheckbox2Slot(bool);
    void setCheckbox3Slot(bool);
    void setCheckbox4Slot(bool);
    void setCheckbox5Slot(bool);
    
private:
    Ui::MainWindow *ui;
    vector<int> m_cubes;
    //if true cubes is fix
    vector<bool> m_fixedCubes;

};

#endif // MAINWINDOW_H
