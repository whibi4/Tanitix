#ifndef DRAWABLE_OBJECT_H
#define DRAWABLE_OBJECT_H

class DrawableObject {
    public:
        DrawableObject(double r, double g, double b, double x, double y, double radius): _rgb(r, g, b), _position(x, y), _radius(radius) {};
        std::tuple<double, double, double> _rgb;
        std::pair<double, double>          _position;
        double                             _radius;
};



#endif //DRAWABLE_OBJECT_H