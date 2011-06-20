
#include "Trace.hpp"

Trace::Trace(std::string const& msg, std::ostream& os)
    : msg_(msg),
      os_ (os)
{
    os_ << "-> " << msg_ << "\n";
}

Trace::~Trace(void)
{
    os_ << "<- " << msg_ << std::endl;
}
