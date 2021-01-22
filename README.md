# Maths4A_Fenetrage
Projet de fenêtrage et de remplissage de polygone en OpenGL pour le cours de mathématiques de 4ème année à l'ESGI.
Ce projet utilise GLAD pour gérer OpenGL 3.3, GLFW pour les fenêtres, SpdLog comme logger et ImGUI pour les interfaces utilisateur. 

# Hiérarchie de dossiers

* dll : contient les dlls :trollface: .
* vendor : contient les dépendances.
* src : contient les script du programme.
	- io : contient le code source des input/output( File etc...)
	- rendering : contient le code source de tout ce qui est impliqué dans le rendu  (shader, mesh etc...)
	- obj : contient le code source des objets utilisé dans ce projet (tracer un polygone, algorithme de fenêtrage etc...)

# Ressources utilisé pour nous aider

* [LearnOpenGl.org english website to learn modern OpenGL](https://learnopengl.com/Getting-started/OpenGL)
* [The Cherno Youtube Channel](https://www.youtube.com/c/TheChernoProject/playlists)
* "Algorithmes pour la synthèse d'images et l'animation 3D", Rémy Malgouyres (french book)
* Le cours de notre professeur de mathématiques

# Fonctionnalités implémentées

- [x] Afficher un menu déroulant (clic droit souris) contenant les champs couleur, tracer polygone, tracer la découpe, appliquer la découpe, remplir.
	* [x] Fenêtre sélécteur de couleur et code hexadécimale
- [x] Tracer des polygones de la couleur choisit
- [x] Tracer la fenêtre de découpe d'une autre couleur (inverse de ce qu'il y a en dessous)
- [x] Afficher le polygone découpé par la fenêtre
- [x] Afficher les rectangles englobants des polygones d'une couleur choisit
- [ ] Remplir les polygones 
