#include "Image_Class.h"
//here is where the function starts where it sets an avg value for pixels to provide a grayscale image 
void grayscale(Image& image)
{
    for (int i = 0; i < image.width; i++)
    {
        for (int j = 0; j < image.height; j++)
        {
          int red = image(i,j,0);   

          int green = image(i,j,1);

          int blue = image(i,j,2);

          int average = (red + green + blue) / 3;

          image(i,j,0) = average;

          image(i,j,1) = average;

          image(i,j,2) = average;
        }
    }
}

int main()
{
//this is where we put our input an image to get a grayscale output 
    Image image("luffy.jpg");

    grayscale(image);
// and this is the final output
    image.saveImage("grayscale.jpg");

    return 0;
}
