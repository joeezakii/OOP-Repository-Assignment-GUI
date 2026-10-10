#include <iostream>
#include <string>
#include "Image_Class.h"

using namespace std;

int main() {

    Image image("Habetik.jpg");
    Image original("Habetik.jpg");
    for (int y = 0; y < image.height; ++y) {
        for (int x = 0; x < image.width; ++x) {
            int r = 0, g = 0, b = 0;
            int count = 0;

            for (int i = -2; i <= 2; ++i) {
                for (int j = -2; j <= 2; ++j) {
                    int w = x + j;
                    int z = y + i;

                    if (w < 0 || w >= image.width || z < 0 || z >= image.height) {
                        continue;
                    }

                    r += original.getPixel(w, z, 0);
                    g += original.getPixel(w, z, 1);
                    b += original.getPixel(w, z, 2);
                    ++count;
                }
            }

            int ar = r / count ;
            int ag = g / count ;
            int ab = b / count ;          
            
            image.setPixel(x, y, 0, ar);
            image.setPixel(x, y, 1, ag);
            image.setPixel(x, y, 2, ab);
        }
    }

    image.saveImage("habetik_oil_painting.jpg");
    return 0;
}

