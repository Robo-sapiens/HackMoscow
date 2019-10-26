#include <iostream>
#include <cstring>
#include "bass.h"
#include <cstdio>
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

    string command;
    
    while (1)
    {
        cin >> command;

        if (command == "exit") break;
        else if (command == "play") player->play(fileName);
        else if (command == "pause") player->pause();
        else if (command == "resume") player->resume();
        else if (command == "stop") player->stop();
        else if (command == "vol") {
            int param;
            cin >> param;
            player->setVolume(param / 100.0);
        }
        else if (command == "pos") {
            int param;
            cin >> param;
            player->setPosition(param / 100.0);
        }
        else if (command == "list") {
            cout << "TODO" << '\n';
        }
        else if (command == "info") {
            cout << "------------------" << '\n';
            cout << "Playing: " << fileName << '\n';
            cout << "Volume: " << player->getVolume() << '\n';
            cout << "Position: " << player->getRelativePosition() << '\n';
            cout << "------------------" << '\n';
        }
        else if (command == "help") {
            cout << "------------------" << '\n';
            cout << "Available commands:" << '\n';
            cout << "- play" << '\n';
            cout << "- pause" << '\n';
            cout << "- resume" << '\n';
            cout << "- stop" << '\n';
            cout << "- vol <0-100:volume>" << '\n';
            cout << "- pos <0-100:position>" << '\n';
            cout << "- info" << '\n';
            cout << "- help" << '\n';
            cout << "- list" << '\n';
            cout << "------------------" << '\n';
        }
    }

    cout << "exit" << '\n';

    return 0;
}