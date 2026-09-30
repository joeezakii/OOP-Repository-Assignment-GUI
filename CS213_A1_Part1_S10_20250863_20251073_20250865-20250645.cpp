#include "Image_Class.h"
#include <iostream>
#include <iomanip>
#include <string>
/* 1. Youssef Khaled Hussein 20250863 (The one who'll submit the assignment 1 part 1) 
Filters: 2,6
2. Bassam Islam Gomaa 20251073 
Filters 4,8
3. Ahmed Bassam Abdelfatah 20250865
Filters 3,7
4. Mostafa Mahmoud Abdella 20250645
Filters 1,5 */
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
cin >> ws;
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
cin >> ws;
getline(cin,namefile_user);
image_after.saveImage(namefile_user);
break;
}
case 4: 
{
string namefile_user;
Image image_after = image_name;
int choice, padding = 0, r = 0, g = 0, b = 0;
        do {
            cout << "Enter padding size in pixels (e.g. 500): ";
            cin >> padding;
        } while (padding < 0);
        
    padding = padding * 2;
        do {
            cout << "Select border color:\n1. Red\n2. Green\n3. Blue\n4. Custom RGB\nEnter choice (1-4): ";
            cin >> choice;
        }
        while (choice < 1 || choice > 4);

    switch (choice) {
        case 1: r = 255; break;
        case 2: g = 255; break;
        case 3: b = 255; break;
        case 4:
            do {
                cout << "Enter R G B (0-255): ";
                cin >> r >> g >> b;
            }
            while (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255);
            break;
        default:
            r = g = b = 255;
            break;
    }

    Image frame(image_after.width + padding, image_after.height + padding) ;

        for (int i = 0; i < frame.width; i++) {
            for (int j = 0; j < frame.height; j++) {
                frame(i, j, 0) = r;
                frame(i, j, 1) = g;
                frame(i, j, 2) = b;
            }
        }
        for (int i = 0; i < image_after.width; i++) {
            for (int j = 0; j < image_after.height; j++) {
                for (int k = 0; k < image_after.channels; k++) {
                    frame(i + padding/2, j + padding/2, k) = image_after(i, j, k);
                }
            }
        }
    cout << "How would you like to name the image alongside the extension?"<< "\n";
cin >> ws;
getline(cin,namefile_user);
image_after.saveImage(namefile_user);
break;
}
case 5: {

}
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
{
string namefile_user;
Image image_after = image_name;
cout<< "Do you want to darken or lighten the image? (Enter darken/Darken or lighten/Lighten):";
string c;
cin >> c;
if (c == "darken" || c == "Darken") {
        cout<<"Enter the darkening percent (0 to 100%):";
        int p;
        cin >> p;
        while(p < 0 || p > 100) {
            cout<<"Invalid input, please try entering the percentage again from 0%-100%"<<endl;
            cin >> p;
        }
         for (int i = 0; i < image_after.width; i++) {
                for (int j = 0; j < image_after.height; j++) {
                    for (int k = 0; k < 3; k++) {
                        image_after(i, j, k) = image_after(i, j, k)*(1 - p / 100.0);
                    }
                }
        }
        cout << "How would you like to name the image alongside the extension?"<< "\n";
        cin >> ws; // what this basically is like when you input the filename, you might put a space or two, this wont count as an input. ws = whitespace
        getline(cin,namefile_user);
        image_after.saveImage(namefile_user);
        break;
    }
    else if (c == "lighten" || c == "Lighten") {
        cout<<"Enter the lightening percent (0 to 100%):";
        int p;
        cin >> p;
    while(p < 0 || p > 100) {
            cout<<"Invalid input, please try entering the percentage again from 0%-100%"<<endl;
            cin >> p;
        }
       for (int i = 0; i < image_after.width; i++) {
                for (int j = 0; j < image_after.height; j++) {
                    for (int k = 0; k < 3; k++) {
                       image_after(i, j, k) = image_after(i, j, k) + (255 - image_after(i, j, k))*(p / 100.0);
                        if(image_after(i, j, k)>255){
                            image_after(i, j, k) = 255;
                        }
                    }
                }
            }
        cout << "How would you like to name the image alongside the extension?"<< "\n";
        cin >> ws; // what this basically is like when you input the filename, you might put a space or two, this wont count as an input. ws = whitespace
        getline(cin,namefile_user);
        image_after.saveImage(namefile_user);
        break;
    }


}
case 8: {
//
}
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