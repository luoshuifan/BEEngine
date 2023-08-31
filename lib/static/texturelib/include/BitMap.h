#pragma once
#include "Core\BE.h"
#include "Texture.h"

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
	
	virtual void Save(const String& Path) const override;
};

BE_END