#include "georeference.h"

georeference::georeference() {
    nedRot = rotationMatrix(0, 0);
    uavRot = rotationMatrix(0, 0, 0);
    pixRot = rotationMatrix(0, 0, 0);
    recalculate();
}

void georeference::recalculate() {
    // actRot = nedRot * uavRot * pixRot;
    rotationMatrix copy = nedRot;
    actRot = ((copy *= uavRot) *= pixRot);
}

void georeference::setGroundHeight(double height) {
    groundHeight = height;
}

void georeference::setCameraTilt(double tilt) {
    cameraTilt = tilt;
    setPixelData(xPixel, yPixel);
}

void georeference::setGpsData(double latitude, double longitude, double height) {
    uavHeight = height;
    nedRot = rotationMatrix(latitude, longitude);
    recalculate();
    calculateLocalization(latitude, longitude, height);
}

void georeference::setGyroData(double roll, double pitch, double yaw) {
    uavRot = rotationMatrix(roll, pitch, yaw);
    recalculate();
}

void georeference::setPixelData(int x, int y) {
    xPixel = x;
    yPixel = y;
    double procX = (x - (PIXEL_MAX_X - 1) / 2.0) * VIEW_ANGLE_X / PIXEL_MAX_X;
    double procY = ((PIXEL_MAX_Y - 1) / 2.0 - y) * VIEW_ANGLE_Y / PIXEL_MAX_Y;
    pixRot = rotationMatrix(0, procY + cameraTilt, procX);
    recalculate();
}

void georeference::calculateLocalization(double latitude, double longitude, double height) {
    double N = (double) SEMI_MAJOR_EARTH_AXIS /
               pow(1 - EPOW2 * pow(sin(latitude * RADIAN), 2), 0.5);
    localization = Point3((N + height) * cos(latitude * RADIAN) * cos(longitude * RADIAN),
                          (N + height) * cos(latitude * RADIAN) * sin(longitude * RADIAN),
                          (N * (1 - EPOW2) + height) * sin(latitude * RADIAN));
    Point3 groundLocalization = Point3((N + groundHeight) * cos(latitude * RADIAN) * cos(longitude * RADIAN),
                                       (N + groundHeight) * cos(latitude * RADIAN) * sin(longitude * RADIAN),
                                       (N * (1 - EPOW2) + groundHeight) * sin(latitude * RADIAN));
    Vector vec = Vector(Point3(0, 0, 0), localization);
    ground = Plane(vec, groundLocalization);
}

static double longitude(Point3 localization) {
    return (atan2(localization.getY(), localization.getX())) * DEGREE;
}

double latitude(Point3 localization) {
    double p = sqrt(pow(localization.getY(), 2) + pow(localization.getX(), 2));
    double th = atan2(SEMI_MAJOR_EARTH_AXIS * localization.getZ(), SEMI_MINOR_EARTH_AXIS * p);
    return (atan2(localization.getZ() + pow(EP, 2) * SEMI_MINOR_EARTH_AXIS * pow(sin(th), 3),
                  p - EPOW2 * SEMI_MAJOR_EARTH_AXIS * pow(cos(th), 3))) * DEGREE;
}

static double height(Point3 localization) {
    double p = sqrt(pow(localization.getY(), 2) + pow(localization.getX(), 2));
    double N = SEMI_MAJOR_EARTH_AXIS / sqrt(1 - EPOW2 * pow(sin(latitude(localization) * RADIAN), 2));
    return p / cos(latitude(localization) * RADIAN) - N;
}

Point3 EcefToLlh(Point3 localization) {
    return Point3(latitude(localization), longitude(localization), height(localization));
}