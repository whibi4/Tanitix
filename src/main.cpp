#include "visio.h"
#include "space.h"

int main(int argc, char** argv) {
    SpaceManger spaceManger;
    Visio visio(&spaceManger);
    return visio.run(argc, argv);
}