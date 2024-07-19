#ifndef ONYX_LOGGER_H
#define ONYX_LOGGER_H
/**
* @file Logger.h
* @brief A Collection of Console Logging Utilities.
*
* ------------------------------------------
* @author Ewan Burnett(EwanBurnettSK@Outlook.com)
* @date 2024 - 07 - 19
*/
#include "Utility.h"
#include <cstdio> 
#include <cstdarg>

namespace Onyx {

    /**
     * @brief Class wrapper for Logging functions. 
    */
    class Log {
    public:
        enum class ELogColour {
            BLACK = 0,
            BLUE,
            GREEN,
            CYAN,
            RED,
            MAGENTA,
            BROWN,
            LIGHTGRAY,
            DARKGRAY,
            LIGHTBLUE,
            LIGHTGREEN,
            LIGHTCYAN,
            LIGHTRED,
            LIGHTMAGENTA,
            YELLOW,
            WHITE,
        };

        static void Print(const char* fmt, ...);
        static void Debug(const char* fmt, ...);
        static void Message(const char* fmt, ...);
        static void Success(const char* fmt, ...);
        static void Failure(const char* fmt, ...);
        static void Warning(const char* fmt, ...);
        static void Error(const char* file, int line, const char* function, const char* fmt, ...);
        static void Fatal(const char* file, int line, const char* function, const char* fmt, ...);

        /**
         * @brief Sets the output FILE stream. set to stdout by default.
         * @param stream a FILE handle to output into. 
        */
        static void SetOutputStream(FILE* stream); 
    private:
        static void _Output(ELogColour colour, FILE* stream, const char* fmt, va_list args);
        static void _Output(ELogColour colour, FILE* stream, const char* fmt, ...);

        static FILE* m_Stream; 
    };
}

#endif