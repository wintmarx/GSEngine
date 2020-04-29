#ifndef FILESIOHEADER
#define FILESIOHEADER

#include <string>

#include "LibExports.h"

namespace FilesIO
{
	GSENGINE_API bool LoadBinaryFile(const std::string &fileName, uint8_t **buffer, size_t &size);
};

#endif

