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
case 2: 
//
break;
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