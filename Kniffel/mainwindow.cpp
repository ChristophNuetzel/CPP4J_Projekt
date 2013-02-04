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
#include <string.h>
#include <QLineEdit>
#include <pointcalculator.h>
#include <QString>

using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    cout << "Spiel gestartet" << endl;

    m_counterThrow = 0;
    m_counterRounds = 1;

    m_cubes = vector<int>(5);
    m_fixedCubes = vector<bool>(5);

    // Create Table Models
    m_modelLeftTable = new QStandardItemModel(6,1,this);
    m_modelRightTable = new QStandardItemModel(5,1,this);

    // creating the player objects
    // In the next version all players are saved in one vector<Player>, so that there doesn't have to be a fixed number of palyers
    // --> The UI has to be adapted to that user-model in the next version!
    m_player1 = new Player::Player(QString("Thomas"), 0);
    m_player2 = new Player::Player(QString("Christoph"), 1);
    initTable();

    // Filling the table with zeros.
    vector<int> zeroInitVector = vector<int>(13);

    for (int i=0; i<13; i++) {
        zeroInitVector[i] = 0;
    }

    fillLeftTableWithModelData(zeroInitVector,0);
    fillLeftTableWithModelData(zeroInitVector,1);

}

MainWindow::~MainWindow()
{
    delete ui;

    delete m_box1;
    delete m_box2;
    delete m_box3;
    delete m_box4;
    delete m_box5;

    delete m_modelLeftTable;
    delete m_modelRightTable;

    delete m_player1;
    delete m_player2;
}

void MainWindow::rollDices(){
    for(uint i = 0; i < m_cubes.size(); i++){
        if( m_fixedCubes[i] != true ){
            m_cubes[i] = generateRandomNumbers();
            setImages(i, m_cubes[i]);
        }
    }
    m_counterThrow++;
    if(m_counterThrow == 3){
        ui->pushButton->setEnabled(false);
    }
    ui->dice->setText(QString::number(m_counterThrow) + "/3");
    vector<int> points = PointCalculator::calculatePointValues(m_cubes);
    ui->leftTableView->setEnabled(true);

    Player::Player &currentPlayer = getCurrentPlayer();
    ui->currentPlayer->setText(currentPlayer.getPlayerName());

    vector<int> userPoints = currentPlayer.getPointList();
    vector<int> resultPoints = vector<int>(13);
    ui->statusText->setText(currentPlayer.getPlayerName() + " ist am Zug");

    for (uint i = 0; i < points.size(); i++){
        if(userPoints[i] != -1){
            resultPoints[i] = userPoints[i];
        }else{
            resultPoints[i] = points[i];
        }
    }

    fillLeftTableWithModelData(resultPoints,currentPlayer.getColumnNumber());

    for(uint i=0; i < userPoints.size(); i++){
        if(userPoints[i] != -1){
            m_modelLeftTable->item(i,currentPlayer.getColumnNumber())->setEnabled(false);
        } else {
            m_modelLeftTable->item(i,currentPlayer.getColumnNumber())->setEnabled(true);
            QColor rowColor = Qt::darkRed ;
            m_modelLeftTable->item(i,currentPlayer.getColumnNumber())->setData(rowColor, Qt::TextColorRole);
        }
    }

    // disable the column of the other players
    for (int i=0; i<13; i++){
        if (currentPlayer.getColumnNumber() == 0) {
            m_modelLeftTable->item(i,1)->setEnabled(false);
        } else {
            m_modelLeftTable->item(i,0)->setEnabled(false);
        }
    }
}

void MainWindow::setImages(int index, int random){
    QLabel *image1 = new QLabel();

    switch(random)
    {
    case 1: image1->setPixmap(QPixmap(":/images/W1"));
        break;
    case 2: image1->setPixmap(QPixmap(":/images/W2"));
        break;
    case 3: image1->setPixmap(QPixmap(":/images/W3"));
        break;
    case 4: image1->setPixmap(QPixmap(":/images/W4"));
        break;
    case 5: image1->setPixmap(QPixmap(":/images/W5"));
        break;
    case 6: image1->setPixmap(QPixmap(":/images/W6"));
        break;
    }
   ui->kubesGridLayout->addWidget(image1, 0, index, 1, 1, Qt::AlignCenter);
}

