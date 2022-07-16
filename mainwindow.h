#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include "bubbletrouble.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    BubbleTrouble *game = NULL;

private slots:
    void startGame();
    void pauseUnpauseGame();
    void openReadMe();
};

#endif // MAINWINDOW_H
