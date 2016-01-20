#include "bskeleton.h"

bSkeleton::bSkeleton(){}

bool bSkeleton::relierVille(const float &gamma)
{
    Vector3D a, b, p;

    for(int i=0; i<villes.size(); i++){
        a = villes[i].getPosition();
        for(int j=0; j<villes.size(); j++){
            if(j != i){
                b = villes[j].getPosition();
                for(int k=0; k<villes.size(); k++){
                    if(k!=i && k!=j){
                        p = villes[k].getPosition();
                        if(powf(distance(a, b), gamma) < powf(distance(a, p), gamma) + powf(distance(b, p), gamma)){
                            routes.push_back(Route(villes[i], villes[j]));
                        }
                    }
                }
            }
        }
    }
}

