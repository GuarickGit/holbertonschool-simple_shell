#include "main.h"

/**
 * remove_trailing_newline - Supprime le '\n' à la fin d'une chaîne
 * @line: chaîne à nettoyer
 *
 * Description :
 * Parcourt la chaîne et remplace le premier '\n' par '\0'
 * Cela évite d'avoir un retour à la ligne dans le nom de commande.
 */
void remove_trailing_newline(char *line)
{
	int i;

	for (i = 0; line[i] != '\0'; i++) /* Parcourt toute la chaîne */
	{
		if (line[i] == '\n') /* Si on trouve un saut de ligne */
		{
			line[i] = '\0'; /* On le remplace par le terminateur */
			break;			/* On sort, car il ne peut y en avoir qu'un à la fin */
		}
	}
}

/**
 * shell_loop - Boucle principale du shell
 * @argv: arguments du programme (argv[0] = nom)
 * @envp: tableau des variables d'environnement
 */
void shell_loop(char **argv, char **envp)
{
	char *line = NULL, *full_path; /* Ligne entrée + chemin final */
	size_t len = 0;				   /* Taille allouée à getline */
	ssize_t n_read;				   /* Nombre de caractères lus */
	char **args;				   /* Tableau des mots (commande + args) */
	int exit_status = 0;

	while (1) /* Boucle infinie du shell */
	{
		if (isatty(STDIN_FILENO)) /* Si entrée interactive (pas un pipe) */
			printf("$ ");		  /* Affiche le prompt */

		n_read = getline(&line, &len, stdin); /* Attend que l'utilisateur tape */
		if (n_read == -1)					  /* Si EOF (Ctrl+D) ou erreur */
		{
			if (isatty(STDIN_FILENO))
				printf("\n");
			free(line); /* Libère la ligne si EOF */
			if (!isatty(STDIN_FILENO))
				exit(exit_status); /* mode non-interactif : on sort avec le bon code */
			else
				exit(0); /* mode interactif : on sort proprement */
		}

		remove_trailing_newline(line); /* Supprime le \n final de la ligne */
		args = parse_line(line);	   /* Découpe la ligne en mots */

		if (args[0] != NULL) /* Si la ligne n'était pas vide */
		{
			if (handle_builtin(args, envp, line)) /* Si c'est un builtin */
			{
				/* free(args); Libère args, ligne libérée dans handle_builtin si exit */
				continue; /* Repart pour une nouvelle commande */
			}
			full_path = find_full_path(args[0], envp); /* Cherche cmd dans PATH */
			if (full_path)
			{
				exit_status = execute_command(full_path, args, envp);
				free(full_path); /* Libère le chemin alloué */
			}
			else /* Si la commande n'existe pas | ligne 99 */
				fprintf(stderr, "%s: 1: %s: not found\n", argv[0], args[0]);
		}
		free(args); /* Libère les arguments à la fin de l’itération */
	}
	if (!isatty(STDIN_FILENO))
		exit(exit_status);

	free(line); /* Libère la ligne après sortie de la boucle */
}

/**
 * main - Point d'entrée du shell
 * @argc: nombre d'arguments passés (non utilisé ici)
 * @argv: tableau des arguments (argv[0] = nom du programme)
 * @envp: tableau contenant les variables d'environnement
 *
 * Return: 0 en cas de succès
 */
int main(int argc, char **argv, char **envp)
{
	(void)argc;				/* argc est inutilisé, on l’annule pour éviter un warning */
	shell_loop(argv, envp); /* Lance la boucle principale du shell */
	return (0);				/* Terminaison normale du shell */
}

/*
 * fprintf envoie un mess. d'erreur vers stderr si la commande est introuvable.
 * Le format suit celui de /bin/sh : "./hsh: 1: commande: not found".
 * argv[0] = "./hsh", 1 = ligne simulée, args[0] = commande entrée.
 */
