#include <cmath>
#include <iostream>
#include "physicalObject.h"
using namespace std;

PhysicalObject::PhysicalObject(Vector2D<double> initialPosition, Vector2D<double> initialVelocity) {
    _currentPosition = initialPosition;
    _currentVelocity = initialVelocity;
    _currentAcceleration = Vector2D<double>(0,0);
    EmptyField<double>* emptyField = new EmptyField<double>();
    _fields.push_back(emptyField);
//Create new drawable object
_drawableObject = new DrawableObject(initialPosition);
};
PhysicalObject::~PhysicalObject() {
    delete _drawableObject;
};
void PhysicalObject::update(Time<double> deltaT) {
    _currentAcceleration = Vector2D<double>(0,0);
    for (auto& field : _fields) {
        _currentAcceleration = _currentAcceleration + field->calculateForce(_currentPosition, _currentVelocity, deltaT);
    };
    _currentVelocity = _currentVelocity + _currentAcceleration * deltaT._second;
    _currentPosition = _currentPosition + _currentVelocity * deltaT._second;
    _drawableObject->_position = _currentPosition;
    //trippy effect
    std::get<0>(_drawableObject->_rgb) =  _currentPosition._x/800;
    std::get<1>(_drawableObject->_rgb) =  _currentPosition._y/600;
    std::get<2>(_drawableObject->_rgb) =  (_currentPosition._y+_currentPosition._x)/1400;

}
