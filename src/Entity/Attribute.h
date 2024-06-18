
#ifndef PHYSICS_DEMO_ATTRIBUTE_H
#define PHYSICS_DEMO_ATTRIBUTE_H

//////////////////////////////////////////////////////
////
////  Entities are composed of Attributes
////  This class defines the base for the following:
////
////  //TODO
////
//////////////////////////////////////////////////////

class Attribute
{
public:

    // pure virtual enables polymorphism
    virtual ~Attribute() = default;
private:
};

#endif //PHYSICS_DEMO_ATTRIBUTE_H
