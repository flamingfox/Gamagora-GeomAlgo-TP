#include "bskeleton.h"

bSkeleton::bSkeleton(){}

void bSkeleton::reserveVilles(unsigned int size)
{
    villes.reserve(size);
}

bool bSkeleton::relierVille(float gamma)
{
    routes.clear();
    if(gamma > 0)
        routes.reserve(villes.size()/gamma);

    //#pragma omp parallel for schedule(dynamic,1)
    for(unsigned int i=0; i<villes.size(); i++){
        const Vector3D a = villes[i].getPosition();

        for(unsigned int j=i+1; j<villes.size(); j++){
            const Vector3D b = villes[j].getPosition();
            float distAB = powf(distance(a, b), gamma);

            unsigned int k = 0;
            for(    ; k<villes.size(); k++){
                if(k!=i && k!=j){
                    const Vector3D p = villes[k].getPosition();
                    if(distAB > (powf(distance(a, p), gamma) + powf(distance(b, p), gamma)))
                        break;
                }
            }
            if(k == villes.size())
                routes.push_back(Route(villes[i], villes[j]));
        }
    }
    return true;
}

bool bSkeleton::relierVille(const Terrain& terrain, float gamma)
{
    routes.clear();
    if(gamma > 0)
        routes.reserve(villes.size()/gamma);


    //#pragma omp parallel for schedule(dynamic,1)
    for(unsigned int i=0; i<villes.size(); i++){
        const Vector3D a = villes[i].getPosition();

        for(unsigned int j=i+1; j<villes.size(); j++){
            const Vector3D b = villes[j].getPosition();
            float distAB = powf(terrain.distance(a, b), gamma);

            unsigned int k = 0;
            for(    ; k<villes.size(); k++){
                if(k!=i && k!=j){
                    const Vector3D p = villes[k].getPosition();
                    if(distAB > (powf(terrain.distance(a, p), gamma) + powf(terrain.distance(b, p), gamma)))
                        break;

                }
            }
            if(k == villes.size())
                routes.push_back(Route(villes[i], villes[j]));
        }
    }
    return true;
}
