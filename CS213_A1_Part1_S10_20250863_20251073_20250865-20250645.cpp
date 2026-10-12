// #define _USE_MATH_DEFINES
#include "Image_Class.h"
#include <iostream>
#include <iomanip>
#include <string>
#include <algorithm>
// #include <cmath>
/* Assignment 1 Part 2

Group Members:
1. Youssef Khaled Hussein 20250863 S10
Filters: 2,6,10,14 
2. Bassam Islam Gomaa 20251073 S10
Filters 4,8,12,16
3. Ahmed Bassam Abdelfatah 20250865 S10
Filters 3,7,11,15
4. Mostafa Mahmoud Abdella 20250645 S33
Filters 1,5,9,13
System Diagram (link): https://drive.google.com/file/d/1e3-aYXaxsDk5M_BQSIHgEAUdC9T8wVeo/view?usp=sharing
Cover Page (link for attachment): https://drive.google.com/file/d/15sVPni21QrRvLyEELZ8vgnmHn0lvryym/view?usp=sharing
Video Demo (link for video): 

*/

using namespace std;
// here is where the function (procedure to be much more accurate) starts where it sets an avg value for pixels to provide a grayscale image
void grayscale(Image &image)
{
    for (int i = 0; i < image.width; i++)
    {
        for (int j = 0; j < image.height; j++)
        {
            int red = image(i, j, 0);

            int green = image(i, j, 1);

            int blue = image(i, j, 2);

            int average = (red + green + blue) / 3;

            image(i, j, 0) = average;

            image(i, j, 1) = average;

            image(i, j, 2) = average;
        }
    }
}
void blackandwhite(Image &image_param)
{
    for (int y = 0; y < image_param.height; ++y)
    {
        for (int x = 0; x < image_param.width; ++x)
        {
            unsigned int red_colour = image_param.getPixel(x, y, 0);
            unsigned int green_colour = image_param.getPixel(x, y, 1);
            unsigned int blue_colour = image_param.getPixel(x, y, 2);
            unsigned int gray_value = int((red_colour * 0.2126) + (green_colour * 0.7152) + (blue_colour * 0.0722));
            // such that 4th parameter of set_pixel is the value of gray colour
            image_param.setPixel(x, y, 0, gray_value);
            image_param.setPixel(x, y, 1, gray_value);
            image_param.setPixel(x, y, 2, gray_value);
        }
    }
}
void InvertImage(Image &image_param)
{
    for (int i = 0; i < image_param.width; i++)
    {
        for (int j = 0; j < image_param.height; j++)
        {
            for (int k = 0; k < 3; k++)
            {
                image_param(i, j, k) = 255 - image_param(i, j, k);
            }
        }
    }
}

void addFrame(Image &image_param)
{
    int choice, padding = 0, r = 0, g = 0, b = 0;
    do
    {
        cout << "Enter padding size in pixels (e.g. 500): ";
        cin >> padding;
    } while (padding < 0);
    padding = padding * 2;
    do
    {
        cout << "Select border color:\n1. Red\n2. Green\n3. Blue\n4. Custom RGB\nEnter choice (1-4): ";
        cin >> choice;
    } while (choice < 1 || choice > 4);

    switch (choice)
    {
    case 1:
        r = 255;
        break;
    case 2:
        g = 255;
        break;
    case 3:
        b = 255;
        break;
    case 4:
        do
        {
            cout << "Enter R G B (0-255): ";
            cin >> r >> g >> b;
        } while (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255);
        break;
    default:
        r = g = b = 255;
        break;
    }

    Image frame(image_param.width + padding, image_param.height + padding);

    for (int i = 0; i < frame.width; i++)
    {
        for (int j = 0; j < frame.height; j++)
        {
            frame(i, j, 0) = r;
            frame(i, j, 1) = g;
            frame(i, j, 2) = b;
        }
    }
    for (int i = 0; i < image_param.width; i++)
    {
        for (int j = 0; j < image_param.height; j++)
        {
            for (int k = 0; k < image_param.channels; k++)
            {
                frame(i + padding / 2, j + padding / 2, k) = image_param(i, j, k);
            }
        }
    }
}

