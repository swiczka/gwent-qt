#pragma once

#include "card.h"
#include "TroopCard.h"
#include "cardList.h"
#include <QDebug>
#include <fstream>
#include <random>
#include <chrono>
#include <iomanip>

cardList::cardList (const cardList& other) : cardArray(other.cardArray),
    troopCardArray(other.troopCardArray),
    usedIds(other.usedIds)
{}

cardList& cardList::operator=(const cardList& other){
    if (this != &other) {
        this->cardArray = other.cardArray;
        this->troopCardArray = other.troopCardArray;
        this->usedIds = other.usedIds;
    }
    return *this;
}

TroopCard& cardList::pickTroopCard(int pickedIndex) {
    if (pickedIndex - 1 < getTroopCardSize()) {
        return getTroopCard(pickedIndex - 1);
    }
    else throw out_of_range("Invalid pickedIndex");
}

Card& cardList::pickCard(int pickedIndex) {
    if (pickedIndex - 1 - getTroopCardSize() < getCardSize()) {
        return getCard(pickedIndex - 1 - getTroopCardSize());
    }
    else throw out_of_range("Invalid pickedIndex");
}

void cardList::addCard(Card cardToAdd) {
    this->usedIds.insert(cardToAdd.getId());
    this->cardArray.push_back(Card(cardToAdd.getName(), cardToAdd.getRange(), cardToAdd.getId()));
}

void cardList::addTroopCard(TroopCard cardToAdd) {
    this->usedIds.insert(cardToAdd.getId());
    this->troopCardArray.push_back(TroopCard(cardToAdd.getName(), cardToAdd.getRange(), cardToAdd.getId(),
        cardToAdd.getStrength(), cardToAdd.getLegendary(), cardToAdd.getSpy(), cardToAdd.getCombo()));
}

void cardList::removeTroopCard(const TroopCard& cardToRemove) {
    troopCardArray.erase(remove_if(troopCardArray.begin(), troopCardArray.end(), [cardToRemove](const TroopCard& card) {
        return (cardToRemove.getId() == card.getId());
        }), troopCardArray.end());
}

void cardList::removeCard(const Card& cardToRemove) {
    cardArray.erase(remove_if(cardArray.begin(), cardArray.end(), [cardToRemove](const Card& card) {
        return (cardToRemove.getId() == card.getId());
        }), cardArray.end());
}

void cardList::removeWeatherCards() {
    cardArray.erase(remove_if(cardArray.begin(), cardArray.end(), [](const Card& card) {
        return (card.getName() == "Freeze" || card.getName() == "Fog" || card.getName() == "Rain");
        }), cardArray.end());
}

void cardList::removeByStrength(int strength) {
    troopCardArray.erase(remove_if(troopCardArray.begin(), troopCardArray.end(), [strength](const TroopCard& card) {
        return (card.getStrength() == strength && !card.getLegendary());
        }), troopCardArray.end());
}

void cardList::shuffleDeck() {
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine e(seed);
    std::shuffle(cardArray.begin(), cardArray.end(), e);
    std::shuffle(troopCardArray.begin(), troopCardArray.end(), e);
}

cardList cardList::getMeeleeCardArray() const{
    cardList toReturn;
    for (const TroopCard& card : troopCardArray) {
        if (card.getRange() == MEELEE) toReturn.addTroopCard(card);
    }

    for (const Card& card : cardArray) {
        if (card.getRange() == MEELEE) toReturn.addCard(card);
    }
    return toReturn;
}

cardList cardList::getShootingCardArray() const {
    cardList toReturn;
    for (const TroopCard& card : troopCardArray) {
        if (card.getRange() == SHOOT) toReturn.addTroopCard(card);
    }

    for (const Card& card : cardArray) {
        if (card.getRange() == SHOOT) toReturn.addCard(card);
    }
    return toReturn;
}

cardList cardList::getBallisticCardArray() const {
    cardList toReturn;
    for (const TroopCard& card : troopCardArray) {
        if (card.getRange() == BALLISTIC) toReturn.addTroopCard(card);
    }

    for (const Card& card : cardArray) {
        if (card.getRange() == BALLISTIC) toReturn.addCard(card);
    }
    return toReturn;
}

