#include "convexe2d.h"

Convexe2D::Convexe2D(const QVector<Vector2D>& points)
{

    if(points.size() < 3)
    {
        _points = points;
        initMinMaxCentre();
        setLinked(true);
        return;
    }
    int i0, i1, i2;
    if(!initNonAlignee(points, i0,i1,i2))   //si tous les points sont alignés
    {
        _points.push_back(points[i0]);
        _points.push_back(points[i1]);
        _min = min(points[i0], points[i1]);
        _max = max(points[i0], points[i1]);
        _centre =(_min+_max)/2;
        setLinked(true);
        return;
    }

    initTriangle(points[i0],points[i1],points[i2]);

    for(int i=i2+1; i< points.size(); i++){
        ajoutPointConvex(points[i]);

#ifdef DEBUG_PROBLEME
        if(i == -1)    //pour le débug, retrouver un indice précis où il y a un problème
            std::cout << "ici" << std::endl;
        else
            for(int i3 = 0; i3 < getNbPoints();  i3++)
            {
                if(inHalfSpaceDroit(_points[i3], _points[(i3+1)%getNbPoints()], _points[(i3+2)%getNbPoints()]))
                    std::cout << "problème " << i3 << " -> " << getNbPoints() << " => " << i << std::endl;
            }
#endif
    }

    initMinMaxCentre();
    setLinked(true);
}

Convexe2D::Convexe2D(const Convexe2D& convexe, const Vector2D& point)
{
    _points = convexe._points;
    ajoutPointConvex(point);
    initMinMaxCentre();
    /*bool debutCoupe = 0;

    for(int i=0; i<convexe._points.length(); i++){
        if(inHalfSpaceDroit(convexe._points[i],convexe._points[(i+1)%convexe._points.length()], point)){
            if(debutCoupe){
                _points.push_back(convexe._points[i]);
                _points.push_back(point);
            }
        }
        else{
            _points.push_back(convexe._points[i]);
            debutCoupe = 1;
        }
    }

    if(_points.empty()){
        _points = convexe._points;
    }*/
    setLinked(true);
}


Convexe2D::Convexe2D(const Vector2D& point0, const Vector2D& point1, const Vector2D& point2)
{    
    initTriangle(point0, point1, point2);
}

void Convexe2D::initTriangle(const Vector2D& point0, const Vector2D& point1, const Vector2D& point2)
{
    if(inHalfSpaceDroit(point0, point1, point2)){
        addPoint(point0);
        addPoint(point2);
        addPoint(point1);
    }
    else{
        addPoint(point0);
        addPoint(point1);
        addPoint(point2);
    }
}


/** Recherche les 3 premiers points non aligné
*/
bool Convexe2D::initNonAlignee(const QVector<Vector2D>& points, int& i0, int& i1, int& i2) const
{
    i0 = 0; i1 = 1; i2 = 2;
    Vector2D p0 = points[i0], p1 = points[i1];
    while(i2 < points.size())
    {
        Vector2D p2 = points[i2];
        if(inHalfSpaceDroit(p0,p1,p2) != ALIGNEE)
            return true;
        else
        {
            //mettre p2 entre p0 et p1
            if(distance2(p0, p1) < distance2(p0, p2)){  // p0 -- p1 -- p2   ou   p1 -- p0 ---- p2
                int swap = i2;
                i2 = i1;
                i1 = swap;
                p1 = points[i1];
                p2 = points[i2];                       // p0 -- p2 --- p1    ou   p2 -- p0 ---- p1
            }
            if(distance2(p0, p1) < distance2(p1, p2))   //p2 -- p0 ---- p1
            {
                int swap = i0;
                i0 = i2;
                i2 = swap;
                p0 = points[i0];                       //p0 -- p2 ---- p1
                //p2 = points[i2];
            }
            i2++;
        }
    }
    return false;   //on ne peut pas construire un triangle avec les points, ils sont tous aligné
}

void Convexe2D::ajoutPointConvex(const Vector2D& p)
{
    int nbP = getNbPoints();
    if(nbP < 2)    {
        _points.push_back(p);
        return;
    }

    int deb, fin;
    if(findIndicesCoupe(p,deb,fin))    {
        int i = (deb+1)%nbP;
        if(i == fin)
            _points.insert(fin, p); //on a juste à supprimer le segment entre deux points et à relier ces dernier au point à ajouter
        else
        {    //sinon, on enlève les points entre l'index de debut de découpe et l'index de fin de découpe
            if(i < fin) //on ne repasse pas par le point 0
            {
                _points[i] = p;
                _points.remove(i+1, fin-i-1);
            }
            else    //sinon, on enlève ce qui est avant indice fin et après l'indice deb
            {
                _points.remove(i, nbP-i);
                if(fin != 0)
                    _points.remove(0,fin);
                _points.push_back(p);
            }
        }
    }
}

/**si 3 points sont alignés, on veut savoir si le premier est sur le segment des deux autres points, plus proche du deuxième point ou plus proche du troisième*/
int coteAlignement(const Vector2D& p, const Vector2D& extrem0, const Vector2D& extrem1)
{
    if(dot(p-extrem0, p-extrem1) <= 0)  //le point est entre extrem0 et extrem1
        return 0;
    else if(dot(p-extrem0, extrem1-extrem0) < 0)
        return -1;   //plus proche de extrem0
    else
        return 1;   //plus proche de extrem1
}

