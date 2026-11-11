// TP 3 — Statistiques d'une série de notes
// Norme : C++23 (std::print, std::println). Compilateurs : GCC 14+, Clang 18+, MSVC 2022 (/utf-8)

#include <algorithm>
#include <array>
#include <cmath>
#include <cstddef>
#include <format>
#include <iostream>
#include <print>
#include <sstream>
#include <string>
#include <string_view>
#include <vector>

enum class Mention { Ajourne, Passable, AssezBien, Bien, TresBien };

constexpr std::size_t nbMentions = 5;
constexpr int nbEtudiantsMin = 1;
constexpr int nbEtudiantsMax = 200;
constexpr double noteMin = 0.0;
constexpr double noteMax = 20.0;
constexpr double seuilValidation = 10.0;

Mention mentionPour(double note)
{
    if (note < seuilValidation) { return Mention::Ajourne; }
    if (note < 12.0) { return Mention::Passable; }
    if (note < 14.0) { return Mention::AssezBien; }
    if (note < 16.0) { return Mention::Bien; }
    return Mention::TresBien;
}

std::string_view libelle(Mention m)
{
    using enum Mention;
    switch (m) {
    case Ajourne:   return "Ajourné";
    case Passable:  return "Passable";
    case AssezBien: return "Assez bien";
    case Bien:      return "Bien";
    case TresBien:  return "Très bien";
    }
    return "Inconnue";
}

// Conversion stricte : toute la ligne doit être un entier.
bool versEntier(const std::string& texte, int& resultat)
{
    std::istringstream flux{texte};
    char reste{};
    return (flux >> resultat) && !(flux >> reste);
}

// Conversion stricte : toute la ligne doit être un réel (virgule acceptée).
bool versReel(std::string texte, double& resultat)
{
    for (char& c : texte) {
        if (c == ',') { c = '.'; }
    }
    std::istringstream flux{texte};
    char reste{};
    return (flux >> resultat) && !(flux >> reste);
}

int lireEntier(std::string_view invite, int min, int max)
{
    while (std::cin) {
        std::cout << invite;
        std::string ligne;
        if (!std::getline(std::cin, ligne)) {
            break;
        }
        int valeur{};
        if (!versEntier(ligne, valeur)) {
            std::cout << "  Saisie invalide : entrez un nombre entier.\n";
        } else if (valeur < min || valeur > max) {
            std::cout << "  La valeur doit être comprise entre " << min << " et " << max << ".\n";
        } else {
            return valeur;
        }
    }
    return min; // fin d'entrée : valeur de repli
}

double lireNote(std::string_view invite)
{
    while (std::cin) {
        std::cout << invite;
        std::string ligne;
        if (!std::getline(std::cin, ligne)) {
            break;
        }
        double note{};
        if (!versReel(ligne, note)) {
            std::cout << "  Saisie invalide : entrez un nombre (ex. 12.5 ou 12,5).\n";
        } else if (note < noteMin || note > noteMax) {
            std::cout << "  La note doit être comprise entre 0 et 20.\n";
        } else {
            return note;
        }
    }
    return noteMin; // fin d'entrée : valeur de repli
}

int main()
{
    std::cout << "Nom de l'UE : ";
    std::string ue;
    std::getline(std::cin, ue);

    const int nb = lireEntier("Nombre d'étudiants (1 à 200) : ", nbEtudiantsMin, nbEtudiantsMax);

    std::vector<double> notes;
    notes.reserve(static_cast<std::size_t>(nb));
    for (int i{1}; i <= nb; ++i) {
        notes.push_back(lireNote(std::format("Note de l'étudiant {} : ", i)));
    }

    double minimum{noteMax};
    double maximum{noteMin};
    double somme{0.0};
    int admis{0};
    std::array<int, nbMentions> repartition{};

    for (double n : notes) {
        minimum = std::min(minimum, n);
        maximum = std::max(maximum, n);
        somme += n;
        if (n >= seuilValidation) { ++admis; }
        ++repartition[static_cast<std::size_t>(mentionPour(n))];
    }

    const double taille = static_cast<double>(notes.size());
    const double moyenne = somme / taille;

    double sommeEcarts{0.0};
    for (double n : notes) {
        sommeEcarts += (n - moyenne) * (n - moyenne);
    }
    const double ecartType = std::sqrt(sommeEcarts / taille);

    std::println("\nStatistiques — {} ({} étudiants)", ue, nb);
    std::println("{:-<58}", "");
    std::println("{:<18}: {:6.2f}", "Note minimale", minimum);
    std::println("{:<18}: {:6.2f}", "Note maximale", maximum);
    std::println("{:<18}: {:6.2f}", "Moyenne", moyenne);
    std::println("{:<18}: {:6.2f}", "Écart-type", ecartType);
    std::println("{:<18}: {:6} ({:.1f} %)", "Admis", admis, 100.0 * admis / taille);

    std::println("\nRépartition par mention");
    for (std::size_t i{0}; i < nbMentions; ++i) {
        const auto m = static_cast<Mention>(i);
        std::println("{:<12} {} ({})", libelle(m),
                     std::string(static_cast<std::size_t>(repartition[i]), '*'), repartition[i]);
    }
}
