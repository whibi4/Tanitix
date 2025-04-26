#include <iostream>
#include <random>
#include "drawableObject.h"
#include "physicalObject.h"
#include "space.h"
#include "Fields.h"
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
    LinearField<double>* field = new LinearField<double>(15, -6);
    Vector2D<double> initialPosition;
    PhysicalObject* object;
    initialPosition = Vector2D<double>(500,60);
    Vector2D<double> initialVelocity = Vector2D<double>(2,16);
    object = new PhysicalObject(initialPosition, initialVelocity);
    addPhysicalObject(object);
    for(auto obj : _objects) {
        obj->addField(field);
    };
};

void SpaceManger::collusionTreatement() {
/*
    for (size_t i = 0; i < _objects.size() - 1; i++) {
        PhysicalObject* obj1 = _objects[i];
        for (size_t j = i + 1; j < _objects.size(); j++) {
            PhysicalObject* obj2 = _objects[j];
            double distance = obj1->getCurrentPosition().distance(obj2->getCurrentPosition());
            if (distance <= 100) {
                obj1->makeRED();
                obj2->makeRED();

                // obj1->updateMotion(motion);
                // obj2->updateMotion(motion);
            }
        };
    }*/
}
