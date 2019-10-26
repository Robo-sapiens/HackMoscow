#include <iostream>
#include <string.h>
#include "bass.h"
#include "stdio.h"
#include "player.h"

using namespace std;

int main(int argc, char **argv)
{
    if (argc != 2) {
        cout << "Format: ./player <audio>" << '\n';
        return 0;
    }

    char *fileName = argv[1];
    cout << "Bass library test: " << fileName << '\n';

    Player *player = new Player();
    player->play(fileName);

    string command;
    
    while (1)
    {
        cin >> command;
        cout << "command: " << command << '\n';

        if (command == "exit") break;
        else if (command == "play") player->play(fileName);
        else if (command == "pause") player->pause();
        else if (command == "resume") player->resume();
        else if (command == "stop") player->stop();
    }

    cout << "exit" << '\n';

    return 0;
}