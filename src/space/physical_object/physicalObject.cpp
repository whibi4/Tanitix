#include <cmath>
#include "physicalObject.h"
using namespace std;

PhysicalObject::PhysicalObject(Vector2D<double> initialPosition, 
                            Motion2D* motion): 
                            _currentPosition(initialPosition), 
                            _motion(motion) {
//Create new drawable object
_drawableObject = new DrawableObject(initialPosition);
};
PhysicalObject::~PhysicalObject() {
    delete _drawableObject;
};
void PhysicalObject::update(Time<double> deltaT) {
    _currentPosition = _motion->getMotionFunction()(deltaT, _currentPosition);
    _drawableObject->_position = _currentPosition;
    //trippy effect
    std::get<0>(_drawableObject->_rgb) =  _currentPosition._x/800;
    std::get<1>(_drawableObject->_rgb) =  _currentPosition._y/600;
    std::get<2>(_drawableObject->_rgb) =  (_currentPosition._y+_currentPosition._x)/1400;

}
