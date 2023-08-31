#pragma once

#include "Core\BE.h"
#include "BitMap.h"
#include "freetype\ftglyph.h"

BE_BEGIN

class BEFreeType
{
private:
	std::string FontPaths;

	FT_Library Library;

	FT_Face Face;

	FT_Glyph Glyph;

public:

	BEFreeType(const std::string& FontPaths = PROJECTDIRPLUS(R"(\third_lib\freetype-2.13.1\build\Fonts\STKAITI.TTF)"));

	bool SetPixelSizes(uint32_t Width, uint32_t Height);

	BEBitMap GetGlyphBitMap(uint64_t CharCode, const String& BitMapName = "");
};

BE_END