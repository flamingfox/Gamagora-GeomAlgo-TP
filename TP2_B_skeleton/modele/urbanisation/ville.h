#ifndef VILLE_H
#define VILLE_H

#include <vector>

#include "./geometrie/vector3d.h"
///#include "route.h"

class Ville
{
    //std::vector<Route> _routes;
    Vector3D _position;
public:
    Ville();
    Ville(const Vector3D& position);
    Ville(const float& x, const float& y, const float& z);

    inline Vector3D getPosition() const {return _position;}
    //inline std::vector<Route> getRoutes() const {return _routes;}

    //bool isConnected(const Ville& voisin) const;
    //std::vector<Ville> getVilleVoisines() const;
};

#endif // VILLE_H
