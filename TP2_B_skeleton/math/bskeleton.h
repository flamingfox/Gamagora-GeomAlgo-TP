#ifndef BSKELETON_H
#define BSKELETON_H

#include "./modele/urbanisation/route.h"
#include "./modele/urbanisation/ville.h"
#include "modele/terrain/terraintab.h"

class bSkeleton
{
    std::vector<Ville*> villes;
    std::vector<Route> routes;
public:
    bSkeleton();
    ~bSkeleton();

    inline void addVille(Ville* ville) {villes.push_back(ville);}
    inline std::vector<Route> getRoutes() const {return routes;}
    inline std::vector<Ville*> getVilles() const {return villes;}

    void reserveVilles(unsigned int size);


    bool relierVille(float gamma);
    bool relierVille(const Terrain& terrain, float gamma);
    //bool relierVilleHauteur(const float &gamma, TerrainTab &terrain);
    bool relierVilleHauteur2(float gamma, const Terrain& terrain);

};

#endif // BSKELETON_H
