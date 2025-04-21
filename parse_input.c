#include "main.h"

/**
 * parse_line - Découpe la ligne de commande en tokens (mots)
 * @line: ligne saisie par l'utilisateur
 *
 * Description :
 * Utilise strtok pour séparer la ligne en mots (commande + arguments),
 * selon les délimiteurs espace, tabulation, retour chariot et saut de ligne.
 * Le tableau est réalloué dynamiquement si nécessaire.
 *
 * Return: tableau de chaînes terminé par NULL (à libérer après usage)
 */
char **parse_line(char *line)
{
	char *token; /* Mot extrait à chaque appel de strtok */
	char **args; /* Tableau de mots (commande + arguments) */
	int bufsize = 64, i = 0; /* Taille initiale du tableau + index */

	args = malloc(sizeof(char *) * bufsize); /* Allocation tableau */
	if (!args)
	{
		perror("malloc"); /* Erreur si malloc échoue */
		exit(EXIT_FAILURE); /* Quitte si erreur mémoire */
		/* EXIT_FAILURE = EXIT(1), Erreur générale ou critique */
	}

	token = strtok(line, " \t\r\n"); /* Premier mot (sép: : espace, tab, ...) */
	while (token != NULL) /* Tant qu'on trouve des mots */
	{
		args[i++] = token; /* Ajoute le mot au tableau */

		if (i >= bufsize) /* Si on dépasse la capacité */
		{
			bufsize += 64; /* On agrandit de 64 cases */
			args = _realloc_args(args, i, bufsize); /* Reallocation */
			if (!args)
			{
				perror("realloc"); /* Erreur si realloc échoue */
				exit(EXIT_FAILURE); /* Quitte en cas de problème mémoire */
			}
		}
		token = strtok(NULL, " \t\r\n"); /* Mot suivant avec mêmes séparateurs */
	}
	args[i] = NULL; /* Termine le tableau avec NULL */
	return (args); /* Retourne le tableau final */
}
