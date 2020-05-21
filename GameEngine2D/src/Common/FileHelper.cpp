#include "FileHelper.h"
#include <fstream>
#include <stdio.h>
#include "StringHelper.h"

#include "Log/Log.h"

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

   bool GetStringsFromCSV(const char* const path, std::vector<std::string>& outVectorStrings, int* pWidth, int* pHeight)
   {

      ASSERT((pWidth == nullptr) == (pHeight == nullptr));  //either both are null or both exists... if one exists then the other must also exist... 

      std::ifstream file;
      file.open(path);

      if (!file.is_open() || file.eof()) { ASSERT(false); return false; }
      
      
      //calculate width
      {
         char buff[1000];
         file.getline(buff, 1000);
         int nWidth = 1;
         for (int i = 0; buff[i] != '\0'; i++)
         {
            if (buff[i] == ',' && (isdigit(buff[i+1]) || buff[i + 1] == '-'))  nWidth++;
         }

         if (pWidth)
         {
            *pWidth = nWidth;
         }
         outVectorStrings.reserve(nWidth* nWidth); //for optimization
      }

      file.seekg(0, file.beg);

      while (!file.eof())
      {
         const int nBuffSize = 1000;
         char buff[nBuffSize];
         file.getline(buff, nBuffSize, '\n');
         
         std::string str;
         str.reserve(5);
         int nLen = StringR::strlen(buff);
         for (int i = 0; i < nLen; i++)
         {
            str.clear();
            for (; buff[i] != ',' && i < nLen; i++)
            {
               str += buff[i];
            }
            if (!str.empty())
            {
               outVectorStrings.emplace_back(str);
            }
         }
         
      }

      if (pHeight && pWidth)
      {
         *pHeight = static_cast<int>(outVectorStrings.size() / *pWidth);
      }

      file.close();
      return true;
   }
}