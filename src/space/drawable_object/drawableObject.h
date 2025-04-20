#ifndef DRAWABLE_OBJECT_H
#define DRAWABLE_OBJECT_H

#include "maths.h"

class PhysicalObject;
class DrawableObject {
    friend class PhysicalObject;
    public:
        const std::tuple<double, double, double>& getRGB() const {return _rgb;};
        const Vector2D<double>& getPosition() const {return _position;};
        const double& getRadius() const {return _radius;};
    private:
        DrawableObject(double r, double g, double b, Vector2D<double> position, double radius): _rgb(r, g, b), _position(position), _radius(radius) {};
        DrawableObject(Vector2D<double> position): _rgb(0.0,0.0,0.0),  _position(position), _radius(50) {};
        std::tuple<double, double, double> _rgb;
        Vector2D<double>                   _position;
        double                             _radius;
};



#endif //DRAWABLE_OBJECT_H