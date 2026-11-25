#pragma once

#include <string>
#include <string_view>

namespace uin {

std::string lireTexte(std::string_view invite);
int lireEntier(std::string_view invite, int min, int max);
double lireNote(std::string_view invite);

}
