#include <iostream>
#include <string.h>
#include <cstring>
#include "bass.h"
#include <cstdio>
#include "player.h"

using namespace std;

int main(int argc, char **argv) {
    if (argc != 2) {
        cout << "enter music dir please\n";
        return 1;
    }
    Player *player = new Player();
    player->uploadFromDir(argv[1]);
    player->showPlaylist();

    string command;
    
    while (1)
    {
        cin >> command;

        if (command == "exit") break;
        else if (command == "play") player->play(0);
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
            player->showPlaylist();
        }
        else if (command == "info") {
            cout << "------------------" << '\n';
            cout << "Playing: " << player->getMusicName() << '\n';
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
            cout << "- ch <number>" << '\n';
            cout << "------------------" << '\n';
        } else if (command == "ch") {
            int number;
            cin >> number;
            player->play(number);
        }
    }


    cout << "exit" << '\n';

    return 0;
}