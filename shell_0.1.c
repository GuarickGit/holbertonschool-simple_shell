#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <stdlib.h>

/**
 * mini_shell - a UNIX command line interpreter.
 * @args: Arguments for the command
 * Return: 0 on success, -1 on failure
 * Returne: Always 0
 */
/*
 * Variable globale qui contient l’environnement (ex: PATH, HOME, etc)
 * Utilisée ici pour passer l’environnement à execve.
*/
extern char **environ;
int main(void)
{
	/* Sert à stocker ce que l’utilisateur tape au clavier. */
	char *buffer = NULL;
	/*
	 * la taille de la mémoire utilisée par buffer. getline qui va l'ajouter
	 * automatiquement
	 */
	size_t bufsize = 0;
	ssize_t chars_read;	/* Nombre de caractères lus avec getline */
	pid_t pid;	/* C’est le numéro du nouveau processus (le fils). */
	int status; /* Pour savoir si le processus s'est bien terminé ou non */
	/*
	 * Boucle infinie : notre shell fonctionne toujours, jusqu’à ce qu’on
	 * fasse Ctrl+D
	 */
	while (1)
	{
	/* On affiche un prompt pour demander à l'utilisateur de taper une commande */
		printf("#cisfun$ ");
		/*
		 * On lit ce que l'utilisateur tape (jusqu'à "Entrée") et on met ça
		 * dans 'buffer'
		 */
		chars_read = getline(&buffer, &bufsize, stdin);
		/* Si l'utilisateur fait Ctrl+D ou une erreur, getline renvoie -1 */
		if (chars_read == -1)
		{
			write(STDOUT_FILENO, "\n", 1);	/* On affiche juste un retour à la ligne */
			break;	/* Et on quitte la boucle (donc le shell) */
		}
		/*
		 * Si la dernière chose dans buffer est un saut de ligne ('\n'),
		 * on le remplace par '\0' (fin de chaîne)
		 */
		if (buffer[chars_read - 1] == '\n')
			buffer[chars_read - 1] = '\0';
		/* Si l’utilisateur n’a rien tapé (juste "Entrée"), on recommence la boucle */
		if (buffer[0] == '\0')
			continue;	/* on continue */
		/* On crée un nouveau processus (le fils). Le fils va exécuter la commande. */
		pid = fork();
		/* Si fork échoue, on affiche une erreur et on recommence la boucle */
		if (pid == -1)
		{
			/* Affiche "Erreur fork" et l'erreur système */
			perror("Erreur fork");
			continue;	/* on continue */
		}
		/* Si on est dans le fils (le nouveau processus créé) */
		if (pid == 0)
		{
			/* On prépare un tableau contenant la commande */
			char *argv[] = {buffer, NULL};
			/* On essaie d'exécuter la commande tapée par l'utilisateur */
			if (execve(buffer, argv, environ) == -1)
			{
				/* Si ça échoue (commande invalide), on affiche une erreur */
				perror("Erreur");
				exit;	/*  Et on quitte le fils avec une erreur */
			}
		}
		else
		{
			/* Si on est dans le parent, on attend que le fils finisse son travail */
			waitpid(pid, &status, 0);
		}
	}
	/* Quand la boucle est finie, on libère la mémoire allouée pour la ligne tapée */
	free(buffer);
	return (0);	/* Et on termine le programme proprement */
}

