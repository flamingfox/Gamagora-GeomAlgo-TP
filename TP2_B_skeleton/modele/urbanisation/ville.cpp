#include "ville.h"


Ville::Ville(){}

Ville::Ville(const Vector3D &position):
    _position(position){}

/*
bool Ville::isConnected(const Ville &voisin) const
{
    for(Route r : routes){
        if(r._ville1 == voisin || r._ville2 == voisin)
            return true;
    }

    return false;
}

std::vector<Ville> Ville::getVilleVoisines() const
{
    std::vector<Ville> voisines;

    for(Route r : routes){
        if(r._ville1 != *this)
            voisines.push_back(r._ville1);

        if(r._ville2 != *this)
            voisines.push_back(r._ville2);

    }

    return voisines;
}
*/
