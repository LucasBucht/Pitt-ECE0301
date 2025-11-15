#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "bitmap.hpp"
#include "Image.hpp"

#include <cstdint>

/* Provided test cases */
TEST_CASE("Test size constructor", "[image]")
{
    int size = 10;
    Image im(size);

    REQUIRE(im.get_width() == size);
    REQUIRE(im.get_height() == size);
}

TEST_CASE("Test set/get pixels after size construction", "[image]")
{
    int size = 8;
    Image im(size);
    int first = 12;
    int second = 13;
    im.set_pixel(first, BLACK);
    im.set_pixel(second, RED);

    bool match = true;
    for (int i = 0; i < size * size; i++)
    {
        if (i == first)
        {
            match = (im.get_pixel(i) == BLACK);
        }
        else if (i == second)
        {
            match = (im.get_pixel(i) == RED);
        }
        else
        {
            match = (im.get_pixel(i) == GREEN);
        }
        if (!match)
        {
            break;
        }
    }
    REQUIRE(match);
}

TEST_CASE("Test copy constructor", "[image]")
{
    // initial image
    int width = 10;
    int height = 8;
    Image im(width, height);

    int first = 0;
    int last = width * height - 1;
    int middle = (width * height - 1) / 2;

    im.set_pixel(first, BLACK);
    im.set_pixel(last, RED);

    // copy image
    Image imgcopy(im);

    // change initial
    im.set_pixel(first, RED);
    im.set_pixel(middle, BLUE);
    im.set_pixel(last, WHITE);

    // test copy
    bool match = true;
    for (int i = 0; i < width * height; i++)
    {
        if (i == first)
        {
            match = (imgcopy.get_pixel(i) == BLACK);
        }
        else if (i == last)
        {
            match = (imgcopy.get_pixel(i) == RED);
        }
        else
        {
            match = (imgcopy.get_pixel(i) == GREEN);
        }
        if (!match)
        {
            break;
        }
    }
    REQUIRE(match);
}

TEST_CASE("Test operator+", "[image]")
{
    int width = 10;
    int height = 12;
    Image im(width, height);

    for (int i = 0; i < width * height; i++)
    {
        im.set_pixel(i, {0x80, 0x05, 0xAA});
    }

    RGBPIXEL val = {0x21, 0x05, 0xFF};

    Image res = im + val;

    bool match = true;
    for (int i = 0; i < width * height; i++)
    {
        match = (res.get_pixel(i) == im.get_pixel(i) + val);
        if (!match)
        {
            break;
        }
    }
    REQUIRE(match);
}


TEST_CASE("Test both parameterized constructors", "[image][constructors]")
{
    SECTION("Square size constructor")
    {
        Image square(5);
        REQUIRE(square.get_width() == 5);
        REQUIRE(square.get_height() == 5);
    }

    SECTION("Width/height constructor")
    {
        Image rect(4, 7);
        REQUIRE(rect.get_width() == 4);
        REQUIRE(rect.get_height() == 7);
    }
}

TEST_CASE("Test deep copy using copy assignment operator", "[image][copy]")
{
    int w = 6, h = 5;
    Image im1(w, h);

    // Initialize first image
    for (int i = 0; i < w * h; i++)
    {
        RGBPIXEL p = {(uint8_t)i, (uint8_t)(i + 1), (uint8_t)(i + 2)};
        im1.set_pixel(i, p);
    }

    // Create second image and assign
    Image im2;
    im2 = im1;

    // Modify im1
    im1.set_pixel(0, RED);
    im1.set_pixel(1, BLUE);

    // im2 should remain unchanged
    REQUIRE(im2.get_pixel(0) != RED);
    REQUIRE(im2.get_pixel(1) != BLUE);

    // Verify  copy
    bool identical = true;
    for (int i = 2; i < w * h; i++)
    {
        if (im1.get_pixel(i) != im2.get_pixel(i))
        {
            identical = false;
            break;
        }
    }
    REQUIRE(identical);
}

TEST_CASE("Test overloaded operator+ in both directions", "[image][operator+]")
{
    int w = 3, h = 3;
    Image im(w, h);
    for (int i = 0; i < w * h; i++)
        im.set_pixel(i, {10, 20, 30});

    RGBPIXEL val = {5, 15, 25};

    Image res1 = im + val;
    Image res2 = val + im;

    bool same = true;
    for (int i = 0; i < w * h; i++)
    {
        RGBPIXEL expected = im.get_pixel(i) + val;
        if (res1.get_pixel(i) != expected || res2.get_pixel(i) != expected)
        {
            same = false;
            break;
        }
    }

    REQUIRE(same);
}