#include "knight2.h"

int main(int argc, char ** argv) {
    string file_armyknights, file_events;
    if (argc == 1) {
        file_armyknights = "tc1_armyknights"; // hard-code
        file_events = "tc1_events";
    }
    else if (argc == 3) {
        file_armyknights = argv[1];
        file_events = argv[2];
    }
    else {
        cout << "Error number of arguments" << endl;
        exit(1);
    }
    
    // BEBGIN
    KnightAdventure * knightAdventure = new KnightAdventure();
    knightAdventure->loadArmyKnights(file_armyknights);
    knightAdventure->loadEvents(file_events);
    knightAdventure->run();

    delete knightAdventure;

    // test doc file armyknights va file events
    // ArmyKnights army(file_armyknights);
    // Events events(file_events);

    // int number_events = events.count();
    // for (int i = 0; i < number_events; i++) cout << events.get(i) << " ";
    // cout << endl;

    // int number_knights = army.count();
    // for (int i = 0; i < number_knights; i++) {
    //     cout << army.getKnight(i)->toString() << endl;
    // }

    // return 0;
}