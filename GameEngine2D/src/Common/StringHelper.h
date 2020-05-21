#pragma once
#include <string>

namespace StringR
{
   int strlen(const char* const str);
   bool strcmp(const char* const str1, const char* const str2);
   bool strcmpi(const char* const str1, const char* const str2);

   //replaces a single backslash with 2 backslashes to make it compatible (In lua, \ is an escape character so "assets\path" would have to be written as "assets\\path"
   std::string ParsePath(const std::string& strPath);

   //first parses the string to make it compatible... Secondly it replaces the \ with . as that is the path seperator in lua (Eg "assets\scene\player.lua" should become "assets.scene.player")... Also remove the extension
   std::string ConvertPathToLuaRequire(const std::string& strPath);

   void Terminate();
   const char* Format(const char* const strFormat, ...);

   std::string ToString(int num);
   int StringToNum(const std::string& str);
}