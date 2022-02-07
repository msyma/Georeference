#include <iostream>
#include "georeference.h"


georeference geo = georeference();

int main() {
    std::cout << "Hello, Target!" << std::endl;
    geo.setCameraTilt(-20);
    geo.setGroundHeight(330);

    {  // actual
        geo.setGpsData(51.282233, 19.549107, 335);
        geo.setGyroData(0, 0, 45);
        geo.setPixelData(1640 + (0), 1232 - (-400)); // middle

        Point3 target = geo.getTarget();
        target.print();
        EcefToLlh(target).print();
    }
    return 0;
}
