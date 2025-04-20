#ifndef PHYSICS_H
#define PHYSICS_H

template<typename T>
class Time {
    public:
        Time(const T &time) : _millisecond(time) {};
        T _millisecond;
};

#endif//PHYSICS_H