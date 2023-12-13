#pragma once

#include "coreGame.h"
#include <random>
#include <thread>

bool enemyEnds = false;
bool playerEnds = false;
//cardList globalDeck;

#define MAX_TROOP_COUNT 6
#define MAX_OTHER_COUNT 3

cardList prepareDeck(cardList allCards) {
    cardList newPlayerDeck;
    allCards.shuffleDeck();

    //add troops first

    for (int i = 0; i < MAX_TROOP_COUNT; i++) {
        newPlayerDeck.addTroopCard(allCards.getTroopCard(i));
    }

    for (int i = 0; i < MAX_OTHER_COUNT; i++) {
        newPlayerDeck.addCard(allCards.getCard(i));
    }
    return newPlayerDeck;
}

void printDeck(const cardList& deck, string color) {
    qDebug() << QString::fromStdString("MEELEE ");
    if (deck.hasFreeze()) qDebug() << "(FROZEN) ";
    if (deck.getMeeleeCardArray().hasHorn()) qDebug() << "(HORNED) ";
    qDebug() << ": ";
    qDebug() << "\tOverall MEELEE strength: " << deck.getMeeleeCardArray().getOverallStrength() << "\n";
    deck.getMeeleeCardArray().printRow();
    qDebug() << "\n";

    qDebug() << QString::fromStdString("SHOOTING ");
    if (deck.hasFog()) qDebug() << "(FOGGED) ";
    if (deck.getShootingCardArray().hasHorn()) qDebug() << "(HORNED) ";
    qDebug() << ": ";
    qDebug() << "\tOverall SHOOTERS strength: " << deck.getShootingCardArray().getOverallStrength() << "\n";
    deck.getShootingCardArray().printRow();
    qDebug() << "\n";

    qDebug() << QString::fromStdString("BALLISTIC ");
    if (deck.hasRain()) qDebug() << "(RAINY) ";
    if (deck.getBallisticCardArray().hasHorn()) qDebug() << "(HORNED) ";
    qDebug() << ": ";
    qDebug() << "\tOverall BALLISTICS strength: " << deck.getBallisticCardArray().getOverallStrength() << "\n";
    deck.getBallisticCardArray().printRow();

    qDebug() << "OVERALL DECK STRENGTH : " << deck.getOverallStrength() << "\n";
    qDebug() << "\n";
}

