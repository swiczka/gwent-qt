#pragma once

#include "coreGame.h"
#include <random>
//#include <thread>
#include <unordered_set>
//#include <unordered_map>

bool enemyEnds = false;
bool playerEnds = false;



#define MAX_TROOP_COUNT 6
#define MAX_OTHER_COUNT 3

cardList prepareDeck(cardList allCards, bool easier) {
    cardList newPlayerDeck;
    allCards.shuffleDeck();

    //add troops first
    if(easier){
        int alreadyAdded = 0, iter = 0;

        while(alreadyAdded != MAX_TROOP_COUNT){
            TroopCard toAdd = allCards.getTroopCard(iter);
            iter++;
            if(!toAdd.getLegendary() && (toAdd.getStrength() < 10)){
                newPlayerDeck.addTroopCard(toAdd);
                alreadyAdded++;
            }
        }
    }
    else{
        for (int i = 0; i < MAX_TROOP_COUNT; i++) {
            newPlayerDeck.addTroopCard(allCards.getTroopCard(i));
        }
    }

    for (int i = 0; i < MAX_OTHER_COUNT; i++) {
        newPlayerDeck.addCard(allCards.getCard(i));
    }
    return newPlayerDeck;
}

void caseClearSkyPlayed(cardList* deck, cardList* nowInPickingUse, cardList* nowInVictimUse, Card pickedCard) {
    nowInPickingUse->removeWeatherCards();
    nowInVictimUse->removeWeatherCards();
    deck->removeCard(pickedCard);
}

void caseWeatherPlayed(cardList* deck, cardList* nowInPickingUse, cardList* nowInVictimUse, Card pickedCard) {
    deck->removeCard(pickedCard);
    nowInPickingUse->addCard(pickedCard);
    nowInVictimUse->addCard(pickedCard);
}

void caseSpyPlayed(cardList* deck, cardList* nowInVictimUse, TroopCard pickedCard, cardList globalDeck) {
    deck->removeTroopCard(pickedCard);
    deck->addTwoCards(globalDeck);
    nowInVictimUse->addTroopCard(pickedCard);
}

bool caseMannequinPlayed(cardList* nowInUse) {
    //zwroc true, gdy sie powiodlo, false gdy nie
    //gdy wybrano manekina
    //sprawdz czy sa wgl jakies karty do podmianki
    if (nowInUse->getNonLegendaryTroops().getTroopCardSize() == 0) {
        qDebug() << "There are no cards to replace!";
        return false;
    }
    else return true;
}

void caseEnemyMannequinPlayed(Enemy* enemy, Card card, TroopCard cardToReplace){
    enemy->deck.removeCard(card);
    enemy->nowInUse.addCard(Card("Mannequin", cardToReplace.getRange(), card.getId()));
    enemy->nowInUse.removeTroopCard(cardToReplace);
    enemy->deck.addTroopCard(cardToReplace);
}



