#include <OpenEXR/ImfRgbaFile.h>
#include <OpenEXR/ImfArray.h>
#include <iostream>
#include <vector>
#include <cstring>

int main()
{
    const char* filename = "image.exr";

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

    // Raw pixel bytes:
    const std::byte* bytes =
        reinterpret_cast<const std::byte*>(&pixels[0][0]);

    size_t byteCount =
        static_cast<size_t>(width) *
        height *
        sizeof(Imf::Rgba);

    std::cout << width << " x " << height << '\n';
    std::cout << "Bytes: " << byteCount << '\n';
}