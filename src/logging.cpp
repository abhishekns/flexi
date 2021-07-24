#include "logging.h"

namespace flexiobjects {
namespace logging {

int Logger::loggingEnabled = 0;

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