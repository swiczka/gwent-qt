#pragma once

#include "card.h"
#include "TroopCard.h"
#include "cardList.h"
#include "enemy.h"

#include <unordered_set>
#include <unordered_map>
#include <QDebug>

cardList prepareDeck(cardList allCards);
void printDeck(const cardList& deck, const string color);
void playerDecision(cardList* deck, cardList* nowInUse, Enemy* enemy);
bool caseEnemyBattleHornPlayed(cardList* deck, cardList* nowInUse, Card& pickedCard);
bool caseBattleHornPlayed(cardList* deck, cardList* nowInUse, Card& pickedCard);
bool caseEnemyScorchPlayed(cardList* deck, cardList* nowInPickingUse, cardList* nowInVictimUse, Card& pickedCard);
bool caseScorchPlayed(cardList* deck, cardList* nowInPickingUse, cardList* nowInVictimUse, Card& pickedCard);
bool caseMannequinPlayed(cardList* deck, cardList* nowInUse, Card& pickedCard);
void caseSpyPlayed(cardList* deck, cardList* nowInPickingUse, cardList* nowInVictimUse, TroopCard pickedCard);
void caseClearSkyPlayed(cardList* deck, cardList* nowInPickingUse, cardList* nowInVictimUse, Card pickedCard);
void caseWeatherPlayed(cardList* deck, cardList* nowInPickingUse, cardList* nowInVictimUse, Card pickedCard);
void enemyDecision(Enemy* enemy, cardList* nowInPlayerUse, cardList* playerDeck);
