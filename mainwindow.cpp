#include "mainwindow.h"
#include "qpushbutton.h"
#include "ui_mainwindow.h"
#include "difficultydialog.h"
#include <QLabel>
#include <QFormLayout>
#include <thread>
#include <chrono>
#include "coreGame.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->enemyFrame->setStyleSheet("background-color: #FF928A;");
    ui->playerFrame->setStyleSheet("background-color: #8AA5FF;");
}

void MainWindow::clearLayout(QLayout *layout) {
    QLayoutItem *item;
    while ((item = layout->takeAt(0)) != nullptr) {
        if (item->layout()) {
            // Jeśli element to inny layout, rekurencyjnie go usuń
            clearLayout(item->layout());
        }
        if (item->widget()) {
            // Jeśli element to widget, zwolnij pamięć i usuń go
            delete item->widget();
        }
        delete item;
    }
}

// Funkcja do czyszczenia wszystkich layoutów
void MainWindow::clearAllLayouts() {
    clearLayout(ui->playerMeeleeLayout);
    clearLayout(ui->playerShootingLayout);
    clearLayout(ui->playerBallisticLayout);
    clearLayout(ui->enemyMeeleeLayout);
    clearLayout(ui->enemyShootingLayout);
    clearLayout(ui->enemyBallisticLayout);
}

void MainWindow::updateCurrentCards(){

    clearAllLayouts();

    vector<Card> tempC = *enemy.nowInUse.getCardArray();
    for(Card& card : tempC){
        if(card.getName() == "Mannequin"){
            QLabel *cardLabel = new QLabel(card.description());
            QFormLayout *cardLayout = new QFormLayout;
            cardLayout->addRow(cardLabel);
            switch (card.getRange()){
            case 1:
                ui->enemyMeeleeLayout->addLayout(cardLayout);
                break;
            case 2:
                ui->enemyShootingLayout->addLayout(cardLayout);
                break;
            case 3:
                ui->enemyBallisticLayout->addLayout(cardLayout);
                break;
            }
        }
    }

    vector<TroopCard> tempT = *enemy.nowInUse.getTroopCardArray();
    for(TroopCard& card : tempT){

        QLabel *cardLabel = new QLabel(card.description());
        QFormLayout *cardLayout = new QFormLayout;
        cardLayout->addRow(cardLabel);

        switch (card.getRange()){
        case 1:
            ui->enemyMeeleeLayout->addLayout(cardLayout);
            break;
        case 2:
            ui->enemyShootingLayout->addLayout(cardLayout);
            break;
        case 3:
            ui->enemyBallisticLayout->addLayout(cardLayout);
            break;
        }
    }

    tempC = *nowInPlayerUse.getCardArray();
    for(Card& card : tempC){
        if(card.getName() == "Mannequin"){
            QLabel *cardLabel = new QLabel(card.description());
            QFormLayout *cardLayout = new QFormLayout;
            cardLayout->addRow(cardLabel);
            switch (card.getRange()){
            case 1:
                ui->playerMeeleeLayout->addLayout(cardLayout);
                break;
            case 2:
                ui->playerShootingLayout->addLayout(cardLayout);
                break;
            case 3:
                ui->playerBallisticLayout->addLayout(cardLayout);
                break;
            }
        }
    }

    tempT = *nowInPlayerUse.getTroopCardArray();
    for(TroopCard& card : tempT){

        QLabel *cardLabel = new QLabel(card.description());
        QFormLayout *cardLayout = new QFormLayout;
        cardLayout->addRow(cardLabel);

        switch (card.getRange()){
        case 1:
            ui->playerMeeleeLayout->addLayout(cardLayout);
            break;
        case 2:
            ui->playerShootingLayout->addLayout(cardLayout);
            break;
        case 3:
            ui->playerBallisticLayout->addLayout(cardLayout);
            break;
        }
    }
}

