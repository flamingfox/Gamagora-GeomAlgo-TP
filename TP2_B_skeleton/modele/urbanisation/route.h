#ifndef ROUTE_H
#define ROUTE_H

#include "ville.h"

class Ville;

class Route
{    
public:
    Route();
    Route(Ville& ville1, Ville& ville2);

    Ville _ville1, _ville2;
};

#endif // ROUTE_H
