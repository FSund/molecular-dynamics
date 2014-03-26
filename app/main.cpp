#include <iostream>
#include <ios>
#include <iomanip>
#include <vector>
#include <sstream>

#include <system.h>

using namespace std;

int main()
{
    double sigma = 3.405;
    uint nUnitCells = 10;
    double unitCellLength = 5.260/sigma;
    double cutoff = sigma;
    System sys(nUnitCells, unitCellLength, cutoff);

    double dt = 0.01;
//    ostringstream filename;
    for (uint i = 0; i < 50; i++)
    {
//        filename << "/home/fsund/Data/molecular-dynamics/statefiles/state" << std::setw(3) << std::setfill('0') << i << ".xyz";
//        sys.writeToXYZ(filename.str());
//        sys.writeToXYZWithBoxID(filename.str());
//        filename.str(""); // clear stringstream

        sys.doOneTimeStep(dt);
        std::cout << "timestep = " << i << endl;
    }

    return 0;
}
