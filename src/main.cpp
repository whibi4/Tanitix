#include "visio.h"
#include "space.h"
#include "physicalObject.h"
 #include "maths.h"
 #include "physics.h"

#include <cmath>
#include <functional>
int main(int argc, char** argv) {
    SpaceManger spaceManger;
    spaceManger.execute();
    Visio visio(&spaceManger);
    return visio.run(argc, argv);
}