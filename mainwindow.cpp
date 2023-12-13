#include "mainwindow.h"
#include "qpushbutton.h"
#include "ui_mainwindow.h"
#include "difficultydialog.h"
#include <QLabel>
#include <QFormLayout>
#include <QMessageBox>
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

    //sprawdzi, czy są aktywne pogodowe
    // if(enemy.nowInUse.hasFreeze()){
    //     ui->
    // }

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

        QLabel *cardLabel = new QLabel();
        if(card.getLegendary()){
            cardLabel->setText("<font color='yellow'>" + card.description() + "</font>");
        }
        else cardLabel->setText(card.description());
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

        QLabel *cardLabel = new QLabel();
        if(card.getLegendary()){
            QString dsc = card.description();
            dsc.replace("\n", "<br>");
            cardLabel->setText("<html><p><span style=\"outline: 10px solid #000000; color: #ecf754;\">" + dsc + "</span></p></html>");
        }
        else cardLabel->setText(card.description());

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

    //ustaw  wyswietlane sily
    ui->enemyMeeleeStrength->setText(QString::fromStdString(to_string(enemy.nowInUse.getMeeleeCardArray().getOverallStrength())));
    ui->enemyShootingStrength->setText(QString::fromStdString(to_string(enemy.nowInUse.getShootingCardArray().getOverallStrength())));
    ui->enemyBallisticStrength->setText(QString::fromStdString(to_string(enemy.nowInUse.getBallisticCardArray().getOverallStrength())));
    ui->playerMeeleeStrength->setText(QString::fromStdString(to_string(nowInPlayerUse.getMeeleeCardArray().getOverallStrength())));
    ui->playerShootingStrength->setText(QString::fromStdString(to_string(nowInPlayerUse.getShootingCardArray().getOverallStrength())));
    ui->playerBallisticStrength->setText(QString::fromStdString(to_string(nowInPlayerUse.getBallisticCardArray().getOverallStrength())));
}

void MainWindow::updatePlayerDeck(){

    clearLayout(ui->deckHorlLayout);

    for (const Card& card : *playerDeck.getCardArray()){

        QPushButton *button = new QPushButton(card.description());

        connect(button, &QPushButton::clicked, [=]() {
            Card cardCopy = card;
            if(!addCardWhenClicked(cardCopy)){
                QMessageBox mb;
                mb.setText("You cannot pick this card!");
                mb.exec();
            }
            else std::this_thread::sleep_for(std::chrono::seconds(1));
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
            std::this_thread::sleep_for(std::chrono::seconds(1));
        });

        QFormLayout *cardLayout = new QFormLayout;
        cardLayout->addRow(button);

        ui->deckHorlLayout->addLayout(cardLayout);
    }
}



bool MainWindow::addCardWhenClicked(Card &pickedCard){

    bool ok = false;
    //dopóki nie będzie prawidłowego wyboru, false

    if (pickedCard.getName() == "Clear Sky") { //usuwamy wszyskie karty pogodowe
        caseClearSkyPlayed(&playerDeck, &nowInPlayerUse, &enemy.nowInUse, pickedCard);
        ok = true;
    }

    //gdy wybrano pożogę
    else if (pickedCard.getName() == "Scorch") {
        if (caseScorchPlayed(&playerDeck, &nowInPlayerUse, &enemy.nowInUse, pickedCard)) {
            ok = true;
        }
        else ok = false;
    }

    // gdy wybrano battle horn
    else if (pickedCard.getName() == "Battle Horn") { //nalezy sprawdzić gdzie można dać battle horn
        if (caseBattleHornPlayed(&playerDeck, &nowInPlayerUse, pickedCard)) {
            ok = true;
        }
        else ok = false;
    }

    // gdy wybrano kartę pogodową
    else if (pickedCard.getName() == "Freeze" || pickedCard.getName() == "Fog" || pickedCard.getName() == "Rain") {
        caseWeatherPlayed(&playerDeck, &nowInPlayerUse, &enemy.nowInUse, pickedCard);
        ok = true;
    }
    //gdy wybrano manek
    //TODO//////////////////////////////////////////////////////
    //
    //
    else if (pickedCard.getName() == "Mannequin") {
        if (caseMannequinPlayed(&playerDeck, &nowInPlayerUse, pickedCard)) {
            ok = true; //wyjdz z petli gdy funkcja zwroci prawde
        }
        else ok = false; //zwróć błąd gdy zwróci false
    }

    if(!ok) return ok;

    //wykonaj te instrukcje tylko jeśli ok = true
    nowInPlayerUse.adjustStrength();
    enemy.nowInUse.adjustStrength();
    updateGameState();
    //std::this_thread::sleep_for(std::chrono::seconds(1));
    enemyDecision(&enemy, &nowInPlayerUse, &playerDeck, globalDeck);
    nowInPlayerUse.adjustStrength();
    enemy.nowInUse.adjustStrength();
    updateGameState();

    return ok;
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
    //std::this_thread::sleep_for(std::chrono::seconds(1));
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