QString enemyDecision(Enemy* enemy, cardList* nowInPlayerUse, cardList* playerDeck, cardList globalDeck) {

    srand((unsigned)time(NULL));
    int random = rand();
    bool canPlay = false;
    bool troopCardPicked = false;
    TroopCard troopCard;
    Card card;



    int hornId = 0;
    switch (enemy->difficulty) {


    case 1: //gdy łatwa trudność

        //break - gdy przeciwnik podejmie decyzje

        while (!canPlay) {

            //sprawdź czy zakończyć grę
            if (enemy->deck.getCardSize() + enemy->deck.getTroopCardSize() == 0 ||
                enemy->deck.hasMannequinsOnly()) {
                qDebug() << "ENEMY SURRENDERS!";
                canPlay = true;
                enemyEnds = true;
                break;
            }

            random_device rd;
            mt19937_64 gen(rd());
            int maxSize = enemy->deck.getCardSize() + enemy->deck.getTroopCardSize();
            uniform_int_distribution<> rCardDistribution(1, maxSize);

            int randomIndex = rCardDistribution(gen);

            if (randomIndex <= enemy->deck.getTroopCardSize()) { //gdy wylosowało troopcard

                troopCard = enemy->deck.pickTroopCard(randomIndex);
                troopCardPicked = true;

                if (troopCard.getSpy()) {
                    caseSpyPlayed(&enemy->deck, nowInPlayerUse, troopCard, globalDeck);
                    canPlay = true;
                    qDebug() << "ENEMY picked " << troopCard.getName();
                    break;
                }
                else {
                    enemy->deck.removeTroopCard(troopCard);
                    enemy->nowInUse.addTroopCard(troopCard);
                    canPlay = true;
                    qDebug() << "ENEMY picked " << troopCard.getName();
                    break;
                }
            }
            else if (randomIndex - enemy->deck.getTroopCardSize() > 0) { //gdy wylosowalo card

                card = enemy->deck.pickCard(randomIndex);

                if (card.getName() == "Clear Sky") {
                    caseClearSkyPlayed(&enemy->deck, &enemy->nowInUse, nowInPlayerUse, card);
                    canPlay = true;
                    qDebug() << "ENEMY picked " << card.getName();
                    break;
                }

                else if (card.getName() == "Scorch") {
                    if (caseEnemyScorchPlayed(&enemy->deck, &enemy->nowInUse, nowInPlayerUse, card)) {
                        canPlay = true;
                        qDebug() << "ENEMY picked " << card.getName();
                        break;
                    }
                    else continue;
                }
                else if (card.getName() == "Battle Horn") {
                    if (caseEnemyBattleHornPlayed(&enemy->deck, &enemy->nowInUse, card)) {
                        canPlay = true;
                        qDebug() << "ENEMY picked " << card.getName();
                        break;
                    }
                    else continue;
                }
                else if (card.getName() == "Freeze" || card.getName() == "Fog" || card.getName() == "Rain") {
                    caseWeatherPlayed(&enemy->deck, &enemy->nowInUse, nowInPlayerUse, card);
                    canPlay = true;
                    qDebug() << "ENEMY picked " << card.getName();
                    break;
                }
                else if (card.getName() == "Mannequin") {
                    continue;
                }
            }
            else {
                qDebug() << "zly indeks";
                continue;
            }
        }
        break;







    case 2:

        qDebug() << "Przeciwnik myśli...";
        //najpierw poszukaj szpiega:
        hornId = enemy->deck.hasHorn();
        troopCard = enemy->deck.hasSpy();
        if (troopCard.getName() != "none"){
            caseSpyPlayed(&enemy->deck, nowInPlayerUse, troopCard, globalDeck);
            troopCardPicked = true;
            break;
        }


        ////////////////////////////////////ROZWAŻ MANEKINA//////////////////////
        ///
        ///
        /// tymczasowo daj manekin na mCard, szpiega na mTroopCard
        card = enemy->deck.hasMannequins();
        troopCard = enemy->nowInUse.hasSpy();

        if(card.getName() != "none" && !troopCard.getLegendary() && troopCard.getName() != "none"){
            caseEnemyMannequinPlayed(enemy, card, troopCard);
            qDebug() << "ENEMY picked Mannequin";
            break;
        }
        //
        //
        card = Card();
        troopCard = TroopCard();
        //////////////////////////////////////////////////////////////////////////
        ///

        //potem zobacz troopCard
        if (enemy->deck.getTroopCardSize() > 0 && random % 10 > 5) {
            //zagraj troopcard
            troopCardPicked = true;
            troopCard = enemy->deck.getTroopCard(0);
            enemy->deck.removeTroopCard(troopCard);
            enemy->nowInUse.addTroopCard(troopCard);
            qDebug() << "ENEMY picked " << troopCard.getName();
            break;
        }

        ///////////////////////////////// ROZWAŻ POGODOWE //////////////////////////////
        //
        //
        if (enemy->deck.hasFreeze() && nowInPlayerUse->getMeeleeCardArray().getNonLegendaryTroops().getOverallStrength() >
            enemy->nowInUse.getMeeleeCardArray().getNonLegendaryTroops().getOverallStrength()) {

            card = Card("Freeze", 1, 24);
            caseWeatherPlayed(&enemy->deck, &enemy->nowInUse, nowInPlayerUse, card);
            qDebug() << "ENEMY picked " << card.getName();
            break;
        }
        if (enemy->deck.hasFog() && nowInPlayerUse->getShootingCardArray().getNonLegendaryTroops().getOverallStrength() >
            enemy->nowInUse.getShootingCardArray().getNonLegendaryTroops().getOverallStrength()) {

            card = Card("Fog", 2, 25);
            caseWeatherPlayed(&enemy->deck, &enemy->nowInUse, nowInPlayerUse, card);
            qDebug() << "ENEMY picked " << card.getName();
            break;
        }
        else if (enemy->deck.hasRain() && nowInPlayerUse->getBallisticCardArray().getNonLegendaryTroops().getOverallStrength() >
            enemy->nowInUse.getBallisticCardArray().getNonLegendaryTroops().getOverallStrength()) {

            card = Card("Rain", 3, 26);
            caseWeatherPlayed(&enemy->deck, &enemy->nowInUse, nowInPlayerUse, card);
            qDebug() << "ENEMY picked " << card.getName();
            break;
        }

        //rozważ clear sky

        if (enemy->deck.hasClearSky()){

            //jeżeli pozytywne to przeciwnik mocniejszy
            int originalPointDifference = enemy->nowInUse.getOverallStrength() - nowInPlayerUse->getOverallStrength();
            bool activeWeatherNow[3] = { nowInPlayerUse->hasFreeze(), nowInPlayerUse->hasFog(), nowInPlayerUse->hasRain() };

            enemy->nowInUse.removeWeatherCards();
            nowInPlayerUse->removeWeatherCards();

            int newPointDifference = enemy->nowInUse.getOverallStrength() - nowInPlayerUse->getOverallStrength();

            if(newPointDifference > originalPointDifference){ //jeżeli opłaca się zagrać clear sky
                card = Card("Clear Sky", 4, 27);
                enemy->deck.removeCard(card);
                qDebug() << "ENEMY picked " << card.getName();
                break;

            }
            else{ //nie opłaca się, przywróć karty
                if(activeWeatherNow[0]){
                    enemy->nowInUse.addCard(Card("Freeze", 1, 24));
                    nowInPlayerUse->addCard(Card("Freeze", 1, 24));
                }
                if(activeWeatherNow[1]){
                    enemy->nowInUse.addCard(Card("Fog", 2, 25));
                    nowInPlayerUse->addCard(Card("Fog", 2, 25));
                }
                if(activeWeatherNow[2]){
                    enemy->nowInUse.addCard(Card("Fog", 3, 26));
                    nowInPlayerUse->addCard(Card("Fog", 3, 26));
                }
            }
        }


        //
        //
        ////////////////////////////////////////////////////////////////////////

        //////////////////////// ROZWAŻ BATTLE HORN ////////////////////////////
        //
        //
        if (hornId > 0 && enemy->nowInUse.getNonLegendaryTroops().getOverallStrength() > 14) {

            card = Card("Battle Horn", 4, hornId);
            caseEnemyBattleHornPlayed(&enemy->deck, &enemy->nowInUse, card);
            qDebug() << "ENEMY picked " << card.getName();
            break;

        }
        //
        //
        /////////////////////////////////////////////////////////////

        //////////////////////////ROZWAŻ POŻOGĘ/////////////////////////////////
        //
        //
        //TODO
        //
        //
        if (enemy->deck.hasScorch() &&
            enemy->nowInUse.getStrongestNonlegendCardSum() < nowInPlayerUse->getStrongestNonlegendCardSum()) {
            if(caseEnemyScorchPlayed(&enemy->deck, &enemy->nowInUse, nowInPlayerUse, card)){
                qDebug() << "ENEMY picked Scorch";
                break;
            }
        }
        //
        //
        ////////////////////////////////////////////////////////////////////////


        if (enemy->deck.getTroopCardSize() > 0){
            troopCardPicked = true;
            troopCard = enemy->deck.getTroopCard(0);
            enemy->deck.removeTroopCard(troopCard);
            enemy->nowInUse.addTroopCard(troopCard);
            qDebug() << "ENEMY picked " << troopCard.getName();
            break;
        }

        {
            qDebug() << "ENEMY SURRENDERS!";
            enemyEnds = true;
            break;
        }
        break;

    default:
        qDebug() << "Invalid argument";
        throw invalid_argument("Invalid argument!");
    }
    enemy->nowInUse.adjustStrength(globalDeck);
    nowInPlayerUse->adjustStrength(globalDeck);

    if(enemyEnds) return "none";
    else if(troopCardPicked){
        qDebug() << "TroopCard picked!";
        return troopCard.getName();
    }
    else return card.getName();
}


