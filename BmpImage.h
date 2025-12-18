#ifndef BMP_IMAGE_H
#define BMP_IMAGE_H

#include "Image.h"
#include "BmpStructures.h"
#include <vector>

class BmpImage : public Image {
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
    BitmapFileHeader fileHeader;
    BitmapInfoHeader infoHeader;
    std::vector<Pixel> pixels;

    int getPadding(int width) const;
};

#endif
