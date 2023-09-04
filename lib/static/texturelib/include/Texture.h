#pragma once
#include "Core\BE.h"
#include "TextureForward.h"
#include "Math\Vector2.h"
#include "Math\MathUtil.h"

BE_BEGIN

class BETexture
{
public:
	int32 Width;

	int32 Height;

	int32 Channels;

	uint8* Buffer;

public:
	BETexture();

	BETexture(uint32 Width, uint32 Height, int32 Channels = 1);

	BETexture(BETexture&& Texture);

	void SetTexture(uint8* Texture);

	void SetTexture(const uint8* Texture);

	void LoadTexture(const String& Path, ETextureType Type = ETextureType::BE_PNG);

	template<ETextureType Type>
	void Save(const String& Path) const;

	const uint8* ReadPixel(const FVector2& Pos)const
	{
		int32 Position = (Pos.Y * Width + Pos.X) * Channels;
		return Buffer + Position;
	}

	void SetPixel(const FVector2& Pos, uint8* Data)
	{
		int32 Position = (Pos.Y * Width + Pos.X) * Channels;
		memcpy(Buffer + Position, Data, Channels);
	}

	virtual ~BETexture();
};

template<ETextureType Type>
void BETexture::Save(const String& Path) const
{
	StbUtil::SaveTexture<Type>(Path, this);
}

BE_END