#include "FileHelper.h"
#include <fstream>
#include <stdio.h>

namespace Engine::File
{
   bool CreateFile(const char* const path, const char* const data)
   {
      std::fstream file;
      file.open(path, std::fstream::out);
      if (file.is_open())
      {
         file << path;
         file.close();
         return true;
      }
      return false;
   }

   bool DeleteFile(const char* const path)
   {
      //std::remove returns 0 when it successfully deletes
      bool bSuccess = !std::remove(path);
      return bSuccess;
   }
}