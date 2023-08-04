#pragma once
#include "SdfDefines.h"

#define STB_IMAGE_IMPLEMENTATION
#include "..\..\..\..\third_lib\stb\stb_image.h"



class SDFGen
{

public:
	SDFGen() = default;

	SDFGen(ESDFWorker Worker = ESDFWorker::CPU) :
		SDFWorker(Worker) {}

	virtual void GenerateSDF() const = 0;

	ESDFWorker SDFWorker;

};


class SDFGenSsedt : public SDFGen
{
public:
	virtual void GenerateSDF() const final;

private:
	void FillGrid(
		FGrid& GridOut, 
		FGrid& GirdInside, 
		const char* TextureData, 
		int32_t Width, 
		int32_t Height,
		int32_t Channels);
};
