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

//to store in extra classes
class InstructionDialog : public QDialog
{
public:
    InstructionDialog()
    {
        QLabel *instrution = new QLabel("Hier soll die Anleitung stehen");
        QHBoxLayout *layout = new QHBoxLayout();
        layout->addWidget(instrution, 0, Qt::AlignCenter);
        setLayout(layout);
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

        QLabel *insertNames = new QLabel("Insert User Names");
        QLabel *labelPlayer1 = new QLabel("Player1");
        QLabel *labelPlayer2 = new QLabel("Player2");
        QPushButton *okButton = new QPushButton("OK");
        QLineEdit *inputPlayer1 = new QLineEdit();
        QLineEdit *inputPlayer2 = new QLineEdit();
        QGridLayout *layout = new QGridLayout();

        layout->addWidget(insertNames,0,0,1,0, Qt::AlignCenter);
        layout->addWidget(labelPlayer1,1,1,Qt::AlignRight );
        layout->addWidget(labelPlayer2,2,1,Qt::AlignRight);
        layout->addWidget(inputPlayer1,1,2);
        layout->addWidget(inputPlayer2,2,2);
        layout->addWidget(okButton,3,2);

        setLayout(layout);

        //connect(okButton, SIGNAL(clicked()), this, SLOT(changeNamesClicked()));

    }

public slots:

