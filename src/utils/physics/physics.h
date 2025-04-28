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
        Weight() : _massKg(1) {}  
        T operator+(const Weight<T>& w)
        {
            return _massKg + w._massKg;
        }
        T operator-(const Weight<T>& w)
        {
            return _massKg - w._massKg;
        }
        T operator*(T scalar) const
        {
            return _massKg * scalar;
        }
        T getMass() const
        {
            return _massKg;
        }
        void setMass(const T &mass)
        {
            _massKg = mass;
        }
    private:
        T _massKg;
};
#endif//PHYSICS_H