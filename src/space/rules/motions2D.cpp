#include "rules.h"
#include <stdexcept>
#include <sstream>
#include <cmath>
void Circular2DMotion::configure(const std::unordered_map<std::string, double> &params) {
    for (const auto& [key, val] : params) {
        if (key.compare("centerX") == 0) {
            _centerX = val;
        } else if (key.compare("centerY") == 0) {
            _centerY = val;
        } else if (key.compare("angularVelocity") == 0) {
            _angularVelocity = val;
        } else {
            std::ostringstream oss;
            oss << "Unexpected value " << key << ". Error occurred.";
            throw std::invalid_argument(oss.str());
        }
    };

    _motionFunction = [this](Time<double> time, Vector2D<double> prevPos) -> Vector2D<double> {
        double radius = sqrt(pow((_centerX-prevPos._x),2) + pow((_centerY-prevPos._y),2));
        double dx = prevPos._x - _centerX;
        double dy = prevPos._y - _centerY;
        double currentAngle = std::atan2(dy, dx);
        double newAngle = currentAngle + _angularVelocity * time._millisecond;
        double newX = _centerX + radius * std::cos(newAngle);
        double newY = _centerY + radius * std::sin(newAngle);
        return Vector2D<double>(newX, newY);
    };
};
void Linear2DMotion::configure(const std::unordered_map<std::string, double> &params) {
    for (const auto& [key, val] : params) {
        if (key.compare("velocity") == 0) {
            _velocity = val;
        } else {
            std::ostringstream oss;
            oss << "Unexpected value " << key << ". Error occurred.";
            throw std::invalid_argument(oss.str());
        }
    };

    _motionFunction = [this](Time<double> time, Vector2D<double> prevPos) -> Vector2D<double> {
        double newX = prevPos._x + _velocity*time._millisecond;
        double newY = prevPos._y + _velocity*time._millisecond;
        return Vector2D<double>(newX, newY);
    };
};
void Constant2dMotion::configure(const std::unordered_map<std::string, double> &params) {
    _motionFunction = [](Time<double> time, Vector2D<double> prevPos) -> Vector2D<double> {
        double newX = prevPos._x;
        double newY = prevPos._y;
        return Vector2D<double>(newX, newY);
    };
};