#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "Mouses.h"
#include <QSignalMapper>

MineSweeper meMineSweeper;
QPushButton *buttons[100][100];

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_type_Play_currentIndexChanged(int index)
{
    if(index==0)
    {
        on_choose_play1_widgetRemoved(index);
        meMineSweeper.setPlayingOfIt(index);
    }
    else if(index==1)
    {
        on_choose_play1_widgetRemoved(index);
        meMineSweeper.setPlayingOfIt(index);
        ui->bomb_count->setRange(0.00, 1.00);
        ui->bomb_count->setSingleStep(0.10);
    }
    else if(index==2)
    {
        on_choose_play1_widgetRemoved(index);
        meMineSweeper.setPlayingOfIt(index);
    }
}


void MainWindow::on_choose_play1_widgetRemoved(int index)
{
    ui->choose_play1->setCurrentIndex(index);
}


void MainWindow::on_input_Board_2_textChanged(const QString &arg1)
{
    meMineSweeper.setBoardName(ui->input_Board_2->displayText().toStdString());
}


void MainWindow::on_Rows_count_6_valueChanged(int arg1)
{
    meMineSweeper.setRows(arg1);
}


void MainWindow::on_Cows_count_6_valueChanged(int arg1)
{
    meMineSweeper.setCols(arg1);
}


void MainWindow::on_Bomb_count_6_valueChanged(int arg1)
{
    meMineSweeper.setBomb(arg1);
}


void MainWindow::on_Rows_count_7_valueChanged(int arg1)
{
    meMineSweeper.setRows(arg1);
}


void MainWindow::on_Cows_count_7_valueChanged(int arg1)
{
    meMineSweeper.setCols(arg1);
}

void MainWindow::on_bomb_count_valueChanged(double arg1)
{
    meMineSweeper.setBomb(arg1);
}


void MainWindow::on_button_Load_2_clicked()
{
    meMineSweeper.setTheFinalString();
    meMineSweeper.Load(meMineSweeper.theVauleOfInputs());
}


void MainWindow::on_button_Load_8_clicked()
{
    meMineSweeper.setTheFinalString();
    meMineSweeper.Load(meMineSweeper.theVauleOfInputs());
}


void MainWindow::on_button_Load_9_clicked()
{
    meMineSweeper.setTheFinalString();
    meMineSweeper.Load(meMineSweeper.theVauleOfInputs());
}


void MainWindow::on_button_Print_GameBoard_clicked()
{
    meMineSweeper.setTypeOfIt("Print");
    meMineSweeper.setSomething("GameBoard");
    meMineSweeper.Print(meMineSweeper.theVauleOfInputs());
}


void MainWindow::on_button_Print_GameAnswer_clicked()
{
    meMineSweeper.setTypeOfIt("Print");
    meMineSweeper.setSomething("GameAnswer");
    meMineSweeper.Print(meMineSweeper.theVauleOfInputs());
}


void MainWindow::on_button_Print_GameState_clicked()
{
    meMineSweeper.setTypeOfIt("Print");
    meMineSweeper.setSomething("GameState");
    meMineSweeper.Print(meMineSweeper.theVauleOfInputs());
}

void MainWindow::on_button_Start_Game_clicked()
{
    meMineSweeper.StartGame();
    if(meMineSweeper.GameState()==1)
    {
        setButton();
        ui->choose_play2->setCurrentIndex(1);
        ui->Bomb_count->setText(QString::fromStdString(meMineSweeper.BombCount()));
        ui->flag_count->setText(QString::fromStdString(meMineSweeper.FlagCount()));
        ui->open_blank_count->setText(QString::fromStdString(meMineSweeper.OpenBlankCount()));
        ui->remain_blank_count->setText(QString::fromStdString(meMineSweeper.RemainBlankCount()));
    }
}

void MainWindow::setButton()
{
    ui->gridLayout_3->removeWidget(ui->keep_layout);
    delete ui->keep_layout;

    for(int i=0;i<meMineSweeper.Rows();i++)
    {
        for(int j=0;j<meMineSweeper.Cols();j++)
        {
            QPalette palette;
            palette.setColor(QPalette::Background, QColor(255,255,255));
            buttons[i][j] = new QPushButton;
            buttons[i][j]->setFixedSize(80,80);
            buttons[i][j]->setAutoFillBackground(true);
            buttons[i][j]->setPalette(palette);
            ui->gridLayout_3->addWidget(buttons[i][j], i, j);
            connect(buttons[i][j], SIGNAL(clicked()), SLOT(setClick(int i,int j)));
        }
    }
}

//QObject::connect(buttons[i][j], SIGNAL(clicked()), SLOT(setClick()));

void MainWindow::setClick(int i,int j)
{
    if(meMineSweeper.checkCilck()==1)
    {
        meMineSweeper.setTypeOfIt("LeftClick");
        meMineSweeper.setSomething(to_string(i));
        meMineSweeper.setBoardName(to_string(j));
        meMineSweeper.setTheFinalString();
        meMineSweeper.LeftClick(meMineSweeper.theVauleOfInputs());
    }
    else if(meMineSweeper.checkCilck()==0)
    {
        meMineSweeper.setTypeOfIt("RightClick");
        meMineSweeper.setSomething(to_string(i));
        meMineSweeper.setBoardName(to_string(j));
        meMineSweeper.setTheFinalString();
        meMineSweeper.RightClick(meMineSweeper.theVauleOfInputs());
    }
}

void Mouses::mousePressEvent(QMouseEvent *event)
{
    if(event->button()==Qt::LeftButton)
    {
        meMineSweeper.changeClick();
    }
    else if(event->button()==Qt::RightButton)
    {
        meMineSweeper.changeClick();
    }
}

void openBlank(int row,int col)
{
    QPalette palette;
    palette.setColor(QPalette::Background, QColor(128,128,128));
    buttons[row][col]->setAutoFillBackground(true);
    buttons[row][col]->setPalette(palette);
    if(meMineSweeper.whatIsInside(row,col)!="0")
    {
        buttons[row][col]->setText(QString::fromStdString(meMineSweeper.whatIsInside(row,col)));
    }
    buttons[row][col]->setEnabled(false);
}

void MainWindow::on_Print_gameboard_clicked()
{
    meMineSweeper.setTypeOfIt("Print");
    meMineSweeper.setSomething("GameBoard");
    meMineSweeper.Print(meMineSweeper.theVauleOfInputs());
}


void MainWindow::on_Print_gameanswer_clicked()
{
    meMineSweeper.setTypeOfIt("Print");
    meMineSweeper.setSomething("GameAnswer");
    meMineSweeper.Print(meMineSweeper.theVauleOfInputs());
}


void MainWindow::on_Print_gamestate_clicked()
{
    meMineSweeper.setTypeOfIt("Print");
    meMineSweeper.setSomething("GameState");
    meMineSweeper.Print(meMineSweeper.theVauleOfInputs());
}

void MainWindow::on_pushButton_clicked()
{
    openBlank(0,0);
}

