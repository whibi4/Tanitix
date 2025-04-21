#ifndef RULES_H
#define RULES_H
#include <iostream>
#include <functional>
#include <unordered_map>
#include "maths.h"
#include "physics.h"


class Motion2D {
    public:
        virtual ~Motion2D() = default;
        virtual void configure(const std::unordered_map<std::string, double>& params) = 0;
        virtual void reverseMotion() = 0;
        virtual std::function<Vector2D<double>(Time<double>, Vector2D<double>)> getMotionFunction() {return _motionFunction;};
    protected:
        std::function<Vector2D<double>(Time<double>, Vector2D<double>)> _motionFunction;
};

class Circular2DMotion: public Motion2D {
    public:
        void configure(const std::unordered_map<std::string, double> &params) override;
        void reverseMotion() {_angularVelocity = -_angularVelocity;};
    private:
        double _centerX;
        double _centerY;
        double _angularVelocity;
};
class Linear2DMotion: public Motion2D {
    public:
        void configure(const std::unordered_map<std::string, double> &params) override;
        void reverseMotion() {_velocity = -_velocity;};
    private:
        double _velocity;
};
class Constant2dMotion: public Motion2D {
    public:
        void configure(const std::unordered_map<std::string, double> &params) override;
        void reverseMotion() {};

};

#endif//RULES_H