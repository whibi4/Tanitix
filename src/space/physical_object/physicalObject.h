#ifndef PHYSICAL_OBJECT_H
#define PHYSICAL_OBJECT_H

#include <functional>
#include "maths.h"
#include "physics.h"
#include "drawableObject.h"
#include "Fields.h"

class PhysicalObject {
    public:
        PhysicalObject(Vector2D<double> initialPosition, Vector2D<double> initialVelocity, Weight<double> weight = Weight<double>(1.0), double radius = 50.0);
        ~PhysicalObject();
        void update(Time<double>);
        DrawableObject* getDrawableObject() const {return _drawableObject;};
        Vector2D<double> getCurrentPosition() const {return _currentPosition;};
        void setCurrentVelocity(Vector2D<double> velocity) {_currentVelocity._x = velocity._x;
                                                            _currentVelocity._y = velocity._y;};
        Vector2D<double> getCurrentVelocity() const {return _currentVelocity;};
        Weight<double> getMass() const {return _weight;};
        double getRadius() const {return _radius;};
        void addField(Field<double>* field) {
            _fields.push_back(field);
        };
        /// debug
        void makeRED() {
            _drawableObject->_rgb = {1,0,0};
        }
    private:
        Vector2D<double>                                                    _currentPosition;
        DrawableObject*                                                     _drawableObject;
        Vector2D<double>                                                    _currentVelocity;
        Vector2D<double>                                                    _currentAcceleration;
        std::vector<Field<double>*>                                         _fields;
        Weight<double>                                                      _weight;
        double                                                              _radius;


};
#endif //PHYSICAL_OBJECT_H