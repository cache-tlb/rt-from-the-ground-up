#ifndef IMAGEIO_H
#define IMAGEIO_H

#include "rgbcolor.h"
#include <vector>

class ImageIO
{
public:
    ImageIO();

    void
    opencv_read_image(const char *file_name, std::vector<RGBColor>& pixels, int &hres, int &vres);
};

#endif // IMAGEIO_H
