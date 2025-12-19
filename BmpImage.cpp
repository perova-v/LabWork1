/*
 * Perova Varvara
 * st141846@student.spbu.ru
 * LabWork1
 */

#include "BmpImage.h"
#include <fstream>
#include <stdexcept>
#include <iostream>
#include <algorithm>
#include <cmath>

BmpImage::BmpImage()
{
    fileHeader = {};
    infoHeader = {};
}

BmpImage::BmpImage(int w, int h, const std::vector<Pixel>& p)
{
    infoHeader.biWidth = w;
    infoHeader.biHeight = h;
    pixels = p;
}

int BmpImage::getWidth() const
{
    return infoHeader.biWidth;
}
int BmpImage::getHeight() const
{
    return infoHeader.biHeight;
}

int BmpImage::getPadding(int width) const
{
    return (ROW_ALIGNMENT - (width * sizeof(Pixel)) % ROW_ALIGNMENT) % ROW_ALIGNMENT;
}

void BmpImage::load(const std::string& filename)
{
    std::ifstream in(filename, std::ios::binary);
    if (!in) throw std::runtime_error("File not found");

    in.read(reinterpret_cast<char*>(&fileHeader), sizeof(fileHeader));
    if (fileHeader.bfType != BMP_SIGNATURE) throw std::runtime_error("Not a BMP");

    in.read(reinterpret_cast<char*>(&infoHeader), sizeof(infoHeader));
    if (infoHeader.biBitCount != BITS_PER_PIXEL) throw std::runtime_error("Only 24-bit supported");

    in.seekg(fileHeader.bfOffBits, std::ios::beg);

    int w = infoHeader.biWidth;
    int h = std::abs(infoHeader.biHeight);
    int padding = getPadding(w);

    pixels.resize(w * h);

    for (int y = 0; y < h; ++y)
    {
        for (int x = 0; x < w; ++x)
        {
            in.read(reinterpret_cast<char*>(&pixels[y * w + x]), sizeof(Pixel));
        }
        in.ignore(padding);
    }
}

void BmpImage::save(const std::string& filename) const
{
    std::ofstream out(filename, std::ios::binary);
    if (!out) throw std::runtime_error("Cannot create file");

    int w = infoHeader.biWidth;
    int h = std::abs(infoHeader.biHeight);
    int padding = getPadding(w);

    BitmapFileHeader outFh;
    BitmapInfoHeader outIh = infoHeader;

    outFh.bfType = BMP_SIGNATURE;
    outFh.bfReserved1 = 0;
    outFh.bfReserved2 = 0;
    outFh.bfOffBits = sizeof(BitmapFileHeader) + sizeof(BitmapInfoHeader);

    uint32_t dataSize = (w * sizeof(Pixel) + padding) * h;
    outFh.bfSize = outFh.bfOffBits + dataSize;

    outIh.biSizeImage = dataSize;
    outIh.biSize = INFO_HEADER_SIZE;
    outIh.biPlanes = 1;
    outIh.biBitCount = BITS_PER_PIXEL;
    outIh.biCompression = NO_COMPRESSION;

    out.write(reinterpret_cast<const char*>(&outFh), sizeof(outFh));
    out.write(reinterpret_cast<const char*>(&outIh), sizeof(outIh));

    uint8_t padByte = 0;
    for (int y = 0; y < h; ++y)
    {
        for (int x = 0; x < w; ++x)
        {
            out.write(reinterpret_cast<const char*>(&pixels[y * w + x]), sizeof(Pixel));
        }
        for (int k = 0; k < padding; ++k)
        {
            out.write(reinterpret_cast<const char*>(&padByte), 1);
        }
    }
}

void BmpImage::rotate90CW()
{
    int w = infoHeader.biWidth;
    int h = infoHeader.biHeight;
    std::vector<Pixel> newPixels(w * h);

    for (int y = 0; y < h; ++y)
    {
        for (int x = 0; x < w; ++x)
        {
            int newX = y;
            int newY = w - 1 - x;
            newPixels[newY * h + newX] = pixels[y * w + x];
        }
    }

    pixels = newPixels;
    std::swap(infoHeader.biWidth, infoHeader.biHeight);
}

void BmpImage::rotate90CCW()
{
    int w = infoHeader.biWidth;
    int h = infoHeader.biHeight;
    std::vector<Pixel> newPixels(w * h);

    for (int y = 0; y < h; ++y)
    {
        for (int x = 0; x < w; ++x)
        {

            int newX = h - 1 - y;
            int newY = x;
            newPixels[newY * h + newX] = pixels[y * w + x];
        }
    }

    pixels = newPixels;
    std::swap(infoHeader.biWidth, infoHeader.biHeight);
}

void BmpImage::applyGaussianFilter()
{
    int w = infoHeader.biWidth;
    int h = infoHeader.biHeight;
    std::vector<Pixel> result = pixels;

    const double kernel[3][3] =
    {
        {0.075, 0.124, 0.075},
        {0.124, 0.204, 0.124},
        {0.075, 0.124, 0.075}
    };

    for (int y = 0; y < h; ++y)
    {
        for (int x = 0; x < w; ++x)
        {
            double r = 0, g = 0, b = 0;

            for (int ky = -1; ky <= 1; ++ky)
            {
                for (int kx = -1; kx <= 1; ++kx)
                {
                    int py = std::clamp(y + ky, 0, h - 1);
                    int px = std::clamp(x + kx, 0, w - 1);

                    Pixel p = pixels[py * w + px];
                    double kVal = kernel[ky + 1][kx + 1];

                    b += p.b * kVal;
                    g += p.g * kVal;
                    r += p.r * kVal;
                }
            }

            result[y * w + x].b = static_cast<uint8_t>(std::clamp(b, 0.0, 255.0));
            result[y * w + x].g = static_cast<uint8_t>(std::clamp(g, 0.0, 255.0));
            result[y * w + x].r = static_cast<uint8_t>(std::clamp(r, 0.0, 255.0));
        }
    }
    pixels = result;
}

Pixel BmpImage::getPixel(int x, int y) const
{
    if (x < 0 || x >= infoHeader.biWidth || y < 0 || y >= infoHeader.biHeight)
        return {0,0,0};
    return pixels[y * infoHeader.biWidth + x];
}
