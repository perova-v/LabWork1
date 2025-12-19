/*
 * Perova Varvara
 * st141846@student.spbu.ru
 * LabWork1
 */

#include <gtest/gtest.h>
#include "BmpImage.h"

TEST(BmpTests, RotateCW_Square)
{
    std::vector<Pixel> d =
    {
        {255,0,0}, {0,255,0},
        {0,0,255}, {255,255,0}
    };
    BmpImage img(2, 2, d);
    img.rotate90CW();

    EXPECT_EQ(img.getWidth(), 2);
    EXPECT_EQ(img.getHeight(), 2);

    Pixel p = img.getPixel(0, 1);
    EXPECT_EQ(p.b, 255);
}


TEST(BmpTests, RotateCW_Rect)
{
    std::vector<Pixel> d(6, {0,0,0});
    BmpImage img(2, 3, d);
    img.rotate90CW();

    EXPECT_EQ(img.getWidth(), 3);
    EXPECT_EQ(img.getHeight(), 2);
}


TEST(BmpTests, RotateCCW_Size)
{
    std::vector<Pixel> d(3, {0,0,0});
    BmpImage img(3, 1, d);
    img.rotate90CCW();

    EXPECT_EQ(img.getWidth(), 1);
    EXPECT_EQ(img.getHeight(), 3);
}


TEST(BmpTests, RotateCCW_Color)
{
    std::vector<Pixel> d(4, {0,0,0});
    d[1] = {0,0,255};

    BmpImage img(2, 2, d);
    img.rotate90CCW();

    Pixel p = img.getPixel(1, 1);
    EXPECT_EQ(p.r, 255);
}


TEST(BmpTests, Gaussian_Center)
{
    std::vector<Pixel> d(9, {0,0,0});
    d[4] = {255, 255, 255};

    BmpImage img(3, 3, d);
    img.applyGaussianFilter();

    Pixel center = img.getPixel(1, 1);
    EXPECT_LT(center.r, 255);
    EXPECT_GT(center.r, 0);
}

TEST(BmpTests, Gaussian_Uniform)
{

    std::vector<Pixel> d(9, {255,255,255});
    BmpImage img(3, 3, d);
    img.applyGaussianFilter();

    Pixel p = img.getPixel(1, 1);
    EXPECT_GT(p.r, 250);
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
