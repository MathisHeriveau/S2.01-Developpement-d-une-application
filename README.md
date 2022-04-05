# S2.01 - D'éveloppement d'une application

## Introduction 

## Version 0 de notre chifoumi 

Objectif de cette première version :
- Source C++ de la classe Chifoumi dans un projet Non Qt

Tâche que nous avons éffectué : 
- Créer un dépot GitHub permettant le versionning
- Création du projet Non Qt
- Remplissage du Word : Dossier d'analyse de conception
- Complétion de la classe Chifoumi

Nous nous sommes organisé de la façons suivant :
Arthur a produit le dossier d'analyse de conception et a créé le GitIgnore
Mathis a créé le projet QT et mis en place le dépot GitHub
Colas a remplie le fichier Chifoumi.cpp et nous l'a fait validé

## Version 1 de notre chifoumi 

Objectif de cette première version :
- Version décrite dans le paragraphe §1 précédent. La barre de menus est inactive


L’utilisateur joue seul contre la machine 
 Lorsque l’utilisateur lance le programme, le plateau se remplit avec les éléments du jeu et se met en état initial 
(cf. Figure 1) : 
- Partie haute : des zones de visualisation, où l’utilisateur pour consulter les informations qui le concernent (zone 
intitulée « Vous »), à savoir son score, le dernier coup qu’il a joué, ainsi que les informations concernant la 
machine, à savoir le score de la machine et le dernier coup qu’elle a joué. 
- Partie basse : des zones d’interaction, où l’utilisateur peut jouer un nouveau coup, ou bien commencer une 
nouvelle partie. 
- A l’état initial, le bouton « Nouvelle partie » est activé et détient le focus, les boutons contenant les figures 
(ciseau, papier, pierre) sont inactifs1
. 
• Lorsque la partie en cours (cf. Figure 2), le déroulement d’une manche est le suivant : 
- Les boutons-figures sont actifs. Les nom et score du joueur sont de couleur bleue2
 : c’est donc son tour de 
jouer. Il joue en sélectionnant la figure qu’il souhaite tirer (pierre, papier, ciseau). La figure choisie s’affiche 
dans la zone d’affichage correspondante. 
- Les nom et score du joueur machine sont de couleur bleue : c’est donc son tour de jouer. Il choisit aussi une 
figure. Il s’agit d’un choix aléatoire. La figure est affichée dans la zone adéquate. 
- Les scores sont mis à jour : + 1 point en fonction du coup de chacun (pierre gagne à ciseau, ciseau gagne à 
papier, papier gagne à pierre). Les scores restent inchangés en cas de coup identique. Une fois recalculés, les 
scores de chaque joueur sont affichés dans les zones prévues. 
- A la fin de la manche, le joueur peut jouer une autre manche (en choisissant une figure), recommencer la partie 
(les scores sont remis à 0), ou bien arrêter le jeu (fermeture de la fenêtre). Il n’y a pas de gagnant. 
Lorsque la partie est en cours, le bouton « Nouvelle Partie » est toujours actif et garde toujours le focus3
. En le 
cliquant, les scores sont remis et réaffichés à 0, les zones d’affichage des derniers coups joués effacées, les figures 
sont actives. 
Les Menus Fichier, Aide et le bouton nouvelle partie sont accessibles via des raccourcis clavier. 
