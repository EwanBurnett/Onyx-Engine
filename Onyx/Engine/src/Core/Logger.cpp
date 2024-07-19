#include "Onyx/Core/Logger.h"
#include <assert.h>
#if ONYX_PLATFORM_WINDOWS
#include <Windows.h>
#endif

FILE* Onyx::Log::m_Stream = stdout;

/**
 * @brief Prints a formatted message in White. 
*/
void Onyx::Log::Print(const char* fmt, ...) {
    va_list args;
    va_start(args, fmt);
    _Output(ELogColour::WHITE, m_Stream, fmt, args);
    va_end(args);
}

/**
  * @brief Only prints when ONYX_DEBUG is defined.
 */
void Onyx::Log::Debug(const char* fmt, ...)
{
#if ONYX_DEBUG
    va_list args;
    va_start(args, fmt);
    _Output(ELogColour::LIGHTGREEN, m_Stream, "[Debug] ");
    _Output(ELogColour::LIGHTGREEN, m_Stream, fmt, args);
    va_end(args);
#endif
}

/**
 * @brief Prints a Status message. 
*/
void Onyx::Log::Status(const char* fmt, ...)
{
    va_list args;
    va_start(args, fmt);
    _Output(ELogColour::LIGHTCYAN, m_Stream, fmt, args);
    va_end(args);
}

/**
 * @brief Prints a Success message.
 * @param fmt 
 * @param  
*/
void Onyx::Log::Success(const char* fmt, ...)
{
    va_list args;
    va_start(args, fmt);
    _Output(ELogColour::GREEN, m_Stream, fmt, args);
    va_end(args);
}

/**
 * @brief Prints a Failure message.
*/
void Onyx::Log::Failure(const char* fmt, ...)
{
    va_list args;
    va_start(args, fmt);
    _Output(ELogColour::BROWN, m_Stream, fmt, args);
    va_end(args);
}

/**
 * @brief Prints a Warning Message.
*/
void Onyx::Log::Warning(const char* fmt, ...)
{
    va_list args;
    va_start(args, fmt);
    _Output(ELogColour::YELLOW, m_Stream, "Warning\n");
    _Output(ELogColour::YELLOW, m_Stream, fmt, args);
    va_end(args);
}

/**
 * @brief Prints an Error message.
 * @param file The caller file. Pass `__FILE__`.
 * @param line The caller line. Pass `__LINE__`.
 * @param function The caller function. Pass `__PRETTY_FUNCTION__`.
*/
void Onyx::Log::Error(const char* file, int line, const char* function, const char* fmt, ...)
{
    va_list args;
    va_start(args, fmt);
    _Output(ELogColour::LIGHTRED, stderr, "Error\nFILE: %s\n\tLINE: %d\n\tFUNCTION: %s\n", file, line, function);
    _Output(ELogColour::LIGHTRED, stderr, fmt, args);
    if (m_Stream != stdout) {
        _Output(ELogColour::LIGHTRED, m_Stream, "Error\nFILE: %s\n\tLINE: %d\n\tFUNCTION: %s\n", file, line, function);
        _Output(ELogColour::LIGHTRED, m_Stream, fmt, args);
    }
    va_end(args);
}

/**
 * @brief Prints a Fatal Error message. This also triggers a Breakpoint. 
 * @param file The caller file. Pass `__FILE__`.
 * @param line The caller line. Pass `__LINE__`.
 * @param function The caller function. Pass `__PRETTY_FUNCTION__`.
*/
void Onyx::Log::Fatal(const char* file, int line, const char* function, const char* fmt, ...)
{
    va_list args;
    va_start(args, fmt);
    _Output(ELogColour::RED, stderr, "FATAL ERROR\nFILE: %s\n\tLINE: %d\n\tFUNCTION: %s\n", file, line, function);
    _Output(ELogColour::RED, stderr, fmt, args);
    if (m_Stream != stdout) {
        _Output(ELogColour::RED, m_Stream, "FATAL ERROR\nFILE: %s\n\tLINE: %d\n\tFUNCTION: %s\n", file, line, function);
        _Output(ELogColour::RED, m_Stream, fmt, args);
    }

    va_end(args);

    DebugBreak();
}

void Onyx::Log::SetOutputStream(FILE* stream)
{
    m_Stream = stream;
}

void Onyx::Log::_Output(ELogColour colour, FILE* stream, const char* fmt, va_list args) {

    //Change the output colour 
#if ONYX_PLATFORM_WINDOWS
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, (WORD)colour);
#else //Assume the program is running on linux
    switch (colour) {
    case ELogColour::BLACK:
        fprintf(stream, "\u001b[30m");
        break;
    case ELogColour::LIGHTBLUE:
    case ELogColour::BLUE:
        fprintf(stream, "\u001b[34m");
        break;
    case ELogColour::LIGHTGREEN:
    case ELogColour::GREEN:
        fprintf(stream, "\u001b[32m");
        break;
    case ELogColour::LIGHTCYAN:
    case ELogColour::CYAN:
        fprintf(stream, "\u001b[36m");
        break;
    case ELogColour::LIGHTRED:
    case ELogColour::RED:
        fprintf(stream, "\u001b[31m");
        break;
    case ELogColour::LIGHTMAGENTA:
    case ELogColour::MAGENTA:
        fprintf(stream, "\u001b[35m");
        break;
    case ELogColour::BROWN:
    case ELogColour::YELLOW:
        fprintf(stream, "\u001b[33m");
        break;
    case ELogColour::LIGHTGRAY:
    case ELogColour::DARKGRAY:
    case ELogColour::WHITE:
    default:
        fprintf(stream, "\u001b[0m");
        break;
    }
#endif

    vfprintf(stream, fmt, args);

    //Reset the output colour
#if ONYX_PLATFORM_WINDOWS
    SetConsoleTextAttribute(hConsole, (WORD)ELogColour::WHITE);
#else
    fprintf(stream, "\u001b[0m");
#endif
}

void Onyx::Log::_Output(ELogColour colour, FILE* stream, const char* fmt, ...)
{
    va_list args;
    va_start(args, fmt);
    _Output(colour, stream, fmt, args);
    va_end(args);
}
