#ifndef ONYX_CORE_UTILITY_H
#define ONYX_CORE_UTILITY_H

#ifdef _MSC_VER
#define __PRETTY_FUNCTION__ __FUNCSIG__
#endif

#if ONYX_PLATFORM_WINDOWS
#include <codecvt> 
#include <string>
#endif


namespace Onyx {

    /**
     * @brief Issues a Breakpoint
     * @remarks Available in Debug configurations only. 
    */
    void DebugBreak();

#if ONYX_PLATFORM_WINDOWS
    /**
    * \brief Converts a Wide String to an ANSI String
    * \param wide
    * \return
   */
    inline std::string WStringToString(const std::wstring& wide)
    {
        //Create a wstring converter
        static std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t> cvt;

        //Return the converted wstring
        return(cvt.to_bytes(wide));
    }

    /**
     * \brief Converts an ANSI String to a Wide String
     * \param str
     * \return
    */
    inline std::wstring StringToWString(const std::string& str)
    {
        if (str.empty() == false) {
            //Create a wstring converter
            static std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t> cvt;

            //Return the converted string
            return(cvt.from_bytes(str));
        }
        else {
            return L"";
        }
    }
#endif

}

#endif