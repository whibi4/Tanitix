#ifndef SPACE_H
#define SPACE_H
#include <iostream>
#include <vector>
#include "maths.h"
class PhysicalObject;
class DrawableObject;
class SpaceManger {
    public:
        SpaceManger() = default;
        void update(Time<double> deltaT);
        void addPhysicalObject(PhysicalObject* phObj) {_objects.push_back(phObj);};
        std::vector<DrawableObject*> getSpaceScene();
    private:
        std::vector<PhysicalObject*> _objects;
};       

#endif //SPACE