#include "jarvisconvex.h"
#include <set>

JarvisConvex::JarvisConvex(const QVector<Vector2D>& points)
{
    int iMin = 0;
    for(int i = 1;  i < points.size();  i++)    {
        if(points[i].x < points[iMin].x)
            iMin = i;
        else if(points[i].x == points[iMin].x && points[i].y < points[iMin].y)
            iMin = i;
    }

    _points.push_back(points[iMin]);

    int next = -1;  //(iMin != 0    ?   0 :   1);


    while(next != iMin)
    {
        //if(indices.count(next) == 0)
        next = iMin;
        _points.push_back(points[next]);

        /*next = 0;
        while(indices.count(next) == 1)
            next++;*/

        for(int i = 0;  i < points.size();  i++)
        {
            int cote = inHalfSpaceDroit(_points[_points.size()-2],_points.last(), points[i]);
            if(cote == ALIGNEE)
            {
                int cote2 = coteAlignement(points[i], _points[_points.size()-2],_points.last());
                if(cote2 == 1   ||
                     (cote2 == 0 && i== iMin && points[i] != _points[_points.size()-2]) )       //i == iMin dans le cas extrême où un point est égal au points iMin
                {
                    _points.last() = points[i];
                    next = i;
                }
            }
            else    {
                if(cote == DROIT)
                {
                    _points.last() = points[i];
                    next = i;
                }

            }
        }
        //    indices.insert(next);

        //_points.push_back(points[next]);
#ifdef DEBUG_PROBLEME
        if(next == 1555)    //pour le débug, retrouver un indice précis où il y a un problème
            std::cout << "ici" << std::endl;
        else
            for(int i3 = 0; i3 < getNbPoints();  i3++)
            {
                if(inHalfSpaceDroit(_points[i3], _points[(i3+1)%getNbPoints()], _points[(i3+2)%getNbPoints()]))
                    std::cout << "problème " << i3 << " -> " << getNbPoints() << " => " << next << std::endl;
            }
#endif
    }
    _points.removeLast();

    initMinMaxCentre();
    this->setLinked(true);
}
