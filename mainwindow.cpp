#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "bubbletrouble.h"
#include <QProcess>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->startButton, SIGNAL(pressed()), this, SLOT(startGame()));
    connect(ui->actionPause, SIGNAL(triggered(bool)), this, SLOT(pauseUnpauseGame()));
    connect(ui->actionHelp, SIGNAL(triggered(bool)), this, SLOT(openReadMe()));
}

MainWindow::~MainWindow()
{
    delete ui;
    delete game;
}

void MainWindow::startGame(){

    game = new BubbleTrouble(ui->spinBox_2->value(), ui->spinBox->value());
    setCentralWidget(game);
}

void MainWindow::pauseUnpauseGame(){
    if(game != NULL){
        game->isPaused = !game->isPaused;
    }
}

void MainWindow::openReadMe(){
    QProcess *proc = new QProcess(this);
    proc->start("notepad.exe ../bubbletroubleqt/README.txt");

}
