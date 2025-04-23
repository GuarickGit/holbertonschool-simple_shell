# Welcome to the projet C - Simple Shell

![alt text](https://s3.eu-west-3.amazonaws.com/hbtn.intranet.project.files/holbertonschool-low_level_programming/235/shell.jpeg)

## mini_shell
## Description
mini_shell est une implémentation simple d'un interpréteur de commande UNIX (shell). Il permet à l'utilisateur de taper des commandes directement, de créer un processus enfant et d'essayer d'exécuter la commande avec execve.

Ce shell fonctionne en boucle tant que l'utilisateur ne quitte pas avec Ctrl+D (EOF). À chaque itération, il affiche un prompt #cisfun$, lit la commande entrée, puis crée un processus fils pour l'exécuter.

## Fonctionnalités

- Affiche un prompt personnalisé : #cisfun$.

- Lecture de la ligne de commande via getline.

- Traitement basique de la commande (sans parsing complexe ni chemins relatifs).

- Création d'un processus fils pour chaque commande via fork.

- Exécution de la commande avec execve.

- Attente de la fin du processus avec waitpid.
## Code principal
```c
int main(void)
```
## Variables principales
```
Variable	 					Rôle
```
- buffer -----Contient la ligne de commande tapée par l'utilisateur
- bufsize -----------Taille allouée pour buffer
- chars_read -------Nombre de caractères lus par getline
- pid ----------Identifiant du processus fils créé par fork
- status ----------Statut de retour du fils (utilisé par waitpid)
- environ --Variable globale contenant les variables d’environnement

## Fonctionnement général

### 1. Affichage du prompt

### 2. Lecture de la commande utilisateur

### 3. Nettoyage du \n final

### 4. Création d'un processus enfant avec fork

### 5. Dans le fils : exécution de la commande avec execve

### 6. Dans le parent : attente de fin du fils avec waitpid

### 7. Répétition du cycle tant que l'utilisateur ne quitte pas

# mini_shell v2
## Description
Cette version de mini_shell implémente un interpréteur de commande UNIX capable d'exécuter des commandes avec arguments, en découpant la ligne utilisateur via strtok. Il repose toujours sur les appels système fork, execve, et waitpid.

Par rapport à la première version, celle-ci gère :

- La séparation des arguments (ex: ls -l /tmp)

- L'utilisation d'une fonction dédiée execute_command() pour lancer les commandes.

## Fonctionnalités

- Affiche un prompt : #cisfun$

- Lecture de ligne utilisateur avec getline

- Parsing des arguments avec strtok

- Exécution de commandes avec execve

- bGestion de processus via fork et waitpid
## Fonctionnement
### Boucle principale (main)
#### 1. Affiche le prompt.

#### 2. Lit une ligne via getline.

#### 3. Nettoie le saut de ligne final.

#### 4. Ignore les lignes vides.

#### 5. Découpe la ligne en mots avec strtok (commande + arguments).

#### 6. Appelle execute_command() pour exécuter.

## Fonction execute_command()
- Crée un processus fils avec fork.

- Dans le fils, exécute la commande avec execve.

- Dans le parent, attend la fin de l’enfant.
## Exemple d’utilisation
```bash
#cisfun$ /bin/ls
#cisfun$ /bin/echo Hello world!
#cisfun$ ./mon_script arg1 arg2
```
## Limites connues
- Ne gère pas les chemins implicites : /bin/ls fonctionne, mais ls seul non (pas de gestion du PATH).

- Ne gère pas les commandes internes (cd, exit, etc.).

- execve est appelé sans environnement (NULL), ce qui peut poser des problèmes sur certaines commandes.

- Mauvais appel à exit :







