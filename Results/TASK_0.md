# Se familiariser avec l'existant

## A- Exécution

**Allez dans le fichier tower_sim.cpp et recherchez la fonction responsable de gérer les inputs du programme. Sur quelle touche faut-il appuyer pour ajouter un avion ? Comment faire pour quitter le programme ? A quoi sert la touche 'F' ?**  

La fonction responsable de gérer les inputs est `create_keystrokes`.  
Pour ajouter un avion, on utilise la touche `C`. Les touches `Q` et `X` permettent de quitter le programme.  
La touche `F` permet de passer l'affichage en plein-écran.  


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


**Identifiez quelle variable contrôle le framerate de la simulation. Ajoutez deux nouveaux inputs au programme permettant d'augmenter ou de diminuer cette valeur. Essayez maintenant de mettre en pause le programme en manipulant ce framerate. Que se passe-t-il ?**  
**Ajoutez une nouvelle fonctionnalité au programme pour mettre le programme en pause, et qui ne passe pas par le framerate.**  

La variable qui contrôle le framerate est `ticks_per_sec`, initialisé au départ avec la variable `DEFAULT_TICKS_PER_SEC` une constante.  

Pour augmenter le framerate on utilisera la touche `A` et pour le diminuer la touche `S`.  

Si on essaie de mettre en pause le programme en passant le framerate à 0, on obtient une erreur de type *`floating point exception`*.  
Pour éviter cette erreur, quand on diminue le framerate, on l'empèchera de passer sous `1u`.  

Pour mettre le jeu en pause, on utilisera la touche `P`.  
Pour ajouter cette fonctionnalité, on créé un flag permettant de savoir si le jeu est actuellement en pause. Si c'est le cas, on ne déplace pas les avions présents à l'image (dans la fonction `timer`).  


**Identifiez quelle variable contrôle le temps de débarquement des avions et doublez-le.**  

La variable qui contrôle le temps de débarquement est `SERVICE_CYCLES`.  


**Lorsqu'un avion a décollé, il réattérit peu de temps après. Faites en sorte qu'à la place, il soit retiré du programme.**  
**Indices :**  
**A quel endroit pouvez-vous savoir que l'avion doit être supprimé ?**  
**Pourquoi n'est-il pas sûr de procéder au retrait de l'avion dans cette fonction ? A quel endroit de la callstack **pourriez-vous le faire à la place ?**  
**Que devez-vous modifier pour transmettre l'information de la première à la seconde fonction ?**  

L'avion peut être supprimé après avoir redécollé, au moment de l'appel à la fonction `get_instructions`.  
Si on supprime l'avion à cet endroit, l'itérateur qu'on retrouve plus tard dans `timer` sera invalidé. On pourrai donc plutôt le supprimer directement dans timer en changeant la boucle foreach pour une boucle for avec itérateur.  
Pour transmettre l'information, il faut modifier le retour de la fonction `move` en `bool`.  


**Lorsqu'un objet de type Displayable est créé, il faut ajouter celui-ci manuellement dans la liste des objets à afficher. Il faut également penser à le supprimer de cette liste avant de le détruire. Faites en sorte que l'ajout et la suppression de display_queue soit "automatiquement gérée" lorsqu'un Displayable est créé ou détruit. Pourquoi n'est-il pas spécialement pertinent d'en faire de même pour DynamicObject ?**  

...


**La tour de contrôle a besoin de stocker pour tout `Aircraft` le `Terminal` qui lui est actuellement attribué, afin de pouvoir le libérer une fois que l'avion décolle.**  
**Cette information est actuellement enregistrée dans un `std::vector<std::pair<const Aircraft*, size_t>>` (size_t représentant l'indice du terminal).**  
**Cela fait que la recherche du terminal associé à un avion est réalisée en temps linéaire, par rapport au nombre total de terminaux.**  
**Cela n'est pas grave tant que ce nombre est petit, mais pour préparer l'avenir, on aimerait bien remplacer le vector par un conteneur qui garantira des opérations efficaces, même s'il y a beaucoup de terminaux.**  
**Modifiez le code afin d'utiliser un conteneur STL plus adapté. Normalement, à la fin, la fonction `find_craft_and_terminal(const Aicraft&)` ne devrait plus être nécessaire.**  

On remplace `std::vector<std::pair<const Aircraft*, size_t>>` par `std::map<const Aircraft*, size_t>`.  
La fonction `find_craft_and_terminal(const Aicraft&)` n'est plus nécessaire et est remplacée par la fonction `find` associée au map.  