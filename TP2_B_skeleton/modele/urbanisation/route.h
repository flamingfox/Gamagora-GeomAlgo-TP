#ifndef ROUTE_H
#define ROUTE_H

#include "ville.h"

class Ville;

class Route
{    
public:
    Route();
    Route(Ville* const ville1, Ville* const ville2);

    Ville* _ville1, * _ville2;
};

#endif // ROUTE_H
