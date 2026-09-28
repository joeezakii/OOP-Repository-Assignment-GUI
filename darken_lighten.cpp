#include<iostream>
#include "Image_Class.h"

using namespace std;

int main() {
    cout<<"Do you want to darken or lighten the image? (Enter darken or lighten):";
    string c;
    cin >> c;
    if (c=="darken") {
        cout<<"Enter the darkening percent (0 to 100%):";
        int p;
        cin >> p;
       
        if (p < 0 || p > 100) {
            cout<<"Invalid input"<<endl;
            return 0;
        }
        else{
            
            Image image("Habetik.jpg");
            for (int i = 0; i < image.width; i++) {
                for (int j = 0; j < image.height; j++) {
                    for (int k = 0; k < 3; k++) {
                        image(i, j, k) = image(i, j, k)*(1 - p / 100.0);
                    }
                }
            }
            image.saveImage("Habetik_darkened.jpg");
        }
    }
    else if (c=="lighten") {
        cout<<"Enter the lightening percent (0 to 100%):";
        int p;
        cin >> p;

       
        if (p < 0 || p > 100) {
            cout<<"Invalid input."<<endl;
            return 0;
        }
        else{
            
            Image image("Habetik.jpg");
            for (int i = 0; i < image.width; i++) {
                for (int j = 0; j < image.height; j++) {
                    for (int k = 0; k < 3; k++) {
                       image(i, j, k) = image(i, j, k) + (255 - image(i, j, k))*(p / 100.0);
                        if(image(i, j, k)>255){
                            image(i, j, k) =255;
                        }
                    }
                }
            }
            image.saveImage("Habetik_lightened.jpg");
        }
    }
    
    return 0;
}
