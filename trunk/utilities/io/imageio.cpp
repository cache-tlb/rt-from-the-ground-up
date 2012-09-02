#include "imageio.h"

ImageIO::ImageIO() {}

void ImageIO::opencv_read_image(const char *file_name, std::vector<RGBColor> &pixels,int &hres,int &vres)
{
    IplImage *img = cvLoadImage(file_name);
    int depth = img->depth;
    double divisor = (double)( (2 << (depth - 1) ) - 1);
    int height = img->height, width = img->width;
    pixels.resize(height*width);
    hres = width; vres = height;
    for(int row = 0; row < height; row++){
        for(int column = 0; column < width; column ++){
            CvScalar s = cvGet2D(img, row, column);
            RGBColor c(s.val[2]/divisor, s.val[1]/divisor, s.val[0]/divisor);
            int index = column + width * row;
            pixels[index] = c;
        }
    }
    cvReleaseImage(&img);
}
