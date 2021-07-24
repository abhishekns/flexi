#include <iostream>
#include <string>

#if BUILDING_LIBFLEXI && HAVE_VISIBILITY
#define LIBFLEXI_DLL_EXPORTED __attribute__((__visibility__("default")))
#elif BUILDING_LIBFLEXI && defined _MSC_VER
#define LIBFLEXI_DLL_EXPORTED __declspec(dllexport)
#elif defined _MSC_VER
#define LIBFLEXI_DLL_EXPORTED __declspec(dllimport)
#else
#define LIBFLEXI_DLL_EXPORTED
#endif


#ifndef __FUNCTION_NAME__
    #ifdef WIN32   //WINDOWS
        #define __FUNCTION_NAME__   __FUNCTION__
        #define __LINE_NO__
        #define __FILE_NAME__
    #else          //*NIX
        #define __FUNCTION_NAME__   __func__
        #define __LINE_NO__ __LINE__
        #define __FILE_NAME__ __FILE__
    #endif
#endif


namespace flexiobjects {
namespace logging {

LIBFLEXI_DLL_EXPORTED class Logger {
private:
    static int loggingEnabled;
public:
    static void enableLogging();
    static void disableLogging();
    static bool isLoggingEnabled();
};

#define TRACE(x) if (Logger::isLoggingEnabled()) std::cout  << __TIMESTAMP__  << ":" << __FILE_NAME__ << ":" << __FUNCTION_NAME__  << ":" << __LINE_NO__ << x <<std::endl;

#define TRACE_FUNC_START    TRACE(": start")
#define TRACE_FUNC_END      TRACE(": end")


#define traceStart() TRACE_FUNC_START
#define traceEnd() TRACE_FUNC_END
#define trace(message) TRACE(message)



} // logging
} // flexiobjects