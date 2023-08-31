#pragma once
#include "Core\BE.h"
#include "ft2build.h"
#include FT_FREETYPE_H

BE_BEGIN

class BETexture
{
public:
	uint32 Width;

	uint32 Height;

	uint32 Channels;

	uint8* Buffer;

public:
	BETexture();

	BETexture(uint32 Width, uint32 Height, int32 Channels = 1);

	BETexture(BETexture&& Texture);

	void SetTexture(uint8* Texture);

	void SetTexture(const uint8* Texture);

	virtual void Save(const String& Path) const = 0;

	virtual ~BETexture();
};

BE_END