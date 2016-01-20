#include "grahamconvex.h"


bool cmpVec2Xless(const Vector2D& l, const Vector2D& r)
{
    if(l.x < r.x)
        return true;
    else if(l.x == r.x) {
        if(l.y < r.y)
            return true;
    }
    return false;
}

bool cmpVec2Xmore(const Vector2D& l, const Vector2D& r)
{
    if(l.x > r.x)
        return true;
    else if(l.x == r.x) {
        if(l.y > r.y)
            return true;
    }
    return false;
}

GrahamConvex::GrahamConvex(const QVector<Vector2D>& points)
{

    if(points.size() < 3)    {
        _points = points;
        initMinMaxCentre();
        this->setLinked(true);
        return;
    }
    QVector<Vector2D> ps = points;
    qSort(ps.begin(),ps.end(), cmpVec2Xless); //liste des points ordonnée de celui avec le plus petit x à celui avec le plus grand.

    QVector<Vector2D> ps2;  //liste des points que l'on va utiliser pour fermer l'enveloppe convexe au retour du dernier au premier point
    ps2.reserve(points.size());
    ps2.push_back(ps.first());

    _points.push_back(ps.first());
    int i;
    for(i = 1;  i < ps.size()-1;  i++)
    {
        const Vector2D& p = ps[i];
        int cote = inHalfSpaceDroit(_points.first(), ps.last(), p);
        if(cote == DROIT)
            break;
        else    {
            if(cote == GAUCHE)
                ps2.push_back(p);
            //si alignée, le point ne sera jamais dans l'enveloppe convexe
        }
    }
    if(i != ps.size()-1)    {
        _points.push_back(ps[i]);
        //construction de la première moitié de l'enveloppe convexe dans sa partie basse
        for(    ;  i < ps.size();  i++)
        {
            const Vector2D& p = ps[i];
            int cote2 = inHalfSpaceDroit(ps.first(),ps.last(),p);
            if(cote2 == DROIT || i == ps.size()-1)            {
                int cote = inHalfSpaceDroit(_points[_points.size()-2],_points.last(),p);
                if(cote == ALIGNEE)
                    _points.last() = p;
                else if(cote == GAUCHE)
                    _points.push_back(p);
                else    //DROIT
                {
                    _points.removeLast();
                    while(_points.size() > 1 && inHalfSpaceDroit(_points[_points.size()-2], _points.last(), p) != GAUCHE)   {
                        _points.removeLast();
                    }
                    _points.push_back(p);
                }
            }
            else    {
                if(cote2 == GAUCHE)
                    ps2.push_back(p);
                //si alignée, le point ne sera jamais dans l'enveloppe convexe
            }
        }
    }
    else
        _points.push_back(ps.last());

    if(ps2.size() > 1)    {
        //std::reverse(ps2.begin(), ps2.end());  //les points on été inséré dans l'ordre lexicographique dans ps2. En les inversant, on pourra le parcourir dans l'autre sans.
        int nbDemiBas = _points.size();
        _points.push_back(ps2.last());
        //construction de la seconde moitié de l'enveloppe convexe dans sa partie haute
        for(int i = ps2.size()-2;  i >= 0; i--)
        {
            const Vector2D& p = ps2[i];
            int cote = inHalfSpaceDroit(_points[_points.size()-2],_points.last(),p);
            if(cote == ALIGNEE)
                _points.last() = p;
            else if(cote == GAUCHE)
                _points.push_back(p);
            else    //DROIT
            {
                _points.removeLast();
                while(_points.size() > nbDemiBas && inHalfSpaceDroit(_points[_points.size()-2], _points.last(), p) != GAUCHE)
                    _points.removeLast();
                _points.push_back(p);
            }
        }
        //on supprime le point de départ et le point d'arrivée qui sont déjà dans la moitié du bas.
        _points.removeLast();

        //_points << ps3;
    }
    initMinMaxCentre();
    this->setLinked(true);
}



/*//première version avec plus de calcul
GrahamConvex::GrahamConvex(const QVector<Vector2D>& points)
{
    if(points.size() < 3)    {
        _points = points;
        initMinMaxCentre();
        this->setLinked(true);
        return;
    }
    QVector<Vector2D> ps = points;
    qSort(ps.begin(),ps.end(), cmpVec2Xless); //liste des points ordonnée de celui avec le plus petit x à celui avec le plus grand.

    QVector<Vector2D> ps2;  //liste des points que l'on va utiliser pour fermer l'enveloppe convexe au retour du dernier au premier point
    ps2.reserve(points.size());

    _points.push_back(ps.first());
    _points.push_back(ps[1]);

    //construction de la première moitié de l'enveloppe convexe dans sa partie basse
    for(int i = 2;  i < ps.size();  i++)
    {
        const Vector2D& p = ps[i];
        int cote = inHalfSpaceDroit(_points[_points.size()-2],_points.last(),p);
        if(cote == ALIGNEE)
            _points.last() = p;
        else if(cote == GAUCHE)
            _points.push_back(p);
        else    //DROIT
        {
            ps2.push_back(_points.last());
            _points.removeLast();
            while(_points.size() > 1 && inHalfSpaceDroit(_points[_points.size()-2], _points.last(), p) != GAUCHE)   {
                ps2.push_back(_points.last());
                _points.removeLast();
            }
            _points.push_back(p);
        }
    }

    if(!ps2.isEmpty())    {
        ps2.push_back(_points.first());
        qSort(ps2.begin(), ps2.end(), cmpVec2Xmore);
        QVector<Vector2D> ps3;  //vector des points de la seconde partie de l'enveloppe que l'on ajoutera à _points
        ps3.push_back(_points.last());
        ps3.push_back(ps2.first());
        //construction de la seconde moitié de l'enveloppe convexe dans sa partie haute
        for(int i = 1;  i < ps2.size(); i++)
        {
            const Vector2D& p = ps2[i];
            int cote = inHalfSpaceDroit(ps3[ps3.size()-2],ps3.last(),p);
            if(cote == ALIGNEE)
                ps3.last() = p;
            else if(cote == GAUCHE)
                ps3.push_back(p);
            else    //DROIT
            {
                ps3.removeLast();
                while(ps3.size() > 1 && inHalfSpaceDroit(ps3[ps3.size()-2], ps3.last(), p) != GAUCHE)
                    ps3.removeLast();
                ps3.push_back(p);
            }
        }
        //on supprime le point de départ et le point d'arrivée qui sont déjà dans la moitié du bas.
        ps3.removeLast();
        ps3.removeFirst();

        _points << ps3;
    }
    initMinMaxCentre();
    this->setLinked(true);
}
*/
