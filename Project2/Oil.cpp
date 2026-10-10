
#include <iostream>
#include "Image_Class.h"
using namespace std;

int main()
{
    Image img("Dog.jpg");

    Image result(img.width, img.height);
//identifies the radius of effect 
    int radius = 3;
    int levels = 20;
//loops each pixel
    for (int x = 0; x < img.width; x++)
    {
        for (int y = 0; y < img.height; y++)
        {
            int count[20] = {0};
            int red[20] = {0};
            int green[20] = {0};
            int blue[20] = {0};

            for (int i = -radius; i <= radius; i++)
            {
                for (int j = -radius; j <= radius; j++)
                {
                    int nx = x + i;
                    int ny = y + j;
//checks pixel relatively to boundaries
                    if (nx >= 0 && nx < img.width &&
                        ny >= 0 && ny < img.height)
                    {
                        int r = img(nx, ny, 0);
                        int g = img(nx, ny, 1);
                        int b = img(nx, ny, 2);

                        int brightness = (r + g + b) / 3;
                        int level = brightness * levels / 256;

                        if (level >= levels)
                            level = levels - 1;

                        count[level]++;
                        red[level] += r;
                        green[level] += g;
                        blue[level] += b;
                    }
                }
            }
            
            int best = 0;

            for (int k = 1; k < levels; k++)
            {
                if (count[k] > count[best])
                    best = k;
            }

            if (count[best] > 0)
            {
                result(x, y, 0) = red[best] / count[best];
                result(x, y, 1) = green[best] / count[best];
                result(x, y, 2) = blue[best] / count[best];
            }
        }
    }

    result.saveImage("oil_painting_applied.jpg");


    return 0;
}