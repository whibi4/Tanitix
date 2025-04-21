#ifndef PHYSICAL_OBJECT_H
#define PHYSICAL_OBJECT_H

#include <functional>
#include "maths.h"
#include "physics.h"
#include "drawableObject.h"
#include "rules.h"

class PhysicalObject {
    public:
        PhysicalObject(Vector2D<double>, Motion2D*);
        ~PhysicalObject();
        void update(Time<double>);
        DrawableObject* getDrawableObject() const {return _drawableObject;};
        Vector2D<double> getCurrentPosition() const {return _currentPosition;};
        Motion2D* getMotion() {return _motion;};
        void updateMotion(Motion2D* motion) {_motion = motion;};
        /// debug
        void makeRED() {
            _drawableObject->_rgb = {1,0,0};
        }
    private:
        Vector2D<double>                                                    _currentPosition;
        Motion2D*                                                           _motion;
        DrawableObject*                                                     _drawableObject;

};
#endif //PHYSICAL_OBJECT_H