
#include "StringHelper.h"
#include <string>

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
}