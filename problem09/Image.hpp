#ifndef _IMAGE_HPP
#define _IMAGE_HPP

#include <string>
#include <cstdint>
#include "bitmap.hpp"


class Image
{
public:
    // Default constructor
    Image();

    // Constructor for a square image 
    Image(int size);

    // Constructor for a rectangular image with given width and height
    Image(int w, int h);

    // Copy constructor
    Image(const Image &im);

    // Destructor
    ~Image();

    // Copy assignment operator
    Image &operator=(Image im);

    // Accessors
    int get_width() const;
    int get_height() const;

    // Pixel accessors
    RGBPIXEL get_pixel(int index) const;
    void set_pixel(int index, const RGBPIXEL color);

    // File read/write
    bool load_from_file(std::string filename);
    bool save_to_file(std::string filename);

    // 

private:
    int width;
    int height;
    RGBPIXEL *image_data;
};

// Non-member overloaded addition operators
Image operator+(const Image &im, const RGBPIXEL &val);
Image operator+(const RGBPIXEL &val, const Image &im);

// OPTIONAL (for bonus): subtraction operators
// Image operator-(const Image &im, const RGBPIXEL &val);
// Image operator-(const RGBPIXEL &val, const Image &im);

#endif // _IMAGE_HPP
