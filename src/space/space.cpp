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

int SpaceManger::addPhysicalObject(PhysicalObject* phObj) {
    for (auto& object : _objects) {
        double distance = object->getCurrentPosition().distance(phObj->getCurrentPosition());
        if (distance <= (object->getRadius() + phObj->getRadius())) {
            std::cerr << "Object already in space" << std::endl;
            return -1;
        }
    }
    _objects.push_back(phObj);
    return 0;
};

void SpaceManger::execute() {
    size_t objCount = 600;
    while (objCount-- > 0) {
        LinearField<double> *field = new LinearField<double>(::random_int(-400, 400), ::random_int(-400, 400));
        Vector2D<double> initialPosition = Vector2D<double>(::random_int(-200, 1000), ::random_int(-200, 800));
        Vector2D<double> initialVelocity = Vector2D<double>(::random_int(-400, 400), ::random_int(-400, 400));
        double mass = random_int(0, 100);
        double radius = mass;
        PhysicalObject *object = new PhysicalObject(initialPosition, initialVelocity, mass, radius);
        if (addPhysicalObject(object)==-1) {
            delete object;
            delete field;
            continue;
        }
        object->addField(field);
    };
};
void SpaceManger::configureObject(double posX, double posY, double VelX, double VelY) {
    LinearField<double> *field = new LinearField<double>(0, 0);
    Vector2D<double> initialPosition = Vector2D<double>(posX, posY);
    Vector2D<double> initialVelocity = Vector2D<double>(VelX, VelY);
    double mass = 30;
    double radius = mass;
    PhysicalObject *object = new PhysicalObject(initialPosition, initialVelocity, mass, radius);
    if (addPhysicalObject(object)==-1) {
        delete object;
        delete field;
    } else {
        object->addField(field);
    }
};

void SpaceManger::collusionTreatement() {

    for (size_t i = 0; i < _objects.size() - 1; i++) {
        PhysicalObject* obj1 = _objects[i];
        for (size_t j = i + 1; j < _objects.size(); j++) {
            PhysicalObject* obj2 = _objects[j];
            double distance = obj1->getCurrentPosition().distance(obj2->getCurrentPosition());
            if (distance <= (obj1->getRadius() + obj2->getRadius())) {
                //collision
                Vector2D<double> normal = (obj2->getCurrentPosition() - obj1->getCurrentPosition()).normalize();
                double v1n = obj1->getCurrentVelocity().dot(normal);
                double v2n = obj2->getCurrentVelocity().dot(normal);
                double v1n_after = ((obj1->getMass() - obj2->getMass()) / (obj1->getMass() + obj2->getMass())) * v1n + (obj2->getMass()*2 / (obj1->getMass() + obj2->getMass())) * v2n;
                double v2n_after = ((obj1->getMass()*2) / (obj1->getMass() + obj2->getMass())) * v1n + ((obj2->getMass() - obj1->getMass()) / (obj1->getMass() + obj2->getMass())) * v2n;
                Vector2D<double> v1n_vec = normal * v1n_after;
                Vector2D<double> v2n_vec = normal * v2n_after;
                Vector2D<double> v1t_vec = obj1->getCurrentVelocity() - (normal * v1n);
                Vector2D<double> v2t_vec = obj2->getCurrentVelocity() - (normal * v2n);
                obj1->setCurrentVelocity(v1t_vec + v1n_vec) ;
                obj2->setCurrentVelocity(v2t_vec + v2n_vec) ;
                obj1->makeRED();
                obj2->makeRED();
            }
        };
    }
}
