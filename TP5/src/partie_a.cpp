#include "tableau.hpp"

#include <print>

int main()
{
    TableauDynamique notes;
    for (int i{0}; i < 10; ++i) {
        ajouter(notes, 10.0 + i);
        std::println("taille {:>2}, capacité {:>2}", notes.taille, notes.capacite);
    }
    std::println("element 2 : {}", element(notes, 2));
    liberer(notes);
}
