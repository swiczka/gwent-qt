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
    void updateCurrentCards();
    void initializeDecks(int diff);
    void updateGameState();
    void clearAllLayouts();
    void clearLayout(QLayout *layout);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    void handleWeather(QString weatherType);
    void restoreColors();
    bool askUserBattleHorn(Card pickedCard, vector<bool> canPlace);

private slots:
    bool addCardWhenClicked(Card &pickedCard);
    void addTroopCardWhenClicked(TroopCard &pickedCard);
};

#endif // MAINWINDOW_H
