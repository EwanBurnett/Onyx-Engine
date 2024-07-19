#ifndef ONYX_UTILITY_H
#define ONYX_UTILITY_H

#ifdef _MSC_VER
#define __PRETTY_FUNCTION__ __FUNCSIG__
#endif

namespace Onyx {

    /**
     * @brief Issues a Breakpoint
     * @remarks Available in Debug configurations only. 
    */
    void DebugBreak();

}

#endif