#pragma once
#include "Image.h"

class Image_process {
public:
    Image_process();
    void applyLaplaceOperator(Image& image);
    void applyRobertsOperator(Image& image);
    void applySobelOperator(Image& image);
};