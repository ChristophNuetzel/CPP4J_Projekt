#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <QStandardItem>
#include <QIcon>
#include <QLabel>
#include <QGraphicsPixmapItem>
#include <QSize>
#include <QPalette>
#include <QStringList>
#include <QTableWidget>
#include <QDialog>
#include <signal.h>
#include <QCheckBox>

using namespace std;

class Dialog : public QDialog
{
public:
    Dialog()
    {
        QDialog *subDialog = new QDialog;
        subDialog->setWindowTitle("Sub Dialog");
        QPushButton *button = new QPushButton("Push to open new dialog", this);
       // connect(button, SIGNAL(clicked()), subDialog, SLOT(show()));
    }
};

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->centralWidget->setStyleSheet("background: rgb(220,220,220)");

    // Create Table Models
    QStandardItemModel *modelLeftTable = new QStandardItemModel(6,1,this);
    QStandardItemModel *modelRightTable = new QStandardItemModel(5,1,this);

    // Set Table 1 & 2 Column Names
    modelLeftTable->setHorizontalHeaderItem(0, new QStandardItem(QString("Player 1")));
    modelLeftTable->setHorizontalHeaderItem(1, new QStandardItem(QString("Player 2")));
    modelRightTable->setHorizontalHeaderItem(0, new QStandardItem(QString("Player 1")));
    modelRightTable->setHorizontalHeaderItem(1, new QStandardItem(QString("Player 2")));

    // Add Models to Table View
    ui->leftTableView->setModel(modelLeftTable);
    ui->rightTableView->setModel(modelRightTable);

    // Set Table ColumnWidth and Color
    ui->leftTableView->setColumnWidth(0, 55);
    ui->leftTableView->setColumnWidth(1, 55);
    ui->leftTableView->setStyleSheet("background: rgb(220,220,220), ; border-style:solid");
    ui->rightTableView->setColumnWidth(0, 55);
    ui->rightTableView->setColumnWidth(1, 55);
    ui->rightTableView->setStyleSheet("background: rgb(220,220,220), ; border-style:solid");
    ui->currentPlayer->setAlignment(Qt::AlignLeft);
    ui->dice->setAlignment(Qt::AlignLeft);
    ui->currentPlayerLabel->setAlignment(Qt::AlignRight);
    ui->diceLabel->setAlignment(Qt::AlignRight);

    // Load Icon to View
    QIcon *i = new QIcon();
    QString *string = new QString("../images/test.jpg");
    i->addFile(*string, QSize(), QIcon::Normal, QIcon::On);

    // Set Table 1 & 2 Row Names
    QStandardItem *first = new QStandardItem(*i,QString("1er"));
    QStandardItem *second = new QStandardItem(*i,QString("2er"));
    QStandardItem *third = new QStandardItem(*i,QString("3er"));
    QStandardItem *fourth = new QStandardItem(*i,QString("4er"));
    QStandardItem *fifth = new QStandardItem(*i,QString("5er"));
    QStandardItem *sixth = new QStandardItem(*i,QString("6er"));
    QStandardItem *threeTurn = new QStandardItem(QString("Dreierpasch"));
    QStandardItem *fourTurn = new QStandardItem(QString("Viererpasch"));
    QStandardItem *fullHouse = new QStandardItem(QString("Full-House"));
    QStandardItem *smallStreet = new QStandardItem(QString("Kleine Straße"));
    QStandardItem *bigStreet = new QStandardItem(QString("Große Straße"));
    QStandardItem *kniffel = new QStandardItem(QString("Kniffel"));
    QStandardItem *chance = new QStandardItem(QString("Chance"));
    QStandardItem *sumUp = new QStandardItem(QString("Summe oben"));
    QStandardItem *bonus = new QStandardItem(QString("Bonus 35P"));
    QStandardItem *totalUp = new QStandardItem(QString("Gesamt oben"));
    QStandardItem *totalDown = new QStandardItem(QString("Gesamt unten"));
    QStandardItem *total = new QStandardItem(QString("Gesamt"));

    // Add Items to Vertical Header
    modelLeftTable->setVerticalHeaderItem(0, first);
    modelLeftTable->setVerticalHeaderItem(1, second);
    modelLeftTable->setVerticalHeaderItem(2, third);
    modelLeftTable->setVerticalHeaderItem(3, fourth);
    modelLeftTable->setVerticalHeaderItem(4, fifth);
    modelLeftTable->setVerticalHeaderItem(5, sixth);
    modelLeftTable->setVerticalHeaderItem(6, threeTurn);
    modelLeftTable->setVerticalHeaderItem(7, fourTurn);
    modelLeftTable->setVerticalHeaderItem(8, fullHouse);
    modelLeftTable->setVerticalHeaderItem(9, smallStreet);
    modelLeftTable->setVerticalHeaderItem(10, bigStreet);
    modelLeftTable->setVerticalHeaderItem(11, kniffel);
    modelLeftTable->setVerticalHeaderItem(12, chance);
    modelRightTable->setVerticalHeaderItem(0, sumUp);
    modelRightTable->setVerticalHeaderItem(1, bonus);
    modelRightTable->setVerticalHeaderItem(2, totalUp);
    modelRightTable->setVerticalHeaderItem(3, totalDown);
    modelRightTable->setVerticalHeaderItem(4, total);

    // Create Images für Kubes
    QLabel *image1 = new QLabel(parent);
    QLabel *image2 = new QLabel(parent);
    QLabel *image3 = new QLabel(parent);
    QLabel *image4 = new QLabel(parent);
    QLabel *image5 = new QLabel(parent);
    QLabel *image6 = new QLabel(parent);
    image1->setPixmap(QPixmap("../images/wuerfel1.gif"));
    image2->setPixmap(QPixmap("../images/wuerfel2.gif"));
    image3->setPixmap(QPixmap("../images/wuerfel3.gif"));
    image4->setPixmap(QPixmap("../images/wuerfel4.gif"));
    image5->setPixmap(QPixmap("../images/wuerfel5.gif"));
    image6->setPixmap(QPixmap("../images/wuerfel6.gif"));

    // Create Checkboxes
    QCheckBox *box1 = new QCheckBox(parent);
    QCheckBox *box2 = new QCheckBox(parent);
    QCheckBox *box3 = new QCheckBox(parent);
    QCheckBox *box4 = new QCheckBox(parent);
    QCheckBox *box5 = new QCheckBox(parent);
    QCheckBox *box6 = new QCheckBox(parent);

    // Add Images & Checkboxes to GridLayout
    ui->kubesGridLayout->addWidget(image1, 0, 0, 1, 1, Qt::AlignCenter);
    ui->kubesGridLayout->addWidget(image2, 0, 1, 1, 1, Qt::AlignCenter);
    ui->kubesGridLayout->addWidget(image3, 0, 2, 1, 1, Qt::AlignCenter);
    ui->kubesGridLayout->addWidget(image4, 0, 3, 1, 1, Qt::AlignCenter);
    ui->kubesGridLayout->addWidget(image5, 0, 4, 1, 1, Qt::AlignCenter);
    ui->kubesGridLayout->addWidget(image6, 0, 5, 1, 1, Qt::AlignCenter);
    ui->kubesGridLayout->addWidget(box1, 1, 0, 1, 1, Qt::AlignCenter);
    ui->kubesGridLayout->addWidget(box2, 1, 1, 1, 1, Qt::AlignCenter);
    ui->kubesGridLayout->addWidget(box3, 1, 2, 1, 1, Qt::AlignCenter);
    ui->kubesGridLayout->addWidget(box4, 1, 3, 1, 1, Qt::AlignCenter);
    ui->kubesGridLayout->addWidget(box5, 1, 4, 1, 1, Qt::AlignCenter);
    ui->kubesGridLayout->addWidget(box6, 1, 5, 1, 1, Qt::AlignCenter);


    //QStandardItem *test = new QStandardItem(QString("irgendwas"));

    //Add to model
    //model->setItem(0,0,firstRow);
    //model->setItem(1,0,secondRow);
    //model->setItem(2,0,thirdRow);
    //model->setItem(3,0,fourthRow);
    //model->setItem(4,0,fifthRow);
    //model->setItem(5,0,test);


    //QStringList *qstring = new QStringList();
    //*qstring << "a" << "b" << "c" << "d" << "e" << "f" ;
    //model->setVerticalHeaderLabels(*qstring);

    // Example
    QStandardItem *bla = new QStandardItem(QString("15"));
    QStandardItem *bla1 = new QStandardItem(QString("28"));
    QStandardItem *bla2 = new QStandardItem(QString("18"));
    QStandardItem *bla3 = new QStandardItem(QString("26"));
    modelLeftTable->setItem( 4, 0, bla);
    modelLeftTable->setItem( 10, 1, bla1);
    modelLeftTable->setItem( 5, 1, bla2);
    modelLeftTable->setItem( 8, 1, bla3);


}



MainWindow::~MainWindow()
{
    delete ui;
}
