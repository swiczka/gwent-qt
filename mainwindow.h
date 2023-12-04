#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "cardList.h"
#include "enemy.h"
#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    Enemy enemy;
    cardList nowInPlayerUse, playerDeck, globalDeck;
    void updatePlayerDeck();
    void initializeDecks(int diff);
    void updateGameState();
    ~MainWindow();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
