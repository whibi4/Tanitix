#ifndef SPACE_H
#define SPACE_H
#include <iostream>
#include <vector>

class PhysicalObject;
class DrawableObject;
class SpaceManger {

    public:
        SpaceManger() = default;
        void update() {};
        std::vector<DrawableObject*> getSpaceScene();
    private:
        std::vector<PhysicalObject*> _objects;
};

#endif //SPACE