#include "Image_Class.h"
#include <iostream>
#include <iomanip>
#include <string>
using namespace std;
int main() 
{
bool flag = true;
int option_no;
string s,choice;
cout << "Which photo would you like to do the changes in, make sure you chose the image with the right filename and extension." << endl;
getline(cin, s);
Image image_name(s);
while(flag) 
{
cout << "Which option would you like to do?" << "\n";
cin >> option_no;
switch(option_no) 
{
case 1: 
//

break;
case 2: {
int x,y;
string namefile_user;
Image image_after = image_name;
for(int y = 0; y < image_after.height; ++y){
for(int x = 0; x < image_after.width; ++x){
unsigned int red_colour = image_name.getPixel(x,y,0);
unsigned int green_colour = image_name.getPixel(x,y,1);
unsigned int blue_colour= image_name.getPixel(x,y,2);
unsigned int gray_value = int((red_colour*0.2126)+(green_colour*0.7152)+(blue_colour*0.0722));
//such that 4th parameter of set_pixel is the value of gray colour
image_after.setPixel(x,y,0,gray_value);
image_after.setPixel(x,y,1,gray_value);
image_after.setPixel(x,y,2,gray_value);
}
}
cout << "How would you like to name the image alongside the extension?"<< "\n";
cin.ignore();
getline(cin,namefile_user);
image_after.saveImage(namefile_user);
break;
}
case 3: 
//
break;
case 4: 
//
break;
case 5: 
//
break;
case 6: 
//
break;
case 7: 
//
break;
case 8: 
//
break;
default:
cout << "Error in the query choice number you have entered, please try again";
}
cout << "Would you like to continue, type in Yes if you want to continue to do more changes and 'No' if you want to end the program";  
cin >> choice;
if(choice == "no" || choice == "No" || choice == "nO") {
    flag = false;
    break;
}
}
return 0;
}