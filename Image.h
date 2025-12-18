#ifndef IMAGE_H
#define IMAGE_H

#include <string>

class Image {
public:
    virtual ~Image() = default;

    virtual void load(const std::string& filename) = 0;
    virtual void save(const std::string& filename) const = 0;

    virtual void rotate90CW() = 0;
    virtual void rotate90CCW() = 0;
    virtual void applyGaussianFilter() = 0;
};

#endif
