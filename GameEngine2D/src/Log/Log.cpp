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

char* buffer = new char[1000];
char* buffer2 = new char[1500];

void DebugTerminate()
{
   delete buffer;
   buffer = nullptr;
   delete buffer2;
   buffer2 = nullptr;
}
void DebugOutputWindow(bool bConsole, int line, const char* const file, const char* const formatString, ...)
{
#ifdef WINDOWS
   //To do: how does this work exactly
   va_list args;
   va_start(args, formatString);
   vsprintf_s(buffer, 1000, formatString, args);
   va_end(args);
   if (bConsole)
   {
      printf("%s(%d): %s", file, line, buffer);
   }
   else
   {
      sprintf_s(buffer2, 1500, "%s(%d): %s", file, line, buffer);
      OutputDebugStringA(buffer2);
   }
   printf("\n");
#endif //WINDOWS defined
}

void DebugInitInfo(int argc, char* argv[])
{
#ifdef WINDOWS
   printf("Executable Path: %s \n", argv[0]);
   char buffer[301];
   GetCurrentDirectoryA(300, buffer);
   printf("Current Working Directory: %s \n", buffer);
   printf("\n");
#endif
}

#endif //DEBUG defined
