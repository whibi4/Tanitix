#ifndef SPACE_H
#define SPACE_H
#include <iostream>
#include <vector>
#include "maths.h"
#include "physics.h"
class PhysicalObject;
class DrawableObject;
class SpaceManger {
    public:
        SpaceManger() = default;
        void execute();
        void update(Time<double> deltaT);
        std::vector<DrawableObject*> getSpaceScene();
    private:
        void addPhysicalObject(PhysicalObject* phObj) {_objects.push_back(phObj);};
        void collusionTreatement();
        std::vector<PhysicalObject*> _objects;
};       

#endif //SPACE