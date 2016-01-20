#include "bskeleton.h"
#include <QDebug>

bSkeleton::bSkeleton(){}

bool bSkeleton::relierVille(const float &gamma)
{
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
                    creationOK =  (powf(distance(a, b), gamma) > (powf(distance(a, p), gamma) + powf(distance(b, p), gamma)))? false : creationOK;

                }
            }
            if(creationOK)
                routes.push_back(Route(villes[i], villes[j]));
        }
    }
}

float distanceHauteur(Vector3D a, Vector3D b, TerrainTab &terrain){
    float cout = 0.0f;
    float nbPas = distance(a,b);
    Vector3D pas = (b-a)/nbPas;
    float hauteur;
    for(float i =0; i< nbPas; i+=1.0){
        hauteur = terrain.getHauteur((a+pas).x,(a+pas).y);
        /*if(hauteur>50)
            cout += 1000;
        cout += 100;*/
        cout += hauteur;
    }
    return cout;
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
}