bool caseEnemyScorchPlayed(cardList* deck, cardList* nowInPickingUse, cardList* nowInVictimUse, Card& pickedCard) {
    //zwroc false jeśli nie ma kart do usunięcia, true jeśli się da usunąć
    //sprawdz czy sa wgl jakies karty do usuniecia
    if (nowInPickingUse->getNonLegendaryTroops().getTroopCardSize() == 0 &&
        nowInVictimUse->getNonLegendaryTroops().getTroopCardSize() == 0) {

        return false;
    }

    // wybieramy najsilniejsze nielegendarne karty
    int maxStrength = 0;

    vector<TroopCard> tempP = *nowInPickingUse->getNonLegendaryTroops().getTroopCardArray();
    vector<TroopCard> tempV = *nowInVictimUse->getNonLegendaryTroops().getTroopCardArray();

    //ustalamy max strength
    for (const TroopCard& card : tempP) {
        if (maxStrength <= card.getStrength())
            maxStrength = card.getStrength();
    }
    for (const TroopCard& card : tempV) {
        if (maxStrength <= card.getStrength())
            maxStrength = card.getStrength();
    }

    nowInPickingUse->removeByStrength(maxStrength);
    nowInVictimUse->removeByStrength(maxStrength);
    deck->removeCard(pickedCard);
    return true;
}

