#ifndef GSENGINE_TGA_LOADER
#define GSENGINE_TGA_LOADER

#include <string>
#include <vector>

uint32_t LoadTGA(std::vector<uint8_t>& image, uint32_t& width, uint32_t& height,
                 int& internalFormat, int& format, const std::string& fileName);

#endif
