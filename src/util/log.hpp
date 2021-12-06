#ifndef util_log_hpp
#define util_log_hpp

#include <iostream>

#include <boost/log/trivial.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/utility/setup/file.hpp>

namespace logging = boost::log;

namespace Log {
    void initialize();
    void log(std::string string);
}

#endif