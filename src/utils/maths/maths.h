#ifndef MATHS_H
#define MATHS_H
#include <cmath>
template <typename T>
class Vector2D
{
public:
    Vector2D(const T &x, const T &y) : _x(x), _y(y) {};
    Vector2D() = default;
    T distance(const Vector2D &otherVecor) { return sqrt(pow((_x - otherVecor._x), 2) + pow((_y - otherVecor._y), 2)); };
    Vector2D<T> operator+(Vector2D<T> v)
    {
        return Vector2D<T>(_x + v._x, _y + v._y);
    }
    Vector2D<T> operator*(T scalar) const { return Vector2D<T>(_x*scalar, _y*scalar); }
    T _x;
    T _y;
};

#endif // MATHS_H