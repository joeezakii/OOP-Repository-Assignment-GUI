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
cout <<"1: Grayscale" << "\n" << "2: Black and White" << "\n" << "3: Inverted Image" << "\n" <<"4: Adding a frame onto a picture"<< "\n" << "5: Flip an Image (Horizontally/Vertically)" << "\n" << "6: Rotate an Image" << "\n" << "7: Darken/Lighten Image" << "\n" << "8: Resize an Image" <<"\n";
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
{
string namefile_user;
Image image_after = image_name;
  for (int i = 0; i < image_after.width; i++) {
        for (int j = 0; j < image_after.height; j++) {
            for (int k = 0; k < 3; k++) {
                image_after(i, j, k) = 255 - image_after(i, j, k);
            }
        }
    }
cout << "How would you like to name the image alongside the extension?"<< "\n";
cin.ignore();
getline(cin,namefile_user);
image_after.saveImage(namefile_user);
break;
}
case 4: 
//
break;
case 5: 
//
break;
case 6:
{
string namefile_user;
int query;
double original_centrex = (image_name.width-1)/2.0; 
double original_centrey = (image_name.height-1)/2.0;
cout << "Press '1' if you would like to rotate 90 degrees clockwise/270 degrees anticlockwise"<< "\n";
cout << "Press '2' if you would like to rotate 180 degrees clockwise/anticlockwise" << "\n";
cout << "Press '3' if you would like to rotate 270 degrees clockwise/90 degrees anticlockwise"<< "\n";
cout << "Press '4' if you want no changes"<< "\n";
cin >> query;
int target_w = (query == 1 || query == 3) ? image_name.height : image_name.width; //if you rotate 90 degrees or 270 degrees, the dimensions will change
int target_h = (query == 1 || query == 3) ? image_name.width : image_name.height;
Image image_after(target_w, target_h);
double target_centrex = (image_after.width - 1) / 2.0;
double target_centrey = (image_after.height - 1) / 2.0;
for(auto y = 0; y < image_after.height; ++y) {
    for(auto x = 0; x < image_after.width; ++x) {
        double halal_cheating_ofx = x - target_centrex;
        double halal_cheating_ofy = y - target_centrey;
        double spun_x = 0;
        double spun_y = 0;

        // rotating section
        if(query == 1) {
            spun_x = -halal_cheating_ofy;
            spun_y = halal_cheating_ofx;
        }
        else if(query == 2) {
            spun_x = -halal_cheating_ofx;
            spun_y = -halal_cheating_ofy;
        }
        else if(query == 3) {
            spun_x = halal_cheating_ofy;
            spun_y = -halal_cheating_ofx;
        }
        else {
            spun_x = halal_cheating_ofx;
            spun_y = halal_cheating_ofy; 
        }
        int source_x = int(spun_x + original_centrex + 0.5);
        int source_y = int(spun_y + original_centrey + 0.5);




       
        if (source_x >= 0 && source_x < image_name.width && source_y >= 0 && source_y < image_name.height) {
    image_after.setPixel(x, y, 0, image_name.getPixel(source_x, source_y, 0)); // Assign validated value to red
    image_after.setPixel(x, y, 1, image_name.getPixel(source_x, source_y, 1)); // Assign validated value to green
    image_after.setPixel(x, y, 2, image_name.getPixel(source_x, source_y, 2)); // Assign validated value to blue
}
}
}
cout << "How would you like to name the image alongside the extension?"<< "\n";
cin >> ws; // what this basically is like when you input the filename, you might put a space or two, this wont count as an input. ws = whitespace
getline(cin,namefile_user);
image_after.saveImage(namefile_user);
break;
}
case 7: 
//
break;
case 8: 
//
break;
default:
cout << "Error in the query choice number you have entered, please try again";
}
cout << "Would you like to continue, type in Yes if you want to continue to do more changes or 'No' if you want to end the program" << "\n";  
cin >> choice;
if(choice == "no" || choice == "No" || choice == "nO") {
    flag = false;
    break;
    return 0;
}
}
return 0;
}