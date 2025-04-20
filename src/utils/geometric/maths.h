#ifndef MATHS_H
#define MATHS_H

template<typename T>
class Vector2D {
    public:
        Vector2D(const T & x, const T & y):_x(x),_y(y){};
        Vector2D() = default;
        T _x;
        T _y;
};

template<typename T>
class Time {
    public:
        Time(const T &time) : _t(time) {};
        T _t;
};

#endif//MATHS_H