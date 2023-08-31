#pragma once
#include "Core\BE.h"

BE_BEGIN

template<typename LambdaFunction>
void Foreach(int32 Width, int32 Height, LambdaFunction Function, int32 StepWidth = 1, int32 StepHeight = 1, int32 WidthBegin = 0, int32 HeightBegin = 0)
{
	for (int32 X = WidthBegin; X < Width; X += StepWidth)
	{
		for (int32 Y = HeightBegin; Y < Height; Y += StepHeight)
		{
			Function(X, Y);
		}
	}
}


BE_END