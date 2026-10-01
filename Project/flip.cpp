#include <iostream>
#include "Image_Class.h"
//flips the image horziontally (Ymen shmal)
void horizontalFlip(Image& image)
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
//flips the image vertically (f2 w t7t)
void verticalFlip(Image& image)
{
    for (int i = 0; i < image.width; i++)
    {
        for (int j = 0; j < image.height / 2; j++)
        {
            for (int c = 0; c < 3; c++)
            {
//temp variable to store the current pixel value so it doesn't get lost  after swap and gets ruined             
                unsigned char temp = image.getPixel(i, j, c);

                image.setPixel(i, j, c,
                    image.getPixel(i, image.height - 1 - j, c));

                image.setPixel(i, image.height - 1 - j, c, temp);
            }
        }
    }
}

int main()
{
    Image image("luffy.jpg");

    Image horizontal = image;
    Image vertical = image;

    horizontalFlip(horizontal);
    verticalFlip(vertical);
// saves the flipped image copies 
    horizontal.saveImage("horizontal.jpg");
    vertical.saveImage("vertical.jpg");


    return 0;
}
