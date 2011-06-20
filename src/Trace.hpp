
#ifndef TRACE_HPP_GUARD
#define TRACE_HPP_GUARD

#include <iostream>
#include <string>

class Trace
{
  public:
     Trace(std::string const& msg, std::ostream& os = std::cout);
    ~Trace(void                                                );

  private:
    std::string   msg_;
    std::ostream& os_;
};

#define TRACE_ALWAYS(MSG)                       \
    Trace const trace##__FILE__##__LINE__ (MSG)

#define TRACE_FUNC_ALWAYS                                       \
    Trace const trace##__FILE__##__LINE__ (std::string(__PRETTY_FUNCTION__))

#define TRACE_FUNC_MSG_ALWAYS(MSG)                                  \
    Trace const trace##__FILE__##__LINE__ (std::string(__PRETTY_FUNCTION__) + MSG)

#endif // TRACE_HPP_GUARD

// this following is intentionally outside the include guards
// so that different files may have different settings for
// ENABLE_TRACE

#ifdef TRACE
#undef TRACE
#endif

#ifdef TRACE_FUNC
#undef TRACE_FUNC
#endif

#ifdef ENABLE_TRACE
#define TRACE(MSG) TRACE_ALWAYS(MSG)
#define TRACE_FUNC TRACE_FUNC_ALWAYS
#define TRACE_FUNC_MSG(MSG) TRACE_FUNC_MSG_ALWAYS(MSG)
#else
#define TRACE(MSG)
#define TRACE_FUNC(MSG)
#define TRACE_FUNC_MSG(MSG)
#endif
