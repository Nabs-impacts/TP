#pragma once

#include "uincampus/regles.hpp"

#include <span>

namespace uin {

struct Statistiques {
    double minimum{};
    double maximum{};
    double moyenne{};
    double ecartType{};
};

[[nodiscard]] double somme(std::span<const double> valeurs);

[[nodiscard]] double moyenne(std::span<const double> notes);

[[nodiscard]] double moyenne(std::span<const double> notes,
                             std::span<const double> coefficients);

[[nodiscard]] Statistiques calculerStatistiques(std::span<const double> notes);

[[nodiscard]] int compterValidees(std::span<const double> notes,
                                  double seuil = seuilValidation);

[[nodiscard]] double arrondir(double valeur, int decimales = 2);

}
