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
    ui->enemyMeeleeFrame->setStyleSheet("background-color: #FF928A;");
    ui->enemyShootingFrame->setStyleSheet("background-color: #FF928A;");
    ui->enemyBallisticFrame->setStyleSheet("background-color: #FF928A;");
    ui->playerMeeleeFrame->setStyleSheet("background-color: #8AA5FF;");
    ui->playerShootingFrame->setStyleSheet("background-color: #8AA5FF;");
    ui->playerBallisticFrame->setStyleSheet("background-color: #8AA5FF;");
}

//autor funkcji: Wes Hardaker stackoverflow
void MainWindow::clearLayout(QLayout *layout) {
    if(layout == NULL) return;

    QLayoutItem *item;

    while ((item = layout->takeAt(0)) != nullptr) {

        if (item->layout()) {
            clearLayout(item->layout());
        }

        if (item->widget()) {
            delete item->widget();
        }
        delete item;
    }
}

void MainWindow::clearAllLayouts() {
    clearLayout(ui->playerMeeleeLayout);
    clearLayout(ui->playerShootingLayout);
    clearLayout(ui->playerBallisticLayout);
    clearLayout(ui->enemyMeeleeLayout);
    clearLayout(ui->enemyShootingLayout);
    clearLayout(ui->enemyBallisticLayout);
}

void MainWindow::handleWeather(QString weatherType){
    if(weatherType == "Freeze"){
        ui->enemyMeeleeFrame->setStyleSheet("background-color: #4d3dff;");
        ui->playerMeeleeFrame->setStyleSheet("background-color: #4d3dff;");
    }
    else if(weatherType == "Fog"){
        ui->enemyShootingFrame->setStyleSheet("background-color: #636363;");
        ui->playerShootingFrame->setStyleSheet("background-color: #636363;");
    }
    else if(weatherType == "Rain"){
        ui->enemyBallisticFrame->setStyleSheet("background-color: #3d4673;");
        ui->playerBallisticFrame->setStyleSheet("background-color: #3d4673;");
    }
}

void MainWindow::restoreColors(){
    ui->enemyMeeleeFrame->setStyleSheet("background-color: #FF928A;");
    ui->enemyShootingFrame->setStyleSheet("background-color: #FF928A;");
    ui->enemyBallisticFrame->setStyleSheet("background-color: #FF928A;");
    ui->playerMeeleeFrame->setStyleSheet("background-color: #8AA5FF;");
    ui->playerShootingFrame->setStyleSheet("background-color: #8AA5FF;");
    ui->playerBallisticFrame->setStyleSheet("background-color: #8AA5FF;");
}

