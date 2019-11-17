//
// Created by kira on 17.11.2019.
//

#ifndef PLAYER_UI_FFT_THREAD_H
#define PLAYER_UI_FFT_THREAD_H

#include <QThread>
#include <QMutex>
#include "player.h"


class FFTWThread : public QThread
{
public:
    explicit FFTWThread(Player *player);
    ~FFTWThread() override;
    void run() override;
    Player *player;
    QMutex *qMutex;
};

#endif //PLAYER_UI_FFT_THREAD_H
