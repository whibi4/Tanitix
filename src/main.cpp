#include "visio.h"
#include "space.h"


int main(int argc, char** argv) {
    SpaceManger spaceManger;
    spaceManger.execute();
    Visio visio(&spaceManger);
    return visio.run(argc, argv);
}