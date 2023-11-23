#define _CRT_SECURE_NO_WARNINGS
#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION

#include "image_process.h"

#include "stb_image.h"
#include "stb_image_write.h"

Image_process::Image_process() {}

void Image_process::applyLaplaceOperator(Image & image)
{
    int w = image.get_m_width();
    int h = image.get_m_height();
    int c = image.get_m_nChannels();

    unsigned char* output = new unsigned char[w * h];
    for (int i = 0; i < w * h; i++) {
        output[i] = image.get_image_data()[i];
    }

    int laplacianMatrix[3][3] = {
        {0,  1, 0},
        {1, -4, 1},
        {0,  1, 0}
    };

    for (int y = 1; y < h - 1; y++) {
        for (int x = 1; x < w - 1; x++) {
            int sum = 0;

            for (int i = -1; i <= 1; i++) {
                for (int j = -1; j <= 1; j++) {
                    int pixel = image.get_image_data()[(y + i) * w + (x + j)];
                    sum += pixel * laplacianMatrix[i + 1][j + 1];
                }
            }
        
            output[y * w + x] = std::max(0, std::min(255, sum));
        }
    }

    stbi_write_jpg("laplace_operator_result.jpg", w, h, 1, output, 100);

    delete[] output;
}

void Image_process::applyRobertsOperator(Image & image)
{
    int w = image.get_m_width();
    int h = image.get_m_height();
    
    unsigned char* output = new unsigned char[w * h];
    for (int i = 0; i < w * h; i++) {
        output[i] = image.get_image_data()[i];
    }

    int robertsMatrixX[2][2] = {
        {1, 0},
        {0, -1}
    };
    int robertsMatrixY[2][2] = {
        {0, 1},
        {-1, 0}
    };

    for (int y = 0; y < h - 1; y++) {
        for (int x = 0; x < w - 1; x++) {
            int sumX = 0;
            int sumY = 0;

            for (int i = 0; i < 2; i++) {
                for (int j = 0; j < 2; j++) {
                    int pixel = image.get_image_data()[(y + i) * w + (x + j)];
                    sumX += pixel * robertsMatrixX[i][j];
                    sumY += pixel * robertsMatrixY[i][j];
                }
            }

            output[y * w + x] = std::min(255, (int) std::sqrt(sumX * sumX + sumY * sumY));
        }
    }

    stbi_write_jpg("roberts_operator_result.jpg", w, h, 1, output, 100);

    delete[] output;
}

void Image_process::applySobelOperator(Image & image)
{
    int w = image.get_m_width();
    int h = image.get_m_height();

    unsigned char* output = new unsigned char[w * h];
    for (int i = 0; i < w * h; i++) {
        output[i] = image.get_image_data()[i];
    }

    int sobelMatrixX[3][3] = {
        {-1, 0, 1},
        {-2, 0, 2},
        {-1, 0, 1}
    };
    int sobelMatrixY[3][3] = {
        {-1, -2, -1},
        {0, 0, 0},
        {1, 2, 1}
    };

    for (int y = 1; y < h - 1; y++) {
        for (int x = 1; x < w - 1; x++) {
            int sumX = 0;
            int sumY = 0;

            for (int i = -1; i <= 1; i++) {
                for (int j = -1; j <= 1; j++) {
                    int pixel = image.get_image_data()[(y + i) * w + (x + j)];
                    sumX += pixel * sobelMatrixX[i + 1][j + 1];
                    sumY += pixel * sobelMatrixY[i + 1][j + 1];
                }
            }

            output[y * w + x] = std::min(255, (int) std::sqrt(sumX * sumX + sumY * sumY));
        }
    }

    stbi_write_jpg("sobel_operator_result.jpg", w, h, 1, output, 100);

    delete[] output;
}
