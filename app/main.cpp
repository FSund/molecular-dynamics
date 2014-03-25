#include <iostream>
#include <ios>
#include <iomanip>
#include <vector>
#include <sstream>

#include <system.h>

using namespace std;

int main()
{
    System sys;

    double dt = 0.01;
    ostringstream filename;
    for (uint i = 0; i < 300; i++)
    {
        filename << "statefiles/state" << std::setw(3) << std::setfill('0') << i << ".xyz";
        sys.writeToXYZ(filename.str());
        filename.str(""); // clear stringstream

        sys.doOneTimeStep(dt);
        std::cout << "timestep = " << i << endl;
    }

    return 0;
}
