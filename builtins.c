#include "main.h"

/**
 * handle_builtin - Vérifie et exécute les commandes internes du shell
 * @args: tableau contenant la commande et ses arguments
 * @envp: tableau des variables d'environnement
 * @line: ligne saisie par l'utilisateur (libérée si besoin)
 *
 * Description :
 * Cette fonction gère les commandes internes "exit" et "env".
 * Si la commande est "exit", le shell est terminé proprement.
 * Si la commande est "env", les variables d'environnement sont affichées.
 *
 * Return: 1 si une commande interne a été exécutée, 0 sinon
 */
int handle_builtin(char **args, char **envp, char *line)
{
	int i;

	/* Vérifie si la commande est "exit" */
	if (strcmp(args[0], "exit") == 0)
	{
		/* Libère la mémoire allouée aux arguments */
		free(args);
		/* Libère la ligne lue */
		free(line);
		/* Termine le programme avec un code de succès */
		exit(0);
	}

	/* Vérifie si la commande est "env" */
	if (strcmp(args[0], "env") == 0)
	{
		/* Parcourt toutes les variables d'environnement */
		for (i = 0; envp[i] != NULL; i++)
			printf("%s\n", envp[i]); /* Affiche chaque variable */

		/* Indique qu'une commande interne a été traitée */
		return (1);
	}

	/* Si aucune commande interne reconnue, retourne 0 */
	return (0);
}
