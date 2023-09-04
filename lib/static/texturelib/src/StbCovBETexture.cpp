#include "StbCovBETexture.h"
#include "Texture.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

BE_BEGIN

namespace StbUtil
{
	void LoadTexture(const String& Path, BETexture* Texture, ETextureType Type)
	{
		Texture->Buffer = stbi_load(Path.c_str(), &Texture->Width, &Texture->Height, &Texture->Channels, 3);
	}

	template<ETextureType Type>
	void SaveTexture(const String& Path, const BETexture* Texture)
	{
		if constexpr (Type == ETextureType::BE_PNG)
		{
			stbi_write_png(Path.c_str(), Texture->Width, Texture->Height, Texture->Channels, Texture->Buffer, 0);
		}
		else if constexpr (Type == ETextureType::BE_JPEG)
		{
			stbi_write_jpg(Path.c_str(), Texture->Width, Texture->Height, Texture->Channels, Texture->Buffer, 0);
		}
		else
		{

		}
	}
}


BE_END