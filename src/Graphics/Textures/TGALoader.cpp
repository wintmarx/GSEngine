#define GSENGINE_EXPORT

#include "Graphics/Textures/TGALoader.h"

#include <stdio.h>

#include "FilesIO/FilesIO.h"
#include "GL/glew.h"

// формат заголовка TGA-файла
#pragma pack(1)
struct TGAHeader {
    uint8_t idlength;
    uint8_t colormap;
    uint8_t datatype;
    uint8_t colormapinfo[5];
    uint16_t xorigin;
    uint16_t yorigin;
    uint16_t width;
    uint16_t height;
    uint8_t bitperpel;
    uint8_t description;
};
#pragma pack()

uint32_t LoadTGA(std::vector<uint8_t>& image, uint32_t& width, uint32_t& height,
                 int& internalFormat, int& format, const std::string& fileName) {
    TGAHeader* header;
    uint8_t* buffer;
    size_t size;

    if (!FilesIO::LoadBinaryFile(fileName.data(), &buffer, size)) {
        return 1;
    }

    if (size <= sizeof(TGAHeader)) {
        printf("Too small file \'%s\'\n", fileName.data());
        delete[] buffer;
        return 2;
    }

    header = (TGAHeader*)buffer;

    if (header->datatype != 2 || (header->bitperpel != 24 && header->bitperpel != 32)) {
        printf("Wrong TGA format \'%s\'\n", fileName.data());
        delete[] buffer;
        return 3;
    }

    width = header->width;
    height = header->height;

    image.assign(buffer + sizeof(TGAHeader) + header->idlength, buffer + size - 1);

    format = header->bitperpel == 24 ? GL_BGR : GL_BGRA;
    internalFormat = format == GL_BGR ? GL_RGB8 : GL_RGBA8;

    delete[] buffer;

    return 0;
}
