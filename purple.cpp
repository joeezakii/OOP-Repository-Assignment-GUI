#include <iostream>
#include <string>
#include <array>
#include "Image_Class.h"
using namespace std;

int main() {
    Image image("Habetik.jpg");
    for (int i = 0; i<image.width; i++) {
        for (int j =0; j<image.height; j++) {
            image(i,j,0) = (image(i,j,0)+128)/2;
            image(i,j,1)= (image(i,j,1)+0)/2;
            image(i,j,2) = (image(i,j,2)+128)/2;

                }
      
 }
  image.saveImage("Habetik_purple.jpg");

return 0;

}