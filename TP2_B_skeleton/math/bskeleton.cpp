#include "bskeleton.h"
#include <QDebug>

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

float distanceHauteur(Vector3D a, Vector3D b, TerrainTab &terrain){
    float cout = 0.0f;
    float nbPas = distance(a,b);
    Vector3D pas = (b-a)/nbPas;
    float hauteur;
    for(float i =0; i< nbPas; i+=1.0){
        hauteur = terrain.getHauteur((a+pas).x,(a+pas).y);
        //hauteur = sqrtf(hauteur);
        cout += hauteur;
    }
    return cout/100000.0f;
}

bool bSkeleton::relierVilleHauteur(const float &gamma, TerrainTab &terrain){
    routes.clear();

    Vector3D a, b, p;
    bool creationOK;
    for(int i=0; i<villes.size(); i++){
        a = villes[i].getPosition();

        for(int j=i+1; j<villes.size(); j++){
            b = villes[j].getPosition();
            creationOK = true;

            for(int k=0; k<villes.size(); k++){
                if(k!=i && k!=j){
                    p = villes[k].getPosition();
                    creationOK =  (powf(distanceHauteur(a, b, terrain), gamma) > (powf(distanceHauteur(a, p, terrain), gamma) + powf(distanceHauteur(b, p, terrain), gamma)))? false : creationOK;
                }
            }
            if(creationOK)
                routes.push_back(Route(villes[i], villes[j]));
        }
    }

    return true;
}
