#include "bmp.h"

#include <fstream>

namespace s2d
{
#pragma pack(push, 1)
    struct BitmapFileHeader
    {
        char id[2];
        i32 file_size_bytes;
        i16 reserved0;
        i16 reserved1;
        i32 data_offset;
    };

    struct BitmapInfoHeader
    {
        i32 header_size_bytes;
        i32 width;
        i32 height;
        i16 color_planes;
        i16 bits_per_pixel;
        i32 compression;
        i32 image_size_bytes;
        i32 horizontal_resolution;
        i32 vertical_resolution;
        i32 color_palette;
        i32 important_colors;
    };

#pragma pack(pop)

    Pixelbuffer load_bmp(const char* file)
    {
        Pixelbuffer image;

        std::fstream f(file);

        if (!f.is_open())
        {
            return image;
        }

        BitmapFileHeader file_header;
        f.read((char*)&file_header, sizeof(file_header));

        // If data offset is 14 + 40, we can read the file
        if (file_header.data_offset != (sizeof(BitmapFileHeader) + sizeof(BitmapInfoHeader)))
        {
            return image;
        }

        

        BitmapInfoHeader info_header;
        f.read((char*)&info_header, sizeof(info_header));

        // only 24-bit supported for now
        if (info_header.bits_per_pixel != 24)
        {
            // TODO: error

            return image;
        }

        // Top-down or bottom-up?
        bool is_top_down;
        if (info_header.height < 0)
        {
            is_top_down = true;
            info_header.height = -info_header.height;
        }
        else
        {
            is_top_down = false;
        }

        int row_size = (int)(std::floor((info_header.bits_per_pixel * info_header.width + 31) / 32) * 4);
        info_header.image_size_bytes = info_header.image_size_bytes == 0 ? info_header.height * row_size : info_header.image_size_bytes;



        image.resize(info_header.width, info_header.height);

        byte* temp = nullptr;
        temp = (byte*)malloc(info_header.image_size_bytes);

        if (temp == nullptr)
        {
            // TODO: error message
            return image;
        }

        f.read((char*)temp, info_header.image_size_bytes);

        if (!f)
        {
            // TODO: error message
            free(temp);
            return image;
        }

        for (int y = 0; y < info_header.height; y++)
        {
            int i = 0;
            if (is_top_down)
            {
                i = 0;
            }
            else
            {
                i = info_header.height - 1 - y;
            }

            int idx = i * row_size;
            
            byte* p = temp + idx;
            for (int x = 0; x < info_header.width; x++, p += 3)
            {
                u32 b = p[0];
                u32 g = p[1];
                u32 r = p[2];

                u32 color = b | (g << 8) | (r << 16) | (0xff000000);

                image.set_pixel(x, y, color);
            }
        }

        

        return image;
    }
}