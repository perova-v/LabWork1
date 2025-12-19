/*
 * Perova Varvara
 * st141846@student.spbu.ru
 * LabWork1
 */

#include <iostream>
#include "BmpImage.h"
#include <filesystem>

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

        std::filesystem::path path(inputFile);
        std::string baseName = path.stem().string();

        BmpImage img;
        img.load(inputFile);
        std::cout << "Image loaded. Size: " << img.getWidth() << "x" << img.getHeight() << std::endl;

        BmpImage imgCW = img;
        imgCW.rotate90CW();

	std::string nameCW = baseName + "_cw.bmp";
        imgCW.save(nameCW);
        std::cout << "Saved " << nameCW << std::endl;

        BmpImage imgCCW = img;
        imgCCW.rotate90CCW();

	std::string nameCCW = baseName + "_ccw.bmp";
        imgCCW.save(nameCCW);
        std::cout << "Saved " << nameCCW << std::endl;

        BmpImage imgGauss = img;
        imgGauss.applyGaussianFilter();
	std::string nameGaussian = baseName + "_gaussian.bmp";
        imgGauss.save(nameGaussian);
        std::cout << "Saved " << nameGaussian << std::endl;

    }
    catch (const std::exception& e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}
