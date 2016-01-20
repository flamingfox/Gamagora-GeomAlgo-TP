#include "bskeleton.h"

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

