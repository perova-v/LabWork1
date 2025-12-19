/*
 * Perova Varvara
 * st141846@student.spbu.ru
 * LabWork1
 */

#include <iostream>
#include "BmpImage.h"

int main(int argc, char* argv[])
{
    try
    {
        if (argc < 2)
        {
            std::cout << "Usage: ./lab1 <input_file.bmp>" << std::endl;
            return 1;
        }

        std::string inputFile = argv[1];

        BmpImage img;
        img.load(inputFile);
        std::cout << "Image loaded. Size: " << img.getWidth() << "x" << img.getHeight() << std::endl;

        BmpImage imgCW = img;
        imgCW.rotate90CW();
        imgCW.save("rotated_cw.bmp");
        std::cout << "Saved rotated_cw.bmp" << std::endl;

        BmpImage imgCCW = img;
        imgCCW.rotate90CCW();
        imgCCW.save("rotated_ccw.bmp");
        std::cout << "Saved rotated_ccw.bmp" << std::endl;

        BmpImage imgGauss = img;
        imgGauss.applyGaussianFilter();
        imgGauss.save("gaussian.bmp");
        std::cout << "Saved gaussian.bmp" << std::endl;

    }
    catch (const std::exception& e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}
