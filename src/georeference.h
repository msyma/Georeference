#ifndef GPS_GEOREFERENCE_H
#define GPS_GEOREFERENCE_H

#include <cmath>
#include "algebra.h"
#include "matrix.h"
#include "config.h"

class georeference {
private:
    rotationMatrix nedRot;
    rotationMatrix uavRot;
    rotationMatrix pixRot;
    rotationMatrix actRot;
    Point3 localization{};
    Plane ground;

    double cameraTilt{0};
    double groundHeight{0};
    double uavHeight{0};
    int xPixel{0};
    int yPixel{0};

public:
    explicit georeference();

    void calculateLocalization(double latitude, double longitude, double height);

    void recalculate();

    void setGroundHeight(double height);

    void setCameraTilt(double tilt);

    void setGpsData(double latitude, double longitude, double height);

    void setGyroData(double roll, double pitch, double yaw);

    void setPixelData(int x, int y);

    Point3 getTarget() const { return ground.intersection(actRot.indicator(), localization); }

    void print() { actRot.print(); }
};

double latitude(Point3 localization);

// Y latitude X longitude Z height
Point3 EcefToLlh(Point3 localization);


#endif //GPS_GEOREFERENCE_H