int MainWindow::generateRandomNumbers(){
    int random_integer = 1 + (rand() % 6 );
    return random_integer;
}

void MainWindow::fillLeftTableWithModelData(vector<int> v, int column){
    for(uint i = 0; i < v.size(); i++){
        QString value = QString::number(v[i]);
        QStandardItem *item = new QStandardItem(value);
        m_modelLeftTable->setItem (i, column, item);
        m_modelLeftTable->item(i,column)->setTextAlignment(Qt::AlignCenter);
    }
}

void MainWindow::fillRightTableWithModelData(vector<int> v, int column){
    for(uint i = 0; i < v.size(); i++){
        QString value = QString::number(v[i]);
        QStandardItem *item = new QStandardItem(value);
        m_modelRightTable->setItem (i, column, item);
        m_modelRightTable->item(i,column)->setTextAlignment(Qt::AlignCenter);
    }
    QColor rowColor = Qt::darkRed ;
    m_modelRightTable->item(4,column)->setData(rowColor, Qt::TextColorRole);
    QFont fnt;
    fnt.setPointSize(10);
    fnt.setBold(true);
    fnt.setFamily("Segoe UI");
    m_modelRightTable->item(4,column)->setFont(fnt);
}

// Initialize Table Content
void MainWindow::initTable(){

    ui->scrollArea->setStyleSheet("background: rgb(8,138,75); text-align: center");
    ui->pushButton->setStyleSheet("background: rgb(220,220,220)");
    ui->dice->setText(QString::number(m_counterThrow)+"/3");

    // Set Table 1 & 2 Column Names
    m_modelLeftTable->setHorizontalHeaderItem(0, new QStandardItem(m_player1->getPlayerName()));
    m_modelLeftTable->setHorizontalHeaderItem(1, new QStandardItem(m_player2->getPlayerName()));
    m_modelRightTable->setHorizontalHeaderItem(0, new QStandardItem(m_player1->getPlayerName()));
    m_modelRightTable->setHorizontalHeaderItem(1, new QStandardItem(m_player2->getPlayerName()));

    // Add Models to Table View
    ui->leftTableView->setModel(m_modelLeftTable);
    ui->rightTableView->setModel(m_modelRightTable);

    // Set Table ColumnWidth and Color
    ui->leftTableView->setColumnWidth(0, 65);
    ui->leftTableView->setColumnWidth(1, 65);
    ui->leftTableView->setStyleSheet("background: rgb(220,220,220), ; border-style:solid");
    ui->rightTableView->setColumnWidth(0, 65);
    ui->rightTableView->setColumnWidth(1, 65);
    ui->rightTableView->setStyleSheet("background: rgb(220,220,220), ; border-style:solid");
    ui->currentPlayer->setAlignment(Qt::AlignLeft);
    ui->dice->setAlignment(Qt::AlignLeft);
    ui->currentPlayerLabel->setAlignment(Qt::AlignLeft);
    ui->diceLabel->setAlignment(Qt::AlignLeft);

    // Load Icon to View
    QIcon *i1 = new QIcon();
    QIcon *i2 = new QIcon();
    QIcon *i3 = new QIcon();
    QIcon *i4 = new QIcon();
    QIcon *i5 = new QIcon();
    QIcon *i6 = new QIcon();

    QString *string1 = new QString(":/images/W1");
    QString *string2 = new QString(":/images/W2");
    QString *string3 = new QString(":/images/W3");
    QString *string4 = new QString(":/images/W4");
    QString *string5 = new QString(":/images/W5");
    QString *string6 = new QString(":/images/W6");

    i1->addFile(*string1, QSize(), QIcon::Normal, QIcon::On);
    i2->addFile(*string2, QSize(), QIcon::Normal, QIcon::On);
    i3->addFile(*string3, QSize(), QIcon::Normal, QIcon::On);
    i4->addFile(*string4, QSize(), QIcon::Normal, QIcon::On);
    i5->addFile(*string5, QSize(), QIcon::Normal, QIcon::On);
    i6->addFile(*string6, QSize(), QIcon::Normal, QIcon::On);

    // Set Table 1 & 2 Row Names
    QStandardItem *first = new QStandardItem(*i1,QString("1er"));
    QStandardItem *second = new QStandardItem(*i2,QString("2er"));
    QStandardItem *third = new QStandardItem(*i3,QString("3er"));
    QStandardItem *fourth = new QStandardItem(*i4,QString("4er"));
    QStandardItem *fifth = new QStandardItem(*i5,QString("5er"));
    QStandardItem *sixth = new QStandardItem(*i6,QString("6er"));
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
    m_modelLeftTable->setVerticalHeaderItem(0, first);
    m_modelLeftTable->setVerticalHeaderItem(1, second);
    m_modelLeftTable->setVerticalHeaderItem(2, third);
    m_modelLeftTable->setVerticalHeaderItem(3, fourth);
    m_modelLeftTable->setVerticalHeaderItem(4, fifth);
    m_modelLeftTable->setVerticalHeaderItem(5, sixth);
    m_modelLeftTable->setVerticalHeaderItem(6, threeTurn);
    m_modelLeftTable->setVerticalHeaderItem(7, fourTurn);
    m_modelLeftTable->setVerticalHeaderItem(8, fullHouse);
    m_modelLeftTable->setVerticalHeaderItem(9, smallStreet);
    m_modelLeftTable->setVerticalHeaderItem(10, bigStreet);
    m_modelLeftTable->setVerticalHeaderItem(11, kniffel);
    m_modelLeftTable->setVerticalHeaderItem(12, chance);
    m_modelRightTable->setVerticalHeaderItem(0, sumUp);
    m_modelRightTable->setVerticalHeaderItem(1, bonus);
    m_modelRightTable->setVerticalHeaderItem(2, totalUp);
    m_modelRightTable->setVerticalHeaderItem(3, totalDown);
    m_modelRightTable->setVerticalHeaderItem(4, total);

    // Create Images für Kubes
    QLabel *image1 = new QLabel();
    QLabel *image2 = new QLabel();
    QLabel *image3 = new QLabel();
    QLabel *image4 = new QLabel();
    QLabel *image5 = new QLabel();
    image1->setPixmap(QPixmap(":/images/W1"));
    image2->setPixmap(QPixmap(":/images/W2"));
    image3->setPixmap(QPixmap(":/images/W3"));
    image4->setPixmap(QPixmap(":/images/W4"));
    image5->setPixmap(QPixmap(":/images/W5"));

    // Create Checkboxes
    m_box1 = new QCheckBox();
    m_box2 = new QCheckBox();
    m_box3 = new QCheckBox();
    m_box4 = new QCheckBox();
    m_box5 = new QCheckBox();

    // Add Images & Checkboxes to GridLayout
    ui->kubesGridLayout->addWidget(image1, 0, 0, 1, 1, Qt::AlignCenter);
    ui->kubesGridLayout->addWidget(image2, 0, 1, 1, 1, Qt::AlignCenter);
    ui->kubesGridLayout->addWidget(image3, 0, 2, 1, 1, Qt::AlignCenter);
    ui->kubesGridLayout->addWidget(image4, 0, 3, 1, 1, Qt::AlignCenter);
    ui->kubesGridLayout->addWidget(image5, 0, 4, 1, 1, Qt::AlignCenter);
    ui->kubesGridLayout->addWidget(m_box1, 1, 0, 1, 1, Qt::AlignCenter);
    ui->kubesGridLayout->addWidget(m_box2, 1, 1, 1, 1, Qt::AlignCenter);
    ui->kubesGridLayout->addWidget(m_box3, 1, 2, 1, 1, Qt::AlignCenter);
    ui->kubesGridLayout->addWidget(m_box4, 1, 3, 1, 1, Qt::AlignCenter);
    ui->kubesGridLayout->addWidget(m_box5, 1, 4, 1, 1, Qt::AlignCenter);

    //Enables cell edit
    ui->leftTableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->rightTableView->setEditTriggers(QAbstractItemView::NoEditTriggers);

    connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(changeCubes()));
    connect(m_box1, SIGNAL(toggled(bool)), this, SLOT(setCheckbox1Slot(bool)));
    connect(m_box2, SIGNAL(toggled(bool)), this, SLOT(setCheckbox2Slot(bool)));
    connect(m_box3, SIGNAL(toggled(bool)), this, SLOT(setCheckbox3Slot(bool)));
    connect(m_box4, SIGNAL(toggled(bool)), this, SLOT(setCheckbox4Slot(bool)));
    connect(m_box5, SIGNAL(toggled(bool)), this, SLOT(setCheckbox5Slot(bool)));
    connect(ui->leftTableView, SIGNAL(clicked(const QModelIndex &)),
            this, SLOT(leftTableCellClick(const QModelIndex & )));

    ui->leftTableView->setStyleSheet("font-weight:bold; background-color: white");
    ui->rightTableView->setStyleSheet("font-weight:bold; background-color: white");
    ui->leftTableView->setSelectionMode(QAbstractItemView::NoSelection);
    ui->rightTableView->setSelectionMode(QAbstractItemView::NoSelection);
    ui->leftTableView->setEnabled(false);
    ui->rightTableView->setEnabled(false);

}


