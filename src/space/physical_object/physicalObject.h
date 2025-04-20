#ifndef PHYSICAL_OBJECT_H
#define PHYSICAL_OBJECT_H

#include <functional>
#include "maths.h"
#include "drawableObject.h"

class PhysicalObject {
    public:
        PhysicalObject(Vector2D<double>, std::function<Vector2D<double>(Time<double>, Vector2D<double>)>);
        ~PhysicalObject();
        void update(Time<double>);
        DrawableObject* getDrawableObject() const {return _drawableObject;};
    private:
        Vector2D<double>                                                    _currentPosition;
        std::function<Vector2D<double>(Time<double>, Vector2D<double>)>     _moveBehavior;
        DrawableObject*                                                     _drawableObject;

};
#endif //PHYSICAL_OBJECT_H