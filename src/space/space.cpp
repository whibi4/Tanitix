#include <iostream>
#include <random>
#include "drawableObject.h"
#include "physicalObject.h"
#include "space.h"
#include "rules.h"
using namespace std;

namespace {
    int random_int(int min, int max) {
        static std::random_device rd;         
        static std::mt19937 gen(rd());        
        std::uniform_int_distribution<> dist(min, max);  
        return dist(gen); 
    }
    double random_double(double min, double max) {
        static std::random_device rd;         
        static std::mt19937 gen(rd());        
        std::uniform_real_distribution<> dist(min, max);  
        return dist(gen);  
    }
}

vector<DrawableObject*> SpaceManger::getSpaceScene() {
    vector<DrawableObject*> result;
    for (auto& object : _objects) {
        result.push_back(object->getDrawableObject());
    };
    return result;
};

void SpaceManger::update(Time<double> deltaT) {
    for (auto& object : _objects) {
        object->update(deltaT);
    };
    collusionTreatement();
};

void SpaceManger::execute() {
    Motion2D* motion;
    Vector2D<double> initialPosition;
    PhysicalObject* object;
    motion= new Circular2DMotion();
    initialPosition = Vector2D<double>(550,120);
    motion->configure({
        {"centerX", 400},
        {"centerY", 300},
        {"angularVelocity", 0.005}
    });
    object = new PhysicalObject(initialPosition, motion);
    addPhysicalObject(object);
    motion= new Circular2DMotion();
    motion->configure({
        {"centerX", 300},
        {"centerY", 200},
        {"angularVelocity", 0.002}
    });

    initialPosition = Vector2D<double>(400,70);
    object = new PhysicalObject(initialPosition, motion);
    addPhysicalObject(object);

    motion= new Linear2DMotion();
    initialPosition = Vector2D<double>(0,0);
    motion->configure({
        {"velocity", 0.1}
    });
    object = new PhysicalObject(initialPosition, motion);
    addPhysicalObject(object);
};

void SpaceManger::collusionTreatement() {
    Motion2D* motion;
    motion= new Constant2dMotion();
    motion->configure({});
    for (size_t i = 0; i < _objects.size() - 1; i++) {
        PhysicalObject* obj1 = _objects[i];
        for (size_t j = i + 1; j < _objects.size(); j++) {
            PhysicalObject* obj2 = _objects[j];
            double distance = obj1->getCurrentPosition().distance(obj2->getCurrentPosition());
            if (distance <= 100) {
                obj1->makeRED();
                obj2->makeRED();
                obj1->getMotion()->reverseMotion();
                obj2->getMotion()->reverseMotion();
                // obj1->updateMotion(motion);
                // obj2->updateMotion(motion);
            }
        };
    }
}
