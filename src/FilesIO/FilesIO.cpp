#define GSENGINE_EXPORT
#include "FilesIO/FilesIO.h"

#include <cstdio>

bool FilesIO::LoadBinaryFile(const std::string &fileName, uint8_t **buffer, size_t &size)
{
    FILE *f;
	if (!(f = fopen(fileName.data(), "rb")))
	{
		printf("Can\'t open file %s\n", fileName.data());
		return false;
	}

    fseek(f, 0, SEEK_END);
    size = ftell(f);

	if (size == 0)
	{
		fclose(f);
		printf("File is empty\n");
		return false;
	}

    rewind(f);

	*buffer = new uint8_t[size];

	size_t read = fread(*buffer, 1, size, f);
    fclose(f);

	if (read != size)
	{
		printf("Can't read all file (%llu/%llu)", read, size);
		delete[] *buffer;
		return false;
	}

	return true;
}
