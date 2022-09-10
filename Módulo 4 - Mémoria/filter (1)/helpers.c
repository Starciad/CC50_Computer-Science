#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#include "helpers.h"

double clamp(double value, double min, double max);

//===========================//
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

//===========================//
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

//===========================//
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

//===========================//
// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE tempImage[height][width];
    for(int x = 0; x < width; x++) {
        for(int y = 0; y < height; y++) {
            tempImage[y][x] = image[y][x];
        }
    }

    int gx[3][3] = {
        {-1, 0, 1},
        {-2, 0, 2},
        {-1, 0, 1}
    };

    int gy[3][3] = {
        {-1, -2, -1},
        { 0,  0,  0},
        { 1,  2,  1}
    };

    //Select Pixel
    for(int x = 0; x < width; x++) {
        for(int y = 0; y < height; y++) {

            int rgx = 0;
            int bgx = 0;
            int ggx = 0;

            int rgy = 0;
            int bgy = 0;
            int ggy = 0;

            //Medium Colors
            for(int pixel_x = 0; pixel_x < 3; pixel_x++) {
                for(int pixel_y = 0; pixel_y < 3; pixel_y++) {

                    int currentPosX = (x + pixel_x - 1);
                    int currentPosY = (y + pixel_y - 1);

                    if(currentPosX < 0 || currentPosX > width ||
                       currentPosY < 0 || currentPosY > height) {
                        continue;
                    }

                    rgx += image[currentPosY][currentPosX].rgbtRed    * gx[pixel_x][pixel_y];
                    ggx += image[currentPosY][currentPosX].rgbtGreen  * gx[pixel_x][pixel_y];
                    bgx += image[currentPosY][currentPosX].rgbtBlue   * gx[pixel_x][pixel_y];

                    rgy += image[currentPosY][currentPosX].rgbtRed    * gy[pixel_x][pixel_y];
                    ggy += image[currentPosY][currentPosX].rgbtGreen  * gy[pixel_x][pixel_y];
                    bgy += image[currentPosY][currentPosX].rgbtBlue   * gy[pixel_x][pixel_y];
                }
            }

            int resultRed   = round(sqrt(pow(rgx, 2) + pow(rgy, 2)));
            int resultGreen = round(sqrt(pow(ggx, 2) + pow(ggy, 2)));
            int resultBlue  = round(sqrt(pow(bgx, 2) + pow(bgy, 2)));

            tempImage[y][x].rgbtRed   = clamp(resultRed, 0, 255);
            tempImage[y][x].rgbtGreen = clamp(resultGreen, 0, 255);
            tempImage[y][x].rgbtBlue  = clamp(resultBlue, 0, 255);

            //printf("=============\n\n");
            //printf("R: %i\n", tempImage[y][x].rgbtRed);
            //printf("G: %i\n", tempImage[y][x].rgbtGreen);
            //printf("B: %i\n\n", tempImage[y][x].rgbtBlue);
        }
    }

    //Copy
    for(int x = 0; x < width; x++) {
        for(int y = 0; y < height; y++) {
            image[y][x].rgbtRed = tempImage[y][x].rgbtRed;
            image[y][x].rgbtGreen = tempImage[y][x].rgbtGreen;
            image[y][x].rgbtBlue = tempImage[y][x].rgbtBlue;
        }
    }

    return;
}

double clamp(double value, double min, double max)
{
  const double result = value < min ? min : value;
  return result > max ? max : result;
}