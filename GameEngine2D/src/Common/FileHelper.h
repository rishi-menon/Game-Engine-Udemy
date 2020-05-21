#pragma once
#include <string>
#include <vector>

namespace Engine::File
{
   extern bool CreateFile(const char* const path, const char* const data);
   extern bool DeleteFile(const char* const path);
   extern bool GetStringsFromCSV(const char* const path, std::vector<std::string>& outVectorStrings, int* pWidth = nullptr, int* pHeight = nullptr);
}