#pragma once

#include <array>
#include <string_view>

namespace uin {

inline constexpr double noteMin = 0.0;
inline constexpr double noteMax = 20.0;
inline constexpr double seuilValidation = 10.0;

enum class Mention { Ajourne, Passable, AssezBien, Bien, TresBien };

inline constexpr std::array seuilsMentions{10.0, 12.0, 14.0, 16.0};

static_assert(seuilsMentions.size() == 4, "Un seuil par mention au-dessus d'Ajourné");
static_assert(seuilsMentions[0] == seuilValidation,
              "La mention Passable commence au seuil de validation");

constexpr bool estNoteValide(double note)
{
    return note >= noteMin && note <= noteMax;
}

Mention mentionPour(double moyenne);
std::string_view libelle(Mention mention);

}
