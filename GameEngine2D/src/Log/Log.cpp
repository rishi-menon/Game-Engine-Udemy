//include pch even if its not required ? Intellisense gives a warning
//#include "pch.h"

#ifdef DEBUG
#include "Log.h"
#include <iostream>

#ifdef WINDOWS
#include <Windows.h>
#endif

static const Log LogMinLevel = Log::Trace;

void DebugLog(const char* const message, Log level, int line, const char* const func)
{
   if (level >= LogMinLevel)
   {
      std::cerr << "Log(" << (unsigned int)level << "): " << message << " (Line: " << line << ", Func: " << func <<")" << std::endl;
   }
}

void DebugLog(double message, Log level, int line, const char* const func)
{
   if (level >= LogMinLevel)
   {
      std::cerr << "Log(" << (unsigned int)level << "): " << message << " (Line: " << line << ", Func: " << func << ")" << std::endl;
   }
}

void DebugPause()
{
   std::cerr << "Paused: Press enter to continue...";
   std::cin.get();
}
void DebugLineBreak()
{
   std::cerr << std::endl;
}

void DebugOutputWindow(bool bConsole, int line, const char* const file, const char* const formatString, ...)
{
#ifdef WINDOWS
   //To do: how does this work exactly
   char buffer[100];
   char buffer2[200];
   va_list args;
   va_start(args, formatString);
   vsprintf(buffer, formatString, args);
   va_end(args);
   if (bConsole)
   {
      printf("%s(%d): %s", file, line, buffer);
   }
   else
   {
      sprintf(buffer2, "%s(%d): %s", file, line, buffer);
      OutputDebugStringA(buffer2);
   }
   printf("\n");
#endif //WINDOWS defined
}

#endif //DEBUG defined
