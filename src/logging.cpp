#include "logging.h"

namespace flexiobjects {
namespace logging {

#ifndef _MSC_VER
int Logger::loggingEnabled = 0;
#endif

void Logger::enableLogging() {
    loggingEnabled = 1;
}

void Logger::disableLogging() {
    loggingEnabled = 0;
}
bool Logger::isLoggingEnabled() {
    return (loggingEnabled) ? true : false;
}

}
}