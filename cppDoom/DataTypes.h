#pragma once

#include <cstdint>


struct Directory
{
	uint32_t LumpOffset;
	uint32_t LumpSizte;
	char LumpName[9];
};

struct Header 
{
	char WADType[5];
	uint32_t DirectoryCount;
	uint32_t DirectoryOffset;
};