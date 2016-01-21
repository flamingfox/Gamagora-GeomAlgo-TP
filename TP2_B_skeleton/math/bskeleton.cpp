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
                    if(distAB > (pow(terrain.distance(a, p), gamma) + pow(terrain.distance(b, p), gamma)))
                        break;

                }
            }
            if(k == villes.size())
                routes.push_back(Route(villes[i], villes[j]));
        }
    }
    return true;
}

double coutConstruction(Vector3D a, Vector3D b, TerrainTab &terrain){//prend en compte la hauteur et la dérivée de la hauteur
    double n = 5.0f;
    double cout = 0.0f;
    double distancetotale=distance(a,b);
    double nbPas = distancetotale/n;
    Vector3D pas = (b-a)/nbPas;
    double hauteur;
    double hauteurnext;

    Vector3D pa = a;
    Vector3D pb;

    for(double i =0; i< distancetotale; i+=n){
        pb = pa + pas;
        hauteur = terrain.getHauteur(pa.x,pa.y);
        hauteurnext = terrain.getHauteur(pb.x,pb.y);
        double c = hauteur/1000.0f;
        double zp = fabs((hauteurnext-hauteur)/pas.getNorm());

        c += zp<0.15 ? zp/0.15 : 40;
        cout += pas.getNorm() * (1 + c);
        pa = pb;
    }
    return cout;


}

bool bSkeleton::relierVilleHauteur2(const float &gamma, TerrainTab &terrain){
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
                    creationOK =  (pow(coutConstruction(a, b, terrain), gamma) > (pow(coutConstruction(a, p, terrain), gamma) + pow(coutConstruction(b, p, terrain), gamma)))? false : creationOK;
                }
            }
            if(creationOK)
                routes.push_back(Route(villes[i], villes[j]));
        }
    }

    return true;
}