// flips the image horziontally (Ymen shmal)
void horizontalFlip(Image &image)
{
    for (int i = 0; i < image.width / 2; i++)
    {
        for (int j = 0; j < image.height; j++)
        {
            for (int c = 0; c < 3; c++)
            {
                unsigned char temp = image.getPixel(i, j, c);

                image.setPixel(i, j, c,
                               image.getPixel(image.width - 1 - i, j, c));

                image.setPixel(image.width - 1 - i, j, c, temp);
            }
        }
    }
}

// flips the image vertically (f2 w t7t)
void verticalFlip(Image &image)
{
    for (int i = 0; i < image.width; i++)
    {
        for (int j = 0; j < image.height / 2; j++)
        {
            for (int c = 0; c < 3; c++)
            {
                // temp variable to store the current pixel value so it doesn't get lost  after swap and gets ruined
                unsigned char temp = image.getPixel(i, j, c);

                image.setPixel(i, j, c,
                               image.getPixel(i, image.height - 1 - j, c));

                image.setPixel(i, image.height - 1 - j, c, temp);
            }
        }
    }
}

void rotate(Image &image_param)
{
    int query;
    double original_centrex = (image_param.width - 1) / 2.0;
    double original_centrey = (image_param.height - 1) / 2.0;
    cout << "Press '1' if you would like to rotate 90 degrees clockwise/270 degrees anticlockwise" << "\n";
    cout << "Press '2' if you would like to rotate 180 degrees clockwise/anticlockwise" << "\n";
    cout << "Press '3' if you would like to rotate 270 degrees clockwise/90 degrees anticlockwise" << "\n";
    cout << "Press '4' if you want no changes" << "\n";
    cin >> query;
    int target_w = (query == 1 || query == 3) ? image_param.height : image_param.width; // if you rotate 90 degrees or 270 degrees, the dimensions will change
    int target_h = (query == 1 || query == 3) ? image_param.width : image_param.height;
    int old_w = image_param.width;
    int old_h = image_param.height;
    double target_centrex = (image_param.width - 1) / 2.0;
    double target_centrey = (image_param.height - 1) / 2.0;
    Image rotated_image(target_w, target_h);
    for (auto y = 0; y < target_h; ++y)
    {
        for (auto x = 0; x < target_w; ++x)
        {
            double halal_cheating_ofx = x - target_centrex;
            double halal_cheating_ofy = y - target_centrey;
            double spun_x = 0;
            double spun_y = 0;

            // rotating section
            if (query == 1)
            {
                spun_x = -halal_cheating_ofy;
                spun_y = halal_cheating_ofx;
            }
            else if (query == 2)
            {
                spun_x = -halal_cheating_ofx;
                spun_y = -halal_cheating_ofy;
            }
            else if (query == 3)
            {
                spun_x = halal_cheating_ofy;
                spun_y = -halal_cheating_ofx;
            }
            else
            {
                spun_x = halal_cheating_ofx;
                spun_y = halal_cheating_ofy;
            }
            int source_x = int(spun_x + original_centrex + 0.5);
            int source_y = int(spun_y + original_centrey + 0.5);

            if (source_x >= 0 && source_x < image_param.width && source_y >= 0 && source_y < image_param.height)
            {
                rotated_image.setPixel(x, y, 0, image_param.getPixel(source_x, source_y, 0)); // Assign validated value to red
                rotated_image.setPixel(x, y, 1, image_param.getPixel(source_x, source_y, 1)); // Assign validated value to green
                rotated_image.setPixel(x, y, 2, image_param.getPixel(source_x, source_y, 2)); // Assign validated value to blue
            }
        }
    }
    image_param = rotated_image;
}

