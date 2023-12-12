#pragma once

#include "card.h"
#include<QDebug>

Card::Card(const Card& other){
    this->name = other.name;
    this->range = other.range;
    this->id = other.id;
}

void Card::setName(QString newName) {
	name = newName; 
}

void Card::setRange(int newRange) {
	range = newRange; 
}

QString Card::getName() const {
	return this->name; 
}

int Card::getRange() const {
	return this->range; 
}

int Card::getId() const {
	return this->id; 


}

QString Card::getStrRange() const {
	switch (this->getRange()) {
	case 1: return "Meelee";
	case 2: return "Shooting";
	case 3: return "Ballistic";
	default: return "Any";
	}
}

QString Card::description() const{
    return QString(getName() + "\nRange: " + getStrRange() + "\n\n");
}

void Card::printCardInfo() const{
    qDebug() << getName() << "\n" << getStrRange() << "\n";
}

bool Card::operator==(const Card& card1) const {
	return (card1.getId() == getId() && card1.getRange() == getRange());
}

Card& Card::operator=(const Card& other) {
    if (this != &other) {
        this->name = other.name;
        this->range = other.range;
        this->id = other.id;
    }
    return *this;
}
