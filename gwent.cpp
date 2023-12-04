// #pragma once

// #include "card.h"
// #include "TroopCard.h"
// #include "cardList.h"
// #include "coreGame.h"
// #include "enemy.h"

// #include <limits>

//#include "card.cpp"
//#include "TroopCard.cpp"
//#include "cardList.cpp"

// int main() {
//     //
//     //
//     // globalDeck - zbi?r zawieraj?cy wszystkie mo?liwe karty
//     //
//     // playerDeck - pocz?tkowa talia gracza
//     // nowInPlayerUse - aktywne karty gracza
//     //
//     //

//     globalDeck.readCardsFromFile();
//     cardList nowInPlayerUse;
//     cardList playerDeck = prepareDeck(globalDeck);
//     string diff;

//     while (1) {
//         cout << "Welcome to GWENT game." << endl;
//         cout << "Pick a difficulty: \n";
//         cout << "1. IZI\n2. NO IZI\n";
//         cin >> diff;
//         if (diff != "1" && diff != "2") {
//             cout << "Inproper difficulty!\n";
//             cout << "Press ENTER to continue...";
//             cin.get();
//             cin.ignore();
//         }
//         else break;
//     }

//     // inicjacja przeciwnika
//     Enemy enemy;
//     enemy.deck = prepareDeck(globalDeck);
//     enemy.difficulty = stoi(diff);


//     while (!(playerEnds && enemyEnds)) {

//         /////////////////////// GRACZ //////////////////////

//         /// je?li gracz nie zako?czy?
//         if (!playerEnds) {
//             cout << GRN + "YOUR TURN!" + reset << endl;
//             cin.get();
//             cin.ignore();

//             playerDecision(&playerDeck, &nowInPlayerUse, &enemy);


//             cout << BLU + "########################### YOUR DECK ###########################" + reset << endl;
//             printDeck(nowInPlayerUse, GRN);
//             cout << endl;

//             cout << MGN + "########################### ENEMY DECK ###########################" + reset << endl;
//             printDeck(enemy.nowInUse, RED);
//             cout << endl;
//             cout << "Press ENTER to continue...";
//             cin.get();
//             cin.ignore(10, '\n');
//         }

//         system("cls");

//         /////////////////////// PRZECIWNIK ///////////////////////

//         //// je?li przeciwnik nie zako?czy? //////////////
//         if (!enemyEnds) {
//             cout << RED + "ENEMY TURN!" << reset << endl << endl;
//             Sleep(1000);

//             enemyDecision(&enemy, &nowInPlayerUse, &playerDeck);
//             //printDeck(enemy.nowInUse, "RED");

//             cout << BLU + "########################### YOUR DECK ###########################" + reset << endl;
//             printDeck(nowInPlayerUse, GRN);
//             cout << endl;
//             cout << MGN + "########################### ENEMY DECK ###########################" + reset << endl;
//             printDeck(enemy.nowInUse, RED);
//             cout << endl;
//             cout << "Press ENTER to continue...";
//             cin.get();
//             cin.ignore(10, '\n');
//         }


//         //system("cls");
//     }

//     //// PODSUMOWANIE ///
//     if (nowInPlayerUse.getOverallStrength() > enemy.nowInUse.getOverallStrength()) {
//         cout << BLU << "**********	YOU WON!  **********" << reset << endl;
//     }
//     else if (nowInPlayerUse.getOverallStrength() < enemy.nowInUse.getOverallStrength()){
//         cout << RED << "**********	YOU LOST!  **********" << reset << endl;
//     }
//     else {
//         cout << "**********  DRAW!  **********" << endl;
//     }
// }
