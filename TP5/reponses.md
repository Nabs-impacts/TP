# TP 5 - Reponses

## Partie A
1. Compilation avec -fsanitize=address,undefined : aucun rapport, c'est normal (CMakeLists deja configure comme ca).
2. Quand taille == capacite, la fonction ajouter :
   - calcule la nouvelle capacite (4 au premier ajout, sinon le double) ;
   - alloue un nouveau tableau plus grand avec new[] ;
   - recopie les anciens elements dans le nouveau tableau ;
   - libere l'ancien tableau avec delete[] ;
   - met a jour le pointeur donnees et la capacite.
   Ensuite la valeur est ajoutee a la fin et taille augmente de 1. Capacites observees : 4, 4, 4, 4, 8, 8, 8, 8, 16, 16.
3. Sans liberer : LeakSanitizer signale "detected memory leaks - Direct leak of 128 byte(s)" (16 double x 8 octets).
4. Avec delete au lieu de delete[] : ASan signale alloc-dealloc-mismatch (operator new [] vs operator delete).
5. La fonction element() est dans tableau.hpp : elle verifie l'indice avec assert avant de renvoyer la reference.

## Partie B
1. ASan signale attempting double-free, au second appel de liberer (celui de notes).
2. copie = notes copie les membres un par un : copie.donnees contient la meme adresse que notes.donnees.
   Les deux structures croient posseder le meme tableau (copie superficielle). Le premier liberer libere le tableau,
   le second le libere une deuxieme fois. Il faudrait une copie profonde : allouer un nouveau tableau et y recopier
   les elements (regle des 3 / des 5, chapitre 9).

## Partie C
Avec std::vector : pas de fonction ajouter, pas de fonction liberer, pas de new/delete, moins de lignes.
Aucune fuite et aucune double liberation possible, et la copie est correcte (copie profonde) par defaut.
