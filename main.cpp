#include <iostream>

#include "Image.h"
#include "Image_process.h"
using namespace std;

#include "stb_image.h"
#include "stb_image_write.h"

int main()
{
    Image image("image.jpg");
    Image_process image_process = Image_process();

    // Apply the Laplace operator and save the result.
        image_process.applyLaplaceOperator(image);
    
    // Apply the Roberts operator and save the result.
        image_process.applyRobertsOperator(image);

        // Apply the Sobel operator and save the result.
        image_process.applySobelOperator(image);

    return 0;
}