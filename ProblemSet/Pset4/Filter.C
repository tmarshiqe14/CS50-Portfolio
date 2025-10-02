#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    float average;

    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            average = (image[i][j].rgbtBlue + image[i][j].rgbtRed + image[i][j].rgbtGreen)/ 3.0;

            image[i][j].rgbtRed = round(average);
            image[i][j].rgbtBlue = round(average);
            image[i][j].rgbtGreen = round(average);


        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{

    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            int originalRed = image[i][j].rgbtRed;
            int originalBlue = image[i][j].rgbtBlue;
            int originalGreen = image[i][j].rgbtGreen;
            int sepiaRed = round(.393 * originalRed + .769 * originalGreen + .189 * originalBlue);
            int sepiaGreen = round(.349 * originalRed + .686 * originalGreen + .168 * originalBlue);
            int sepiaBlue = round(.272 * originalRed + .534 * originalGreen + .131 * originalBlue);

            if(sepiaRed > 255)
            {
                sepiaRed = 255;
            }
            if(sepiaGreen > 255)
            {
                sepiaGreen = 255;
            }
            if(sepiaBlue > 255)
            {
                sepiaBlue = 255;
            }


            image[i][j].rgbtRed = sepiaRed;
            image[i][j].rgbtBlue = sepiaBlue;
            image[i][j].rgbtGreen = sepiaGreen;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width/2; j++)
        {

            RGBTRIPLE temp;

            temp = image[i][j];
            image[i][j] = image[i][width - 1 - j];
            image[i][width - 1 - j] = temp;


        }
    }

    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE copy[height][width];
    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            int totalRed = 0, totalBlue = 0, totalGreen = 0;
            int count = 0;
            copy[i][j] = image[i][j];

            for(int di = -1; di <= 1; di++)
            {
            for(int dj = -1; dj <= 1; dj++)
            {
                int ni = i + di;
                int nj = j + dj;

                if(ni >= 0 && ni < height && nj >= 0 && nj < width)
                {
                    totalRed += image[ni][nj].rgbtRed;
                    totalBlue += image[ni][nj].rgbtBlue;
                    totalGreen += image[ni][nj].rgbtGreen;
                    count++;

                }
            }


            }

            int newRed = round((float)totalRed/count);
            int newBlue = round((float)totalBlue/count);
            int newGreen = round((float)totalGreen/count);

            copy[i][j].rgbtRed = newRed;
            copy[i][j].rgbtBlue = newBlue;
            copy[i][j].rgbtGreen = newGreen;

        }

    }


    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            image[i][j] = copy[i][j];
        }
    }


    return;
}
