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


