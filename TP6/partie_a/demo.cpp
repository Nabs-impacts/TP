#include "uincampus/calculs.hpp"
#include "uincampus/regles.hpp"

#include <print>
#include <vector>

int main()
{
    const std::vector<double> notes{12.0, 15.0, 9.0, 14.5};
    const double m = uin::moyenne(notes);
    std::println("Moyenne : {:.2f}", m);
    std::println("Mention : {}", uin::libelle(uin::mentionPour(m)));
    std::println("Validées : {}", uin::compterValidees(notes));
}
