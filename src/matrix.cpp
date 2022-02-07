#include "matrix.h"

matrix::matrix(int height, int width) : width(width), height(height) {
    array = new double *[height];
    for (int h = 0; h < height; h++) {
        array[h] = new double[width];
    }
}

matrix::matrix(const matrix &m) {
    *this = matrix(m.height, m.width);
    for (int h = 0; h < height; h++) {
        for (int w = 0; w < width; w++) {
            array[h][w] = m.array[h][w];
        }
    }
}

void matrix::deleteArray() {
    for (int h = 0; h < height; h++) {
        delete[] array[h];
    }
    delete[] array;
}

matrix &matrix::operator=(const matrix &m) {
    if (this == &m) { return *this; }
    // deleteArray();

    height = m.getHeight();
    width = m.getWidth();
    array = new double *[height];
    for (int h = 0; h < height; h++) {
        array[h] = new double[width];
        for (int w = 0; w < width; w++) {
            array[h][w] = m.array[h][w];
        }
    }
    return *this;
}

matrix &matrix::operator*=(const matrix &m2) {
    matrix m1;
    m1 = *this;
    deleteArray();
    *this = matrix(m1.height, m2.width);

    double value;
    for (int x = 0; x < height; x++) {
        for (int y = 0; y < width; y++) {
            value = 0;
            for (int i = 0; i < m1.getWidth(); i++) {
                value += m1.getElement(x, i) * m2.getElement(i, y);
            }
            setElement(x, y, value);
        }
    }
    return *this;
}

void matrix::print() const {
    std::cout << "Matrix size: " << getHeight() << ", " << getWidth() << std::endl;
    for (int h = 0; h < height; h++) {
        std::cout << "[";
        for (int w = 0; w < width; w++) {
            std::cout << getElement(h, w) << ", ";
        }
        std::cout << "]" << std::endl;
    }
    std::cout << std::endl;
}

rotationMatrix::rotationMatrix(double latitude, double longitude) {
    m = matrix(3, 3);

    m.setElement(0, 0, -sin(latitude * RADIAN) * cos(longitude * RADIAN));
    m.setElement(0, 1, -sin(longitude * RADIAN));
    m.setElement(0, 2, -cos(latitude * RADIAN) * cos(longitude * RADIAN));

    m.setElement(1, 0, -sin(latitude * RADIAN) * sin(longitude * RADIAN));
    m.setElement(1, 1, cos(longitude * RADIAN));
    m.setElement(1, 2, -cos(latitude * RADIAN) * sin(longitude * RADIAN));

    m.setElement(2, 0, cos(latitude * RADIAN));
    m.setElement(2, 1, 0);
    m.setElement(2, 2, -sin(latitude * RADIAN));
}

rotationMatrix::rotationMatrix(double roll, double pitch, double yaw) {
    m = matrix(3, 3);

    m.setElement(0, 0, cos(yaw * RADIAN) * cos(pitch * RADIAN));
    m.setElement(0, 1,
                 cos(yaw * RADIAN) * sin(pitch * RADIAN) * sin(roll * RADIAN) - sin(yaw * RADIAN) * cos(roll * RADIAN));
    m.setElement(0, 2,
                 cos(yaw * RADIAN) * sin(pitch * RADIAN) * cos(roll * RADIAN) + sin(yaw * RADIAN) * sin(roll * RADIAN));

    m.setElement(1, 0, sin(yaw * RADIAN) * cos(pitch * RADIAN));
    m.setElement(1, 1,
                 sin(yaw * RADIAN) * sin(pitch * RADIAN) * sin(roll * RADIAN) + cos(yaw * RADIAN) * cos(roll * RADIAN));
    m.setElement(1, 2,
                 sin(yaw * RADIAN) * sin(pitch * RADIAN) * cos(roll * RADIAN) - cos(yaw * RADIAN) * sin(roll * RADIAN));

    m.setElement(2, 0, -sin(pitch * RADIAN));
    m.setElement(2, 1, cos(pitch * RADIAN) * sin(roll * RADIAN));
    m.setElement(2, 2, cos(pitch * RADIAN) * cos(roll * RADIAN));
}

Vector rotationMatrix::indicator() const {
    matrix col = matrix(3, 1);
    col.setElement(0, 0, 1);
    col.setElement(1, 0, 0);
    col.setElement(2, 0, 0);
    // matrix matrixIndicator = m * col;
    matrix matrixIndicator = m;
    matrixIndicator *= col;
    return Vector(
            matrixIndicator.getElement(0, 0),
            matrixIndicator.getElement(1, 0),
            matrixIndicator.getElement(2, 0));
}

rotationMatrix &rotationMatrix::operator=(const rotationMatrix &rm) {
    m = rm.m;
    return *this;
}

rotationMatrix &rotationMatrix::operator*=(const rotationMatrix &rm) {
    m = (m *= rm.m);
    return *this;
}
