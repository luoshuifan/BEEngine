#include "Texture.h"

BE_BEGIN

BETexture::BETexture() :
	Width(0), Height(0), Channels(0), Buffer(nullptr) {}

BETexture::BETexture(uint32 InWidth, uint32 InHeight, int32 InChannels)
	:Width(InWidth), Height(InHeight),Channels(InChannels)
{
	Buffer = new uint8[Width * Height * Channels];
}

BETexture::~BETexture()
{
	if (Buffer)
		delete Buffer;
}

BETexture::BETexture(BETexture&& Texture)
{
	Width = Texture.Width;
	Height = Height;
	Channels = Texture.Channels;
	SetTexture(Texture.Buffer);
}

void BETexture::SetTexture(uint8* Texture)
{
	Buffer = Texture;
	Texture = nullptr;
}

void BETexture::SetTexture(const uint8* Texture)
{
	std::memcpy(Buffer, Texture, Width * Height * Channels);
}

void BETexture::LoadTexture(const String& Path, ETextureType Type)
{

}


BE_END