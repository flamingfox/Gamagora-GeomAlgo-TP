#include "unionconvex.h"

UnionConvex::UnionConvex()
{
}



void UnionConvex::add(const Convexe2D& c)
{
    convexs.push_back(c);
}


UnionConvex Morph(const UnionConvex& conv1, const UnionConvex& conv2, float t)
{
    UnionConvex res();
    if(conv1.convexs.size() != conv2.convexs.size())
        return res;


    for(int iconv = 0;  iconv < conv1.convexs.size();   iconv++)
    {
        Convexe2D c1 = conv1[iconv]*(1-t);
        Convexe2D c2 = conv2[iconv]*t;

        Convexe2D c = c1 + c2;
        res.convexs.push_back(c);
    }
    return res;
}
