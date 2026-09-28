#include <iostream>
#include <array>
#include "Image_Class.h"
using namespace std;

int main() {
    Image image("Habetik.jpg");
    for (int i = 0; i < image.width; i++) {
        for (int j = 0; j < image.height; j++) {
            for (int k = 0; k < 3; k++) {
                image(i, j, k) = 255 - image(i, j, k);
            }
        }
    }

    image.saveImage("Habetik_inverted.jpg");
    return 0;
}