bool caseScorchPlayed(cardList* deck, cardList* nowInPickingUse, cardList *nowInVictimUse, Card& pickedCard) {
    //zwroc false jeśli nie ma kart do usunięcia, true jeśli się da usunąć
    //sprawdz czy sa wgl jakies karty do usuniecia
    if (nowInPickingUse->getNonLegendaryTroops().getTroopCardSize() <= 0 &&
        nowInVictimUse->getNonLegendaryTroops().getTroopCardSize() <= 0) {
        qDebug() << "There are no cards to remove!" << "\n";

        return false;
    }

    // wybieramy najsilniejsze nielegendarne karty
    int maxStrength = 0;

    //ustalamy max strength
    vector<TroopCard> tempP = *nowInPickingUse->getNonLegendaryTroops().getTroopCardArray();
    vector<TroopCard> tempV = *nowInVictimUse->getNonLegendaryTroops().getTroopCardArray();

    for (const TroopCard& card : tempP) {
        if (maxStrength <= card.getStrength()) maxStrength = card.getStrength();
    }
    for (const TroopCard& card : tempV) {
        if (maxStrength <= card.getStrength()) maxStrength = card.getStrength();
    }

    nowInPickingUse->removeByStrength(maxStrength);
    nowInVictimUse->removeByStrength(maxStrength);
    deck->removeCard(pickedCard);
    return true;
}

vector<bool> caseBattleHornPlayed(cardList* nowInUse) {
    vector<bool>availableSpots = { true, true, true };
    if (nowInUse->getMeeleeCardArray().hasHorn()) {
        availableSpots[0] = false;
    }
    if (nowInUse->getShootingCardArray().hasHorn()) {
        availableSpots[1] = false;
    }
    if (nowInUse->getBallisticCardArray().hasHorn()) {
        availableSpots[2] = false;
    }
    return availableSpots;
}

bool caseEnemyBattleHornPlayed(cardList* deck, cardList* nowInUse, Card& pickedCard) {
    vector<bool>availableSpots = { true, true, true };
    if (nowInUse->getMeeleeCardArray().hasHorn()) {
        availableSpots[0] = false;
    }
    if (nowInUse->getShootingCardArray().hasHorn()) {
        availableSpots[1] = false;
    }
    if (nowInUse->getBallisticCardArray().hasHorn()) {
        availableSpots[2] = false;
    }

    int strengths[3];
    // indeks 0 -> meelee
    // indeks 1 -> shooting
    // indeks 2-> ballistic

    strengths[0] = nowInUse->getMeeleeCardArray().getNonLegendaryTroops().getOverallStrength();
    strengths[1] = nowInUse->getShootingCardArray().getNonLegendaryTroops().getOverallStrength();
    strengths[2] = nowInUse->getBallisticCardArray().getNonLegendaryTroops().getOverallStrength();

    // znajdź największą siłę
    int maxStrength = 0;
    int searchedIndex = -1;

    for (int i = 0; i <3; i++) {
        if (strengths[i] > maxStrength && availableSpots[i] == true) {
            maxStrength = strengths[i];
            searchedIndex = i;
        }
    }

    if (searchedIndex == -1) return false;
    else {
        nowInUse->addCard(Card(pickedCard.getName(), searchedIndex + 1, pickedCard.getId()));
        deck->removeCard(pickedCard);
        return true;
    }
}