void brightness(Image &image_param)
{
    cout << "Do you want to darken or lighten the image? (Enter darken/Darken or lighten/Lighten):";
    string c;
    cin >> c;
    if (c == "darken" || c == "Darken")
    {
        cout << "Enter the darkening percent (0 to 100%):";
        int p;
        cin >> p;
        while (p < 0 || p > 100)
        {
            cout << "Invalid input, please try entering the percentage again from 0%-100%" << endl;
            cin >> p;
        }
        for (int i = 0; i < image_param.width; i++)
        {
            for (int j = 0; j < image_param.height; j++)
            {
                for (int k = 0; k < 3; k++)
                {
                    image_param(i, j, k) = image_param(i, j, k) * (1 - p / 100.0);
                }
            }
        }
    }

    else if (c == "lighten" || c == "Lighten")
    {
        cout << "Enter the lightening percent (0 to 100%):";
        int p;
        cin >> p;
        while (p < 0 || p > 100)
        {
            cout << "Invalid input, please try entering the percentage again from 0%-100%" << endl;
            cin >> p;
        }
        for (int i = 0; i < image_param.width; i++)
        {
            for (int j = 0; j < image_param.height; j++)
            {
                for (int k = 0; k < 3; k++)
                {
                    image_param(i, j, k) = image_param(i, j, k) + (255 - image_param(i, j, k)) * (p / 100.0);
                    if (image_param(i, j, k) > 255)
                    {
                        image_param(i, j, k) = 255;
                    }
                }
            }
        }
    }
}
void MergeImages(Image &image_param)
{
    string second_image_filename;
    cout << "Enter the second image filename with extension to blend with the first image: " << "\n";
    cin >> second_image_filename;

    Image second_image(second_image_filename);
    if (image_param.width == second_image.width && image_param.height == second_image.height)
    {
        for (int i = 0; i < image_param.width; i++)
        {
            for (int j = 0; j < image_param.height; j++)
            {
                for (int k = 0; k < 3; k++)
                {
                    image_param(i, j, k) = (image_param(i, j, k) + second_image(i, j, k)) / 2;
                }
            }
        }
    }
    else
    {
        cout << "Uh oh.., both images have different dimensions. Would you like to select option 1 to resize the image or option 2 to merge the common area of both images? (Enter 1 or 2): " << "\n";
        int resize_or_merge;
        cin >> resize_or_merge;
        while (resize_or_merge != 1 && resize_or_merge != 2)
        {
            cout << "Invalid input. Please enter 1 to resize or 2 to merge: " << "\n";
            cin >> resize_or_merge;
        }
        if (resize_or_merge == 1)
        {
            int target_width = max(image_param.width, second_image.width);
            int target_height = max(image_param.height, second_image.height);
            Image blended_image(target_width, target_height);
            for (int p = 0; p < target_width - 1; ++p)
            {
                for (int q = 0; q < target_height - 1; ++q)
                {
                    int src_x1 = p * image_param.width / target_width;
                    int src_y1 = q * image_param.height / target_height;
                    int src_x2 = p * second_image.width / target_width;
                    int src_y2 = q * second_image.height / target_height;
                    for (int k = 0; k < 3; ++k)
                    {
                        blended_image(p, q, k) = (image_param(src_x1, src_y1, k) + second_image(src_x2, src_y2, k)) / 2;
                    }
                }
            }
            image_param = blended_image;
        }
        else
        {
            int target_width = min(image_param.width, second_image.width);
            int target_height = min(image_param.height, second_image.height);
            Image blended_image(target_width, target_height);
            for (int p = 0; p < target_width - 1; ++p)
            {
                for (int q = 0; q < target_height - 1; ++q)
                {
                    for (int k = 0; k < 3; ++k)
                    {
                        blended_image(p, q, k) = (image_param(p, q, k) + second_image(p, q, k)) / 2;
                    }
                }
            }
            image_param = blended_image;
        }
    }
}

