#include <iostream>
#include <random>
#include "drawableObject.h"
#include "physicalObject.h"
#include "space.h"
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
    }
};