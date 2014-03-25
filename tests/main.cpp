#include <cmath>

#include <unittest++/UnitTest++.h>
#include <vector3d.h>

#include <force.h>
#include <atom.h>

using namespace std;

SUITE(Vector3D)
{
    struct Data
    {
        Data() :
            u(Vector3D(1.0, -2.0, 3.0)),
            v(Vector3D(2.0, -4.0, 6.0)),
            zero(Vector3D())
        {}
        ~Data() { /* some teardown */ }

        Vector3D u;
        Vector3D v;
        Vector3D zero;
    };

    TEST_FIXTURE(Data, DefaultConstructor)  { CHECK_EQUAL(Vector3D(), zero); }
    TEST_FIXTURE(Data, DoubleConstructor)   { CHECK_EQUAL(u, Vector3D(1.0, -2.0, 3.0)); }
    TEST_FIXTURE(Data, CopyConstructor)     { CHECK_EQUAL(u, Vector3D(u)); }
    TEST_FIXTURE(Data, LengthSquared)       { CHECK_EQUAL(u.lengthSquared(), 1.0+4.0+9.0); }
    TEST_FIXTURE(Data, Length)              { CHECK_EQUAL(u.length(), sqrt(1.0+4.0+9.0)); }

    TEST_FIXTURE(Data, AddVectors)          { CHECK_EQUAL(u+v, Vector3D(3.0, -6.0, 9.0)); }
    TEST_FIXTURE(Data, MultiplyAndDivide)   { CHECK_EQUAL(u*2.0/2.0, u); }
    TEST_FIXTURE(Data, Multiply1)           { CHECK_EQUAL(u*2.0, v); }
    TEST_FIXTURE(Data, Multiply2)           { CHECK_EQUAL(u*-2.0, -v); }
    TEST_FIXTURE(Data, Divide1)             { CHECK_EQUAL(v/2.0, u); }
    TEST_FIXTURE(Data, Divide2)             { CHECK_EQUAL(v/-2.0, -u); }
}

SUITE(Forces)
{
    struct ForceData
    {
        ForceData() :
            force(new Force),
            atom1(new Atom(Vector3D(0.0, 0.0, 0.0))),
            atom2(new Atom(Vector3D(2.0, 0.0, 0.0))),
            systemSize(Vector3D(10.0, 1.0, 1.0)),
            halfSystemSize(systemSize/2.0)
        {
            force->calculateAndApplyForces(atom1, atom2, systemSize, halfSystemSize);
        }

        Force *force;
        Atom *atom1;
        Atom *atom2;
        Vector3D systemSize;
        Vector3D halfSystemSize;
    };

    TEST_FIXTURE(ForceData, ForceCalculation)
    {
        CHECK(
               atom1->getForce()[0] == -24.0*(2.0 - pow(2.0, 6.0))/pow(2.0, 13.0)*2.0/2.0
            && atom1->getForce()[1] == 0.0
            && atom1->getForce()[2] == 0.0
        );
    }

    TEST_FIXTURE(ForceData, NewtonsThirdLaw)
    {
        CHECK(
               atom1->getForce()[0] == -atom2->getForce()[0]
            && atom1->getForce()[1] == -atom2->getForce()[1]
            && atom1->getForce()[2] == -atom2->getForce()[2]
        );
    }
}

int main()
{
    return UnitTest::RunAllTests();
}
