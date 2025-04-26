#ifndef PHYSICS_H
#define PHYSICS_H

template<typename T>
class Time {
    public:
        Time(const T &time, bool sec){
            if (sec) {
                _second = time;
                _millisecond = time * 1000;
            } else {
                _millisecond = time;
                _second = time / 1000;
            }
        };
        T _millisecond;
        T _second;
};
template<typename T>
class Weight {
    public:
        Weight(const T &mass) : _massKg(mass) {};
        T _massKg;
};
#endif//PHYSICS_H