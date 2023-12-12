#pragma once

#include "TroopCard.h"
#include <QDebug>

TroopCard::TroopCard(QString name, int range, int id, int strength, bool isLegendary, bool isSpy, bool isCombo) :
    Card(name, range, id), strength(strength), isLegendary(isLegendary), isSpy(isSpy), isCombo(isCombo) {
}

TroopCard::TroopCard(const TroopCard& other) : Card(other),
    strength(other.strength),
    isLegendary(other.isLegendary),
    isSpy(other.isSpy),
    isCombo(other.isCombo) {

}

void TroopCard::setStrength(int newStrength) {
	strength = newStrength;
}

void TroopCard::setLegendary(bool newIsLegendary) {
	isLegendary = newIsLegendary;
}

void TroopCard::setSpy(bool newIsSpy) {
	isSpy = newIsSpy;
}

void TroopCard::setCombo(bool newIsCombo) {
	isCombo = newIsCombo;
}

int TroopCard::getStrength() const {
	return this->strength; 
}
bool TroopCard::getLegendary() const {
	return this->isLegendary; 
}
bool TroopCard::getSpy() const {
	return this->isSpy; 
}
bool TroopCard::getCombo() const {
	return this->isCombo; 
}

QString TroopCard::description() const {
    QString d;
    d = getName() + "\nRange: " + getStrRange() + "\n" + "Strength: " + QString::number(getStrength()) + "\n";
    if (getLegendary()) d += "Legendary ";
    if (getCombo()) d += "Combo ";
    if (getSpy()) d += "Spy ";
    d += "\n";
    return d;
}

void TroopCard::printCardInfo() const {
    qDebug() << getName() << "\n" << getStrRange() << "\n" << "Str: " << getStrength() << "\n";
    if (getLegendary()) qDebug() << "Legendary ";
    if (getCombo()) qDebug() << "Combo ";
    if (getSpy()) qDebug() << "Spy ";
    qDebug() << "\n";
}

bool TroopCard::operator==(const TroopCard& card1) const {
	return (card1.getId() == getId() && card1.getRange() == getRange());
}

TroopCard& TroopCard::operator=(const TroopCard& other){
    if (this != &other) {
        Card::operator=(other);
        this->strength = other.strength;
        this->isLegendary = other.isLegendary;
        this->isSpy = other.isSpy;
        this->isCombo = other.isCombo;
    }
    return *this;
}

