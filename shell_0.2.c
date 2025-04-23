#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

/**
 * execute_command - Execute a command using fork and execve.
 * @args: Arguments for the command
 * Return: 0 on success, -1 on failure
 *
 *
 */

/* args = tableau avec la commande et ses arguments */
int execute_command(char **args)
{
/* une Variable qui va contenir le PID du nouveau processus enfant. */
	pid_t pid;
/* une Variable pour stocker le résultat de l'exécution (réussi ou erreur) */
	int status;
	/*
	 * Crée un nouveau processus (l’enfant). Deux programmes vont maintenant
	 * s'exécuter en même temps : le parent et l’enfant.
	*/
	pid = fork();
	if (pid == -1)	/* Si fork() échoue, pid vaut -1 */
	{
	/* Affiche un message d'erreur automatique selon le problème du système. */
		perror("error");
		/* On quitte la fonction et on indique qu'il y a eu une erreur. */
		return (-1);
	}

	if (pid == 0)	/* Ce bloc est exécuté uniquement dans le processus enfant. */
	{
		/*
		 * Tente d’exécuter la commande avec ses arguments. args[0] = nom de la
		 * commande, args = tableau d'arguments et NULL = pas de varible
		 * d'environnement
		 */
		if (execve(args[0], args, NULL) == -1)
		{
			/* Si la commande ne peut pas s’exécuter, affiche une erreur. */
			perror("error");
			exit;	/* Quitte l’enfant immédiatement avec un code d’erreur. */
		}
	}
	else
	{
		waitpid(pid, &status, 0); /* Le parent attend que l’enfant finisse. */
	}

	return (0);	/* Retourne 0 pour dire que tout s’est bien passé. */
}
/**
 * main - Simple shell implementation
 * Return: Always 0
 */
int main(void)
{
	/* Pointeur qui contiendra la ligne tapée par l'utilisateur. */
	char *buffer = NULL;
	size_t bufsize = 0;	/* Taille initiale de buffer. getline() va s’en occuper */
	ssize_t chars_read;	/* Nombre de caractères lus par getline(). */
	char *args[1024];	/* Tableau pour stocker la commande + ses arguments. */
	int i;	/* Utilisé dans une boucle pour remplir le tableau args. */

	/* Boucle infinie = le shell tourne toujours tant qu’on ne le quitte pas. */
	while (1)
	{
		/* Affiche le prompt, pour que l'utilisateur tape une commande */
		printf("#cisfun$ ");
		/* Lit une ligne tapée au clavier, et la met dans buffer. */
		chars_read = getline(&buffer, &bufsize, stdin);
		/* Si getline() échoue (ex : Ctrl+D), on quitte. */
		if (chars_read == -1)
		{
			perror("error");	/* ffiche un message d'erreur automatique. */
			break;	/* On sort de la boucle while */
		}
		/* Si la dernière lettre est un retour à la ligne (\n)... */
		if (buffer[chars_read - 1] == '\n')
			/* ...on le remplace par \0 pour bien finir la chaîne de texte. */
			buffer[chars_read - 1] = '\0';
		/* Si l’utilisateur a juste appuyé sur Entrée (ligne vide)... */
		if (buffer[0] == '\0')
			continue;	/* ... on recommence le prompt. */
		/* Coupe la ligne en morceaux. Le premier mot devient args[0]. */
		args[0] = strtok(buffer, " ");
		/* Boucle pour découper le reste de la ligne (les arguments). */
		for (i = 1; i < 1024; i++)
		{
	/* Chaque appel récupère un nouveau mot, jusqu'à ce qu’il n’y en ait plus. */
			args[i] = strtok(NULL, " ");
			/* Quand il n’y a plus de mots, on arrête la boucle. */
			if (args[i] == NULL)
				break;
		}
	/* On appelle notre fonction pour exécuter la commande avec ses arguments */
		execute_command(args);
	}

	free(buffer);	/* On libère la mémoire utilisée pour lire les lignes. */
	return (0); /* on retourne 0 */
}
