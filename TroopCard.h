#pragma once

#include "card.h"

class TroopCard : public Card {
    Q_OBJECT
public:

    TroopCard(QString name = "none", int range = 0, int id = 0, int strength = 0, bool isLegendary = false,
              bool isSpy = false, bool isCombo = false);

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
