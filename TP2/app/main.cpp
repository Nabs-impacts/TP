#include "uincampus/version.hpp"
#include <print>

int main() {
    std::println("UIN-Campus\nSystème de gestion académique");
    std::println("Version {}", uin::version());
}
