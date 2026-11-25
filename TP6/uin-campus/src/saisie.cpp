#include "uincampus/saisie.hpp"
#include "uincampus/regles.hpp"

#include <iostream>
#include <sstream>

namespace uin {

namespace {

struct EntierLu {
    bool valide{false};
    int valeur{0};
};

struct ReelLu {
    bool valide{false};
    double valeur{0.0};
};

std::string lireLigne(std::string_view invite)
{
    std::cout << invite;
    std::string ligne;
    std::getline(std::cin, ligne);
    return ligne;
}

[[nodiscard]] EntierLu versEntier(const std::string& texte)
{
    std::istringstream flux{texte};
    int valeur{};
    char reste{};
    const bool valide = static_cast<bool>(flux >> valeur) && !(flux >> reste);
    return {valide, valeur};
}

[[nodiscard]] ReelLu versReel(std::string texte)
{
    for (char& c : texte) {
        if (c == ',') {
            c = '.';
        }
    }
    std::istringstream flux{texte};
    double valeur{};
    char reste{};
    const bool valide = static_cast<bool>(flux >> valeur) && !(flux >> reste);
    return {valide, valeur};
}

}

std::string lireTexte(std::string_view invite)
{
    return lireLigne(invite);
}

int lireEntier(std::string_view invite, int min, int max)
{
    while (std::cin) {
        const auto [valide, valeur] = versEntier(lireLigne(invite));
        if (!valide) {
            std::cout << "   Saisie invalide : entrez un nombre entier.\n";
        } else if (valeur < min || valeur > max) {
            std::cout << "   La valeur doit être comprise entre " << min << " et " << max << ".\n";
        } else {
            return valeur;
        }
    }
    return min;
}

double lireNote(std::string_view invite)
{
    while (std::cin) {
        const auto [valide, note] = versReel(lireLigne(invite));
        if (!valide) {
            std::cout << "   Saisie invalide : entrez un nombre (ex. 12.5 ou 12,5).\n";
        } else if (!estNoteValide(note)) {
            std::cout << "   La note doit être comprise entre " << noteMin << " et " << noteMax << ".\n";
        } else {
            return note;
        }
    }
    return noteMin;
}

}
