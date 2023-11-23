#pragma once
#include <iostream>
#include <vector>

class Image {
public:
    Image();
    Image(const char* filename);
    Image(int width, int height, int nChannels);
    Image(const Image& image);
    ~Image();

    void applyLaplaceOperator();
    void applyRobertsOperator();
    void applySobelOperator();

    int get_m_width();
    int get_m_height();
    int get_m_nChannels();
    unsigned char* get_image_data();

    void set_m_nChannels(int m_nChannels);
    void set_image_data(unsigned char* image_data);

private:

    int m_width;
    int m_height;
    int m_nChannels;

    int m_size;
    unsigned char* image_data;

};