#ifndef SYSTEMGENERATOR_H
#define SYSTEMGENERATOR_H

#include <vector>
#include <random>
#include <cmath>

#include <atom.h>

class SystemGenerator
{
public:
//    SystemGenerator();
    std::vector<Atom> generateFCC(const int nUnitCells, const double unitCellLength);
    void boltzmannDistributeVelocities(const double temperature, const std::vector<Atom*> atoms);
    void uniformDistributeVelocities(const double uniformRange, const std::vector<Atom*> atoms);

private:
    void removeDriftInVelocity(const std::vector<Atom*> atoms);
};

#endif // SYSTEMGENERATOR_H
