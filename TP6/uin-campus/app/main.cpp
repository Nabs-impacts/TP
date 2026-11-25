#include "uincampus/uincampus.hpp"

#include <cstdlib>
#include <format>
#include <print>
#include <span>
#include <string>
#include <string_view>
#include <vector>

namespace {

enum class Suite { Continuer, Terminer, Erreur };

void afficherAide()
{
    std::println("Usage : uin-campus [--version] [--aide]");
    std::println("  --version   affiche la version et les informations de construction");
    std::println("  --aide      affiche cette aide");
}

[[nodiscard]] Suite traiterOptions(std::span<char*> arguments)
{
    if (arguments.size() <= 1) {
        return Suite::Continuer;
    }
    for (const std::string_view option : arguments.subspan(1)) {
        if (option == "--version") {
            std::println("{}", uin::informationsConstruction());
            return Suite::Terminer;
        }
        if (option == "--aide") {
            afficherAide();
            return Suite::Terminer;
        }
        std::println(stderr, "Option inconnue : {}", option);
        afficherAide();
        return Suite::Erreur;
    }
    return Suite::Continuer;
}

void afficherLigne(std::string_view libelle, std::string_view valeur)
{
    std::println("{:<24}{:>20}", libelle, valeur);
}

}

int main(int argc, char* argv[])
{
    switch (traiterOptions(std::span{argv, static_cast<std::size_t>(argc)})) {
    case Suite::Terminer: return EXIT_SUCCESS;
    case Suite::Erreur: return EXIT_FAILURE;
    case Suite::Continuer: break;
    }

    std::println("UIN-Campus {} — Relevé d'un étudiant\n", uin::version());

    const std::string nom = uin::lireTexte("Nom de l'étudiant : ");
    const int nbUE = uin::lireEntier("Nombre d'UE (1 à 30) : ", 1, 30);

    std::vector<double> notes;
    std::vector<double> coefficients;
    notes.reserve(static_cast<std::size_t>(nbUE));
    coefficients.reserve(static_cast<std::size_t>(nbUE));
    for (int i{1}; i <= nbUE; ++i) {
        notes.push_back(uin::lireNote(std::format("   Note de l'UE {} : ", i)));
        coefficients.push_back(
            static_cast<double>(uin::lireEntier(std::format("   Coefficient de l'UE {} : ", i), 1, 10)));
    }

    const double moyenneGenerale = uin::arrondir(uin::moyenne(notes, coefficients));
    const auto [mini, maxi, moyenneSimple, ecartType] = uin::calculerStatistiques(notes);
    const int validees = uin::compterValidees(notes);

    std::println("\n{:-<44}", "");
    afficherLigne("Étudiant", nom);
    afficherLigne("Moyenne pondérée", std::format("{:.2f}", moyenneGenerale));
    afficherLigne("Moyenne simple", std::format("{:.2f}", moyenneSimple));
    afficherLigne("Note min / max", std::format("{:.2f} / {:.2f}", mini, maxi));
    afficherLigne("Écart-type", std::format("{:.2f}", ecartType));
    afficherLigne("UE validées", std::format("{} / {}", validees, nbUE));
    afficherLigne("Mention", uin::libelle(uin::mentionPour(moyenneGenerale)));
    std::println("{:-<44}", "");

    return EXIT_SUCCESS;
}
