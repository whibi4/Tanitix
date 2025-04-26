#include "maths.h"
#include "physics.h"
#include <functional>
#include <vector>
#ifndef FIELDS_H
#define FIELDS_H
template<typename T>
//Field mother class
class Field{
    public:
        virtual ~Field() = default;
        //Function to calculate the force on an object
        virtual Vector2D<T> calculateForce(Vector2D<T> pos, Vector2D<T> vel, Time<T> time)=0;
    protected:
        Field()= default;
        //Different components of a field 'e.g. gravity, magnetic field, ...'
        std::vector<T> _fieldComponents;

};

template<typename T>
class EmptyField: public Field<T>{
    public:
        EmptyField()= default;
        ~EmptyField()= default;
        Vector2D<T> calculateForce(Vector2D<T> pos, Vector2D<T> vel, Time<T> time) override {
            return Vector2D<T>(0,0);
        };
};

template<typename T>
class LinearField: public Field<T>{
    public:
        LinearField(T forceX, T forceY) {
            this->_fieldComponents.push_back(forceX);
            this->_fieldComponents.push_back(forceY);
        };
        ~LinearField()= default;
        Vector2D<T> calculateForce(Vector2D<T> pos, Vector2D<T> vel, Time<T> time) override {
            return Vector2D<T>(this->_fieldComponents[0],this->_fieldComponents[1]);
        };
};

#endif