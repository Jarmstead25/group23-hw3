
#include "address.h"
#include <sstream>

string address::address_info()
{
    std::ostringstream output;

    output << address_line1 << "\n";
    output << address_line2 << "\n";
    output << city << "\n";
    output << state << "\n";
    output << zip << "\n";

    return output.str();
}