void resize(Image &image_param)
{
    int option, w, h, new_w, new_h;
    string namefile_user;
    cout << "Select an option out of the 3 options: \n"
         << "1: Double the image size\n"
         << "2: Half the image size \n"
         << "3: Resize image using custom dimensions \n";
    cin >> option;

    switch (option)
    {
    case 1:
        w = image_param.width * 2;
        h = image_param.height * 2;
        break;
    case 2:
        w = image_param.width / 2;
        h = image_param.height / 2;
        break;
    case 3:
        cout << "Enter the custom width: ";
        cin >> w;
        cout << "Enter the custom height: ";
        cin >> h;
        break;

    default:
        cout << "Invalid\n";
        w = image_param.width;
        h = image_param.height;
        break;
    }
    Image cust(w, h);
    float scale_X = (float)image_param.width / cust.width;
    float scale_Y = (float)image_param.height / cust.height;

    for (int i = 0; i < cust.width; i++)
    {
        for (int j = 0; j < cust.height; j++)
        {

            float orignil_X = (float)(i * scale_X);
            float orignil_Y = (float)(j * scale_Y);

            for (int k = 0; k < image_param.channels; k++)
            {
                cust(i, j, k) = image_param(orignil_X, orignil_Y, k);
            }
        }
    }
    cout << "How would you like to name the image alongside the extension?" << "\n";
    cin >> ws;
    getline(cin, namefile_user);
    cust.saveImage(namefile_user);
}
void detectEdges(Image &image_param)
{
    grayscale(image_param);
    Image edge_image(image_param.width, image_param.height);
    for (int i = 1; i < image_param.width; i++)
    {
        for (int j = 1; j < image_param.height; j++)
        {
            int gx = -1 * image_param(i - 1, j - 1, 0) + 1 * image_param(i + 1, j - 1, 0) + -2 * image_param(i - 1, j, 0) + 2 * image_param(i + 1, j, 0) + -1 * image_param(i - 1, j + 1, 0) + 1 * image_param(i + 1, j + 1, 0);

            int gy = -1 * image_param(i - 1, j - 1, 0) - 2 * image_param(i, j - 1, 0) - 1 * image_param(i + 1, j - 1, 0) + 1 * image_param(i - 1, j + 1, 0) + 2 * image_param(i, j + 1, 0) + 1 * image_param(i + 1, j + 1, 0);

            int magnitude = (int)sqrt((double)(pow(gx, 2) + pow(gy, 2)));
            if (magnitude > 255)
                magnitude = 255;

            edge_image(i, j, 0) = 255 - magnitude;
            edge_image(i, j, 1) = 255 - magnitude;
            edge_image(i, j, 2) = 255 - magnitude;
        }
    }
    image_param = edge_image;
}

void Crop(Image &image_param)
{
    int w, x, y, z;
    cout << "Insert starting point for width and height" << endl;
    cin >> w >> x;
    cout << "Insert crop width and height desired" << endl;
    cin >> y >> z;
    while (w < 0 || x < 0 || y < 0 || z < 0 || w > image_param.width || x > image_param.height || w + y > image_param.width || x + z > image_param.height)
    {
        cout << "Invalid crop dimensions, try entering correct dimension values again.." << endl;
        cin >> w >> x >> y >> z;
    }
    Image cropped_image(y, z);
    for (int i = 0; i < y; i++)
    {
        for (int j = 0; j < z; j++)
        {
            for (int k = 0; k < 3; k++)
            {
                cropped_image(i, j, k) = image_param(w + i, x + j, k);
            }
        }
    }
    image_param = cropped_image;
}

void Blur(Image &pic)
{

    int radius;
    cout << "Enter blur intensity \n";
    cin >> radius;
    while (radius > 10 || radius < 0)
    {
        cout << "Error value in blur intensity, enter a value between 0 to 10" << "\n";
        cin >> radius;
    }
    Image blurred = pic;

    int k_area = (2 * radius + 1) * (2 * radius + 1);

    for (int i = 0; i < pic.width; i++)
    {
        for (int j = 0; j < pic.height; j++)
        {
            for (int k = 0; k < pic.channels; k++)
            {
                int sum = 0;
                int count = 0;
                for (int x = -radius; x <= radius; x++)
                {
                    for (int y = -radius; y <= radius; y++)
                    {
                        int nx = i + x;
                        int ny = j + y;
                        if (nx >= 0 && nx < pic.width && ny >= 0 && ny < pic.height)
                        {
                            sum += pic.getPixel(nx, ny, k);
                            count++;
                        }
                    }
                }
                blurred.setPixel(i, j, k, sum / count);
            }
        }
    }
    pic = blurred;
}

