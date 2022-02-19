# Se familiariser avec l'existant

## A- Exécution

**Allez dans le fichier tower_sim.cpp et recherchez la fonction responsable de gérer les inputs du programme. Sur quelle touche faut-il appuyer pour ajouter un avion ? Comment faire pour quitter le programme ? A quoi sert la touche 'F' ?**  

La fonction responsable de gérer les inputs est `create_keystrokes`.  
Pour ajouter un avion, on utilise la touche `c`. Les touches `q` et `x` permettent de quitter le programme.  
La touche `f` permet de passer l'affichage en plein-écran.  


**Ajoutez un avion à la simulation et attendez. Que est le comportement de l'avion ? Quelles informations s'affichent dans la console ?**  

L'avion apparait dans la fenêtre, atterri, se déplace dans l'aéroport, décole puis recommence la procédure.  
La console affiche les actions de l'avion ainsi que son nom.  


**Ajoutez maintenant quatre avions d'un coup dans la simulation. Que fait chacun des avions ?**  

En créant 4 avions, on se rend compte que seuls 3 avions peuvent entrer dans l'aéroport en simultanés.  
Les avions supplémentaires effectuent alors des tours au dessus de l'aéroport en attendant qu'une place se libère.  
A part cette réglementation, la procédure ne change pas.  


## B- Analyse du code

**Listez les classes du programme à la racine du dossier src/. Pour chacune d'entre elle, expliquez ce qu'elle représente et son rôle dans le programme.**  

Les classes présentent à la racine du dossier src/ sont :  
* AircraftType : représente chaque type d'avion possible
* Aircraft : représente chaque avion
* AirportType : représente le type d'aéroport
* Airport : représente l'aéroport lui-même
* Point2D et Point3D : permettent de faire des opérations sur des points
* Runway : représente la piste de l'aéroport
* Terminal : représente les terminaux de l'aéroport
* TowerSimulation : permet d'initialiser le programme, créer des avions, etc...
* Tower : représente la tour de controle de l'aéroport
* WaypointType : représente les routes de l'aéroport (air, sol, terminal)
* Waypoint : représente une route de l'aéroport


**Pour les classes Tower, Aircaft, Airport et Terminal, listez leurs fonctions-membre publiques et expliquez précisément à quoi elles servent. Réalisez ensuite un schéma présentant comment ces différentes classes intéragissent ensemble.**  

Classe Tower :  
* get_instructions : guide les avions autour de l'aéroport (ie : leur assigne un terminal ou les fait repartir, leur refait faire un tour au dessus de l'aéroport s'il n'y a pas de place)
* arrived_at_terminal : permet de commencer le service à l'arrivée de l'avion dans un terminal

Classe Aircraft :
* get_flight_num : donne le numéro du vol
* distance_to : donne la distance de l'avion par rapport à un point
* display : affiche l'avion
* move : déplace l'avion

Classe Airport :
* get_tower : donne la tour de l'aéroport
* display : affiche l'aéroport
* move : appelle la méthode `move` de chaque terminaux

Classe Terminal : 
* in_use : détermine si le terminal est utilisé
* is_servicing : détermine s'il y a encore un service en cours dans le terminal
* assign_craft : assigne un avion au terminal
* start_service : commence le service de l'avion assigné dans le terminal
* finish_service : termine le service de l'avion
* move : fait progresser les étapes du service de l'avion

Schéma de l'interraction de ces classes entre elles :   
![]()


**Quelles classes et fonctions sont impliquées dans la génération du chemin d'un avion ? Quel conteneur de la librairie standard a été choisi pour représenter le chemin ? Expliquez les intérêts de ce choix.**  

La classe `Aircraft` avec la fonction `add_waypoint`, la classe `AirportType` avec les fonctions `air_to_terminal` et `terminal_to_air` ainsi que la classe `Tower` avec `get_instructions` permettent de générer le chemin d'un avion.  
Le chemin est contenu dans une `std::deque<Waypoint>`, ce qui implémente une FIFO et est parfait pour représenter une route à suivre.  


## C- Bidouillons !

**Déterminez à quel endroit du code sont définies les vitesses maximales et accélération de chaque avion. Le Concorde est censé pouvoir voler plus vite que les autres avions. Modifiez le programme pour tenir compte de cela.**  

Les spécifications de chaque avions sont définies dans `AircraftType`.  
Le Concorde vole maintenant plus vite que les autres avions (.08f au lieu de .05f).  


