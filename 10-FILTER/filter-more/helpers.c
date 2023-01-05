//////////////////////////////////////////////////////////////////////////////////
// Engineer: IBRAHIM AYAZ
// Create Date: 05.01.2023 23:35:00
// Design Name: filter
//
// Description: Program for applying filter to bmp formatted image files.
// Expected filters are grayscale, reflect, blur and edges.
// All the details about the Problem Set are described at the following link:
// https://cs50.harvard.edu/x/2022/psets/4/filter/more/
//
// Output: The output should generate the filtered image of the given original
// image.
//////////////////////////////////////////////////////////////////////////////////

#include "helpers.h"
#include "math.h"

// Convert image to grayscale
// In order to convert the image to the grayscale form, calculate the average color value for each pixel
// by adding all the color channels and dividing the sum by 3.
// Then assign this average value to all the color channels.
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    int average = 0;
    for(int row = 0; row < height; row++)
    {
        for(int column = 0; column < width; column++)
        {
            average = round((image[row][column].rgbtBlue + image[row][column].rgbtGreen + image[row][column].rgbtRed)/3.00);
            image[row][column].rgbtBlue = image[row][column].rgbtGreen = image[row][column].rgbtRed = average;
        }
    }
}

// Reflect image horizontally
// To have the reflection of the image horizontaly, first assign the left side pixel to a temporary variable.
// Then assign the right side corresponded pixel to the left side variable.
// Finally assign the temporary variable to the left side corresponded pixel.
// Loop until half of the row count! Otherwise you can have a double reflected image which is identical with the original.
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp[height][width];
    for(int row = 0; row < height; row++)
    {
        for(int column = 0; column < width / 2; column++)
        {
            temp[row][column]               = image[row][column];
            image[row][column]              = image[row][width - 1 - column];
            image[row][width - 1 - column]  = temp[row][column];
        }
    }
}

// Blur image
// First store all the pixel values from the original image to a temporary 2D array.
// Then inside of a loop, determine the position of the array and eliminate the out of bound positions.
// For each valid position, add all the valid neighborhood positions color channels seperately.
// Divide the sum by the number of added values and assign it to corresponded variables.
// Assign every pixel from the temp variable to original image.
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp[height][width];
    for(int row = 0; row < height; row++)
    {
        for(int column = 0; column < width; column++)
        {
            temp[row][column] = image[row][column];
        }
    }

    for(int row = 0; row < height; row++)
    {
        for(int column = 0; column < width; column++)
        {
            int total_blue, total_green, total_red;
            total_blue = total_green = total_red = 0;
            int currentX = 0;
            int currentY = 0;
            float counter = 0.00;

            for(int i = -1; i < 2; i++)
            {
                for(int j = -1; j < 2; j++)
                {
                    currentX = row      + i;
                    currentY = column   + j;
                    if(currentX < 0 || currentX > (height - 1) || currentY < 0 || currentY > (width - 1))
                    {
                        continue;
                    }
                    total_blue  += image[currentX][currentY].rgbtBlue;
                    total_green += image[currentX][currentY].rgbtGreen;
                    total_red   += image[currentX][currentY].rgbtRed;

                    counter++;
                }
            }
            temp[row][column].rgbtBlue  = round(total_blue/counter);
            temp[row][column].rgbtGreen = round(total_green/counter);
            temp[row][column].rgbtRed   = round(total_red/counter);
        }
    }

    for(int row = 0; row < height; row++)
    {
        for(int column = 0; column < width; column++)
        {
            image[row][column].rgbtBlue     = temp[row][column].rgbtBlue;
            image[row][column].rgbtGreen    = temp[row][column].rgbtGreen;
            image[row][column].rgbtRed      = temp[row][column].rgbtRed;
        }
    }
}

// Detect edges
// First store all the pixel values from the original image to a temporary 2D array.
// Then inside of a loop, determine the position of the array and for the out of bound positions,
// add 0 to gx and gy values then continue to the next iteration of the loop.
// For each valid position, multiply the gx and gy's respective indexes with the corresponded pixel.
// Calculate the square root of the squared gx + squared gy.
// Assign the value to the temp array's corresponded channels.
// Assign every pixel from the temp variable to original image.
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp[height][width];
    for(int row = 0; row < height; row++)
    {
        for(int column = 0; column < width; column++)
        {
            temp[row][column] = image[row][column];
        }
    }

    for(int row = 0; row < height; row++)
    {
        for(int column = 0; column < width; column++)
        {
            int gx_b, gx_g, gx_r, gy_b, gy_g, gy_r;
            gx_b = gx_g = gx_r = gy_b = gy_g = gy_r = 0;
            int final_blue, final_green, final_red;
            final_blue = final_green = final_red = 0;
            int currentX = 0;
            int currentY = 0;
            int gx[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
            int gy[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};

            for(int i = -1; i < 2; i++)
            {
                for(int j = -1; j < 2; j++)
                {
                    currentX = row      + i;
                    currentY = column   + j;
                    if(currentX < 0 || currentX > (height - 1) || currentY < 0 || currentY > (width - 1))
                    {
                        gx_b += 0;
                        gx_g += 0;
                        gx_r += 0;

                        gy_b += 0;
                        gy_g += 0;
                        gy_r += 0;
                        continue;
                    }
                    gx_b += gx[i + 1][j + 1] * image[currentX][currentY].rgbtBlue;
                    gx_g += gx[i + 1][j + 1] * image[currentX][currentY].rgbtGreen;
                    gx_r += gx[i + 1][j + 1] * image[currentX][currentY].rgbtRed;

                    gy_b += gy[i + 1][j + 1] * image[currentX][currentY].rgbtBlue;
                    gy_g += gy[i + 1][j + 1] * image[currentX][currentY].rgbtGreen;
                    gy_r += gy[i + 1][j + 1] * image[currentX][currentY].rgbtRed;
                }
            }
            final_blue  = round(sqrt((gx_b * gx_b) + (gy_b * gy_b)));
            final_green = round(sqrt((gx_g * gx_g) + (gy_g * gy_g)));
            final_red   = round(sqrt((gx_r * gx_r) + (gy_r * gy_r)));


            temp[row][column].rgbtBlue  = (final_blue) > 255 ? 255 : final_blue;
            temp[row][column].rgbtGreen = (final_green) > 255 ? 255 : final_green;
            temp[row][column].rgbtRed   = (final_red) > 255 ? 255 : final_red;
        }
    }

    for(int row = 0; row < height; row++)
    {
        for(int column = 0; column < width; column++)
        {
            image[row][column].rgbtBlue     = temp[row][column].rgbtBlue;
            image[row][column].rgbtGreen    = temp[row][column].rgbtGreen;
            image[row][column].rgbtRed      = temp[row][column].rgbtRed;
        }
    }
}
