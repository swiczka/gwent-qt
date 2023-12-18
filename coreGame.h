#pragma once

#include "card.h"
#include "TroopCard.h"
#include "cardList.h"
#include "enemy.h"


#include <QDebug>

cardList prepareDeck(cardList allCards, bool easier);
bool caseEnemyBattleHornPlayed(cardList* deck, cardList* nowInUse, Card& pickedCard);
vector<bool> caseBattleHornPlayed(cardList* nowInUse);
bool caseEnemyScorchPlayed(cardList* deck, cardList* nowInPickingUse, cardList* nowInVictimUse, Card& pickedCard);
bool caseScorchPlayed(cardList* deck, cardList* nowInPickingUse, cardList* nowInVictimUse, Card& pickedCard);
bool caseMannequinPlayed(cardList* nowInUse);
void caseSpyPlayed(cardList* deck, cardList* nowInVictimUse, TroopCard pickedCard, cardList globalDeck);
void caseClearSkyPlayed(cardList* deck, cardList* nowInPickingUse, cardList* nowInVictimUse, Card pickedCard);
void caseWeatherPlayed(cardList* deck, cardList* nowInPickingUse, cardList* nowInVictimUse, Card pickedCard);
QString enemyDecision(Enemy* enemy, cardList* nowInPlayerUse, cardList* playerDeck, cardList globalDeck);
