#pragma once

#include "card.h"

class TroopCard : public Card {
    Q_OBJECT
public:

    TroopCard(QString name, int range, int id, int strength, bool isLegendary, bool isSpy, bool isCombo);

    TroopCard(const TroopCard& other);

	void setStrength(int newStrength);
	void setLegendary(bool newIsLegendary);
	void setSpy(bool newIsSpy);

	void setCombo(bool newIsCombo);

	int getStrength() const;
	bool getLegendary() const;
	bool getSpy() const;
	bool getCombo() const;

    QString description() const override;

	void printCardInfo() const override;

	bool operator==(const TroopCard& card1) const;

    TroopCard& operator=(const TroopCard& other);

private:
	int strength;
	bool isLegendary;
	bool isSpy;
	bool isCombo;
};