// This method is not implemented yet
void MainWindow::deleteAllTableContent(){
    cout << "Foo!" << endl;
}

Player::Player &MainWindow::getCurrentPlayer()
{
    if(m_counterRounds % 2 == 0){
        return *m_player2;
    }
    return *m_player1;
}

// Slot
void MainWindow::changeCubes(){
    rollDices();
}

// Slot
void MainWindow::leftTableCellClick(const QModelIndex & index ){
    int row = index.row();
    int column = index.column();

    Player::Player &currentPlayer = getCurrentPlayer();

    vector<int> currentPoints = currentPlayer.getPointList();

    if (currentPoints[row] == -1 ){
        currentPlayer.setPointValue(row, (PointCalculator::calculatePointValues(m_cubes)[row]));
        m_modelLeftTable->item(row,column)->setEnabled(false);
        m_counterThrow = 0;
        ui->pushButton->setEnabled(true);
        ui->dice->setText(QString("0/3"));
        ui->leftTableView->setEnabled(false);
        m_box1->setChecked(false);
        m_box2->setChecked(false);
        m_box3->setChecked(false);
        m_box4->setChecked(false);
        m_box5->setChecked(false);
        m_counterRounds++;

        // updated point list after setting the point value
        currentPoints = currentPlayer.getPointList();

        for (uint i = 0; i < currentPoints.size(); i++){
            if(currentPoints[i] == -1){
                currentPoints[i] = 0;
            }
        }

        fillLeftTableWithModelData(currentPoints,currentPlayer.getColumnNumber());
        Player::Player &currentPlayer = getCurrentPlayer();
        ui->currentPlayer->setText(currentPlayer.getPlayerName());
        ui->statusText->setText(currentPlayer.getPlayerName() + " ist jetzt am Zug");

        // This code is executed, when the game is over.
        // It calculates the results.
        if(m_counterRounds > 26){
            ui->pushButton->setEnabled(false);
            ui->statusText->setText("Spiel Beendet");
            ui->currentPlayer->setText("Spiel Beendet");
            ui->rightTableView->setEnabled(true);
            vector<int> rightTablePlayer1 = m_player1->getSumPointList();
            vector<int> rightTablePlayer2 = m_player2->getSumPointList();
            fillRightTableWithModelData(rightTablePlayer1, 0);
            fillRightTableWithModelData(rightTablePlayer2, 1);

            int resultPlayer1 = m_modelRightTable->item(4,0)->text().toInt();
            int resultPlayer2 = m_modelRightTable->item(4,1)->text().toInt();
            ui->statusText_2->setStyleSheet("color: rgb(255,255,255)");
            if(resultPlayer1 > resultPlayer2){
                ui->statusText_2->setText(m_player1->getPlayerName() + " hat gewonnen");
            }else{
                ui->statusText_2->setText(m_player2->getPlayerName() + " hat gewonnen");
            }
        }

    } else {
        cout << "Punkt schon vergeben. Bitte andere Zeile auswaehlen!" << endl;
    }
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
