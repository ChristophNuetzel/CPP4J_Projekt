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

//to store in extra classes
class InstructionDialog : public QDialog
{
public:
    InstructionDialog()
    {
        //implement the dialog content here
        this->resize(300,150);
    }
};

//to store in extra classes
class InsertNamesDialog : public QDialog
{
public:
    InsertNamesDialog()
    {
        //implement the dialog content here
        this->resize(300,150);
    }
};

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    m_cubes = vector<int>(5);
    m_fixedCubes = vector<bool>(5);

    // Create Table Models
    QStandardItemModel *modelLeftTable = new QStandardItemModel(6,1,this);
    QStandardItemModel *modelRightTable = new QStandardItemModel(5,1,this);

    initTable(modelLeftTable, modelRightTable);
    fillTableWithStuff(modelLeftTable, modelRightTable);

    QStringList *qstring = new QStringList();
    *qstring << "a" << "b" << "c" << "d" << "e" << "f" ;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::rollDices(){
    for(int i = 0; i < m_cubes.size(); i++){
        if( m_fixedCubes[i] != true ){
            m_cubes[i] = generateRandomNumbers();
            setImages(i, m_cubes[i]);
        }
    }
}

void MainWindow::setImages(int index, int random){
    QLabel *image1 = new QLabel();
    cout <<"index: " << index << " random: " << random << endl;
    switch(random)
    {
    case 1: image1->setPixmap(QPixmap(":/images/w1"));
        break;
    case 2: image1->setPixmap(QPixmap(":/images/w2"));
        break;
    case 3: image1->setPixmap(QPixmap(":/images/w3"));
        break;
    case 4: image1->setPixmap(QPixmap(":/images/w4"));
        break;
    case 5: image1->setPixmap(QPixmap(":/images/w5"));
        break;
    case 6: image1->setPixmap(QPixmap(":/images/w6"));
        break;
    }
   ui->kubesGridLayout->addWidget(image1, 0, index, 1, 1, Qt::AlignCenter);
}

int MainWindow::generateRandomNumbers(){
    int random_integer = 1 + (rand() % 6 );
    return random_integer;
}

// Slot
void MainWindow::changeCubesSlot(){
    rollDices();
    cout << "---" << endl;
}
// Slot
void MainWindow::showInstructionDialogSlot(){
    cout << "skldjf";
    InstructionDialog *dialog = new InstructionDialog;
    dialog->setWindowTitle("Instruction Dialog");
    dialog->show();
}

// Start Dialog to insert user names
void MainWindow::insertNamesDialog(){
    cout << "skldjf";
    InsertNamesDialog *dialog = new InsertNamesDialog;
    dialog->setWindowTitle("Insert Names Dialog");
    dialog->show();
}

// Initialize Table Content
void MainWindow::initTable(QStandardItemModel *modelLeftTable, QStandardItemModel *modelRightTable){

        ui->centralWidget->setStyleSheet("background: rgb(220,220,220)");

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
    QString *string = new QString(":/images/test");
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
    QLabel *image1 = new QLabel();
    QLabel *image2 = new QLabel();
    QLabel *image3 = new QLabel();
    QLabel *image4 = new QLabel();
    QLabel *image5 = new QLabel();
    image1->setPixmap(QPixmap(":/images/w1"));
    image2->setPixmap(QPixmap(":/images/w2"));
    image3->setPixmap(QPixmap(":/images/w3"));
    image4->setPixmap(QPixmap(":/images/w4"));
    image5->setPixmap(QPixmap(":/images/w5"));

    // Create Checkboxes
    QCheckBox *box1 = new QCheckBox();
    QCheckBox *box2 = new QCheckBox();
    QCheckBox *box3 = new QCheckBox();
    QCheckBox *box4 = new QCheckBox();
    QCheckBox *box5 = new QCheckBox();

    // Add Images & Checkboxes to GridLayout
    ui->kubesGridLayout->addWidget(image1, 0, 0, 1, 1, Qt::AlignCenter);
    ui->kubesGridLayout->addWidget(image2, 0, 1, 1, 1, Qt::AlignCenter);
    ui->kubesGridLayout->addWidget(image3, 0, 2, 1, 1, Qt::AlignCenter);
    ui->kubesGridLayout->addWidget(image4, 0, 3, 1, 1, Qt::AlignCenter);
    ui->kubesGridLayout->addWidget(image5, 0, 4, 1, 1, Qt::AlignCenter);
    ui->kubesGridLayout->addWidget(box1, 1, 0, 1, 1, Qt::AlignCenter);
    ui->kubesGridLayout->addWidget(box2, 1, 1, 1, 1, Qt::AlignCenter);
    ui->kubesGridLayout->addWidget(box3, 1, 2, 1, 1, Qt::AlignCenter);
    ui->kubesGridLayout->addWidget(box4, 1, 3, 1, 1, Qt::AlignCenter);
    ui->kubesGridLayout->addWidget(box5, 1, 4, 1, 1, Qt::AlignCenter);

    connect(ui->instructionButton, SIGNAL(clicked()), this, SLOT(showInstructionDialogSlot()));
    connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(changeCubesSlot()));
    connect(box1, SIGNAL(toggled(bool)), this, SLOT(setCheckbox1Slot(bool)) );
    connect(box2, SIGNAL(toggled(bool)), this, SLOT(setCheckbox2Slot(bool)) );
    connect(box3, SIGNAL(toggled(bool)), this, SLOT(setCheckbox3Slot(bool)) );
    connect(box4, SIGNAL(toggled(bool)), this, SLOT(setCheckbox4Slot(bool)) );
    connect(box5, SIGNAL(toggled(bool)), this, SLOT(setCheckbox5Slot(bool)) );

}

// Fills the table with some stupid numbers
void MainWindow::fillTableWithStuff(QStandardItemModel *modelLeftTable, QStandardItemModel *modelRightTable){

    QStandardItem *bla = new QStandardItem(QString("15"));
    QStandardItem *bla1 = new QStandardItem(QString("28"));
    QStandardItem *bla2 = new QStandardItem(QString("18"));
    QStandardItem *bla3 = new QStandardItem(QString("26"));
    modelLeftTable->setItem( 4, 0, bla);
    modelLeftTable->setItem( 10, 1, bla1);
    modelLeftTable->setItem( 5, 1, bla2);
    modelLeftTable->setItem( 8, 1, bla3);

    //connect(ui->leftTableView, SIGNAL( clicked(const QModelIndex &) ),
            //this, SLOT(cellselected(const QModelIndex & )) );
}

// Slot
void MainWindow::setCheckbox1Slot( bool b ){
    if(b == true){
        m_fixedCubes[0] = true;
    }else{
        m_fixedCubes[0] = false;
    }
}
// Slot
void MainWindow::setCheckbox2Slot( bool b ){
    if(b == true){
        m_fixedCubes[1] = true;
    }else{
        m_fixedCubes[1] = false;
    }
}
// Slot
void MainWindow::setCheckbox3Slot( bool b ){
    if(b == true){
        m_fixedCubes[2] = true;
    }else{
        m_fixedCubes[2] = false;
    }
}
// Slot
void MainWindow::setCheckbox4Slot( bool b ){
    if(b == true){
        m_fixedCubes[3] = true;
    }else{
        m_fixedCubes[3] = false;
    }
}
// Slot
void MainWindow::setCheckbox5Slot( bool b ){
    if(b == true){
        m_fixedCubes[4] = true;
    }else{
        m_fixedCubes[4] = false;
    }
}



