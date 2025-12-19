/*
 * Perova Varvara
 * st141846@student.spbu.ru
 * LabWork1
 */

#ifndef BMP_STRUCTURES_H
#define BMP_STRUCTURES_H

#include <cstdint>

#pragma pack(push, 1)

struct BitmapFileHeader
{
    uint16_t bfType;
    uint32_t bfSize;
    uint16_t bfReserved1;
    uint16_t bfReserved2;
    uint32_t bfOffBits;
};

struct BitmapInfoHeader
{
    uint32_t biSize;
    int32_t  biWidth;
    int32_t  biHeight;
    uint16_t biPlanes;
    uint16_t biBitCount;
    uint32_t biCompression;
    uint32_t biSizeImage;
    int32_t  biXPelsPerMeter;
    int32_t  biYPelsPerMeter;
    uint32_t biClrUsed;
    uint32_t biClrImportant;
};

struct Pixel
{
    uint8_t b;
    uint8_t g;
    uint8_t r;
};

#pragma pack(pop)

#endif
