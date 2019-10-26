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

    command_parser(*player);

    cout << "exit" << '\n';

    return 0;
}