#pragma once

#include "cardList.h"

class Enemy : QObject{
    Q_OBJECT
public:
	cardList nowInUse;
	cardList deck;
	int difficulty{ 0 };
};


