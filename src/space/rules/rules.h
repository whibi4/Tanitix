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
        std::function<Vector2D<double>(Time<double>, Vector2D<double>)> getMotionFunction() {return _motionFunction;};
    protected:
        std::function<Vector2D<double>(Time<double>, Vector2D<double>)> _motionFunction;
};

class Circular2DMotion: public Motion2D {
    public:
        void configure(const std::unordered_map<std::string, double> &params) override;
};
class Linear2DMotion: public Motion2D {
    public:
        void configure(const std::unordered_map<std::string, double> &params) override;
};
class Constant2dMotion: public Motion2D {
    public:
        void configure(const std::unordered_map<std::string, double> &params) override;

};

#endif//RULES_H