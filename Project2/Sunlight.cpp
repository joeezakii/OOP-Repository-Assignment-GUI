#include <iostream>
#include <string>
#include <cstring>
#include "Image_Class.h"
using namespace std;
//pixel has values of 0-255 for each channel this limits the values 
int limit(int value) {
    if (value > 255) return 255;
    if (value < 0) return 0;
    return value;
}
//this applies the sunlight effect to each pixel
void sunlight(Image& img) {
    for (int x = 0; x < img.width; x++) {
        for (int y = 0; y < img.height; y++) {
            int r = img(x, y, 0) * 1.15 + 15;
            int g = img(x, y, 1) * 1.08 + 15;
            int b = img(x, y, 2) * 0.85 + 15;

            img(x, y, 0) = limit(r);
            img(x, y, 1) = limit(g);
            img(x, y, 2) = limit(b);
        }
    }
}
//saves the image after applying the filter/effect
int main() {
    
        Image original("Dog.jpg");
        Image result = original;

        sunlight(result);

        result.saveImage("applied_sunlight.jpg");
    
       return 0;
}
//Voila!!!