void MainWindow::updatePlayerDeck(){

    clearLayout(ui->deckHorlLayout);

    for (const Card& card : *playerDeck.getCardArray()){
        QPushButton *button = new QPushButton(card.description());

        connect(button, &QPushButton::clicked, [=]() {
            Card cardCopy = card;
            addCardWhenClicked(cardCopy);
        });

        QFormLayout *cardLayout = new QFormLayout;
        cardLayout->addRow(button);

        ui->deckHorlLayout->addLayout(cardLayout);
    }

    for (const TroopCard& card : *playerDeck.getTroopCardArray()){
        QPushButton *button = new QPushButton(card.description());

        connect(button, &QPushButton::clicked, [=]() {
            TroopCard troopCardCopy = card;
            addTroopCardWhenClicked(troopCardCopy);
        });

        QFormLayout *cardLayout = new QFormLayout;
        cardLayout->addRow(button);

        ui->deckHorlLayout->addLayout(cardLayout);
    }
}



void MainWindow::addCardWhenClicked(Card &pickedCard){

    bool leaveLoop = false;
    //dopóki nie będzie prawidłowego wyboru, false
    while(!leaveLoop){

        if (pickedCard.getName() == "Clear Sky") { //usuwamy wszyskie karty pogodowe
            caseClearSkyPlayed(&playerDeck, &nowInPlayerUse, &enemy.nowInUse, pickedCard);
            leaveLoop = true;
        }

        //gdy wybrano pożogę
        else if (pickedCard.getName() == "Scorch") {
            if (caseScorchPlayed(&playerDeck, &nowInPlayerUse, &enemy.nowInUse, pickedCard)) {
                leaveLoop = true;
            }
            else continue;
        }

        // gdy wybrano battle horn
        else if (pickedCard.getName() == "Battle Horn") { //nalezy sprawdzić gdzie można dać battle horn
            if (caseBattleHornPlayed(&playerDeck, &nowInPlayerUse, pickedCard)) {
                leaveLoop = true;
            }
            else continue;
        }

        // gdy wybrano kartę pogodową
        else if (pickedCard.getName() == "Freeze" || pickedCard.getName() == "Fog" || pickedCard.getName() == "Rain") {
            caseWeatherPlayed(&playerDeck, &nowInPlayerUse, &enemy.nowInUse, pickedCard);
            leaveLoop = true;
        }
        //gdy wybrano manekina

        //TODO//////////////////////////////////////////////////////
        //
        //
        else if (pickedCard.getName() == "Mannequin") {
            if (caseMannequinPlayed(&playerDeck, &nowInPlayerUse, pickedCard)) {
                leaveLoop = true; //wyjdz z petli gdy funkcja zwroci prawde
            }
            else continue; //zwróć błąd gdy zwróci false
        }

        nowInPlayerUse.adjustStrength();
        enemy.nowInUse.adjustStrength();
        updateGameState();
        std::this_thread::sleep_for(std::chrono::seconds(1));
        enemyDecision(&enemy, &nowInPlayerUse, &playerDeck, globalDeck);
        nowInPlayerUse.adjustStrength();
        enemy.nowInUse.adjustStrength();
        updateGameState();
    }
}

void MainWindow::addTroopCardWhenClicked(TroopCard &pickedCard){

    qDebug() << "You've chosen " << pickedCard.getName();

    if (pickedCard.getSpy()) { //sprawdzamy czy wybrano szpiega
        caseSpyPlayed(&playerDeck, &nowInPlayerUse, &enemy.nowInUse, pickedCard, globalDeck);
    }

    else { //nie szpieg
        nowInPlayerUse.addTroopCard(pickedCard);
        playerDeck.removeTroopCard(pickedCard);
    }
    nowInPlayerUse.adjustStrength();
    enemy.nowInUse.adjustStrength();
    updateGameState();
    std::this_thread::sleep_for(std::chrono::seconds(1));
    enemyDecision(&enemy, &nowInPlayerUse, &playerDeck, globalDeck);
    nowInPlayerUse.adjustStrength();
    enemy.nowInUse.adjustStrength();
    updateGameState();
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
    this->updateCurrentCards();
}

MainWindow::~MainWindow()
{
    delete ui;
}
