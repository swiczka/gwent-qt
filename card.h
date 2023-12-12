#pragma once

#include<QString>
#include<QObject>

using namespace std;

#define MEELEE 1
#define SHOOT 2
#define BALLISTIC 3

class Card : public QObject {
    Q_OBJECT
public:

    Card(QString name, int range, int id)
		: name(name), range(range), id(id) {
	}

    Card(const Card& other);

    void setName(QString newName);
	void setRange(int newRange);

    QString getName() const;
	int getRange() const;
	int getId() const;
    QString getStrRange() const;

    virtual QString description() const;

	virtual void printCardInfo() const;

	bool operator==(const Card& card1) const;

    Card& operator=(const Card& other);

private:
    QString name;
	int range;
	int id;
};

