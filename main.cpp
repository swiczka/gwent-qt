#include "mainwindow.h"
#include "difficultydialog.h"
#include "card.h"
#include "TroopCard.h"
#include "cardList.h"
//#include "coreGame.h"
#include "enemy.h"
#include <QDebug>
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    DifficultyDialog difficultyDialog;
    if (difficultyDialog.exec() != QDialog::Accepted)
        return 0; // Jeśli użytkownik anuluje, zakończ program


    int selectedDifficulty = difficultyDialog.getDifficulty();
    qDebug() << selectedDifficulty;

    MainWindow w(nullptr);
    w.show();
    w.initializeDecks(selectedDifficulty);
    w.updateGameState();

    return a.exec();
}
