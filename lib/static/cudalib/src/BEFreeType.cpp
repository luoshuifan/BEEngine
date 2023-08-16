#include <string>
#include <iostream>
#include "BEFreeType.h"


BEFreeType::BEFreeType(const std::string& InFontPaths) :
	FontPaths(InFontPaths)
{
	FT_Error Error = FT_Init_FreeType(&Library);
	if (Error)
	{
		std::cout << "File: " << __FILE__ << " BEFreeType Library Error! Line : " << __LINE__ << std::endl;
	}

	Error = FT_New_Face(Library, FontPaths.c_str(), 0, &Face);
	if (Error == FT_Err_Unknown_File_Format)
	{
		std::cout << "File: " << __FILE__ << " BEFreeType Face Error! Line : " << __LINE__ << std::endl;
	}
	else if (Error)
	{
		std::cout << "File: " << __FILE__ << " BEFreeType Face Error! Line : " << __LINE__ << std::endl;
	}

	//Error = FT_Set_Char_Size(Face, 0, 16 * 64, 300, 300);
	//Error = FT_Set_Pixel_Sizes(Face, 0, 32);
	SetPixelSizes(32, 32);
}

bool BEFreeType::SetPixelSizes(uint32_t Width, uint32_t Height)
{
	return FT_Set_Pixel_Sizes(Face, Width, Height) == 0;
}

BEBitMap BEFreeType::GetGlyphBitMap(uint64_t CharCode)
{
	uint32_t GlyphIndex = FT_Get_Char_Index(Face, CharCode);
	FT_Error Error = FT_Load_Glyph(Face, GlyphIndex, FT_LOAD_DEFAULT);

	if (Face->glyph->format != FT_GLYPH_FORMAT_BITMAP)
	{
		Error = FT_Render_Glyph(Face->glyph, FT_RENDER_MODE_NORMAL);
	}
	return Face->glyph->bitmap;
}

