#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtRed = round((image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue)/3.0);
            image[i][j].rgbtGreen = image[i][j].rgbtRed;
            image[i][j].rgbtBlue = image[i][j].rgbtRed;
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
            // 原始像素值
            int originalRed = image[i][j].rgbtRed;
            int originalGreen = image[i][j].rgbtGreen;
            int originalBlue = image[i][j].rgbtBlue;

            // 计算sepia值
            int sepiaRed = round(.393f * originalRed + .769f * originalGreen + .189f * originalBlue);
            int sepiaGreen = round(.349f * originalRed + .686f * originalGreen + .168f * originalBlue);
            int sepiaBlue = round(.272f * originalRed + .534f * originalGreen + .131f * originalBlue);

            // 钳位到0-255范围
            image[i][j].rgbtRed = (sepiaRed > 255) ? 255 : (sepiaRed < 0) ? 0 : sepiaRed;
            image[i][j].rgbtGreen = (sepiaGreen > 255) ? 255 : (sepiaGreen < 0) ? 0 : sepiaGreen;
            image[i][j].rgbtBlue = (sepiaBlue > 255) ? 255 : (sepiaBlue < 0) ? 0 : sepiaBlue;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < (round)(width/2); j++)
        {
            int tmp;
            tmp = image[i][j].rgbtRed;
            image[i][j].rgbtRed = image[i][width - j - 1].rgbtRed;
            image[i][width - j - 1].rgbtRed = tmp;

            int tmp1;
            tmp1 = image[i][j].rgbtGreen;
            image[i][j].rgbtGreen = image[i][width - j - 1].rgbtGreen;
            image[i][width - j - 1].rgbtGreen = tmp1;

            int tmp2;
            tmp2 = image[i][j].rgbtBlue;
            image[i][j].rgbtBlue = image[i][width -j - 1].rgbtBlue;
            image[i][width -j - 1].rgbtBlue = tmp2;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
        // 创建副本
    RGBTRIPLE copy[height][width];
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            copy[i][j] = image[i][j];
        }
    }

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            int totalRed = 0, totalGreen = 0, totalBlue = 0;
            int count = 0;

            // 遍历当前像素周围的3x3网格
            for (int di = -1; di <= 1; di++) {
                for (int dj = -1; dj <= 1; dj++) {
                    int ni = i + di;
                    int nj = j + dj;

                    // 检查是否越界
                    if (ni >= 0 && ni < height && nj >= 0 && nj < width) {
                        totalRed += copy[ni][nj].rgbtRed;
                        totalGreen += copy[ni][nj].rgbtGreen;
                        totalBlue += copy[ni][nj].rgbtBlue;
                        count++;
                    }
                }
            }

            // 计算平均值
            image[i][j].rgbtRed = round((float)totalRed / count);
            image[i][j].rgbtGreen = round((float)totalGreen / count);
            image[i][j].rgbtBlue = round((float)totalBlue / count);
        }
    }
    return;
}
