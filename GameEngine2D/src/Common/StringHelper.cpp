
#include "StringHelper.h"
#include <sstream>
#include <string>
#include <unordered_map>
#include <cstdarg>

namespace StringR {

   int strlen(const char* const str)
   {
      int i = 0;
      for (; str[i] != '\0'; i++);
      return i;
   }

   //for consistency this returns 0 when the strings are equal
   bool strcmp(const char* const str1, const char* const str2)
   {
      int len1 = strlen(str1);
      int len2 = strlen(str2);
      if (len1 != len2) { return true; }

      for (int i = 0; i < len1; i++)
      {
         if (str1[i] != str2[i])
         {
            return true;
         }
      }
      return false;
      
   }
   bool strcmpi(const char* const str1, const char* const str2)
   {
      int len1 = strlen(str1);
      int len2 = strlen(str2);
      if (len1 != len2) { return true; }
      
      for (int i = 0; i < len1; i++)
      {
         if (tolower(str1[i]) != tolower(str2[i]))
         {
            return true;
         }
      }
      return false;
   }

   ////////////////////////////////////////////////////////////////////////////////
   //Delimiters
   static const std::unordered_map<char, std::string> delimitersMap{
      {'\\', "\\\\"},
      {'\'', "\\\'"},
      {'\"', "\\\""},
   };
   std::string ParsePath(const std::string& strSource)
   {
      std::string srcCopy;
      srcCopy.reserve(100);

      for (std::size_t i = 0; i < strSource.size(); i++)
      {
         char c = strSource.at(i);
         std::unordered_map<char, std::string>::const_iterator it = delimitersMap.find(c);
         if (it != delimitersMap.end())
         {
            srcCopy += it->second;
         }
         else
         {
            srcCopy.push_back(c);
         }
      }
      return srcCopy;
   }

   static const std::unordered_map<char, std::string> luaRequirePathMap{
      {'\\', "."},
   };
   std::string ConvertPathToLuaRequire(const std::string& strPath)
   {
      std::string strCopy;
      strCopy.reserve(strPath.size());

      //loop until last '.' ie dont copy the extension... If no extension was provided then loop till the end
      std::size_t index = strPath.rfind('.');
      if (index == std::string::npos) { index = strPath.size(); }
      for (std::size_t i = 0; i < index; i++)
      {
         char c = strPath.at(i);
         std::unordered_map<char, std::string>::const_iterator it = luaRequirePathMap.find(c);
         if (it != luaRequirePathMap.end())
         {
            strCopy += it->second;
         }
         else
         {
            strCopy += c;
         }
      }

      return StringR::ParsePath(strCopy);
   }

   //////////////////////////////////////////////////////////////
   //format
   static int nBufferSize = 1024;
   static char* commonBuffer = new char[nBufferSize+1];

   void Terminate()
   {
      delete commonBuffer;
      commonBuffer = nullptr;
   }

   const char* Format(const char* const strFormat, ...)
   {
      va_list args;
      va_start(args, strFormat);
      vsprintf_s(commonBuffer, nBufferSize, strFormat, args);
      va_end(args);
      return commonBuffer;
   }

   //////////////////////////////////////////////////////

   std::string ToString(int num)
   {
      std::stringstream ss;
      ss << num;
      return ss.str();
   }

   int StringToNum(const std::string& str)
   {
      int n = std::stoi(str);
      return n;
   }
}