#include "rules.h"
#include <stdexcept>
#include <sstream>
#include <cmath>
void Circular2DMotion::configure(const std::unordered_map<std::string, double> &params) {
    double x,y,w;
    for (const auto& [key, val] : params) {
        if (key.compare("centerX") == 0) {
            x = val;
        } else if (key.compare("centerY") == 0) {
            y = val;
        } else if (key.compare("angularVelocity") == 0) {
            w = val;
        } else {
            std::ostringstream oss;
            oss << "Unexpected value " << key << ". Error occurred.";
            throw std::invalid_argument(oss.str());
        }
    };

    _motionFunction = [=](Time<double> time, Vector2D<double> prevPos) -> Vector2D<double> {
        double radius = sqrt(pow((x-prevPos._x),2) + pow((y-prevPos._y),2));
        double dx = prevPos._x - x;
        double dy = prevPos._y - y;
        double currentAngle = std::atan2(dy, dx);
        double newAngle = currentAngle + w * time._millisecond;
        double newX = x + radius * std::cos(newAngle);
        double newY = y + radius * std::sin(newAngle);
        return Vector2D<double>(newX, newY);
    };
};
void Linear2DMotion::configure(const std::unordered_map<std::string, double> &params) {
    double v;
    for (const auto& [key, val] : params) {
        if (key.compare("velocity") == 0) {
            v = val;
        } else {
            std::ostringstream oss;
            oss << "Unexpected value " << key << ". Error occurred.";
            throw std::invalid_argument(oss.str());
        }
    };

    _motionFunction = [=](Time<double> time, Vector2D<double> prevPos) -> Vector2D<double> {
        double newX = prevPos._x + v*time._millisecond;
        double newY = prevPos._y + v*time._millisecond;
        return Vector2D<double>(newX, newY);
    };
};
void Constant2dMotion::configure(const std::unordered_map<std::string, double> &params) {
    _motionFunction = [=](Time<double> time, Vector2D<double> prevPos) -> Vector2D<double> {
        double newX = prevPos._x;
        double newY = prevPos._y;
        return Vector2D<double>(newX, newY);
    };
};