void TVEffect(Image &image_param)
{
    for (int i = 0; i < image_param.width - 1; i++)
    {
        for (int j = 0; j < image_param.height - 1; j++)
        {
            if (j % 2 == 0 || j % 3 == 0)
            {
                image_param(i, j, 0) = (image_param(i, j, 0) * 3) / 5;
                image_param(i, j, 1) = (image_param(i, j, 1) * 3) / 5;
                image_param(i, j, 2) = (image_param(i, j, 2) * 3) / 5;
            }
            int noise = (rand() % 31) - 15;
            for (int k = 0; k < 3; k++)
            {
                int pixel_value = image_param(i, j, k) + noise;
                if (pixel_value > 255)
                    pixel_value = 255;
                else if (pixel_value < 0)
                    pixel_value = 0;
                image_param(i, j, k) = pixel_value;
            }
        }
    }
}

// pixel has values of 0-255 for each channel this limits the values
int limit(int value)
{
    if (value > 255)
        return 255;
    if (value < 0)
        return 0;
    return value;
}
// this applies the sunlight effect to each pixel
void sunlight(Image &image_param)
{
    for (int x = 0; x < image_param.width; x++)
    {
        for (int y = 0; y < image_param.height; y++)
        {
            int r = image_param.getPixel(x, y, 0) * 1.15 + 15;
            int g = image_param.getPixel(x, y, 1) * 1.08 + 15;
            int b = image_param.getPixel(x, y, 2) * 0.85 + 15;

            image_param.setPixel(x, y, 0, limit(r));
            image_param.setPixel(x, y, 1, limit(g));
            image_param.setPixel(x, y, 2, limit(b));
        }
    }
}
void PurpleEffect(Image& image_param) {
    for (int i = 0; i < image_param.width; i++)
            {
                for (int j = 0; j < image_param.height; j++)
                {
                    image_param(i, j, 0) = (image_param(i, j, 0) + 128) / 2;
                    image_param(i, j, 1) = (image_param(i, j, 1) + 0) / 2;
                    image_param(i, j, 2) = (image_param(i, j, 2) + 128) / 2;
                }
            }
}

void Infrared(Image &image_param)
{
    Image image_infrared = image_param;
    for (int i = 0; i < image_infrared.width; ++i)
    {
        for (int j = 0; j < image_infrared.height; ++j)
        {
            int r = image_infrared(i, j, 0);
            int g = image_infrared(i, j, 1);
            int b = image_infrared(i, j, 2);
            int avg = (r + g + b) / 3;
            int newR = 255;
            int newG = 255 - avg;
            int newB = (255 - avg) * 0.6;
            image_infrared.setPixel(i, j, 0, newR);
            image_infrared.setPixel(i, j, 1, newG);
            image_infrared.setPixel(i, j, 2, newB);
        }
    }
    image_param = image_infrared;
}

// void OilPainterFunction(Image& image_param) {
//     int factor = 48;

//     for (int i = 0; i < image_param.width; ++i) {
//         for (int j = 0; j < image_param.height; ++j) {
//             for (int k = 0; k < 3; ++k) {
//                 int val = image_param(i, j, k);

//                 // Quantize/round color to the nearest block
//                 val = (val / factor) * factor + (factor / 2);

//                 // Clamp values between 0 and 255
//                 if (val > 255) val = 255;
//                 if (val < 0) val = 0;

//                 image_param(i, j, k) = val;
//             }
//         }
//     }
// }

