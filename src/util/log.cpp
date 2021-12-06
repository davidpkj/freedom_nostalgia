#include "log.hpp"

namespace Log
{
    void initialize()
    {
        logging::add_file_log("latest.log");
        logging::core::get() -> set_filter(logging::trivial::severity >= logging::trivial::info);
    }

    void log(std::string string) {
        BOOST_LOG_TRIVIAL(info) << string; 
    }
}