#include <cmath>
#include "physicalObject.h"
using namespace std;

PhysicalObject::PhysicalObject(Vector2D<double> initialPosition, 
                            std::function<Vector2D<double>(Time<double>, Vector2D<double>)> moveBehavior): 
                            _currentPosition(initialPosition), 
                            _moveBehavior(moveBehavior) {
//Create new drawable object
_drawableObject = new DrawableObject(initialPosition);
};
PhysicalObject::~PhysicalObject() {
    delete _drawableObject;
};
void PhysicalObject::update(Time<double> deltaT) {
    _currentPosition = _moveBehavior(deltaT, _currentPosition);
    _drawableObject->_position = _currentPosition;
}