void playerDecision(cardList* deck, cardList* nowInUse, Enemy* enemy) {
    // bool leaveLoop = false;
    // if (deck->getCardSize() == 0 && deck->getTroopCardSize() == 0) {
    // 	playerEnds = true;
    // 	leaveLoop = true;
    // }

    // while (!leaveLoop) {
    // 	deck->printCardArray();
    // 	cout << "Pick a number of a card you want to play or 0 to pass. " << endl;
    // 	string pickedStrIndex;
    // 	cin >> pickedStrIndex;
    // 	try {

    // 		int pickedIndex = stoi(pickedStrIndex); // konwersja znakow na int

    // 		if (pickedIndex == 0) { //jezeli gracz chce zakonczyc
    // 			playerEnds = true;
    // 			leaveLoop = true;
    // 		}

    // 		else if (pickedIndex - 1 < deck->getTroopCardSize()) { // sprawdzamy czy wybrano troopcard

    // 			TroopCard& pickedCard = deck->pickTroopCard(pickedIndex);
    // 			cout << "You've chosen " << pickedCard.getName() << endl;

    // 			if (pickedCard.getSpy()) { //sprawdzamy czy wybrano szpiega
    // 				caseSpyPlayed(deck, nowInUse, &enemy->nowInUse, pickedCard);
    // 			}
    // 			else { //nie szpieg
    // 				nowInUse->addTroopCard(pickedCard);
    // 				deck->removeTroopCard(pickedCard);
    // 			}
    // 			leaveLoop = true;
    // 		}

    // 		else if (pickedIndex - 1 - deck->getTroopCardSize() >= 0 && //sprawdzamy czy wybrano inna karte
    // 			pickedIndex - 1 - deck->getTroopCardSize() < deck->getCardSize()) {

    // 			Card pickedCard = deck->pickCard(pickedIndex);
    // 			cout << "You've chosen " << pickedCard.getName() << endl;

    // 			if (pickedCard.getName() == "Clear Sky") { //usuwamy wszyskie karty pogodowe
    // 				caseClearSkyPlayed(deck, nowInUse, &enemy->nowInUse, pickedCard);
    // 				leaveLoop = true;
    // 			}
    // 			//gdy wybrano pożogę
    // 			else if (pickedCard.getName() == "Scorch") {
    // 				if (caseScorchPlayed(deck, nowInUse, &enemy->nowInUse, pickedCard)) {
    // 					leaveLoop = true;
    // 				}
    // 				else continue;
    // 			}
    // 			// gdy wybrano battle horn
    // 			else if (pickedCard.getName() == "Battle Horn") { //nalezy sprawdzić gdzie można dać battle horn

    // 				if (caseBattleHornPlayed(deck, nowInUse, pickedCard)) {
    // 					leaveLoop = true;
    // 				}
    // 				else continue;
    // 			}
    // 			// gdy wybrano kartę pogodową
    // 			else if (pickedCard.getName() == "Freeze" || pickedCard.getName() == "Fog" || pickedCard.getName() == "Rain") {
    // 				caseWeatherPlayed(deck, nowInUse, &enemy->nowInUse, pickedCard);
    // 				leaveLoop = true;
    // 			}
    // 			//gdy wybrano manekina
    // 			else if (pickedCard.getName() == "Mannequin") {
    // 				if (caseMannequinPlayed(deck, nowInUse, pickedCard)) {
    // 					leaveLoop = true; //wyjdz z petli gdy funkcja zwroci prawde
    // 				}
    // 				else continue; //zwróć błąd gdy zwróci false
    // 			}
    // 		}
    // 		else {
    // 			cout << "Picked incorrect option!" << endl;
    // 			cout << "Press ENTER to try again..." << endl;
    // 			cin.get();
    // 			cin.ignore(2, '\n');
    // 			continue;
    // 		}
    // 	}
    // 	catch (const std::invalid_argument& e) {
    // 		std::cerr << "Error: You have to put an integer number: " << e.what() << std::endl;
    // 		cout << "Press ENTER to try again..." << endl;
    // 		cin.get();
    // 		cin.ignore(2, '\n');
    // 		continue;
    // 	}
    // 	catch (const std::out_of_range& e) {
    // 		std::cerr << "Error. Out of range: " << e.what() << std::endl;
    // 		continue;
    // 	}

    // 	nowInUse->adjustStrength();
    // 	enemy->nowInUse.adjustStrength();

    // }

    // if (deck->getCardSize() == 0 && deck->getTroopCardSize() == 0) {
    // 	playerEnds = true;
    // 	leaveLoop = true;
    // }
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

void caseSpyPlayed(cardList* deck, cardList* nowInPickingUse, cardList* nowInVictimUse, TroopCard pickedCard, cardList globalDeck) {
    deck->removeTroopCard(pickedCard);
    deck->addTwoCards(globalDeck);
    nowInVictimUse->addTroopCard(pickedCard);
}

bool caseMannequinPlayed(cardList* deck, cardList* nowInUse, Card& pickedCard) {
    // //zwroc true, gdy sie powiodlo, false gdy nie
    // //gdy wybrano manekina
    // //sprawdz czy sa wgl jakies karty do podmianki
    // if (nowInUse->getNonLegendaryTroops().getTroopCardSize() <= 0) {
    // 	cout << "There are no cards to replace!" << endl;
    // 	cout << "Press ENTER to choose again..." << endl;
    // 	cin.get();
    // 	cin.ignore();
    // 	return false;
    // }
    // string chosenStrIndex;
    // nowInUse->getNonLegendaryTroops().printCardArray();
    // cout << "Which card do you want to replace?" << endl;
    // cin >> chosenStrIndex;
    // try {
    // 	int chosenIndex = stoi(chosenStrIndex);
    // 	//gdy gracz wprowadzi liczbe spoza zakresu
    // 	if (chosenIndex > nowInUse->getNonLegendaryTroops().getTroopCardSize() ||
    // 		chosenIndex < 1) {
    // 		cout << "Invalid index! Please try again." << endl;
    // 		cout << "Press ENTER to try again..." << endl;
    // 		cin.get();
    // 		cin.ignore();
    // 		return false;
    // 	}
    // 	//gdy poprawnie uzyje manekina
    // 	else {
    // 		TroopCard chosenCard = nowInUse->getNonLegendaryTroops().getTroopCard(chosenIndex - 1);
    // 		//removeTroopCard(nowInUse, chosenCard);
    // 		nowInUse->removeTroopCard(chosenCard);
    // 		nowInUse->addCard(Card("Mannequin", chosenCard.getRange(), pickedCard.getId()));
    // 		deck->addTroopCard(chosenCard);
    // 		deck->removeCard(pickedCard);
    // 		deck->restoreDefaultStrength();
    // 		return true;
    // 	}
    // }
    // //gdy zostanie wprowadzona nie int
    // catch (const invalid_argument& e) {
    // 	cerr << "Error: You have to put an integer number: " << e.what() << endl;
    // 	cout << "Press ENTER to try again..." << endl;
    // 	cin.get();
    // 	cin.ignore();
    // 	return false;
    // }
    return false;
}



void enemyDecision(Enemy* enemy, cardList* nowInPlayerUse, cardList* playerDeck, cardList globalDeck) {

    srand((unsigned)time(NULL));
    int random = rand();
    bool canPlay = false;
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

                TroopCard card = enemy->deck.pickTroopCard(randomIndex);

                if (card.getSpy()) {
                    caseSpyPlayed(&enemy->deck, &enemy->nowInUse, nowInPlayerUse, card, globalDeck);
                    canPlay = true;
                    qDebug() << "ENEMY picked " << card.getName();
                    break;
                }
                else {
                    enemy->deck.removeTroopCard(card);
                    enemy->nowInUse.addTroopCard(card);
                    canPlay = true;
                    qDebug() << "ENEMY picked " << card.getName();
                    break;
                }
            }
            else if (randomIndex - enemy->deck.getTroopCardSize() > 0) { //gdy wylosowalo card

                Card card = enemy->deck.pickCard(randomIndex);

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



        if (enemy->deck.getTroopCardSize() > 0 && random % 10 > 5) {
            //zagraj troopcard

            if (random % 10 > 7) {

            }
        }

        ///////////////////////////////// ROZWAŻ POGODOWE //////////////////////////////
        //
        //
        else if (enemy->deck.hasFreeze() && nowInPlayerUse->getMeeleeCardArray().getNonLegendaryTroops().getOverallStrength() >
            enemy->nowInUse.getMeeleeCardArray().getNonLegendaryTroops().getOverallStrength()) {
            //zagraj freeze
        }
        else if (enemy->deck.hasFog() && nowInPlayerUse->getShootingCardArray().getNonLegendaryTroops().getOverallStrength() >
            enemy->nowInUse.getShootingCardArray().getNonLegendaryTroops().getOverallStrength()) {
            //zagraj fog
        }
        else if (enemy->deck.hasRain() && nowInPlayerUse->getBallisticCardArray().getNonLegendaryTroops().getOverallStrength() >
            enemy->nowInUse.getBallisticCardArray().getNonLegendaryTroops().getOverallStrength()) {
            //zagraj rain
        }


        //
        //
        ////////////////////////////////////////////////////////////////////////

        //////////////////////// ROZWAŻ BATTLE HORN ////////////////////////////
        //
        //
        else if (enemy->deck.hasHorn() &&
            enemy->nowInUse.getMeeleeCardArray().getNonLegendaryTroops().getOverallStrength() > 8 &&
            !enemy->nowInUse.getMeeleeCardArray().hasHorn()) {
            //zagraj battle horn na meelee
        }
        else if (enemy->deck.hasHorn() &&
            enemy->nowInUse.getShootingCardArray().getNonLegendaryTroops().getOverallStrength() > 8 &&
            !enemy->nowInUse.getShootingCardArray().hasHorn()) {
            //zagraj battle horn na shooting
        }
        else if (enemy->deck.hasHorn() &&
            enemy->nowInUse.getBallisticCardArray().getNonLegendaryTroops().getOverallStrength() > 8 &&
            !enemy->nowInUse.getBallisticCardArray().hasHorn()) {
            //zagraj battle horn na ballistic
        }
        //
        //
        /////////////////////////////////////////////////////////////

        //////////////////////////ROZWAŻ POŻOGĘ/////////////////////////////////
        //
        //
        else if (enemy->deck.hasScorch() &&
            enemy->nowInUse.getStrongestNonlegendCardSum() < nowInPlayerUse->getStrongestNonlegendCardSum()) {
            //zagraj scorch
        }

        break;

    default:
        qDebug() << "Invalid argument";
        throw invalid_argument("Invalid argument!");
    }
    enemy->nowInUse.adjustStrength();
    nowInPlayerUse->adjustStrength();
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

void cardList::adjustStrength() {
    /////////////////// ZALEZNE OD KART POGODOWYCH/////////////////////////
    //
    //
    this->restoreDefaultStrength(); ///// !!! przywracamy domyślne wartości sił kart ////////

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

void cardList::restoreDefaultStrength() {
    cardList originalDeck;
    originalDeck.readCardsFromFile();
    for (TroopCard& card : troopCardArray) {
        for (TroopCard& ogCard : *originalDeck.getTroopCardArray()) {
            if (card.getName() == ogCard.getName()) {
                card.setStrength(ogCard.getStrength());
                break;
            }
        }
    }
}
