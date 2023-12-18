#pragma once
#ifndef ALLCARDS_H
#define ALLCARDS_H

#include "card.h"
#include "TroopCard.h"
#include "cardList.h"


void prepareGlobalDeck(cardList* globalDeck){
    globalDeck->addCard(Card("Freeze", 1, 24));
    globalDeck->addCard(Card("Fog", 2, 25));
    globalDeck->addCard(Card("Rain", 3, 26));
    globalDeck->addCard(Card("Clear Sky", 4, 27));
    globalDeck->addCard(Card("Mannequin", 4, 28));
    globalDeck->addCard(Card("Mannequin", 4, 29));
    globalDeck->addCard(Card("Battle Horn", 4, 30));
    globalDeck->addCard(Card("Battle Horn", 4, 31));
    globalDeck->addCard(Card("Scorch", 4, 32));

    globalDeck->addTroopCard(TroopCard("Geralt", 1, 1, 15, true, false, false));
    globalDeck->addTroopCard(TroopCard("Ciri", 1, 2, 15, true, false, false));
    globalDeck->addTroopCard(TroopCard("Vesemir", 1, 3, 6, false, false, false));
    globalDeck->addTroopCard(TroopCard("Triss", 2, 4, 7, true, false, false));
    globalDeck->addTroopCard(TroopCard("Zoltan", 1, 5, 5, false, false, false));
    globalDeck->addTroopCard(TroopCard("Avallach", 1, 6, 0, true, true, false));
    globalDeck->addTroopCard(TroopCard("Redanian Archer", 2, 7, 3, false, false, false));
    globalDeck->addTroopCard(TroopCard("Yennefer", 2, 8, 7, true, false, false));
    globalDeck->addTroopCard(TroopCard("Vernon Roche", 1, 9, 10, false, false, false));
    globalDeck->addTroopCard(TroopCard("Philippa Eilhart", 2, 10, 10, true, false, false));
    globalDeck->addTroopCard(TroopCard("Ves", 1, 11, 5, false, false, false));
    globalDeck->addTroopCard(TroopCard("Dijkstra", 1, 12, 4, false, true, false));
    globalDeck->addTroopCard(TroopCard("Keira Metz", 2, 13, 5, false, false, false));
    globalDeck->addTroopCard(TroopCard("Trebuchet", 3, 14, 6, false, false, false));
    globalDeck->addTroopCard(TroopCard("Trebuchet", 3, 15, 6, false, false, false));
    globalDeck->addTroopCard(TroopCard("Catapult", 3, 16, 8, false, false, true));
    globalDeck->addTroopCard(TroopCard("Catapult", 3, 17, 8, false, false, true));
    globalDeck->addTroopCard(TroopCard("Poor Infantry", 1, 18, 1, false, false, true));
    globalDeck->addTroopCard(TroopCard("Poor Infantry", 1, 19, 1, false, false, true));
    globalDeck->addTroopCard(TroopCard("Poor Infantry", 1, 20, 1, false, false, true));
    globalDeck->addTroopCard(TroopCard("Blue Stripes", 1, 21, 4, false, false, true));
    globalDeck->addTroopCard(TroopCard("Blue Stripes", 1, 22, 4, false, false, true));
    globalDeck->addTroopCard(TroopCard("Blue Stripes", 1, 23, 4, false, false, true));

    globalDeck->addTroopCard(TroopCard("Sheldon", 2, 33, 4, false, false, false));
    globalDeck->addTroopCard(TroopCard("Siege Tower", 3, 34, 6, false, false, false));
}


#endif // ALLCARDS_H
