# Assertions et exceptions

## Objectif 1 - Crash des avions

Actuellement, quand un avion s'écrase, une exception de type `AircraftCrash` (qui est un alias de `std::runtime_error` déclaré dans `config.hpp`) est lancée.

**1. Faites en sorte que le programme puisse continuer de s'exécuter après le crash d'un avion. Pour cela, remontez l'erreur jusqu'à un endroit approprié pour procéder à la suppression de cet avion (assurez-vous bien que plus personne ne référence l'avion une fois l'exception traitée). Vous afficherez également le message d'erreur de l'exception dans `cerr`.**  

On fait remonter l'erreur dans la fonction `move` de `AircraftManager` et on la traite dans un try-catch.  
On fait en sorte que l'avion soit supprimé si l'exception est levée.  

**2. Introduisez un compteur qui est incrémenté chaque fois qu'un avion s'écrase. Choisissez une touche du clavier qui n'a pas encore été utilisée (`m` par exemple ?) et affichez ce nombre dans la console lorsque l'utilisateur appuie dessus.**  

On créé une nouvelle clé dans la fonction `TowerSimulation::create_keystrokes`. La touche associée est `m`.  
Appuyer sur cette touche permet d'afficher le nombre de crashs depuis le lancement du programme.  

Dans la classe `AircraftManager`, on ajoute un attribut privé représentant le nombre de crash. Cet attribut est incrémenté à chaque fois qu'une exception de type `AircraftCrash` est levée.  
On ajoute aussi une fonction qui affiche le nombre de crash. C'est cette fonction qui est appelé dans `TowerSimulation::create_keystrokes`.  

**3. Si vous avez fini d'implémenter la gestion du kérosène (Task_2 - Objectif 2 - A), lancez une exception de type `AircraftCrash` lorsqu'un avion tombe à court d'esssence. Normalement, cette exception devrait être traitée de la même manière que lorsqu'un avion s'écrase parce qu'il a attérit trop vite.**  

A la place d'afficher un messag et retourner `false` dans `Aircraft::move`, on lance une `AircraftCrash` avec un message indiquand qu'il n'y avait plus assez de fuel.  
Le traitement dans la fonction `move` de `AircraftManager` reste inchangé.  

**4. **BONUS** Rédéfinissez `AircraftCrash` en tant que classe héritant de `std::runtime_error`, plutôt qu'en tant qu'alias. Arrangez-vous pour que son constructeur accepte le numéro de vol, la position, la vitesse de l'avion au moment du crash, et la raison du crash (`"out of fuel"` / `"bad landing"`). Vous utiliserez toutes ces informations pour générer le joli message de l'exception.**  

On créé une classe `AircraftCrash` qui hérite de `std::runtime_error`.  
On utilise maintenant cette classe pour remonter des exceptions à la place de l'alias initial.  
Cette classe prend le numéro de vol, la position et la vitesse de l'avion au moment du crash ainsi qu'un message.  



## Objectif 2 - Détecter les erreurs de programmation

**Pour sécuriser votre code, repassez sur les différentes fonctions de votre programme et ajoutez des assertions permettant de vérifier qu'elles sont correctement utilisées.**  
**Voici quelques idées :**  
**- fonctions d'initialisation appelées une seule fois**  
**- état attendu d'un objet lorsqu'une fonction est appelée dessus**  
**- vérification de certains paramètres de fonctions**  
**- ...**  

On rajoute des `assert(...)` dans plusieurs fonctions afin de sécuriser le code.  
On vérifie ainsi que les paramètres donnés aux fonctions ne sont pas nuls.  
