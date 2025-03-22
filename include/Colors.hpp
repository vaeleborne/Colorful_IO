#ifndef COLORS_HPP
#define COLORS_HPP
#include <string>
namespace ColorfulIO::Colors
{
    const std::string RESET = "\x1b[0m";
    namespace Foreground
    {
        const std::string BLACK     =    "\x1b[30m";
        const std::string RED       =    "\x1b[31m";
        const std::string GREEN     =    "\x1b[32m";
        const std::string YELLOW    =    "\x1b[33m";
        const std::string BLUE      =    "\x1b[34m";
        const std::string MAGENTA   =    "\x1b[35m";
        const std::string CYAN      =    "\x1b[36m";
        const std::string WHITE     =    "\x1b[37m";


        const std::string BOLD_BLACK     =    "\x1b[1;30m";
        const std::string BOLD_RED       =    "\x1b[1;31m";
        const std::string BOLD_GREEN     =    "\x1b[1;32m";
        const std::string BOLD_YELLOW    =    "\x1b[1;33m";
        const std::string BOLD_BLUE      =    "\x1b[1;34m";
        const std::string BOLD_MAGENTA   =    "\x1b[1;35m";
        const std::string BOLD_CYAN      =    "\x1b[1;36m";
        const std::string BOLD_WHITE     =    "\x1b[1;37m";

        const std::string HI_BLACK     =    "\x1b[90m";
        const std::string HI_RED       =    "\x1b[91m";
        const std::string HI_GREEN     =    "\x1b[92m";
        const std::string HI_YELLOW    =    "\x1b[93m";
        const std::string HI_BLUE      =    "\x1b[94m";
        const std::string HI_MAGENTA   =    "\x1b[95m";
        const std::string HI_CYAN      =    "\x1b[96m";
        const std::string HI_WHITE     =    "\x1b[97m";
    }

    namespace Background
    {
        const std::string BLACK     =    "\x1b[40m";
        const std::string RED       =    "\x1b[41m";
        const std::string GREEN     =    "\x1b[42m";
        const std::string YELLOW    =    "\x1b[43m";
        const std::string BLUE      =    "\x1b[44m";
        const std::string MAGENTA   =    "\x1b[45m";
        const std::string CYAN      =    "\x1b[46m";
        const std::string WHITE     =    "\x1b[47m";

        const std::string HI_BLACK     =    "\x1b[100m";
        const std::string HI_RED       =    "\x1b[101m";
        const std::string HI_GREEN     =    "\x1b[102m";
        const std::string HI_YELLOW    =    "\x1b[103m";
        const std::string HI_BLUE      =    "\x1b[104m";
        const std::string HI_MAGENTA   =    "\x1b[105m";
        const std::string HI_CYAN      =    "\x1b[106m";
        const std::string HI_WHITE     =    "\x1b[107m";

    }
}

#endif