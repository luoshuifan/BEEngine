#pragma once
#include "BEPch.h"
//BE ÷’—…÷Æ º

#define BE_BEGIN namespace BE{
#define BE_END }

using int32 = int32_t;
using uint32 = uint32_t;

using int16 = int16_t;
using uint16 = uint16_t;

using int8 = int8_t;
using uint8 = uint8_t;

using String = std::string;

#define PRO R"(F:\Cplusplus\BEEngine)"
static const String PROJECT_DIR = PROJECTDIR;

inline String PROJECTDIRPLUS(const String& Str)
{
	String Dir = PRO;
	return Dir + Str;
}
