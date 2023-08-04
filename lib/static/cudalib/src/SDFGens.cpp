#include "SDFGens.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "..\..\..\..\third_lib\stb\stb_image_write.h"

#include <string>
#include <iostream>

const std::string FileName = "";

void SDFGenSsedt::GenerateSDF() const
{
	int Width, Height;
	int Channels;

	unsigned char* TextureData = 
		stbi_load(FileName.c_str(), &Width, &Height, &Channels, 0);

	if (!TextureData)
		std::cout << "texture " << FileName << " read fail" << std::endl;

	FGrid GridOut{ Width + 2, Height + 2 };
	FGrid GridInside{ Width + 2, Height + 2 };




	//stbi_write_png()

	stbi_image_free(TextureData);
}

void SDFGenSsedt::FillGrid(
	FGrid& GridOut,
	FGrid& GirdInside, 
	const char* TextureData, 
	int32_t Width, 
	int32_t Height,
	int32_t Channels)
{
	for (int32_t X = 0; X < Width; ++X)
	{
		for (int32_t Y = 0; Y < Height; ++Y)
		{
			int32_t Position = Y * Width * Channels + X * Channels;
			
		}
	}
}
