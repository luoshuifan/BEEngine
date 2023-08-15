#pragma once
#include "SdfDefines.h"

class FSDFGen
{
public:
	FSDFGen(ESDFWorker Worker = ESDFWorker::CPU) :
		SDFWorker(Worker) {}

	virtual void GenerateSDF() const = 0;

	ESDFWorker SDFWorker;

};

//8ssedt 
class FSDFGenSsedt : public FSDFGen
{
public:

	virtual void GenerateSDF() const final;

private:
	void FillGrid(
		FGrid& GridOut, 
		FGrid& GridInside, 
		const unsigned char* TextureData, 
		int32_t Width, 
		int32_t Height,
		int32_t Channels) const;

	void FillGridDistances(
		FGrid& Grid,
		int32_t Width,
		int32_t Height) const;
};

void GetIsotropicSobel(
	const unsigned char* TextureData,
	int32_t X,
	int32_t Y,
	int32_t Width,
	int32_t Height,
	FPoint& Point
);
