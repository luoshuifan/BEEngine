#include "Core/BEPch.h"
#include "BEFreeType.h"
#include "Core\BELog.h"
#include "freetype\ftglyph.h"

BE_BEGIN

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

	SetPixelSizes(32, 32);
}

bool BEFreeType::SetPixelSizes(uint32_t Width, uint32_t Height)
{
	return FT_Set_Pixel_Sizes(Face, Width, Height) == 0;
}

BEBitMap BEFreeType::GetGlyphBitMap(uint64_t CharCode, const String& BitMapName)
{
	if (Face == nullptr)
		BEPrint(__FILE__, __LINE__, "Face is nullptr");

	uint32_t GlyphIndex = FT_Get_Char_Index(Face, CharCode);
	FT_Error Error = FT_Load_Glyph(Face, GlyphIndex, FT_LOAD_DEFAULT | FT_LOAD_NO_BITMAP);
	FT_Get_Glyph(Face->glyph, &Glyph);

	if (Face->glyph->format != FT_GLYPH_FORMAT_BITMAP)
	{
		Error = FT_Render_Glyph(Face->glyph, FT_RENDER_MODE_NORMAL);
	}
	FT_BBox Box;
	FT_Glyph_Get_CBox(Glyph, FT_GLYPH_BBOX_TRUNCATE, &Box);

	return BEBitMap{ Face->glyph->bitmap, BitMapName};
}

BE_END
