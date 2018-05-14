#ifndef IMAGE_H
#define IMAGE_H
#include "png.h"
#include "rgbapixel.h"
#include <cstdint>
#include <iostream>
using std::uint8_t;

class Image : public PNG
{
  public:
    void naiveCompression();
    void flipleft();
    void adjustbrightness (int r, int g, int b);
    void invertcolors();
};

#endif