//
// Created by kira on 30.11.2019.
//

#ifndef PLAYER_UI_PLAYER_UI_FIXED_QUEUE_H_
#define PLAYER_UI_PLAYER_UI_FIXED_QUEUE_H_
#include <array>


template<typename T, std::size_t N>
class fixed_queue {
public:
//    explicit fixed_queue(unsigned size);
    fixed_queue();
//    ~fixed_queue();

    void push_back(const T &item);
    T &at(unsigned id);

    [[nodiscard]] unsigned size() const;

private:
//    unsigned _size;
    std::array<T, N> _data;
    unsigned _front;
    unsigned _back;
    unsigned _current_size;
};


template<typename T, std::size_t N>
fixed_queue<T, N>::fixed_queue() :
    _data(),
    _front(0),
    _back(0),
    _current_size(0) {}

template<typename T, std::size_t N>
void fixed_queue<T, N>::push_back(const T &item) {
    if ((_back + 1) % N == _front) {
        delete _data[_front];
        _front = (_front + 1) % N;
    } else {
        ++_current_size;
    }
    _data[_back] = item;
    _back = (_back + 1) % N;
}

template<typename T, std::size_t N>
T &fixed_queue<T, N>::at(unsigned id) {
    return _data[(_front + id) % N];
}

template<typename T, std::size_t N>
unsigned fixed_queue<T, N>::size() const {
    return _current_size;
}

#endif //PLAYER_UI_PLAYER_UI_FIXED_QUEUE_H_
