#include "Image.h"
#include <iostream>

#include "stb_image.h"
#include "stb_image_write.h"

Image::Image()
{
}

Image::Image(const char *filename)
{
    image_data = stbi_load(filename, &m_width, &m_height, &m_nChannels, 0);
    std::cout << m_nChannels << std::endl;
        if (!image_data) {
            std::cerr << "Failed to load the image." << std::endl;
            exit(1);
        }
}

Image::Image(int width, int height, int nChannels)
{
    m_width = width;
    m_height = height;
    m_nChannels = nChannels;
    m_size = width * height * nChannels;
    image_data = new unsigned char[m_width * m_height * m_nChannels];
}

Image::Image(const Image &image)
{
    m_width = image.m_width;
    m_height = image.m_height;
    m_nChannels = image.m_nChannels;
    m_size = m_width * m_height * m_nChannels;
    image_data = image.image_data;
}

Image::~Image()
{
    if (image_data) {
            stbi_image_free(image_data);
        }
}

void Image::applyLaplaceOperator()
{
    unsigned char* output = new unsigned char[m_width * m_height];
    for (int i = 0; i < m_width * m_height; i++) {
        output[i] = image_data[i];
    }

    int laplacianMatrix[3][3] = {
        {0,  1, 0},
        {1, -4, 1},
        {0,  1, 0}
    };

    for (int y = 1; y < m_height - 1; y++) {
        for (int x = 1; x < m_width - 1; x++) {
            int sum = 0;

            for (int i = -1; i <= 1; i++) {
                for (int j = -1; j <= 1; j++) {
                    int pixel = image_data[(y + i) * m_width + (x + j)];
                    sum += pixel * laplacianMatrix[i + 1][j + 1];
                }
            }
            std::cout << (int) image_data[1] << std::endl;
            //std::cout << std::max(0, std::min(255, sum)) << " " << (int) image_data[y * m_width + x] << std::endl;
            output[y * m_width + x] = std::max(0, std::min(255, sum));
        }
    }

    stbi_write_png("laplacian.png", m_width, m_height, 1, output, m_width);

    delete[] output;
}

void Image::applyRobertsOperator()
{
    // if (m_nChannels != 1) {
    //         std::cerr << "Roberts operator is applicable to grayscale images only." << std::endl;
    //         return;
    //     }

    //     std::vector<unsigned char> roberts_output(m_width * m_height);

    //     for (int y = 0; y < m_height - 1; y++) {
    //         for (int x = 0; x < m_width - 1; x++) {
    //             int p1 = image_data[y * m_width + x];
    //             int p2 = image_data[y * m_width + x + 1];
    //             int p3 = image_data[(y + 1) * m_width + x];
    //             int p4 = image_data[(y + 1) * m_width + x + 1];
    //             int gx = p1 - p4;
    //             int gy = p2 - p3;
    //             int magnitude = std::sqrt(gx * gx + gy * gy);
    //             roberts_output[y * m_width + x] = static_cast<unsigned char>(std::max(0, std::min(255, magnitude)));
    //         }
    //     }

    //             stbi_write_png("result_roberts_operator.png", m_width, m_height, 1, roberts_output.data(), m_width);

}

void Image::applySobelOperator()
{
    // if (m_nChannels != 1) {
    //         std::cerr << "Sobel operator is applicable to grayscale images only." << std::endl;
    //         return;
    //     }

    //     std::vector<unsigned char> sobel_output(m_width * m_height);

    //     for (int y = 1; y < m_height - 1; y++) {
    //         for (int x = 1; x < m_width - 1; x++) {
    //             int gx = (image_data[(y - 1) * m_width + x - 1] - image_data[(y - 1) * m_width + x + 1]) +
    //                      2 * (image_data[y * m_width + x - 1] - image_data[y * m_width + x + 1]) +
    //                      (image_data[(y + 1) * m_width + x - 1] - image_data[(y + 1) * m_width + x + 1]);
    //             int gy = (image_data[(y - 1) * m_width + x - 1] - image_data[(y + 1) * m_width + x - 1]) +
    //                      2 * (image_data[(y - 1) * m_width + x] - image_data[(y + 1) * m_width + x]) +
    //                      (image_data[(y - 1) * m_width + x + 1] - image_data[(y + 1) * m_width + x + 1]);
    //             int magnitude = std::sqrt(gx * gx + gy * gy);
    //             sobel_output[y * m_width + x] = static_cast<unsigned char>(std::max(0, std::min(255, magnitude)));
    //         }
    //     }

    //     stbi_write_png("result_sobel_operator.png", m_width, m_height, 1, sobel_output.data(), m_width);
}

int Image::get_m_width()
{
    return m_width;
}

int Image::get_m_height()
{
    return m_height;
}

int Image::get_m_nChannels()
{
    return m_nChannels;
}

unsigned char *Image::get_image_data()
{
    return image_data;
}

void Image::set_m_nChannels(int m_nChannels)
{
    this->m_nChannels = m_nChannels;
}

void Image::set_image_data(unsigned char* image_data)
{
    this->image_data = image_data;
}