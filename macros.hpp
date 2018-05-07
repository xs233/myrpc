#ifndef __MACROS_HPP__
#define __MACROS_HPP__

namespace myrpc {

#undef DISALLOW_EVIL_CONSTRUCTORS
#define DISALLOW_EVIL_CONSTRUCTORS(TypeName)    \
    TypeName(const TypeName&) = delete;         \
    void operator=(const TypeName&) = delete

} // namespace myrpc

#endif