void MainWindow::updateCurrentCards(){

    clearAllLayouts();

    vector<Card> tempC = *enemy.nowInUse.getCardArray();
    for(Card& card : tempC){
        if(card.getName() == "Mannequin"){

            QLabel *cardLabel = new QLabel(card.description());
            cardLabel->setStyleSheet("QLabel{margin-left: 10px; border-radius: 25px; background: white; color: #4A0C46;}");
            QFormLayout *cardLayout = new QFormLayout;
            cardLayout->addRow(cardLabel);

            switch (card.getRange()){
            case MEELEE:
                ui->enemyMeeleeLayout->addLayout(cardLayout);
                break;
            case SHOOT:
                ui->enemyShootingLayout->addLayout(cardLayout);
                break;
            case BALLISTIC:
                ui->enemyBallisticLayout->addLayout(cardLayout);
                break;
            }
        }
        else if(card.getName() == "Freeze" || card.getName() == "Fog" || card.getName() == "Rain"){
            handleWeather(card.getName());
        }
        else if(card.getName() == "Battle Horn"){
            switch(card.getRange()){
            case MEELEE:
                ui->enemyMeeleeLabel->setText("<font color='red'>Meelee</font>");
                break;
            case SHOOT:
                ui->enemyShootingLabel->setText("<font color='red'>Shooting</font>");
                break;
            case BALLISTIC:
                ui->enemyBallisticLabel->setText("<font color='red'>Ballistic</font>");
                break;
            }
        }
    }

    vector<TroopCard> tempT = *enemy.nowInUse.getTroopCardArray();
    for(TroopCard& card : tempT){

        QLabel *cardLabel = new QLabel();
        QFrame *cardFrame = new QFrame();

        //wyróżnij legendarne karty

        if(card.getLegendary()){
            cardFrame->setStyleSheet("QFrame{background-color: #ffff91; border-radius: 10px;}");
        }
        else cardFrame->setStyleSheet("QFrame{background-color: white; border-radius: 10px;}");

        cardLabel->setText(card.description());
        cardLabel->setAlignment(Qt::AlignCenter);

        //tworzy layout wewnątrz QFrame (jako dziecko qframe)
        QFormLayout *cardLayout = new QFormLayout(cardFrame);

        cardLayout->addWidget(cardLabel);
        cardFrame->setFixedSize(150, 85);

        switch (card.getRange()){
        case MEELEE:
            ui->enemyMeeleeLayout->addWidget(cardFrame);
            break;
        case SHOOT:
            ui->enemyShootingLayout->addWidget(cardFrame);
            break;
        case BALLISTIC:
            ui->enemyBallisticLayout->addWidget(cardFrame);
            break;
        }
    }

    tempC = *nowInPlayerUse.getCardArray();
    for(Card& card : tempC){
        if(card.getName() == "Mannequin"){
            QLabel *cardLabel = new QLabel(card.description());
            QFormLayout *cardLayout = new QFormLayout;
            cardLabel->setStyleSheet("border: 1px solid black");
            cardLayout->addRow(cardLabel);
            switch (card.getRange()){
            case MEELEE:
                ui->playerMeeleeLayout->addLayout(cardLayout);
                break;
            case SHOOT:
                ui->playerShootingLayout->addLayout(cardLayout);
                break;
            case BALLISTIC:
                ui->playerBallisticLayout->addLayout(cardLayout);
                break;
            }
        }

        else if(card.getName() == "Freeze" || card.getName() == "Fog" || card.getName() == "Rain"){
            handleWeather(card.getName());
        }

        else if(card.getName() == "Battle Horn"){
            switch(card.getRange()){
            case MEELEE:
                ui->playerMeeleeLabel->setText("<font color='blue'>Meelee</font>");
                break;
            case SHOOT:
                ui->playerShootingLabel->setText("<font color='blue'>Shooting</font>");
                break;
            case BALLISTIC:
                ui->playerBallisticLabel->setText("<font color='blue'>Ballistic</font>");
                break;
            }
        }
    }

    //troopcardy gracza

    tempT = *nowInPlayerUse.getTroopCardArray();
    for(TroopCard& card : tempT){

        QLabel *cardLabel = new QLabel();
        QFrame *cardFrame = new QFrame();

        //wyróżnij legendarne karty

        if(card.getLegendary()){
            cardFrame->setStyleSheet("QFrame{background-color: #ffff91; border-radius: 10px;}");
        }
        else cardFrame->setStyleSheet("QFrame{background-color: white; border-radius: 10px;}");

        cardLabel->setText(card.description());
        cardLabel->setAlignment(Qt::AlignCenter);

        //tworzy layout wewnątrz QFrame (jako dziecko qframe)
        QFormLayout *cardLayout = new QFormLayout(cardFrame);

        cardLayout->addWidget(cardLabel);
        cardFrame->setFixedSize(150, 85);

        switch (card.getRange()){
        case MEELEE:
            ui->playerMeeleeLayout->addWidget(cardFrame);
            break;
        case SHOOT:
            ui->playerShootingLayout->addWidget(cardFrame);
            break;
        case BALLISTIC:
            ui->playerBallisticLayout->addWidget(cardFrame);
            break;
        }
    }

    //jezeli nie ma zadnych aktywnych kart pogody, upewnij się że kolory ui są przywrócone:
    if(!nowInPlayerUse.hasFog() && !nowInPlayerUse.hasFreeze() && !nowInPlayerUse.hasRain() &&
        !enemy.nowInUse.hasFog() && !enemy.nowInUse.hasFreeze() && !enemy.nowInUse.hasRain()){
        restoreColors();
    }


    //ustaw  wyswietlane sily
    ui->enemyMeeleeStrength->setText(QString::fromStdString(to_string(enemy.nowInUse.getMeeleeCardArray().getOverallStrength())));
    ui->enemyShootingStrength->setText(QString::fromStdString(to_string(enemy.nowInUse.getShootingCardArray().getOverallStrength())));
    ui->enemyBallisticStrength->setText(QString::fromStdString(to_string(enemy.nowInUse.getBallisticCardArray().getOverallStrength())));
    ui->playerMeeleeStrength->setText(QString::fromStdString(to_string(nowInPlayerUse.getMeeleeCardArray().getOverallStrength())));
    ui->playerShootingStrength->setText(QString::fromStdString(to_string(nowInPlayerUse.getShootingCardArray().getOverallStrength())));
    ui->playerBallisticStrength->setText(QString::fromStdString(to_string(nowInPlayerUse.getBallisticCardArray().getOverallStrength())));

    ui->playerOverallStrength->setText(QString::fromStdString(to_string(nowInPlayerUse.getOverallStrength())));
    ui->enemyOverallStrength->setText(QString::fromStdString(to_string(enemy.nowInUse.getOverallStrength())));
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
            //else std::this_thread::sleep_for(std::chrono::seconds(1));
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
            //std::this_thread::sleep_for(std::chrono::seconds(1));
        });

        QFormLayout *cardLayout = new QFormLayout;
        cardLayout->addRow(button);

        ui->deckHorlLayout->addLayout(cardLayout);
    }
}

bool MainWindow::askUserBattleHorn(Card pickedCard, vector<bool> canPlace){
    QMessageBox msgBox;

    msgBox.setWindowTitle("Where do you want to put a battle horn?");
    msgBox.setText("Pick one option:");

    QPushButton *button0 = nullptr, *button1 = nullptr, *button2 = nullptr;

    if(canPlace[0]){
        button0 = msgBox.addButton("Meelee", QMessageBox::ActionRole);
    }
    if(canPlace[1]){
        button1 = msgBox.addButton("Shooting", QMessageBox::ActionRole);
    }
    if(canPlace[2]){
        button2 = msgBox.addButton("Ballistic", QMessageBox::ActionRole);
    }

    msgBox.exec();

    if(msgBox.clickedButton() == button0){
        nowInPlayerUse.addCard(Card(pickedCard.getName(), MEELEE, pickedCard.getId()));
        playerDeck.removeCard(pickedCard);
        return true;
    }
    else if(msgBox.clickedButton() == button1){
        nowInPlayerUse.addCard(Card(pickedCard.getName(), SHOOT, pickedCard.getId()));
        playerDeck.removeCard(pickedCard);
        return true;
    }
    else if(msgBox.clickedButton() == button2){
        nowInPlayerUse.addCard(Card(pickedCard.getName(), BALLISTIC, pickedCard.getId()));
        playerDeck.removeCard(pickedCard);
        return true;
    }
    return false;
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
        vector<bool> result = caseBattleHornPlayed(&nowInPlayerUse);
        if (result[0] || result[1] || result[2]) {
            ok = askUserBattleHorn(pickedCard, result);
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
