#ifndef GPS_MATRIX_H
#define GPS_MATRIX_H

#include <iostream>
#include <cstdlib>
#include <cmath>
#include "algebra.h"
#include "config.h"

class matrix {
private:
    int width{};
    int height{};
    double **array{};

public:
    explicit matrix(int height = 1, int width = 1);

    matrix(const matrix &m);

    ~matrix() { this->deleteArray(); };

    int getWidth() const { return width; }

    int getHeight() const { return height; }

    double getElement(int h, int w) const { return array[h][w]; }

    void setElement(int h, int w, double value) { array[h][w] = value; }

    void deleteArray();

    void print() const;

    matrix &operator=(const matrix &m);

    matrix &operator*=(const matrix &m2);
};


class rotationMatrix {
private:
    matrix m;
public:
    rotationMatrix() { m = matrix(3, 3); }

    explicit rotationMatrix(const matrix& _m) : m(_m) {};

    rotationMatrix(double latitude, double longitude);

    rotationMatrix(double roll, double pitch, double yaw);

    Vector indicator() const;

    void print() { m.print(); }

    rotationMatrix &operator=(const rotationMatrix &rm);

    rotationMatrix &operator*=(const rotationMatrix &rm);
};

#endif //GPS_MATRIX_H