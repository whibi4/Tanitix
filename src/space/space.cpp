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
    size_t objCount = 600;
    while (objCount-- > 0) {
        LinearField<double> *field = new LinearField<double>(::random_int(-400, 400), ::random_int(-400, 400));
        Vector2D<double> initialPosition = Vector2D<double>(::random_int(-200, 1000), ::random_int(-200, 800));
        Vector2D<double> initialVelocity = Vector2D<double>(::random_int(-400, 400), ::random_int(-400, 400));
        PhysicalObject *object = new PhysicalObject(initialPosition, initialVelocity);
        addPhysicalObject(object);
        object->addField(field);
    };
};

void SpaceManger::collusionTreatement() {

    for (size_t i = 0; i < _objects.size() - 1; i++) {
        PhysicalObject* obj1 = _objects[i];
        for (size_t j = i + 1; j < _objects.size(); j++) {
            PhysicalObject* obj2 = _objects[j];
            double distance = obj1->getCurrentPosition().distance(obj2->getCurrentPosition());
            if (distance <= 100) {
                obj1->makeRED();
                obj2->makeRED();
            }
        };
    }
}
