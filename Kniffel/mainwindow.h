#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QModelIndex>
#include <QStandardItemModel>

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
    ~MainWindow();

public slots:
    void showInstructionDialog();

    
private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