    void changeNamesClicked(){
        cout << "Button ok was clicked!" << endl;
        this->close();
    }
};

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //To Do : Change to Player class names

    m_counterThrow = 0;
    m_counterRounds = 0;

    m_cubes = vector<int>(5);
    m_fixedCubes = vector<bool>(5);

    // Create Table Models
    m_modelLeftTable = new QStandardItemModel(6,1,this);
    m_modelRightTable = new QStandardItemModel(5,1,this);

    initTable();
    //QString str = QString("skldf");
    m_player1 = new Player::Player(QString("Thomas"));
    m_player2 = new Player::Player(QString("Christoph"));



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
    m_counterThrow++;
    if(m_counterThrow == 3){
        ui->pushButton->setEnabled(false);
    }
    ui->dice->setText(QString::number(m_counterThrow));
    vector<int> points = PointCalculator::calculatePointValues(m_cubes);
    ui->leftTableView->setEnabled(true);
    Player::Player currentPlayer = getCurrentPlayer();
    //ui->currentPlayer->setText(currentPlayer.getPlayerName());

    vector<int> userPoints = currentPlayer.getPointList();
    vector<int> resultPoint = vector<int>(13);

    for (int i = 0; i < points.size(); i++){
        if(userPoints[i] != -1){
            resultPoint[i] = userPoints[i];
        }else{
            resultPoint[i] = points[i];
        }
    }
    fillLeftTableWithModelData(resultPoint, 1);

    for(int i=0; i < userPoints.size(); i++){
        if(userPoints[i] != -1){
            m_modelLeftTable->item(i,1)->setEnabled(false);
        } else {
            m_modelLeftTable->item(i,1)->setEnabled(true);
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

// Start Dialog to insert user names
void MainWindow::insertNamesDialog(){
    InsertNamesDialog *dialog = new InsertNamesDialog;
    dialog->setWindowTitle("Insert Names Dialog");
    dialog->show();
}

void MainWindow::fillLeftTableWithModelData(vector<int> v, int column){
    for(int i = 0; i < v.size(); i++){
        QString value = QString::number(v[i]);
        QStandardItem *item = new QStandardItem(value);
        cout << "v[i]: " << v[i] << " value: " << value.toStdString() << endl;
        m_modelLeftTable->setItem (i, column, item);
        //m_modelLeftTable->item((i,column))->setText("<font color='red'");
    }
}

// Initialize Table Content
void MainWindow::initTable(){

    ui->centralWidget->setStyleSheet("background: rgb(220,220,220); text-align: center");
    ui->dice->setText(QString::number(m_counterThrow));

    // Set Table 1 & 2 Column Names
    m_modelLeftTable->setHorizontalHeaderItem(0, new QStandardItem(QString("Player 1")));
    m_modelLeftTable->setHorizontalHeaderItem(1, new QStandardItem(QString("Player 2")));
    m_modelRightTable->setHorizontalHeaderItem(0, new QStandardItem(QString("Player 1")));
    m_modelRightTable->setHorizontalHeaderItem(1, new QStandardItem(QString("Player 2")));

    // Add Models to Table View
    ui->leftTableView->setModel(m_modelLeftTable);
    ui->rightTableView->setModel(m_modelRightTable);

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
    image1->setPixmap(QPixmap(":/images/w1"));
    image2->setPixmap(QPixmap(":/images/w2"));
    image3->setPixmap(QPixmap(":/images/w3"));
    image4->setPixmap(QPixmap(":/images/w4"));
    image5->setPixmap(QPixmap(":/images/w5"));

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

    connect(ui->actionInstruction, SIGNAL(triggered()), this, SLOT(showInstructionDialog()));
    connect(ui->action_Change_Names, SIGNAL(triggered()), this, SLOT(showInsertNamesDialog()));
    connect(ui->action_New_Game, SIGNAL(triggered()), this, SLOT(startNewGameClicked()));
    connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(changeCubes()));
    connect(m_box1, SIGNAL(toggled(bool)), this, SLOT(setCheckbox1Slot(bool)));
    connect(m_box2, SIGNAL(toggled(bool)), this, SLOT(setCheckbox2Slot(bool)));
    connect(m_box3, SIGNAL(toggled(bool)), this, SLOT(setCheckbox3Slot(bool)));
    connect(m_box4, SIGNAL(toggled(bool)), this, SLOT(setCheckbox4Slot(bool)));
    connect(m_box5, SIGNAL(toggled(bool)), this, SLOT(setCheckbox5Slot(bool)));
    connect(ui->leftTableView, SIGNAL(clicked(const QModelIndex &)),
            this, SLOT(leftTableCellClick(const QModelIndex & )));
    connect(ui->rightTableView, SIGNAL(clicked(const QModelIndex &) ),
            this, SLOT(rightTableCellClick(const QModelIndex & )));

    ui->leftTableView->setStyleSheet("font-weight:bold; background-color: white");
    ui->leftTableView->setEnabled(false);

}


// To Do
void MainWindow::deleteAllTableContent(){
    cout << "Delete all table content" << endl;
}

Player::Player MainWindow::getCurrentPlayer()
{
    if(m_counterRounds % 2 == 0){
        return *m_player2;
    }
    return *m_player1;
}

// Slot
void MainWindow::changeCubes(){
    rollDices();
    cout << "---" << endl;
    //deleteAllTableContent();
}
// Slot
void MainWindow::showInstructionDialog(){
    InstructionDialog *dialog = new InstructionDialog;
    dialog->setWindowTitle("Instruction Dialog");
    dialog->show();
}

// Slot
void MainWindow::showInsertNamesDialog(){
    cout << "Show insert Names Dialog" << endl;
    insertNamesDialog();
}

// Slot - To Do
void MainWindow::startNewGameClicked(){
    cout << "A new Game was started!" << endl;
}



// Slot - To Do
void MainWindow::leftTableCellClick(const QModelIndex & index ){
    int row = index.row();
    int column = index.column();

    vector<int> currentPoints = m_player1->getPointList();

    if (currentPoints[row] == -1 ){
        m_player1->setPointValue(row, (PointCalculator::calculatePointValues(m_cubes)[row]));
        cout << "Klick Spalte/Reihe : " << column << " / " << row  << endl;
        m_modelLeftTable->item(row,column)->setEnabled(false);
        m_counterThrow = 0;
        ui->pushButton->setEnabled(true);
        ui->dice->setText(QString("0"));
        ui->leftTableView->setEnabled(false);
        m_box1->setChecked(false);
        m_box2->setChecked(false);
        m_box3->setChecked(false);
        m_box4->setChecked(false);
        m_box5->setChecked(false);
        m_counterRounds++;
    } else {
        cout << "Punkt schon vergeben" << endl;
    }
}

// Slot - To Do
void MainWindow::rightTableCellClick(const QModelIndex & index){
    int row = index.row();
    int column = index.column();
    cout << "Klick Spalte/Reihe : " << column << " / " << row << endl;
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
