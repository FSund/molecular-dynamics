#ifndef BOX_H
#define BOX_H

#include <vector>
#include <list>

#include <atom.h>

class Box
{
public:
    Box() = delete; // delete default constructor
    Box(const std::vector<&Atom>& atoms);

private:
    std::list<&Atom> atoms;
};

#endif // BOX_H