bool Convexe2D::findIndicesCoupe(const Vector2D& p, int& deb, int& fin)
{
    //if(p.x == 0.5)
    //    deb = -1;
    int i = 0, i2 = (i+1)%getNbPoints();
    int cote = inHalfSpaceDroit(_points[i], _points[i2], p);
    bool startOut;   //indique si le segment 0<->1 n'est pas compris dans la zone à couper.

    if(cote == ALIGNEE){
        int cote2 = coteAlignement(p, _points[i], _points[i2]);
        if(cote2 == 0)
            return false;  //le point à ajouter est sur l'enveloppe convexe. Il n'y a pas à l'ajouter à l'enveloppe.
        else if(cote2 == -1)
            startOut = false;
        else
            startOut = true;
    }
    else if(cote == GAUCHE)
        startOut = true;
    else    //droit
        startOut = false;


    if(startOut)    {
        if(cote == ALIGNEE)
            deb = 0;
        else    {
            for(i = 1;  i < getNbPoints();  i++)
            {
                i2 = (i+1)%getNbPoints();
                int cote1 = inHalfSpaceDroit(_points[i], _points[i2], p);
                if(cote1 == ALIGNEE){
                    if(coteAlignement(p, _points[i], _points[i2]) == 0)         return false;  //le point à ajouter est sur l'enveloppe convexe. Il n'y a pas à l'ajouter à l'enveloppe.
                    else                                                        break;  //on commence la coupe au point i
                }
                else if(cote1 == DROIT)
                    break;  //on conmmence la coupe au point i
            }
            if(i == getNbPoints())
                return false;  //le points est à l'interieur de l'enveloppe
            deb = i;
        }

        for(i = deb+1;  i < getNbPoints();  i++)
        {
            i2 = (i+1)%getNbPoints();
            cote = inHalfSpaceDroit(_points[i], _points[i2], p);
            if(cote == ALIGNEE){
                if(coteAlignement(p, _points[i], _points[i2]) == 0)
                    return false;  //le point à ajouter est sur l'enveloppe convexe. Il n'y a pas à l'ajouter à l'enveloppe.
                else{
                    i++;    break;  //on termine la coupe au point i
                }
            }
            else if(cote == GAUCHE)
                break;  //on termine la coupe au point i
        }
        fin = (i == getNbPoints()   ?   0   :   i);
    }
    else
    {
        for(i = getNbPoints()-1;  i > 1;  i--)
        {
            i2 = (i+1)%getNbPoints();
            cote = inHalfSpaceDroit(_points[i], _points[i2], p);
            if(cote == ALIGNEE){
                if(coteAlignement(p, _points[i], _points[i2]) == 0)         return false;  //le point à ajouter est sur l'enveloppe convexe. Il n'y a pas à l'ajouter à l'enveloppe.
                else    {
                    i--;    break;  //on commence la coupe au point i2
                }
            }
            else if(cote == GAUCHE)
                break;  //on conmmence la coupe au point i2
        }
        deb = (i+1)%getNbPoints();

        for(i = 1;  i < getNbPoints()-1;  i++)
        {
            i2 = (i+1)%getNbPoints();
            cote = inHalfSpaceDroit(_points[i], _points[i2], p);
            if(cote == ALIGNEE){
                if(coteAlignement(p, _points[i], _points[i2]) == 0)
                    return false;  //le point à ajouter est sur l'enveloppe convexe. Il n'y a pas à l'ajouter à l'enveloppe.
                else{
                    i++;    break;  //on termine la coupe au point i
                }
            }
            else if(cote == GAUCHE)
                break;  //on termine la coupe au point i
        }
        fin = i;
    }
    return true;
}



int inHalfSpaceDroit(const Vector2D& extrem0, const Vector2D& extrem1, const Vector2D& p)
{
    //float val = (a->Y - b->Y) * (c->X - a->X) + (b->X - a->X) * (c->Y - a->Y);
    Vector2D orthoDir = (extrem1 - extrem0).crossProduct();

    float val = (p-extrem0).dotProduct(orthoDir);
    if( val < 0 )
        return DROIT;
    else if(val == 0)   //si aligné
        return ALIGNEE;

    return GAUCHE;  //==0
}



Convexe2D Convexe2D::operator+(const Convexe2D& convexe) const
{
    QVector<Vector2D> pointsAdd;
    for(const Vector2D& p1 : this->_points)
        for(const Vector2D& p2 : convexe._points)
            pointsAdd.push_back(p1+p2);

    return Convexe2D(pointsAdd);
}

Convexe2D Convexe2D::operator*(float scale) const
{
    Convexe2D res(*this);
    res.scale(scale);
    return res;
}

void Convexe2D::scale(float s)
{
    for(Vector2D& p: this->_points)
        p *= s;
    if(s >= 0)  {
        _min *= s;
        _max *= s;
    }
    else    {
        std::reverse(_points.begin(), _points.end());
        _min = _max*s;
        _max = _min*s;
    }
    _centre *= s;

}
