/***
 * Author: Sriharsha Gangam
 * ------------------------
  Contains classes for basic 2D figutres, shapes ond oints from the cartesian geometry.
 * */

#include<iostream>
#include<queue>
#include<stack>
#include<cassert>
#include<cmath>

/**
 * A Class representing 2 Dimenstional point represented by cartesian coordinates x and y.
 */
class Point {
    int x, y;
    public:
        int getx () const {
            return x; 
        }
        int gety () const {
            return y; 
        }
        Point(){ 
            this->x = 0;
            this->y = 0;
        }
        Point(const Point & p){ 
            this->x = p.x;
            this->y = p.y;
        }
        Point(int x, int y){ 
            this->x = x;
            this->y = y;
        }
};

/**
 * A Class representing 2 Dimenstional vector represented by the tuple x, y
 */

class Vector2D {
    int x, y;
    public:
        Vector2D(int x, int y){ 
            this->x = x;
            this->y = y;
        }
        Vector2D (const Point & p) { 
            this->x = p.getx(); 
            this->y = p.gety(); 
        }
        Vector2D (const Vector2D & v) { 
            this->x = v.x;
            this->y = v.y;
        }
        //Vector from point p1 to p2 = Vector(p2) - Vector(p1)
        Vector2D (const Point & p1, const Point & p2) {
            this->x = p2.getx() - p1.getx();
            this->y = p2.gety() - p1.gety();
        }
        Vector2D operator-(const Vector2D & v) const {
            return Vector2D(x - v.x, y - v.y);
        }
        Vector2D operator+(const Vector2D & v) const {
            return Vector2D(x + v.x, y + v.y);
        }
        int dotProduct(const Vector2D & v) const {
            return x*v.x + y*v.y;
        }
};

/**
 * A Class representing a rectangled given as 4 points given by p1, p2, p3 and p4.
 */

class Rectangle {
    Point p1, p2, p3, p4;
    public:
    Rectangle (const Point & p1, const Point & p2, const Point & p3, const Point & p4) {
        this->p1 = p1; this->p2 = p2; this->p3 = p3; this->p4 = p4;
    }

    /**
     * @param p: Does the point p lie inside the this rectangle?
     */
    bool isInside (const Point & p) {
        int proj1 = Vector2D(p1, p).dotProduct(Vector2D(p1, p4));
        int len1 = Vector2D(p1, p4).dotProduct(Vector2D(p1, p4));
        int proj2 = Vector2D(p1, p).dotProduct(Vector2D(p1, p2));
        int len2 = Vector2D(p1, p2).dotProduct(Vector2D(p1, p2));
        //std::cout << proj1 << " " << len1 <<  " " << proj1 << " " << len1 << std::endl;
        return (proj1 > 0 && proj1 < len1 && proj2 > 0 && proj2 < len2);
    }

};

/**
 * A Class representing a circle given by the radius and centera.
 */

class Circle {
    unsigned int r; 
    Point center;
    public:
        Circle (unsigned int r, const Point & center){
            this->center = center;
            this->r = r;
        }
};

void testInsideRectangle () {
    Point p1(1,1);
    Point p2(10,1);
    Point p3(10,10);
    Point p4(1,10);
    Rectangle r(p1, p2, p3, p4);
    assert(r.isInside(Point(2,2)));
    assert(r.isInside(Point(4,5)));
    assert(not r.isInside(Point(0, 10)));
    assert(not r.isInside(Point(1, 10)));
    assert(not r.isInside(Point(4, -2)));
}

int main(int argc, char *argv[]) {
    testInsideRectangle();
    return 0;
}
