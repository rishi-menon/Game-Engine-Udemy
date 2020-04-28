#pragma once

#ifdef DEBUG

#if 0
#define ASSERT(x) if (!(x))   { LOGW("Assertion failed... \n"); DebugPause(); }
#else
#define ASSERT(x) if (!(x))   { LOGW("Assertion failed... \n"); __debugbreak(); }
#endif

//#define ASSERT(x)   if (!(x))  __debugbreak()

//Higher levels have a greater priority. If the level is greater than the minimum then it is logged
enum class Log : unsigned int
{
   Trace = 0,
   Info,
   Warn,
   Error,
   Fatal
};

#define LOG(message, level)             DebugLog (message, level, __LINE__, __func__)
#define LOG_PAUSE()                     DebugPause()
#define LOG_LINE_BREAK()                DebugLineBreak();
#define LOG_INIT_PRINT(argc, argv)      DebugInitInfo(argc, argv)
#define LOG_TERMINATE()                 DebugTerminate()

#ifdef WINDOWS
#define LOG_OUTPUT(s, ...) DebugOutputWindow(false, __LINE__, __FILE__, s, __VA_ARGS__)
#define LOGW(s, ...)       DebugOutputWindow(true , __LINE__, __FILE__, s, __VA_ARGS__)
#else
#define LOG_OUTPUT(s, ...)
#define LOGW(s, ...)
#endif
//DO NOT call these directly... This does not exist in release builds. Use the macro to disable it from release build
extern void DebugLog(const char* const message, Log level, int line, const char* const func);
extern void DebugLog(double message, Log level, int line, const char* const func);
extern void DebugPause();  //Pause the console output 
extern void DebugLineBreak();

extern void DebugOutputWindow(bool LogConsole, int line, const char* const file, const char* const formatString, ...);
extern void DebugInitInfo(int argc, char* argv[]);
extern void DebugTerminate();
#else
//Release Build
#define ASSERT(x) 
#define LOG(message, level) 
#define LOG_PAUSE() 
#define LOG_LINE_BREAK() 
#define LOG_INIT_PRINT()
#define LOG_TERMINATE() 

#define LOG_OUTPUT(s, ...)
#define LOGW(s, ...)
#endif