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
        void configureObject(double posX, double posY, double VelX, double VelY);
        void update(Time<double> deltaT);
        std::vector<DrawableObject*> getSpaceScene();
    private:
        int addPhysicalObject(PhysicalObject* phObj);
        void collusionTreatement();
        std::vector<PhysicalObject*> _objects;
};

#endif //SPACE