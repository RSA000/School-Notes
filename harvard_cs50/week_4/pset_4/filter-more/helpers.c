#include "helpers.h"
#include <math.h>
#include <stdio.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    // grabbing each pixel
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            RGBTRIPLE pixel = image[i][j];
            int average = round((pixel.rgbtBlue + pixel.rgbtGreen + pixel.rgbtRed) / 3.0);
            image[i][j].rgbtBlue = average;
            image[i][j].rgbtGreen = average;
            image[i][j].rgbtRed = average;
        }
    }
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    // grabbing each pixel
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            RGBTRIPLE pixel = image[i][j];
            int red = round(0.393 * pixel.rgbtRed + 0.769 * pixel.rgbtGreen + 0.189 * pixel.rgbtBlue);
            int green = round(0.349 * pixel.rgbtRed + 0.686 * pixel.rgbtGreen + 0.168 * pixel.rgbtBlue);
            int blue = round(0.272 * pixel.rgbtRed + 0.534 * pixel.rgbtGreen + 0.131 * pixel.rgbtBlue);

            if (red > 255)
            {
                red = 255;
            }
            else if (red < 0)
            {
                red = 0;
            }
            if (green > 255)
            {
                green = 255;
            }
            else if (green < 0)
            {
                green = 0;
            }
            if (blue > 255)
            {
                blue = 255;
            }
            else if (blue < 0)
            {
                blue = 0;
            }

            pixel.rgbtRed = red;
            pixel.rgbtGreen = green;
            pixel.rgbtBlue = blue;

            image[i][j] = pixel;
        }
    }
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++)
        {
            RGBTRIPLE tmp = image[i][j];
            image[i][j] = image[i][width - j - 1];
            image[i][width - j - 1] = tmp;
        }
    }
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // Creating 2d array copy of image
    RGBTRIPLE image_copy[height][width];
    // for each row
    for (int i = 0; i <= height; i++)
    {
        // for each element in row
        for (int j = 0; j <= width; j++)
        {
            // first check if top left corner
            if (i == 0 && j == 0)
            {
                // for each r,g,b, value we get the average
                image_copy[i][j].rgbtRed = round((image[i][j].rgbtRed + image[i + 1][j].rgbtRed + image[i][j + 1].rgbtRed +
                                                  image[i + 1][j + 1].rgbtRed) / 4.0);

                image_copy[i][j].rgbtBlue = round((image[i][j].rgbtBlue + image[i + 1][j].rgbtBlue + image[i][j + 1].rgbtBlue +
                                                   image[i + 1][j + 1].rgbtBlue) / 4.0);

                image_copy[i][j].rgbtGreen = round(
                                                 (image[i][j].rgbtGreen + image[i + 1][j].rgbtGreen + image[i][j + 1].rgbtGreen +
                                                  image[i + 1][j + 1].rgbtGreen) / 4.0);

            }

            // then check if top right
            else if (i == 0 && j == width - 1)
            {
                // for each r,g,b value we get the average
                image_copy[i][j].rgbtRed = round((image[i][j].rgbtRed + image[i + 1][j].rgbtRed + image[i][j - 1].rgbtRed +
                                                  image[i + 1][j - 1].rgbtRed) / 4.0);

                image_copy[i][j].rgbtBlue = round((image[i][j].rgbtBlue + image[i + 1][j].rgbtBlue + image[i][j - 1].rgbtBlue +
                                                   image[i + 1][j - 1].rgbtBlue) / 4.0);

                image_copy[i][j].rgbtGreen = round((image[i][j].rgbtGreen + image[i + 1][j].rgbtGreen + image[i][j - 1].rgbtGreen +
                                                    image[i + 1][j - 1].rgbtGreen) / 4.0);
            }

            // then check if bottom left corner
            else if (i == height - 1 && j == 0)
            {
                image_copy[i][j].rgbtRed = round((image[i][j].rgbtRed + image[i - 1][j].rgbtRed + image[i][j + 1].rgbtRed +
                                                  image[i - 1][j + 1].rgbtRed) / 4.0);

                image_copy[i][j].rgbtBlue = round((image[i][j].rgbtBlue + image[i - 1][j].rgbtBlue + image[i][j + 1].rgbtBlue +
                                                   image[i - 1][j + 1].rgbtBlue) / 4.0);

                image_copy[i][j].rgbtGreen = round((image[i][j].rgbtGreen + image[i - 1][j].rgbtGreen + image[i][j + 1].rgbtGreen +
                                                    image[i - 1][j + 1].rgbtGreen) / 4.0);
            }

            // then check if right bottom corner
            else if (i == height - 1 && j == width - 1)
            {
                image_copy[i][j].rgbtRed = round((image[i][j].rgbtRed + image[i - 1][j].rgbtRed + image[i][j - 1].rgbtRed +
                                                  image[i - 1][j - 1].rgbtRed) / 4.0);

                image_copy[i][j].rgbtBlue = round((image[i][j].rgbtBlue + image[i - 1][j].rgbtBlue + image[i][j - 1].rgbtBlue +
                                                   image[i - 1][j - 1].rgbtBlue) / 4.0);

                image_copy[i][j].rgbtGreen = round((image[i][j].rgbtGreen + image[i - 1][j].rgbtGreen + image[i][j - 1].rgbtGreen +
                                                    image[i - 1][j - 1].rgbtGreen) / 4.0);
            }

            // then check if top row
            else if (i == 0 && j < width - 1)
            {
                image_copy[i][j].rgbtRed = round((image[i][j].rgbtRed + image[i][j - 1].rgbtRed + image[i][j + 1].rgbtRed +
                                                  image[i + 1][j].rgbtRed + image[i + 1][j + 1].rgbtRed + image[i + 1][j - 1].rgbtRed) / 6.0);

                image_copy[i][j].rgbtBlue = round((image[i][j].rgbtBlue + image[i][j - 1].rgbtBlue + image[i][j + 1].rgbtBlue +
                                                   image[i + 1][j].rgbtBlue + image[i + 1][j + 1].rgbtBlue + image[i + 1][j - 1].rgbtBlue) / 6.0);

                image_copy[i][j].rgbtGreen = round((image[i][j].rgbtGreen + image[i][j - 1].rgbtGreen + image[i][j + 1].rgbtGreen +
                                                    image[i + 1][j].rgbtGreen + image[i + 1][j + 1].rgbtGreen + image[i + 1][j - 1].rgbtGreen) / 6.0);
            }

            // then check if bottom row
            else if (i == height - 1 && j < width - 1)
            {
                image_copy[i][j].rgbtRed = round((image[i][j].rgbtRed + image[i][j - 1].rgbtRed + image[i][j + 1].rgbtRed +
                                                  image[i - 1][j].rgbtRed + image[i - 1][j + 1].rgbtRed + image[i - 1][j - 1].rgbtRed) / 6.0);

                image_copy[i][j].rgbtBlue = round((image[i][j].rgbtBlue + image[i][j - 1].rgbtBlue + image[i][j + 1].rgbtBlue +
                                                   image[i - 1][j].rgbtBlue + image[i - 1][j + 1].rgbtBlue + image[i - 1][j - 1].rgbtBlue) / 6.0);

                image_copy[i][j].rgbtGreen = round((image[i][j].rgbtGreen + image[i][j - 1].rgbtGreen + image[i][j + 1].rgbtGreen +
                                                    image[i - 1][j].rgbtGreen + image[i - 1][j + 1].rgbtGreen + image[i - 1][j - 1].rgbtGreen) / 6.0);

            }

            // then check left side
            else if (j == 0)
            {
                image_copy[i][j].rgbtRed = round((image[i][j].rgbtRed + image[i - 1][j].rgbtRed + image[i - 1][j + 1].rgbtRed +
                                                  image[i][j + 1].rgbtRed + image[i + 1][j].rgbtRed + image[i + 1][j + 1].rgbtRed) / 6.0);

                image_copy[i][j].rgbtGreen = round((image[i][j].rgbtGreen + image[i - 1][j].rgbtGreen + image[i - 1][j + 1].rgbtGreen +
                                                    image[i][j + 1].rgbtGreen + image[i + 1][j].rgbtGreen + image[i + 1][j + 1].rgbtGreen) / 6.0);

                image_copy[i][j].rgbtBlue = round((image[i][j].rgbtBlue + image[i - 1][j].rgbtBlue + image[i - 1][j + 1].rgbtBlue +
                                                   image[i][j + 1].rgbtBlue + image[i + 1][j].rgbtBlue + image[i + 1][j + 1].rgbtBlue) / 6.0);
            }

            // else if right side
            else if (j == width - 1)
            {
                image_copy[i][j].rgbtRed = round((image[i][j].rgbtRed + image[i - 1][j].rgbtRed + image[i - 1][j - 1].rgbtRed +
                                                  image[i][j - 1].rgbtRed + image[i + 1][j].rgbtRed + image[i + 1][j - 1].rgbtRed) / 6.0);

                image_copy[i][j].rgbtGreen = round((image[i][j].rgbtGreen + image[i - 1][j].rgbtGreen + image[i - 1][j - 1].rgbtGreen +
                                                    image[i][j - 1].rgbtGreen + image[i + 1][j].rgbtGreen + image[i + 1][j - 1].rgbtGreen) / 6.0);

                image_copy[i][j].rgbtBlue = round((image[i][j].rgbtBlue + image[i - 1][j].rgbtBlue + image[i - 1][j - 1].rgbtBlue +
                                                   image[i][j - 1].rgbtBlue + image[i + 1][j].rgbtBlue + image[i + 1][j - 1].rgbtBlue) / 6.0);
            }

            // else grab surrounding pixels like normal
            else if (i < height && j < width)
            {
                image_copy[i][j].rgbtRed = round((image[i][j].rgbtRed + image[i][j + 1].rgbtRed + image[i][j - 1].rgbtRed +
                                                  image[i - 1][j].rgbtRed + image[i - 1][j - 1].rgbtRed + image[i - 1][j + 1].rgbtRed +
                                                  image[i + 1][j].rgbtRed + image[i + 1][j - 1].rgbtRed + image[i + 1][j + 1].rgbtRed) / 9.0);

                image_copy[i][j].rgbtBlue = round((image[i][j].rgbtBlue + image[i][j + 1].rgbtBlue + image[i][j - 1].rgbtBlue +
                                                   image[i - 1][j].rgbtBlue + image[i - 1][j - 1].rgbtBlue + image[i - 1][j + 1].rgbtBlue +
                                                   image[i + 1][j].rgbtBlue + image[i + 1][j - 1].rgbtBlue + image[i + 1][j + 1].rgbtBlue) / 9.0);

                image_copy[i][j].rgbtGreen = round((image[i][j].rgbtGreen + image[i][j + 1].rgbtGreen + image[i][j - 1].rgbtGreen +
                                                    image[i - 1][j].rgbtGreen + image[i - 1][j - 1].rgbtGreen + image[i - 1][j + 1].rgbtGreen +
                                                    image[i + 1][j].rgbtGreen + image[i + 1][j - 1].rgbtGreen + image[i + 1][j + 1].rgbtGreen) / 9.0);
            }
        }
    }
    // then we change image to image_copy
    // for each row
    for (int i = 0; i < height; i++)
    {
        // for each value in row
        for (int j = 0; j < width; j++)
        {
            image[i][j] = image_copy[i][j];
        }
    }
}



// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    // copy
    RGBTRIPLE image_copy[height][width];

    // for each row
    for (int i = 0; i < height; i++)
    {
        // for each element
        for (int j = 0; j < width; j++)
        {
            // if left corner
            if (i == 0 && j == 0)
            {
                int gxRed = (image[i][j + 1].rgbtRed * 2) + (image[i + 1][j + 1].rgbtRed);
                int gxGreen = (image[i][j + 1].rgbtGreen * 2) + (image[i + 1][j + 1].rgbtGreen);
                int gxBlue = (image[i][j + 1].rgbtBlue * 2) + (image[i + 1][j + 1].rgbtBlue);

                int gyRed = (image[i + 1][j].rgbtRed * 2) + (image[i + 1][j + 1].rgbtRed);
                int gyGreen = (image[i + 1][j].rgbtGreen * 2) + (image[i + 1][j + 1].rgbtGreen);
                int gyBlue = (image[i + 1][j].rgbtBlue * 2) + (image[i + 1][j + 1].rgbtBlue);


                // Red
                if (sqrt((gxRed * gxRed) + (gyRed * gyRed)) > 255)
                {
                    image_copy[i][j].rgbtRed = 255;
                }
                else
                {
                    image_copy[i][j].rgbtRed = round(sqrt((gxRed * gxRed) + (gyRed * gyRed)));
                }

                // Green
                if (sqrt((gxGreen * gxGreen) + (gyGreen * gyGreen)) > 255)
                {
                    image_copy[i][j].rgbtGreen = 255;
                }
                else
                {
                    image_copy[i][j].rgbtGreen = round(sqrt((gxGreen * gxGreen) + (gyGreen * gyGreen)));
                }

                // Blue
                if (sqrt((gxBlue * gxBlue) + (gyBlue * gyBlue)) > 255)
                {
                    image_copy[i][j].rgbtBlue = 255;
                }
                else
                {
                    image_copy[i][j].rgbtBlue = round(sqrt((gxBlue * gxBlue) + (gyBlue * gyBlue)));
                }
            }
            // else if right corner
            else if (i == 0 && j == width - 1)
            {
                int gxRed = (image[i][j - 1].rgbtRed * -2) + (image[i + 1][j - 1].rgbtRed * -1);
                int gxGreen = (image[i][j - 1].rgbtGreen * -2) + (image[i + 1][j - 1].rgbtGreen * -1);
                int gxBlue = (image[i][j - 1].rgbtBlue * -2) + (image[i + 1][j - 1].rgbtBlue * -1);

                int gyRed = (image[i + 1][j - 1].rgbtRed) + (image[i + 1][j].rgbtRed * 2);
                int gyGreen = (image[i + 1][j - 1].rgbtGreen) + (image[i + 1][j].rgbtGreen * 2);
                int gyBlue = (image[i + 1][j - 1].rgbtBlue) + (image[i + 1][j].rgbtBlue * 2);


                // Red
                if (sqrt((gxRed * gxRed) + (gyRed * gyRed)) > 255)
                {
                    image_copy[i][j].rgbtRed = 255;
                }
                else
                {
                    image_copy[i][j].rgbtRed = round(sqrt((gxRed * gxRed) + (gyRed * gyRed)));
                }

                // Green
                if (sqrt((gxGreen * gxGreen) + (gyGreen * gyGreen)) > 255)
                {
                    image_copy[i][j].rgbtGreen = 255;
                }
                else
                {
                    image_copy[i][j].rgbtGreen = round(sqrt((gxGreen * gxGreen) + (gyGreen * gyGreen)));
                }

                // Blue
                if (sqrt((gxBlue * gxBlue) + (gyBlue * gyBlue)) > 255)
                {
                    image_copy[i][j].rgbtBlue = 255;
                }
                else
                {
                    image_copy[i][j].rgbtBlue = round(sqrt((gxBlue * gxBlue) + (gyBlue * gyBlue)));
                }
            }
            // else if bottom left corner
            else if (i == height - 1 && j == 0)
            {
                int gxRed = (image[i][j + 1].rgbtRed * 2) + (image[i - 1][j + 1].rgbtRed);
                int gxGreen = (image[i][j + 1].rgbtGreen * 2) + (image[i - 1][j + 1].rgbtGreen);
                int gxBlue = (image[i][j + 1].rgbtBlue * 2) + (image[i - 1][j + 1].rgbtBlue);

                int gyRed = (image[i - 1][j + 1].rgbtRed * -1) + (image[i - 1][j].rgbtRed * -2);
                int gyGreen = (image[i - 1][j + 1].rgbtGreen * -1) + (image[i - 1][j].rgbtGreen * -2);
                int gyBlue = (image[i - 1][j + 1].rgbtBlue * -1) + (image[i - 1][j].rgbtBlue * -2);


                // Red
                if (sqrt((gxRed * gxRed) + (gyRed * gyRed)) > 255)
                {
                    image_copy[i][j].rgbtRed = 255;
                }
                else
                {
                    image_copy[i][j].rgbtRed = round(sqrt((gxRed * gxRed) + (gyRed * gyRed)));
                }

                // Green
                if (sqrt((gxGreen * gxGreen) + (gyGreen * gyGreen)) > 255)
                {
                    image_copy[i][j].rgbtGreen = 255;
                }
                else
                {
                    image_copy[i][j].rgbtGreen = round(sqrt((gxGreen * gxGreen) + (gyGreen * gyGreen)));
                }

                // Blue
                if (sqrt((gxBlue * gxBlue) + (gyBlue * gyBlue)) > 255)
                {
                    image_copy[i][j].rgbtBlue = 255;
                }
                else
                {
                    image_copy[i][j].rgbtBlue = round(sqrt((gxBlue * gxBlue) + (gyBlue * gyBlue)));
                }
            }
            // else if bottom right corner
            else if (i == height - 1 && j == width - 1)
            {
                int gxRed = (image[i - 1][j - 1].rgbtRed * -1) + (image[i][j - 1].rgbtRed * -2);
                int gxGreen = (image[i - 1][j - 1].rgbtGreen * -1) + (image[i][j - 1].rgbtGreen * -2);
                int gxBlue = (image[i - 1][j - 1].rgbtBlue * -1) + (image[i][j - 1].rgbtBlue * -2);

                int gyRed = (image[i - 1][j].rgbtRed * -2) + (image[i - 1][j - 1].rgbtRed * -1);
                int gyGreen = (image[i - 1][j].rgbtGreen * -2) + (image[i - 1][j - 1].rgbtGreen * -1);
                int gyBlue = (image[i - 1][j].rgbtBlue * -2) + (image[i - 1][j - 1].rgbtBlue * -1);


                // Red
                if (sqrt((gxRed * gxRed) + (gyRed * gyRed)) > 255)
                {
                    image_copy[i][j].rgbtRed = 255;
                }
                else
                {
                    image_copy[i][j].rgbtRed = round(sqrt((gxRed * gxRed) + (gyRed * gyRed)));
                }

                // Green
                if (sqrt((gxGreen * gxGreen) + (gyGreen * gyGreen)) > 255)
                {
                    image_copy[i][j].rgbtGreen = 255;
                }
                else
                {
                    image_copy[i][j].rgbtGreen = round(sqrt((gxGreen * gxGreen) + (gyGreen * gyGreen)));
                }

                // Blue
                if (sqrt((gxBlue * gxBlue) + (gyBlue * gyBlue)) > 255)
                {
                    image_copy[i][j].rgbtBlue = 255;
                }
                else
                {
                    image_copy[i][j].rgbtBlue = round(sqrt((gxBlue * gxBlue) + (gyBlue * gyBlue)));
                }
            }
            // else if top row
            else if (i == 0 && j <= width - 1)
            {
                int gxRed = (image[i][j + 1].rgbtRed * 2)  + (image[i][j - 1].rgbtRed * -2) +
                            (image[i + 1][j + 1].rgbtRed) + (image[i + 1][j - 1].rgbtRed * -1);

                int gxGreen = (image[i][j + 1].rgbtGreen * 2)  + (image[i][j - 1].rgbtGreen * -2) +
                              (image[i + 1][j + 1].rgbtGreen) + (image[i + 1][j - 1].rgbtGreen * -1);

                int gxBlue = (image[i][j + 1].rgbtBlue * 2)  + (image[i][j - 1].rgbtBlue * -2) +
                             (image[i + 1][j + 1].rgbtBlue) + (image[i + 1][j - 1].rgbtBlue * -1);

                int gyRed = (image[i + 1][j].rgbtRed * 2) + (image[i + 1][j + 1].rgbtRed) +
                            (image[i + 1][j - 1].rgbtRed);

                int gyGreen = (image[i + 1][j].rgbtGreen * 2) + (image[i + 1][j + 1].rgbtGreen) +
                              (image[i + 1][j - 1].rgbtGreen);

                int gyBlue = (image[i + 1][j].rgbtBlue * 2) + (image[i + 1][j + 1].rgbtBlue) +
                             (image[i + 1][j - 1].rgbtBlue);


                // Red
                if (sqrt((gxRed * gxRed) + (gyRed * gyRed)) > 255)
                {
                    image_copy[i][j].rgbtRed = 255;
                }
                else
                {
                    image_copy[i][j].rgbtRed = round(sqrt((gxRed * gxRed) + (gyRed * gyRed)));
                }

                // Green
                if (sqrt((gxGreen * gxGreen) + (gyGreen * gyGreen)) > 255)
                {
                    image_copy[i][j].rgbtGreen = 255;
                }
                else
                {
                    image_copy[i][j].rgbtGreen = round(sqrt((gxGreen * gxGreen) + (gyGreen * gyGreen)));
                }

                // Blue
                if (sqrt((gxBlue * gxBlue) + (gyBlue * gyBlue)) > 255)
                {
                    image_copy[i][j].rgbtBlue = 255;
                }
                else
                {
                    image_copy[i][j].rgbtBlue = round(sqrt((gxBlue * gxBlue) + (gyBlue * gyBlue)));
                }
            }
            // else if bottom row
            else if (i == height - 1 && j <= width - 1)
            {
                int gxRed = (image[i][j + 1].rgbtRed * 2)  + (image[i][j - 1].rgbtRed * -2) +
                            (image[i - 1][j + 1].rgbtRed * 1) + (image[i - 1][j - 1].rgbtRed * -1);

                int gxGreen = (image[i][j + 1].rgbtGreen * 2)  + (image[i][j - 1].rgbtGreen * -2) +
                              (image[i - 1][j + 1].rgbtGreen * 1) + (image[i - 1][j - 1].rgbtGreen * -1);

                int gxBlue = (image[i][j + 1].rgbtBlue * 2)  + (image[i][j - 1].rgbtBlue * -2) +
                             (image[i - 1][j + 1].rgbtBlue * 1) + (image[i - 1][j - 1].rgbtBlue * -1);


                int gyRed = (image[i - 1][j].rgbtRed * -2) + (image[i - 1][j + 1].rgbtRed * -1) +
                            (image[i - 1][j - 1].rgbtRed * -1);

                int gyGreen = (image[i - 1][j].rgbtGreen * -2) + (image[i - 1][j + 1].rgbtGreen * -1) +
                              (image[i - 1][j - 1].rgbtGreen * -1);

                int gyBlue = (image[i - 1][j].rgbtBlue * -2) + (image[i - 1][j + 1].rgbtBlue * -1) +
                             (image[i - 1][j - 1].rgbtBlue * -1);


                //Red
                if (sqrt((gxRed * gxRed) + (gyRed * gyRed)) > 255)
                {
                    image_copy[i][j].rgbtRed = 255;
                }
                else
                {
                    image_copy[i][j].rgbtRed = round(sqrt((gxRed * gxRed) + (gyRed * gyRed)));
                }

                // Green
                if (sqrt((gxGreen * gxGreen) + (gyGreen * gyGreen)) > 255)
                {
                    image_copy[i][j].rgbtGreen = 255;
                }
                else
                {
                    image_copy[i][j].rgbtGreen = round(sqrt((gxGreen * gxGreen) + (gyGreen * gyGreen)));
                }

                // Blue
                if (sqrt((gxBlue * gxBlue) + (gyBlue * gyBlue)) > 255)
                {
                    image_copy[i][j].rgbtBlue = 255;
                }
                else
                {
                    image_copy[i][j].rgbtBlue = round(sqrt((gxBlue * gxBlue) + (gyBlue * gyBlue)));
                }
            }

            // else if left side
            else if (j == 0)
            {
                int gxRed = (image[i][j + 1].rgbtRed * 2) + (image[i + 1][j + 1].rgbtRed) + (image[i - 1][j + 1].rgbtRed);
                int gxGreen = (image[i][j + 1].rgbtGreen * 2) + (image[i + 1][j + 1].rgbtGreen) + (image[i - 1][j + 1].rgbtGreen);
                int gxBlue = (image[i][j + 1].rgbtBlue * 2) + (image[i + 1][j + 1].rgbtBlue) + (image[i - 1][j + 1].rgbtBlue);

                int gyRed = (image[i - 1][j].rgbtRed * -2) + (image[i - 1][j + 1].rgbtRed * -1) + (image[i + 1][j].rgbtRed * 2) +
                            (image[i + 1][j + 1].rgbtRed);

                int gyGreen = (image[i - 1][j].rgbtGreen * -2) + (image[i - 1][j + 1].rgbtGreen * -1) + (image[i + 1][j].rgbtGreen * 2) +
                              (image[i + 1][j + 1].rgbtGreen);

                int gyBlue = (image[i - 1][j].rgbtBlue * -2) + (image[i - 1][j + 1].rgbtBlue * -1) + (image[i + 1][j].rgbtBlue * 2) +
                             (image[i + 1][j + 1].rgbtBlue);


                //Red
                if (sqrt((gxRed * gxRed) + (gyRed * gyRed)) > 255)
                {
                    image_copy[i][j].rgbtRed = 255;
                }
                else
                {
                    image_copy[i][j].rgbtRed = round(sqrt((gxRed * gxRed) + (gyRed * gyRed)));
                }

                // Green
                if (sqrt((gxGreen * gxGreen) + (gyGreen * gyGreen)) > 255)
                {
                    image_copy[i][j].rgbtGreen = 255;
                }
                else
                {
                    image_copy[i][j].rgbtGreen = round(sqrt((gxGreen * gxGreen) + (gyGreen * gyGreen)));
                }

                // Blue
                if (sqrt((gxBlue * gxBlue) + (gyBlue * gyBlue)) > 255)
                {
                    image_copy[i][j].rgbtBlue = 255;
                }
                else
                {
                    image_copy[i][j].rgbtBlue = round(sqrt((gxBlue * gxBlue) + (gyBlue * gyBlue)));
                }
            }
            // else if right side
            else if (j == width - 1)
            {
                int gxRed = (image[i][j - 1].rgbtRed * -2) + (image[i + 1][j - 1].rgbtRed * -1) + (image[i - 1][j - 1].rgbtRed * -1);
                int gxGreen = (image[i][j - 1].rgbtGreen * -2) + (image[i + 1][j - 1].rgbtGreen * -1) + (image[i - 1][j - 1].rgbtGreen * -1);
                int gxBlue = (image[i][j - 1].rgbtBlue * -2) + (image[i + 1][j - 1].rgbtBlue * -1) + (image[i - 1][j - 1].rgbtBlue * -1);

                int gyRed = (image[i - 1][j].rgbtRed * -2) + (image[i - 1][j - 1].rgbtRed * -1) + (image[i + 1][j].rgbtRed * 2) +
                            (image[i + 1][j - 1].rgbtRed);

                int gyGreen = (image[i - 1][j].rgbtGreen * -2) + (image[i - 1][j - 1].rgbtGreen * -1) +
                              (image[i + 1][j].rgbtGreen * 2) + (image[i + 1][j - 1].rgbtGreen);

                int gyBlue = (image[i - 1][j].rgbtBlue * -2) + (image[i - 1][j - 1].rgbtBlue * -1) + (image[i + 1][j].rgbtBlue * 2) +
                             (image[i + 1][j - 1].rgbtBlue);

                //Red
                if (sqrt((gxRed * gxRed) + (gyRed * gyRed)) > 255)
                {
                    image_copy[i][j].rgbtRed = 255;
                }
                else
                {
                    image_copy[i][j].rgbtRed = round(sqrt((gxRed * gxRed) + (gyRed * gyRed)));
                }

                // Green
                if (sqrt((gxGreen * gxGreen) + (gyGreen * gyGreen)) > 255)
                {
                    image_copy[i][j].rgbtGreen = 255;
                }
                else
                {
                    image_copy[i][j].rgbtGreen = round(sqrt((gxGreen * gxGreen) + (gyGreen * gyGreen)));
                }

                // Blue
                if (sqrt((gxBlue * gxBlue) + (gyBlue * gyBlue)) > 255)
                {
                    image_copy[i][j].rgbtBlue = 255;
                }
                else
                {
                    image_copy[i][j].rgbtBlue = round(sqrt((gxBlue * gxBlue) + (gyBlue * gyBlue)));
                }
            }
            // else everything else
            else
            {
                // Red
                int gxr = image[i + 1][j + 1].rgbtRed + (image[i][j + 1].rgbtRed * 2) + image[i - 1][j + 1].rgbtRed +
                          (-1 * image[i + 1][j - 1].rgbtRed) + (image[i][j - 1].rgbtRed * -2) + (-1 * image[i - 1][j - 1].rgbtRed);

                int gyr = (image[i + 1][j].rgbtRed * 2) + image[i + 1][j + 1].rgbtRed + image[i + 1][j - 1].rgbtRed +
                          (image[i - 1][j].rgbtRed * -2) + (-1 * image[i - 1][j - 1].rgbtRed) + (-1 * image[i - 1][j + 1].rgbtRed);

                if (sqrt((gxr * gxr) + (gyr * gyr)) > 255)
                {
                    image_copy[i][j].rgbtRed = 255;
                }
                else
                {
                    image_copy[i][j].rgbtRed = round(sqrt((gxr * gxr) + (gyr * gyr)));
                }

                // Green
                int gxg = image[i + 1][j + 1].rgbtGreen + (image[i][j + 1].rgbtGreen * 2) + image[i - 1][j + 1].rgbtGreen +
                          (-1 * image[i + 1][j - 1].rgbtGreen) + (image[i][j - 1].rgbtGreen * -2) + (-1 * image[i - 1][j - 1].rgbtGreen);

                int gyg = (image[i + 1][j].rgbtGreen * 2) + image[i + 1][j + 1].rgbtGreen + image[i + 1][j - 1].rgbtGreen +
                          (image[i - 1][j].rgbtGreen * -2) + (-1 * image[i - 1][j - 1].rgbtGreen) + (-1 * image[i - 1][j + 1].rgbtGreen);

                if (sqrt((gxg * gxg) + (gyg * gyg)) > 255)
                {
                    image_copy[i][j].rgbtGreen = 255;
                }
                else
                {
                    image_copy[i][j].rgbtGreen = round(sqrt((gxg * gxg) + (gyg * gyg)));
                }

                // Blue
                int gxb = image[i + 1][j + 1].rgbtBlue + (image[i][j + 1].rgbtBlue * 2) + image[i - 1][j + 1].rgbtBlue +
                          (-1 * image[i + 1][j - 1].rgbtBlue) + (image[i][j - 1].rgbtBlue * -2) + (-1 * image[i - 1][j - 1].rgbtBlue);

                int gyb = (image[i + 1][j].rgbtBlue * 2) + image[i + 1][j + 1].rgbtBlue + image[i + 1][j - 1].rgbtBlue +
                          (image[i - 1][j].rgbtBlue * -2) + (-1 * image[i - 1][j - 1].rgbtBlue) + (-1 * image[i - 1][j + 1].rgbtBlue);

                if (sqrt((gxb * gxb) + (gyb * gyb)) > 255)
                {
                    image_copy[i][j].rgbtBlue = 255;
                }
                else
                {
                    image_copy[i][j].rgbtBlue = round(sqrt((gxb * gxb) + (gyb * gyb)));
                }



            }
        }
    }
    // then we change image to image_copy
    // for each row
    for (int i = 0; i < height; i++)
    {
        // for each value in row
        for (int j = 0; j < width; j++)
        {
            image[i][j] = image_copy[i][j];
        }
    }
}