int main()
{
    bool flag = true;
    int option_no;
    string s, choice;
    cout << "Which photo would you like to do the changes in, make sure you chose the image with the right filename and extension." << endl;
    cin >> ws;
    getline(cin, s);
    Image image_name(s);
    while (flag)
    {
        cout << "Which option would you like to do?" << "\n";
        cout << "1: Grayscale" << "\n"
             << "2: Black and White" << "\n"
             << "3: Inverted Image" << "\n"
             << "4: Adding a frame onto a picture" << "\n"
             << "5: Flip an Image (Horizontally/Vertically)" << "\n"
             << "6: Rotate an Image" << "\n"
             << "7: Darken/Lighten Image" << "\n"
             << "8: Resize an Image" << "\n";
        cout << "9: Merge/Blend Two Images" << "\n"
             << "10: Detect Image Edges" << "\n"
             << "11: Crop Image" << "\n"
             << "12: Blur Image" << "\n"
             << "13: Adjust Natural Sunlight of Picture" << "\n"
             << "14: TV Image Effect" << "\n"
             << "15: Purple Image Effect" << "\n"
             << "16: Infrared Image Effect" << "\n"
             << "17: Skew Images" << "\n"
             << "18: Oil Paint an Image" << "\n";
        cin >> option_no;
        switch (option_no)
        {
        case 1:
        {
            // this is where we put our input an image to get a grayscale output
            Image image_after = image_name;
            string namefile_user;
            grayscale(image_after);
            cout << "How would you like to name the image alongside the extension?" << "\n";
            cin >> ws;
            getline(cin, namefile_user);
            image_after.saveImage(namefile_user);
            break;
        }
        case 2:
        {
            int x, y;
            string namefile_user;
            Image image_after = image_name;
            blackandwhite(image_after);
            cout << "How would you like to name the image alongside the extension?" << "\n";
            cin >> ws;
            getline(cin, namefile_user);
            image_after.saveImage(namefile_user);
            break;
        }
        case 3:
        {
            string namefile_user;
            Image image_after = image_name;
            InvertImage(image_after);
            cout << "How would you like to name the image alongside the extension?" << "\n";
            cin >> ws;
            getline(cin, namefile_user);
            image_after.saveImage(namefile_user);
            break;
        }
        case 4:
        {
            string namefile_user;
            Image image_after = image_name;
            addFrame(image_after);
            cout << "How would you like to name the image alongside the extension?" << "\n";
            cin >> ws;
            getline(cin, namefile_user);
            image_after.saveImage(namefile_user);
            break;
        }
        case 5:
        {
            string namefile_user, flip_query;
            Image image_after = image_name;
            cout << "Would you like to flip the image horizontally or vertically?" << "\n";
            cin >> flip_query;
            while (flip_query != "horizontally" && flip_query != "Horizontally" && flip_query != "vertically" && flip_query != "Vertically")
            {
                cout << "Incorrect query, please try again." << "\n";
                cin >> flip_query;
            }

            if (flip_query == "horizontally" || flip_query == "Horizontally")
            {
                horizontalFlip(image_after);
                cout << "How would you like to name the image alongside the extension?" << "\n";
                cin >> ws;
                getline(cin, namefile_user);
                image_after.saveImage(namefile_user);
            }
            else if (flip_query == "vertically" || flip_query == "Vertically")
            {
                verticalFlip(image_after);
                cout << "How would you like to name the image alongside the extension?" << "\n";
                cin >> ws;
                getline(cin, namefile_user);
                image_after.saveImage(namefile_user);
            }
        }
        break;
        case 6:
        {
            string namefile_user;
            Image image_after = image_name;
            rotate(image_after);
            cout << "How would you like to name the image alongside the extension?" << "\n";
            cin >> ws; // what this basically is like when you input the filename, you might put a space or two, this wont count as an input. ws = whitespace
            getline(cin, namefile_user);
            image_after.saveImage(namefile_user);
            break;
        }
        case 7:
        {
            string namefile_user;
            Image image_after = image_name;
            brightness(image_after);
            cout << "How would you like to name the image alongside the extension?" << "\n";
            cin >> ws; // what this basically is like when you input the filename, you might put a space or two, this wont count as an input. ws = whitespace
            getline(cin, namefile_user);
            image_after.saveImage(namefile_user);
            break;
        }
        case 8:
        {
            string namefile_user;
            Image image_after = image_name;
            resize(image_after);
            cout << "How would you like to name the image alongside the extension?" << "\n";
            cin >> ws;
            getline(cin, namefile_user);
            image_after.saveImage(namefile_user);
            break;
        }

        case 9:
        {
            string namefile_user;
            Image image_after = image_name;
            MergeImages(image_after);
            cout << "How would you like to name the image alongside the extension?" << "\n";
            cin >> ws;
            getline(cin, namefile_user);
            image_after.saveImage(namefile_user);
            break;
        }

        case 10:
        {
            string namefile_user;
            Image image_after = image_name;
            detectEdges(image_after);
            cout << "How would you like to name the image alongside the extension?" << "\n";
            cin >> ws;
            getline(cin, namefile_user);
            image_after.saveImage(namefile_user);
            break;
        }

        case 11:
        {
            string namefile_user;
            Image image_after = image_name;
            Crop(image_after);
            cout << "How would you like to name the image alongside the extension?" << "\n";
            cin >> ws;
            getline(cin, namefile_user);
            image_after.saveImage(namefile_user);
            break;
        }

        case 12:
        {
            string namefile_user;
            Image image_after = image_name;
            Blur(image_after);
            cout << "How would you like to name the image alongside the extension?" << "\n";
            cin >> ws;
            getline(cin, namefile_user);
            image_after.saveImage(namefile_user);
            break;
        }
        case 13:
        {
            string namefile_user;
            Image image_after = image_name;
            sunlight(image_after);
            cout << "How would you like to name the image alongside the extension?" << "\n";
            cin >> ws;
            getline(cin, namefile_user);
            image_after.saveImage(namefile_user);
            break;
        }

        case 14:
        {
            string namefile_user;
            Image image_after = image_name;
            TVEffect(image_after);
            cout << "How would you like to name the image alongside the extension?" << "\n";
            cin >> ws;
            getline(cin, namefile_user);
            image_after.saveImage(namefile_user);
            break;
        }

        case 15:
        {
            string namefile_user;
            Image image_after = image_name;
            PurpleEffect(image_after);
            cout << "How would you like to name the image alongside the extension?" << "\n";
            cin >> ws;
            getline(cin, namefile_user);
            image_after.saveImage(namefile_user);
            break;
        }

        case 16:
        {
            string namefile_user;
            Image image_after = image_name;
            Infrared(image_after);
            cout << "How would you like to name the image alongside the extension?" << "\n";
            cin >> ws;
            getline(cin, namefile_user);
            image_after.saveImage(namefile_user);
            break;
        }
        // case 17: {
        // string namefile_user;
        // Image image_after = image_name;
        // int angle;
        // cout << "Enter the angle of skew (in degrees): ";
        // cin >> angle;
        // double pi = M_PI;
        // double radians = angle * pi / 180.0;
        // int shift = abs(tan(radians) * image_after.height);
        // int target_width = image_after.width + shift;
        // int target_height = image_after.height;
        // Image skewed_image(target_width, target_height);
        // for (int i = 0; i < target_width; ++i) {
        //         for (int j = 0; j < target_height; ++j) {
        //             skewed_image(i, j, 0) = 255;
        //             skewed_image(i, j, 1) = 255;
        //             skewed_image(i, j, 2) = 255;
        //         }
        //     }
        // for(int i = 0; i < skewed_image.width;++i) {
        //     for(int j = 0; j < skewed_image.height;++j) {
        //         int offset_y = target_height - 1 - j;
        //         int src_x = i - (offset_y * tan(radians));
        //         int src_y = j;
        //         if (src_x >= 0 && src_x < image_name.width && src_y >= 0 && src_y < image_name.height) {
        //                 for (int k = 0; k < 3; ++k) {
        //                     skewed_image(i, j, k) = image_name.getPixel(src_x, src_y, k);
        //                 }
        //             }
        //     }
        // }
        // cout << "How would you like to name the image alongside the extension?"<< "\n";
        // cin >> ws;
        // getline(cin,namefile_user);
        // skewed_image.saveImage(namefile_user);
        // break;
        // }

        // case 18: {
        // string namefile_user;
        // Image image_after = image_name;
        // OilPainterFunction(image_after);
        // cout << "How would you like to name the image alongside the extension?"<< "\n";
        // cin >> ws;
        // getline(cin,namefile_user);
        // image_after.saveImage(namefile_user);
        // }

        break;
        default:
            cout << "Error in the query choice number you have entered, please try again";
        }
        cout << "Would you like to continue, type in Yes if you want to continue to do more changes or 'No' if you want to end the program" << "\n";
        cin >> choice;
        if (choice == "no" || choice == "No" || choice == "nO")
        {
            flag = false;
            break;
            return 0;
        }
    }

    return 0;
}
