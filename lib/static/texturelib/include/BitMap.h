#pragma once
#include "Core\BE.h"
#include "Texture.h"
#include "ft2build.h"
#include FT_FREETYPE_H

BE_BEGIN

struct BEBitMap :
	public BETexture
{
public:
	String Name;

public:

	BEBitMap() = default;

	BEBitMap(const FT_Bitmap& FTBitMap, const String& InName) :
		BETexture(FTBitMap.width, FTBitMap.rows, FTBitMap.pitch / FTBitMap.rows), Name(InName)
	{
		SetTexture(FTBitMap.buffer);
	}

	BEBitMap(int32 Width, int32 Height, int32 Channels, const String& InName) :
		BETexture(Width, Height, Channels), Name(InName)
	{	}
	
};

BE_END