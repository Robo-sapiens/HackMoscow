//
// Created by kira on 16.11.2019.
//

#ifndef PLAYER_UI_AUDIO_THREAD_H
#define PLAYER_UI_AUDIO_THREAD_H

#include <QThread>
#include "player.h"

class AudioThread : public QThread {
public:
    explicit AudioThread(Player *player);
    void run() override;
    Player *player;
};

#endif //PLAYER_UI_AUDIO_THREAD_H
