#pragma once

#include "ft2build.h"
#include FT_FREETYPE_H

struct BEBitMap
{
public:
	uint32_t Width;

	uint32_t Height;

	uint8_t* Buffer;

public:

	BEBitMap() = default;

	BEBitMap(const FT_Bitmap& FTBitMap):
		Width(FTBitMap.width), Height(FTBitMap.rows)
	{
		Buffer = new uint8_t[Width * Height];
		std::memcpy(Buffer, FTBitMap.buffer, Width * Height);
	}

	~BEBitMap()
	{
		if (Buffer)
			delete Buffer;
	}
};

class BEFreeType
{
private:
	std::string FontPaths;

	FT_Library Library;

	FT_Face Face;

public:

	BEFreeType() = default;

	BEFreeType(const std::string& FontPaths);

	bool SetPixelSizes(uint32_t Width, uint32_t Height);

	BEBitMap GetGlyphBitMap(uint64_t CharCode);
};