void cardList::adjustStrength(cardList& globalDeck) {
    /////////////////// ZALEZNE OD KART POGODOWYCH/////////////////////////
    //
    //
    this->restoreDefaultStrength(globalDeck); ///// !!! przywracamy domyślne wartości sił kart ////////

    if (find(cardArray.begin(), cardArray.end(), Card("Freeze", MEELEE, 24)) != cardArray.end()) {
        for (TroopCard &card : troopCardArray) { //przeszukaj meelee
            if (!card.getLegendary() && card.getRange() == MEELEE) card.setStrength(1); // ustaw siłę kart meelee na 1 jesli jest freeze
        }
    }
    if (find(cardArray.begin(), cardArray.end(), Card("Fog", SHOOT, 25)) != cardArray.end()) {
        for (TroopCard &card : troopCardArray) { //przeszukaj shooting
            if (!card.getLegendary() && card.getRange() == SHOOT) card.setStrength(1); // ustaw siłę kart shooting na 1 jesli jest fog
        }
    }
    if (find(cardArray.begin(), cardArray.end(), Card("Rain", BALLISTIC, 26)) != cardArray.end()) {
        for (TroopCard &card : troopCardArray) { //przeszukaj ballistic
            if (!card.getLegendary() && card.getRange() == BALLISTIC) card.setStrength(1); // ustaw siłę kart ballistic na 1 jesli jest rain
        }
    }
    //
    //
    /////////////////////////////////////////////////////////////////////////

    //////////////////// ZALEŻNE OD BATTLE HORN /////////////////////////////
    //
    //
    if (find(cardArray.begin(), cardArray.end(), Card("Battle Horn", MEELEE, 30)) != cardArray.end() ||
        find(cardArray.begin(), cardArray.end(), Card("Battle Horn", MEELEE, 31)) != cardArray.end()) {
        for (TroopCard &card : troopCardArray) {

            if (!card.getLegendary() && card.getRange() == MEELEE) card.setStrength(card.getStrength() * 2);
        }
    }
    if (find(cardArray.begin(), cardArray.end(), Card("Battle Horn", SHOOT, 30)) != cardArray.end() ||
        find(cardArray.begin(), cardArray.end(), Card("Battle Horn", SHOOT, 31)) != cardArray.end()) {
        for (TroopCard& card : troopCardArray) {
            if (!card.getLegendary() && card.getRange() == SHOOT) card.setStrength(card.getStrength() * 2);
        }
    }
    if (find(cardArray.begin(), cardArray.end(), Card("Battle Horn", BALLISTIC, 30)) != cardArray.end() ||
        find(cardArray.begin(), cardArray.end(), Card("Battle Horn", BALLISTIC, 31)) != cardArray.end()) {
        for (TroopCard& card : troopCardArray) {
            if (!card.getLegendary() && card.getRange() == BALLISTIC) card.setStrength(card.getStrength() * 2);
        }
    }
    //
    //
    ///////////////////////////////////////////////////////////////////////////

    ///////////////////////////SPRAWDZA COMBO//////////////////////////////////
    //
    //
    unordered_set<QString> uniqueNames;

    for (TroopCard& card : troopCardArray) {
        if (card.getCombo() && uniqueNames.find(card.getName()) == uniqueNames.end()) {
            uniqueNames.insert(card.getName());

            int count = 0;
            for (TroopCard& card_ : troopCardArray) { //policz ilosc danej karty
                if (card_.getName() == card.getName()) {
                    count++;
                }
            }

            for (TroopCard& card_ : troopCardArray) {
                if (card_.getName() == card.getName()) {
                    card_.setStrength(card_.getStrength() * count);
                }
            }
        }
    }
    //
    //
    ////////////////////////////////////////////////////////////

}

void cardList::restoreDefaultStrength(cardList& originalDeck) {
    for (TroopCard& card : troopCardArray) {
        for (TroopCard& ogCard : *originalDeck.getTroopCardArray()) {
            if (card.getName() == ogCard.getName()) {
                card.setStrength(ogCard.getStrength());
                break;
            }
        }
    }
}
