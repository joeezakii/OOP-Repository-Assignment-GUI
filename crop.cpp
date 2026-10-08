#include <iostream>
#include <string>
#include <array>
#include "Image_Class.h"
using namespace std;

int main(){
    Image image("Habetik.jpg");
   int w,x,y,z; 
    
    cout<<"Insert starting point for width and height"<<endl;
    cin>>w>>x;
    cout<<"Insert crop width and height desired"<<endl;
    cin>>y>>z;
    if (w<0 || x<0 || y<0 || z<0 || w>image.width || x>image.height || w+y>image.width || x+z>image.height){
        cout<<"Invalid crop dimensions"<<endl;
        return 1;
    }
        Image crop(y,z);
        
    for(int i=0; i<y; i++){
        for(int j=0; j<z; j++){
            for(int k=0; k<3; k++){
                crop(i,j,k)=image(w+i,x+j,k);
            }
        }
    }
    crop.saveImage("Habetik_cropped.jpg");
    cout<<"your cropped image is ready"<<endl;
    


}