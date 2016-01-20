#ifndef BSKELETON_H
#define BSKELETON_H

#include "./modele/urbanisation/route.h"
#include "./modele/urbanisation/ville.h"
#include "modele/terrain/terraintab.h"

class bSkeleton
{
    std::vector<Ville> villes;
    std::vector<Route> routes;
public:
    bSkeleton();

    inline void addVille(const Ville& ville) {villes.push_back(ville);}
    inline std::vector<Route> getRoutes() const {return routes;}
    inline std::vector<Ville> getVilles() const {return villes;}

    bool relierVille(const float& gamma);
    bool relierVilleHauteur(const float &gamma, TerrainTab &terrain);

};

#endif // BSKELETON_H
