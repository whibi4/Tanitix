#include "visio.h"
#include "space.h"
#include "physicalObject.h"
#include "maths.h"

#include <cmath>
#include <functional>
int main(int argc, char** argv) {
    SpaceManger spaceManger;
    Vector2D<double> initialPosition(300,300);

    std::function<Vector2D<double>(Time<double>, Vector2D<double>)> motion = [](Time<double> t, Vector2D<double> previousPosition) -> Vector2D<double>
    {
        const double centerX = 400.0;
        const double centerY = 300.0;
        const double radius = 100.0;
        const double angularSpeed = 0.005; // radians per second
        // Vector from center to previous position
        double dx = previousPosition._x - centerX;
        double dy = previousPosition._y - centerY;
        // Calculate current angle of the object in orbit
        double currentAngle = std::atan2(dy, dx);
        // Compute new angle based on time
        double newAngle = currentAngle + angularSpeed * t._t;

        // Compute new position using the new angle
        double newX = centerX + radius * std::cos(newAngle);
        double newY = centerY + radius * std::sin(newAngle);

        return Vector2D<double>(newX, newY);
    };

    PhysicalObject* object = new PhysicalObject(initialPosition, motion );
    spaceManger.addPhysicalObject(object);
    Visio visio(&spaceManger);
    return visio.run(argc, argv);
}