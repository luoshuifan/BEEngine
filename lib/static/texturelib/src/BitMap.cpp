#include "BitMap.h"
#include "StbCovBETexture.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

BE_BEGIN

void BEBitMap::Save(const String & Path) const
{
	String BitMapPath = Path + Name;
	stbi_write_png(BitMapPath.c_str(), Width, Height, Channels, Buffer, 0);
}

BE_END