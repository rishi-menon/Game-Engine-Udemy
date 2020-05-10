#pragma once
#include <string>

namespace Engine::File
{
   extern bool CreateFile(const char* const path, const char* const data);
   extern bool DeleteFile(const char* const path);
}