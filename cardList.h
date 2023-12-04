#pragma once

#include "card.h"
#include"TroopCard.h"

#include<vector>
#include<unordered_set>

using namespace std;

class cardList : QObject{
    Q_OBJECT
public:

    cardList() = default;

    cardList(const cardList& other);

    cardList& operator=(const cardList& other);

	vector<Card>* getCardArray() { return &cardArray; }

	vector<TroopCard>* getTroopCardArray() { return &troopCardArray; }

	//usedids powi¹zane bêdzie z deckiem
	unordered_set<int>* getUsedIds() { return &usedIds;  }

	void setUsedIds(unordered_set<int> usedIds) { this->usedIds = usedIds;  }

	void printCardArray() const;

	TroopCard& pickTroopCard(int pickedIndex);

	Card& pickCard(int pickedIndex);

	void addCard(Card cardToAdd);
	void addTroopCard(TroopCard cardToAdd);

	void removeTroopCard(const TroopCard& cardToRemove);

	void removeCard(const Card& cardToRemove);

	void removeWeatherCards();

	void removeByStrength(int strength);

	void shuffleDeck();

	int getTroopCardSize() const{
		return troopCardArray.size();
	}

	int getCardSize() const{
		return cardArray.size();
	}

	Card& getCard(int index) {
		return cardArray[index];
	}

	TroopCard& getTroopCard(int index) {
		return troopCardArray[index];
	}

	cardList getMeeleeCardArray() const;
	cardList getShootingCardArray() const;
	cardList getBallisticCardArray() const;

	cardList getNonLegendaryTroops() const;

	int getStrongestNonlegendCardSum() const;
	
	bool hasFreeze() const;
	bool hasFog() const;
	bool hasRain() const;
	bool hasHorn() const;
	bool hasScorch() const;
	bool hasMannequinsOnly() const;

	void printRow() const;

	void adjustStrength();

	void restoreDefaultStrength();

	int getOverallStrength() const;

	void addTwoCards(cardList globalDeck);

	void readCardsFromFile();

	
private:
	vector<Card> cardArray;
	vector<TroopCard> troopCardArray;
	unordered_set<int> usedIds;
};
