#include <iostream>
#include <random>
#include "drawableObject.h"
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
    int maxCount = random_int(4,10);
    size_t count = 0;
    while(true) {
        if (count > maxCount) break;
        double x = random_double(0, 800);
        double y = random_double(0, 600);
        double radius = random_double(10, 50);
        double r = random_double(0, 1);
        double g = random_double(0, 1);
        double b = random_double(0, 1);
        result.push_back(new DrawableObject(r,g,b,x,y,radius));
        count ++;
    }
    return result;
}