cardList cardList::getNonLegendaryTroops() const {
    cardList toReturn;
    for (const TroopCard &card : troopCardArray) {
        if (!card.getLegendary()) toReturn.addTroopCard(card);
    }
    return toReturn;
}

int cardList::getStrongestNonlegendCardSum() const{

    int maxStrength = 0;
    int toReturn = 0;

    const vector<TroopCard>& temp = *getNonLegendaryTroops().getTroopCardArray();

    for (const TroopCard& card : temp) {

        int strength = card.getStrength();

        if (strength > maxStrength) {
            maxStrength = strength;
            toReturn = strength;
        }
        else if (strength == maxStrength) {
            toReturn += strength;
        }

    }
    return toReturn;
}

bool cardList::hasFreeze() const {
    if (find_if(cardArray.begin(), cardArray.end(), [](const Card& card) {
        return card.getName() == "Freeze";
        }
        ) == cardArray.end()) return false;
    else return true;
}

bool cardList::hasFog() const {
    if (find_if(cardArray.begin(), cardArray.end(), [](const Card& card) {
        return card.getName() == "Fog";
        }) == cardArray.end()) return false;
    else return true;
}

bool cardList::hasRain() const {
    if (find_if(cardArray.begin(), cardArray.end(), [](const Card& card) {
        return card.getName() == "Rain";
        }) == cardArray.end()) return false;
    else return true;
}

//je¿eli zwróci 0 to nie ma, je¿eli jest to zwróci id battle horn (potrzebne do decyzji przeciwnika na normalnym)
int cardList::hasHorn() const {
    int id = 0;

    if (std::any_of(cardArray.begin(), cardArray.end(), [&](const Card& card) {
            id = card.getId();
            return card.getName() == "Battle Horn";
        })) return id;

    else return 0;
}

bool cardList::hasScorch() const {
    return find_if(cardArray.begin(), cardArray.end(), [](const Card& card) {
        return card.getName() == "Scorch";
        }) != cardArray.end();
}

bool cardList::hasClearSky() const {
    return find_if(cardArray.begin(), cardArray.end(), [](const Card& card) {
        return card.getName() == "Clear Sky";
           }) != cardArray.end();
}

bool cardList::hasMannequinsOnly() const {
    if (troopCardArray.size() > 0) return false;

    else {
        return find_if(cardArray.begin(), cardArray.end(), [](const Card& card) {
            return card.getName() != "Mannequin";
            }) == cardArray.end();
    }
}

//if returns card with none name, there are no spies, otheriwse return a spy
TroopCard cardList::hasSpy() const
{
    for(auto &card : troopCardArray){
        if(card.getSpy()) return card;
    }
    return TroopCard();
}

int cardList::getOverallStrength() const {
    int strength = 0;
    for (const TroopCard &card : troopCardArray) {
        strength += card.getStrength();
    }
    return strength;
}

void cardList::addTwoCards(cardList globalDeck) {

    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> distribution(1, globalDeck.getCardSize() + globalDeck.getTroopCardSize());

    int howManyAdded = 0;

    while (howManyAdded != 2) {
        int randomIndex = distribution(gen);

        if (randomIndex <= globalDeck.getTroopCardSize()) { //gdy wylosowa?o troopcard

            TroopCard toAdd = globalDeck.pickTroopCard(randomIndex);

            if (usedIds.find(toAdd.getId()) == usedIds.end()) { //gdy nie znaleziono tej karty juz w talii
                this->addTroopCard(toAdd);
                howManyAdded++;
            }

        }
        else if (randomIndex - globalDeck.getTroopCardSize() <= globalDeck.getCardSize() &&
            randomIndex - globalDeck.getTroopCardSize() > 0) { //gdy wylosowalo card

            Card toAdd = globalDeck.pickCard(randomIndex);

            if (usedIds.find(toAdd.getId()) == usedIds.end()) {
                this->addCard(toAdd);
                howManyAdded++;
            }
        }
    }
}
