#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#include "helpers.h"

double clamp(double value, double min, double max);

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    //Select Pixel
    for(int y = 0; y < height; y++)
    {
        for(int x = 0; x < width; x++)
        {
            int mediumValue = clamp(round((image[y][x].rgbtBlue + image[y][x].rgbtGreen + image[y][x].rgbtRed) / 3.00), 0, 255);

            image[y][x].rgbtBlue = mediumValue;
            image[y][x].rgbtGreen = mediumValue;
            image[y][x].rgbtRed = mediumValue;
        }
    }

    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Cores originais
            int red = image[i][j].rgbtRed;
            int green = image[i][j].rgbtGreen;
            int blue = image[i][j].rgbtBlue;

            // Cores sepia
            int sepia_red = round(.393 * red + .769 * green + .189 * blue);
            int sepia_green = round(.349 * red + .686 * green + .168 * blue);
            int sepia_blue = round(.272 * red + .534 * green + .131 * blue);

            if (i == 0 && j == 0)
            {
                printf("sepia rgb(%i, %i, %i)\n", sepia_red, sepia_green, sepia_blue);
            }

            // Troca as cores
            image[i][j].rgbtRed = sepia_red > 255 ? 255 : sepia_red;
            image[i][j].rgbtGreen = sepia_green > 255 ? 255 : sepia_green;
            image[i][j].rgbtBlue = sepia_blue > 255 ? 255 : sepia_blue;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
        //Select pixel
    for(int y = 0; y < height; y++){
        RGBTRIPLE tempPixel;

        int currentPos = 0;
        int endPos = width - 1;

        while(currentPos < endPos){
            tempPixel = image[y][currentPos];

            image[y][currentPos] = image[y][endPos];
            image[y][endPos] = tempPixel;

            currentPos++;
            endPos--;
        }
    }

    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE copy[height][width];
    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            copy[y][x] = image[y][x];
        }
    }

    //Select pixel
    for(int x = 0; x < width; x++){
        for(int y = 0; y < height; y++){

            int mediumAmount = 0;

            int mediumR = 0;
            int mediumG = 0;
            int mediumB = 0;

            //Medium Colors
            for(int pixel_x = 0; pixel_x < 3; pixel_x++){
                for(int pixel_y = 0; pixel_y < 3; pixel_y++){
                    int currentPosX = (x + pixel_x - 1);
                    int currentPosY = (y + pixel_y - 1);

                    if(currentPosX < 0 || currentPosX > width ||
                       currentPosY < 0 || currentPosY > height){
                        continue;
                    }

                    mediumR += copy[currentPosY][currentPosX].rgbtRed;
                    mediumG += copy[currentPosY][currentPosX].rgbtGreen;
                    mediumB += copy[currentPosY][currentPosX].rgbtBlue;

                    mediumAmount++;
                }
            }

            image[y][x].rgbtRed   = round(mediumR / mediumAmount);
            image[y][x].rgbtGreen = round(mediumG / mediumAmount);
            image[y][x].rgbtBlue  = round(mediumB / mediumAmount);
        }
    }

    return;
}

double clamp(double value, double min, double max)
{
  const double result = value < min ? min : value;
  return result > max ? max : result;
}