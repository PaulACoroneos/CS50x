#include "helpers.h"
#include <math.h>
#include <stdio.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    int average = 0;
    for (int i = 0; i < width; i++)
    {
        for (int j = 0; j < height; j++)
        {
            average = round((image[j][i].rgbtBlue + image[j][i].rgbtRed + image[j][i].rgbtGreen) / 3.0);
            image[j][i].rgbtBlue = average;
            image[j][i].rgbtRed = average;
            image[j][i].rgbtGreen = average;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    int origRed, origGreen, origBlue;
    for (int i = 0; i < width; i++)
    {
        for (int j = 0; j < height; j++)
        {
            origRed = image[j][i].rgbtRed;
            origGreen = image[j][i].rgbtGreen;
            origBlue = image[j][i].rgbtBlue;

            image[j][i].rgbtBlue = fmin(round(.272 * origRed + .534 * origGreen + .131 * origBlue), 255);
            image[j][i].rgbtRed = fmin(round(.393 * origRed + .769 * origGreen + .189 * origBlue), 255);
            image[j][i].rgbtGreen = fmin(round(.349 * origRed + .686 * origGreen + .168 * origBlue), 255);
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{

    int colCounter;

    //maintain row location but fill in cols of image backwards into new image
    for (int i = 0; i < height; i++)
    {
        colCounter = 0;
        for (int j = width - 1; j >= width / 2; j--)
        {
            RGBTRIPLE temp = image[i][colCounter];
            image[i][colCounter] = image[i][j];
            image[i][j] = temp;
            colCounter++;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE tempImage[height][width];
    RGBTRIPLE pixel, right, lowerRight, lower, lowerLeft, left, upperLeft, upper, upperRight;

    //copy image to temp image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            tempImage[i][j] = image[i][j];
        }
    }

    //now loop through every pixel in image using tempImage to calculate new blurred version
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            //there are quite a few cases to handle here. Going to handle 1 by one.

            // Here are some shortcuts to pre-calculate locations. A little wasteful but in most cases all are needed
            if (i > 0)
            {
                upper = tempImage[i - 1][j];
                upperRight = tempImage[i - 1][j + 1];
            }
            if (j > 0)
            {
                left = tempImage[i][j - 1];
                lowerLeft = tempImage[i + 1][j - 1];
            }
            if (j > 0 && i > 0)
            {
                upperLeft = tempImage[i - 1][j - 1];
            }
            if (j < width - 1)
            {
                right = tempImage[i][j + 1];
            }
            if (i < height - 1)
            {
                lower = tempImage[i + 1][j];
            }
            if (i < height - 1 && j < width - 1)
            {
                lowerRight = tempImage[i + 1][j + 1];
            }

            pixel = tempImage[i][j];

            // CORNERS

            //case 1. Upper left hand corner pixel
            if (i - 1 < 0 && j - 1 < 0)
            {
                //pixel + right + lower right + lower
                image[i][j].rgbtGreen = round((pixel.rgbtGreen + right.rgbtGreen + lowerRight.rgbtGreen + lower.rgbtGreen) / (float)4);
                image[i][j].rgbtRed = round((pixel.rgbtRed + right.rgbtRed + lowerRight.rgbtRed + lower.rgbtRed) / (float)4);
                image[i][j].rgbtBlue = round((pixel.rgbtBlue + right.rgbtBlue + lowerRight.rgbtBlue + lower.rgbtBlue) / (float)4);
            }
            //case 2. Upper right hand corner pixel
            else if (i - 1 < 0 && j + 1 == width)
            {
                //pixel + left + lower left + lower
                image[i][j].rgbtGreen = round((pixel.rgbtGreen + left.rgbtGreen + lowerLeft.rgbtGreen + lower.rgbtGreen) / (float)4);
                image[i][j].rgbtRed = round((pixel.rgbtRed + left.rgbtRed + lowerLeft.rgbtRed + lower.rgbtRed) / (float)4);
                image[i][j].rgbtBlue = round((pixel.rgbtBlue + left.rgbtBlue + lowerLeft.rgbtBlue + lower.rgbtBlue) / (float)4);
            }
            //case 3. Lower left hand corner pixel
            else if (i + 1 == height && j - 1 < 0)
            {
                //pixel + right + upper right + upper
                image[i][j].rgbtGreen = round((pixel.rgbtGreen + right.rgbtGreen + upperRight.rgbtGreen + upper.rgbtGreen) / (float)4);
                image[i][j].rgbtRed = round((pixel.rgbtRed + right.rgbtRed + upperRight.rgbtRed + upper.rgbtRed) / (float)4);
                image[i][j].rgbtBlue = round((pixel.rgbtBlue + right.rgbtBlue + upperRight.rgbtBlue + upper.rgbtBlue) / (float)4);
            }
            //case 4. Lower right hand corner pixel
            else if (i + 1 == height && j + 1 == width)
            {
                //pixel + left + upper left + upper
                image[i][j].rgbtGreen = round((pixel.rgbtGreen + left.rgbtGreen + upperLeft.rgbtGreen + upper.rgbtGreen) / (float)4);
                image[i][j].rgbtRed = round((pixel.rgbtRed + left.rgbtRed + upperLeft.rgbtRed + upper.rgbtRed) / (float)4);
                image[i][j].rgbtBlue = round((pixel.rgbtBlue + left.rgbtBlue + upperLeft.rgbtBlue + upper.rgbtBlue) / (float)4);
            }

            // EDGES

            //case 5. Top row pixel not corner
            else if (i - 1 < 0)
            {
                // printf("updating top row\n");
                //pixel + left + right + lowerLeft + lower + lowerRight
                image[i][j].rgbtGreen = round((pixel.rgbtGreen + left.rgbtGreen + right.rgbtGreen + lowerLeft.rgbtGreen + lower.rgbtGreen + lowerRight.rgbtGreen) / (float)6);
                image[i][j].rgbtRed = round((pixel.rgbtRed + left.rgbtRed + right.rgbtRed + lowerLeft.rgbtRed + lower.rgbtRed + lowerRight.rgbtRed) / (float)6);
                image[i][j].rgbtBlue = round((pixel.rgbtBlue + left.rgbtBlue + right.rgbtBlue + lowerLeft.rgbtBlue + lower.rgbtBlue + lowerRight.rgbtBlue) / (float)6);
            }

            //case 6. lower row not corner
            else if (i + 1 == height)
            {
                // printf("updating bottom row\n");
                //pixel + left + right + upperLeft + upper + upperRight
                image[i][j].rgbtGreen = round((pixel.rgbtGreen + left.rgbtGreen + right.rgbtGreen + upperLeft.rgbtGreen + upper.rgbtGreen + upperRight.rgbtGreen) / (float)6);
                image[i][j].rgbtRed = round((pixel.rgbtRed + left.rgbtRed + right.rgbtRed + upperLeft.rgbtRed + upper.rgbtRed + upperRight.rgbtRed) / (float)6);
                image[i][j].rgbtBlue = round((pixel.rgbtBlue + left.rgbtBlue + right.rgbtBlue + upperLeft.rgbtBlue + upper.rgbtBlue + upperRight.rgbtBlue) / (float)6);
            }

            //case 7. left column not corner
            else if (j - 1 < 0)
            {
                // printf("updating left col\n");
                //pixel + upper + upperRight + right + lowerRight + lower
                image[i][j].rgbtGreen = round((pixel.rgbtGreen + upper.rgbtGreen + upperRight.rgbtGreen + right.rgbtGreen + lowerRight.rgbtGreen + lower.rgbtGreen) / (float)6);
                image[i][j].rgbtRed = round((pixel.rgbtRed + upper.rgbtRed + upperRight.rgbtRed + right.rgbtRed + lowerRight.rgbtRed + lower.rgbtRed) / (float)6);
                image[i][j].rgbtBlue = round((pixel.rgbtBlue + upper.rgbtBlue + upperRight.rgbtBlue + right.rgbtBlue + lowerRight.rgbtBlue + lower.rgbtBlue) / (float)6);
            }

            //case 8. right column not corner
            else if (j + 1 == width)
            {
                // printf("updating right col\n");
                //pixel + upper + upperLeft + left + lowerLeft + lower
                image[i][j].rgbtGreen = round((pixel.rgbtGreen + upper.rgbtGreen + upperLeft.rgbtGreen + left.rgbtGreen + lowerLeft.rgbtGreen + lower.rgbtGreen) / (float)6);
                image[i][j].rgbtRed = round((pixel.rgbtRed + upper.rgbtRed + upperLeft.rgbtRed + left.rgbtRed + lowerLeft.rgbtRed + lower.rgbtRed) / (float)6);
                image[i][j].rgbtBlue = round((pixel.rgbtBlue + upper.rgbtBlue + upperLeft.rgbtBlue + left.rgbtBlue + lowerLeft.rgbtBlue + lower.rgbtBlue) / (float)6);
            }

            //case9. Middle pixel
            else
            {
                //pixel + upper + upperRight + right + lowerRight + lower + lowerLeft + left + upperLeft
                image[i][j].rgbtGreen = round((pixel.rgbtGreen + upper.rgbtGreen + upperRight.rgbtGreen + right.rgbtGreen + lowerRight.rgbtGreen + lower.rgbtGreen + lowerLeft.rgbtGreen + left.rgbtGreen + upperLeft.rgbtGreen) / (float)9);
                image[i][j].rgbtRed = round((pixel.rgbtRed + upper.rgbtRed + upperRight.rgbtRed + right.rgbtRed + lowerRight.rgbtRed + lower.rgbtRed + lowerLeft.rgbtRed + left.rgbtRed + upperLeft.rgbtRed) / (float)9);
                image[i][j].rgbtBlue = round((pixel.rgbtBlue + upper.rgbtBlue + upperRight.rgbtBlue + right.rgbtBlue + lowerRight.rgbtBlue + lower.rgbtBlue + lowerLeft.rgbtBlue + left.rgbtBlue + upperLeft.rgbtBlue) / (float)9);
            }
        }
    }
    return;
}
