#include "bskeleton.h"
#include <QDebug>

bSkeleton::bSkeleton(){}

bSkeleton::~bSkeleton(){
    for(Ville* ville:   villes)
        delete ville;
}

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
        const Vector3D& a = villes[i]->getPosition();

        for(unsigned int j=i+1; j<villes.size(); j++){
            const Vector3D& b = villes[j]->getPosition();
            float distAB = powf(distance(a, b), gamma);

            unsigned int k;
            for(k = 0; k<villes.size(); k++){
                if(k!=i && k!=j){
                    const Vector3D& p = villes[k]->getPosition();
                    float distAP = powf(distance(a, p), gamma);
                    if(distAB < distAP) //si la distance de AB* est déjà plus grande que la distance AP*,
                        continue;       // pas besoin de calculer la distance BP* qui peut être lourd en temps de calcul selon la méthode utilisé.
                    else if(distAB > distAP + powf(distance(b, p), gamma))  //si la distance AB* est supérieur à la somme des deux autres
                        break;          //la route n'ai pas insérer dans le B-squelette.
                }
            }
            if(k == villes.size())  //si aucun somme de routes n'a une plus petit distance* que celle de AB
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
        const Vector3D& a = villes[i]->getPosition();

        for(unsigned int j=i+1; j<villes.size(); j++){
            const Vector3D& b = villes[j]->getPosition();
            double distAB = pow(terrain.distance(a, b), gamma);

            unsigned int k;
            for(k = 0; k<villes.size(); k++){
                if(k!=i && k!=j){
                    const Vector3D& p = villes[k]->getPosition();
                    double distAP = pow(terrain.distance(a, p), gamma);
                    if(distAB < distAP)
                        continue;
                    else if(distAB > distAP + pow(terrain.distance(b, p), gamma))
                        break;

                }
            }
            if(k == villes.size())
                routes.push_back(Route(villes[i], villes[j]));
        }
    }
    return true;
}

double coutConstruction(const Vector3D& a, const Vector3D& b, const Terrain& terrain, double n = 5.0){//prend en compte la hauteur et la dérivée de la hauteur
    double distancetotale = distance(a,b);
    double hauteur = terrain.getHauteur(a);

    double cout = 0.0;
    Vector3D pa = a;
    double nbPas = distancetotale/n;
    const Vector3D pas = (b-a)/nbPas;

    for(double i = 0; i< distancetotale-n; i+=n){
        const Vector3D pb = pa + pas;
        double hauteurnext = terrain.getHauteur(pb);
        double zp = fabs((hauteurnext-hauteur)/n);

        double c = hauteur/1000.0;
        c += zp<0.15 ? zp/0.15 : 40;
        cout += n * (1 + c);

        pa = pb;
        hauteur = hauteurnext;
    }
    //effectuer le dernier pas de calcul de distance jusqu'à 'b'
    double dist = distance(pa, b);
    double hauteurFin = terrain.getHauteur(b);
    double zp = fabs((hauteurFin-hauteur)/dist);

    double c = hauteur/1000.0;
    c += zp<0.15 ? zp/0.15 : 40;
    cout += dist * (1 + c);


    return cout;
}

bool bSkeleton::relierVilleHauteur2(float gamma, const Terrain& terrain){
    routes.clear();

    for(unsigned int i=0; i<villes.size(); i++){
        const Vector3D& a = villes[i]->getPosition();

        for(unsigned int j=i+1; j<villes.size(); j++){
            const Vector3D& b = villes[j]->getPosition();
            double distAB = pow(coutConstruction(a, b, terrain), gamma);

            unsigned int k;
            for(k=0; k<villes.size(); k++){
                if(k!=i && k!=j){
                    const Vector3D& p = villes[k]->getPosition();
                    double distAP = pow(coutConstruction(a, p, terrain), gamma);
                    if(distAB < distAP)
                        continue;
                    else if(distAB > distAP + pow(coutConstruction(b, p, terrain), gamma))
                        break;
                }
            }
            if(k == villes.size())
                routes.push_back(Route(villes[i], villes[j]));
        }
    }
    return true;
}
