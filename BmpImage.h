/*
 * Perova Varvara
 * st141846@student.spbu.ru
 * LabWork1
 */

#ifndef BMP_IMAGE_H
#define BMP_IMAGE_H

#include "Image.h"
#include "BmpStructures.h"
#include <vector>

class BmpImage : public Image
{
public:
    BmpImage();
    BmpImage(int w, int h, const std::vector<Pixel>& p);

    void load(const std::string& filename) override;
    void save(const std::string& filename) const override;

    void rotate90CW() override;
    void rotate90CCW() override;
    void applyGaussianFilter() override;

    int getWidth() const;
    int getHeight() const;
    Pixel getPixel(int x, int y) const;

private:
    static const int ROW_ALIGNMENT = 4;
    static const uint16_t BMP_SIGNATURE = 0x4D42;
    static const uint16_t BITS_PER_PIXEL = 24;
    static const uint32_t NO_COMPRESSION = 0;
    static const uint32_t INFO_HEADER_SIZE = 40;

    BitmapFileHeader fileHeader;
    BitmapInfoHeader infoHeader;
    std::vector<Pixel> pixels;

    int getPadding(int width) const;
};

#endif
