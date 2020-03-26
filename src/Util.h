#ifndef __UTIL_H__
#define __UTIL_H__

#include "Vector4.h"

typedef Vector4 Point;

Point intersection2D(Point p1, Point p2, Point p3, Point p4)
{
    return Point(
        ((p1.getX()*p2.getY() - p1.getY()*p2.getX()) * (p3.getX() - p4.getX()) 
        - (p1.getX() - p2.getX()) * (p3.getX()*p4.getY() - p3.getY()*p4.getX())) /
        ((p1.getX() - p2.getX()) * (p3.getY() - p4.getY()) 
        - (p1.getY() - p2.getY()) * (p3.getX() - p4.getX())),

        ((p1.getX()*p2.getY() - p1.getY()*p2.getX()) * (p3.getY() - p4.getY()) 
        - (p1.getY() - p2.getY()) * (p3.getX()*p4.getY() - p3.getY()*p4.getX())) /
        ((p1.getX() - p2.getX()) * (p3.getY() - p4.getY()) 
        - (p1.getY() - p2.getY()) * (p3.getX() - p4.getX())),

        0.0f, 0.0f
    );
}

#endif // !__UTIL_H__