
#include <QImage>
#include <QPainter>
#include <iostream>
#include "ville.h"

#include "modele/terrain/terraintab.h"

int main(int argc, char *argv[])
{
    QImage img("map.png");
    TerrainTab terrain = TerrainTab(img, 1000, 1000);
    QImage res = img.scaled(1000,1000);

    QPainter paint(&res);

    std::vector<Ville> villes;
    int nb = 1000;
    villes.reserve(nb);
    for(int i=0; i < nb; i++){
        Vector2D pos((rand()%1001),(rand()%1001));
        Ville ville(Vector3D(XY(pos), terrain.getHauteur(XY(pos)))); //t.getHauteur(pos)
        /*for(int j = 0;  j < villes.size();  j++)   {
            Ville& ville2 = villes[j];
            float dist2 = distance2(ville.pos, ville2.pos);
            if(dist2 < 900){
                if(rand()%900 > dist2){
                    ville.idVilles.push_back(j);
                    ville2.idVilles.push_back(i);
                }
            }
        }*/

        villes.push_back(ville);
    }

    for(int i = 0;  i < villes.size();  i++)
    {
        const Ville& ville = villes[i];
        paint.setBrush(QColor(0, 255, 0));
        paint.drawPoint(XY(ville.pos));
        for(int j : ville.idVilles) {
            if(j > i)
            {
                paint.setBrush(QColor(255, 0, 0));
                paint.drawLine(XY(ville.pos), XY(villes[j].pos));
            }
        }
    }
    paint.end();
    res.save("resultat.png");

    return 0;
}

