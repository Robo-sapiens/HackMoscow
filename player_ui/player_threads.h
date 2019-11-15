//
// Created by kira on 14.11.2019.
//

#ifndef PLAYER_QTHREAD_H
#define PLAYER_QTHREAD_H

#include <QThread>
#include <iostream>

class player_threads : public QThread {
public:
    explicit player_threads(int i) : i(i) {};
    void run() {
        for (int j = 0; j > -1; ++j) {
            std::cout << "thread " << i << std::endl;
        }
    }
    int i;
};


#endif //PLAYER_QTHREAD_H
