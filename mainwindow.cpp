#include "mainwindow.h"
#include "qpushbutton.h"
#include "ui_mainwindow.h"
#include "difficultydialog.h"
#include <QLabel>
#include <QFormLayout>
#include "coreGame.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->enemyFrame->setStyleSheet("background-color: #FF928A;");
    ui->playerFrame->setStyleSheet("background-color: #8AA5FF;");
}

void MainWindow::updatePlayerDeck(){

    for (Card &card : *playerDeck.getCardArray()){

        QLabel *label = new QLabel(card.getName() + "\nRange: " + card.getStrRange() + "\n\n");
        QPushButton *button = new QPushButton("Choose");

        QFormLayout *cardLayout = new QFormLayout;

        cardLayout->addRow(label);
        cardLayout->addRow(button);

        ui->deckHorlLayout->addLayout(cardLayout);

    }

    for (TroopCard &card : *playerDeck.getTroopCardArray()){

        QString description = "";

        if (card.getLegendary()) {
            description += "Legendary ";
        }
        if (card.getCombo()) {
            description += "Combo ";
        }
        if (card.getSpy()) {
            description += "Spy ";
        }

        QLabel *label = new QLabel(card.getName() + "\nRange: " + card.getStrRange() +
                                   "\nStrength: " + QString::number(card.getStrength()) + "\n" + description);
        QPushButton *button = new QPushButton("Choose");

        QFormLayout *cardLayout = new QFormLayout;

        cardLayout->addRow(label);
        cardLayout->addRow(button);

        ui->deckHorlLayout->addLayout(cardLayout);

    }



}

void MainWindow::initializeDecks(int diff){
    //     //
    //     //
    //     // globalDeck - zbi?r zawieraj?cy wszystkie mo?liwe karty
    //     //
    //     // playerDeck - pocz?tkowa talia gracza
    //     // nowInPlayerUse - aktywne karty gracza
    //     //
    //     //

    globalDeck.readCardsFromFile();
    playerDeck = prepareDeck(globalDeck);
    enemy.deck = prepareDeck(globalDeck);
    enemy.difficulty = diff;
}

void MainWindow::updateGameState(){
    this->updatePlayerDeck();
}

MainWindow::~MainWindow()
{
    delete ui;
}
