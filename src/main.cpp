#include <OpenEXR/ImfRgbaFile.h>
#include <OpenEXR/ImfArray.h>

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <stb_image_write.h>

#include <iostream>
#include <vector>

int main(int argc, const char *argv[])
{
    if (argc != 3)
    {
        std::cerr << "Usage: exr2hdr [input] [output]" << std::endl;

        return 0;
    }

    // Read

    const char* filename = argv[1];

    Imf::RgbaInputFile file(filename);

    Imath::Box2i dw = file.dataWindow();

    int width  = dw.max.x - dw.min.x + 1;
    int height = dw.max.y - dw.min.y + 1;

    Imf::Array2D<Imf::Rgba> pixels;
    pixels.resizeErase(height, width);

    file.setFrameBuffer(
        &pixels[0][0] - dw.min.x - dw.min.y * width,
        1,
        width
    );

    file.readPixels(dw.min.y, dw.max.y);

    // Write

    std::vector<float> data(width * height * 4);

    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            const auto& p = pixels[y][x];

            const size_t i = (x + y * width) * 4;

            data[i + 0] = p.r;
            data[i + 1] = p.g;
            data[i + 2] = p.b;
            data[i + 3] = p.a;
        }
    }

    stbi_write_hdr(argv[2], width, height, 4, data.data());
}