#ifndef GPS_ALGEBRA_H
#define GPS_ALGEBRA_H

#include <cmath>
#include <iostream>
#include <iomanip>

class Point3 {
private:
    double x;
    double y;
    double z;
public:
    Point3() = default;

    Point3(double _x, double _y, double _z) : x(_x), y(_y), z(_z) {};

    double getLargeNorm() const;

    double getNorm() const;

    double getX() const { return x; }

    double getY() const { return y; }

    double getZ() const { return z; }

    void print() const;

    Point3 &operator=(const Point3 &p1);
};

Point3 operator+(const Point3 &p1, const Point3 &p2);

Point3 operator-(const Point3 &p1);

Point3 operator-(const Point3 &p1, const Point3 &p2);

bool operator==(const Point3 &lhs, const Point3 &rhs);


class Vector {
    double x;
    double y;
    double z;

public:
    Vector(double x = 0, double y = 0, double z = 0) : x(x), y(y), z(z) {};

    Vector(const Point3 begin, const Point3 end) {
        x = end.getX() - begin.getX();
        y = end.getY() - begin.getY();
        z = end.getZ() - begin.getZ();
    }

    double getX() const { return x; }

    double getY() const { return y; }

    double getZ() const { return z; }

    double getLength() const { return sqrt(x * x + y * y + z * z); }

    void setLength(double length);

    Vector &operator=(const Vector &v) = default;

    Point3 movePoint(const Point3 &p) const;

    Vector add(const Vector &v) const;

    Vector extend(double m) const;

    Vector cross(const Vector &v) const;

    Vector versor() const;

    Vector perpendicular(Point3 &pOnLine, Point3 &direction) const;

    double dot(const Vector &v) const;
};

class Plane {
private:
    Vector vector;
    Point3 point;
public:
    explicit Plane(Vector normalVector = Vector(), Point3 p0 = Point3()) : vector(normalVector), point(p0) {}

    Point3 intersection(Vector v, Point3 p) const {
        double t = -(vector.getX() * (p.getX() - point.getX()) + vector.getY() * (p.getY() - point.getY()) +
                     vector.getZ() * (p.getZ() - point.getZ())) /
                   (v.getX() * vector.getX() + v.getY() * vector.getY() + v.getZ() * vector.getZ());
        // std::cout << "intersection t = " << t << std::endl;
        // std::cout << "X -> " << v.getX() << " Y -> " << v.getY() << " Z -> " << v.getZ() <<std::endl;
        Point3 result = Point3(
                p.getX() + t * v.getX(),
                p.getY() + t * v.getY(),
                p.getZ() + t * v.getZ()
        );
        // std::cout << "LENGTH: " << sqrt((p - result).getLargeNorm()) << std::endl;

        return result;
    }

};


#endif //GPS_ALGEBRA_H
