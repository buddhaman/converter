#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

#include "emscripten.h"

#if 0
int main(int argc, char** argv)
{
    printf("THis is tim!!!!\n");
    return 0;
}
#endif

extern "C" {

    EMSCRIPTEN_KEEPALIVE
    void* alloc_memory(int size) {
        return malloc(size);
    }

    EMSCRIPTEN_KEEPALIVE

    // Assume that each pixel is represented by 4 bytes (RGBA
    EMSCRIPTEN_KEEPALIVE
    void negate_image(uint8_t* img, int width, int height) {
        int total_pixels = width * height;
        for (int i = 0; i < total_pixels; ++i) {
            int index = i * 4; // Index for the RGBA values of each pixel
            img[index] = 255 - img[index];       // R
            img[index + 1] = 255 - img[index + 1]; // G
            img[index + 2] = 255 - img[index + 2]; // B
            // Alpha (img[index + 3]) remains unchanged
        }
    }

    struct Writer
    {
        uint8_t* data;
        size_t offset;
    };

    void write_func(void *context, void *data, int size)
    {
        Writer* writer = (Writer*)context;
        printf("Now writing %d bytes\n", size);
        memcpy(writer->data + writer->offset, data, size);
        writer->offset+=size;
    }

    EMSCRIPTEN_KEEPALIVE
    size_t make_download(uint8_t* dest, uint8_t* img, int width, int height) {
        Writer writer = {dest, 0};

        int components = 4;
        int stride_in_bytes = components*width;
        stbi_write_png_to_func(write_func, 
                               &writer, 
                               width, 
                               height, 
                               components, 
                               img, 
                               stride_in_bytes);
        return writer.offset;
    }
}
