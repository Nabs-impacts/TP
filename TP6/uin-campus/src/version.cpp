#include "uincampus/version.hpp"
#include "uincampus/config.hpp"

#include <format>

namespace uin {

namespace {

std::string compilateur()
{
#if defined(__clang__)
    return std::format("Clang {}.{}.{}", __clang_major__, __clang_minor__,
                       __clang_patchlevel__);
#elif defined(__GNUC__)
    return std::format("GCC {}.{}.{}", __GNUC__, __GNUC_MINOR__, __GNUC_PATCHLEVEL__);
#elif defined(_MSC_VER)
    return std::format("MSVC {}", _MSC_VER);
#else
    return "compilateur inconnu";
#endif
}

}

std::string_view version()
{
    return config::version;
}

std::string informationsConstruction()
{
    const std::string_view configuration =
        config::typeConstruction.empty() ? std::string_view{"multi-configuration"}
                                         : config::typeConstruction;
    return std::format("{} {} — {} — C++ ({}) — {}",
                       config::nomProjet, config::version, compilateur(),
                       __cplusplus, configuration);
}

}
