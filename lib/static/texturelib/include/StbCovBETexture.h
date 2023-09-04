#pragma once
#include "Core\BE.h"
#include "TextureForward.h"

BE_BEGIN

namespace StbUtil
{
	void LoadTexture(const String& Path, BETexture* Texture, ETextureType Type);

	template<ETextureType Type>
	void SaveTexture(const String& Path, const BETexture* Texture);
}


BE_END