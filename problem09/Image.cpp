#include "Image.hpp"

#include <stdexcept>

// Default constructor
Image::Image() : width(0), height(0), image_data(nullptr) {}

// Square image constructor
Image::Image(int size)
    : width(size), height(size), image_data(nullptr)
{
    if (size > 0)
    {
        image_data = new RGBPIXEL[width * height];
        for (int i = 0; i < width * height; ++i)
        {
            image_data[i] = GREEN; // set all pixels to GREEN
        }
    }
    else
    {
        image_data = nullptr;
    }
}

// Rectangular image constructor
Image::Image(int w, int h)
    : width(w), height(h), image_data(nullptr)
{
    if (w > 0 && h > 0)
    {
        image_data = new RGBPIXEL[width * height];
        for (int i = 0; i < width * height; ++i)
        {
            image_data[i] = GREEN; 
            // set all pixels to GREEN
        }
    }
    else
    {
        image_data = nullptr;
    }
}

// Copy constructor
Image::Image(const Image &im)
    : width(im.width), height(im.height), image_data(nullptr)
{
    if (im.image_data != nullptr)
    {
        image_data = new RGBPIXEL[width * height];
        for (int i = 0; i < width * height; ++i)
        {
            image_data[i] = im.image_data[i];
        }
    }
}

// Destructor
Image::~Image()
{
    delete[] image_data;
    image_data = nullptr;
    width = height = 0;
}

// Copy-assignment operator
Image &Image::operator=(Image im)
{
    // manually swap width
    int tempWidth = width;
    width = im.width;
    im.width = tempWidth;

    // manually swap height
    int tempHeight = height;
    height = im.height;
    im.height = tempHeight;

    // manually swap pointer
    RGBPIXEL *tempData = image_data;
    image_data = im.image_data;
    im.image_data = tempData;

    return *this;
}

// Getters
int Image::get_width() const { return width; }
int Image::get_height() const { return height; }

// Pixel accessors
RGBPIXEL Image::get_pixel(int index) const
{
    if (index < 0 || index >= width * height)
    {
        throw std::out_of_range("Pixel index out of range");
    }
    return image_data[index];
}

void Image::set_pixel(int index, const RGBPIXEL color)
{
    if (index < 0 || index >= width * height)
    {
        throw std::out_of_range("Pixel index out of range");
    }
    image_data[index] = color;
}

// Bonus
bool Image::load_from_file(std::string filename)
{
    // Free existing data
    if (image_data != nullptr)
    {
        delete[] image_data;
        image_data = nullptr;
        width = height = 0;
    }

    RGBIMAGEDATA bmp = import_bmp(filename);

    // Check for failure
    if (bmp.data == nullptr || bmp.width <= 0 || bmp.height <= 0)
    {
        std::cerr << "Failed to load BMP file: " << filename << std::endl;
        return false;
    }

    // Transfer data to this Image
    width = bmp.width;
    height = bmp.height;
    image_data = bmp.data;

    return true;
}

bool Image::save_to_file(std::string filename)
{
    if (image_data == nullptr || width <= 0 || height <= 0)
    {
        std::cerr << "No image data to save." << std::endl;
        return false;
    }

    RGBIMAGEDATA outData;
    outData.data = image_data;
    outData.width = width;
    outData.height = height;

    if (!export_bmp(outData, filename))
    {
        std::cerr << "Failed to save BMP file: " << filename << std::endl;
        return false;
    }

    return true;
}

// Non-member overloaded addition operators
Image operator+(const Image &im, const RGBPIXEL &val)
{
    Image result(im); 
    // copy of the original
    int total = result.get_width() * result.get_height();

    for (int i = 0; i < total; ++i)
    {
        result.set_pixel(i, result.get_pixel(i) + val);
    }
    return result;
}

Image operator+(const RGBPIXEL &val, const Image &im)
{
    return im + val;
}
