#include "main.h"

/**
 * execute_command - Crée un processus pour exécuter une commande
 * @command: chemin absolu de la commande à exécuter
 * @args: tableau d'arguments à passer à execve
 * @envp: tableau des variables d'environnement
 *
 * Description :
 * Cette fonction crée un processus fils pour exécuter une commande
 * en utilisant execve. Le processus parent attend que le fils termine.
 * Si execve échoue dans le fils, celui-ci quitte avec le code 127
 * (convention Unix pour "commande non trouvée").
 */
int execute_command(char *command, char **args, char **envp)
{
	int status; /* Contiendra les informations de sortie du processus fils */
	pid_t pid; /* Identifiant du processus créé par fork() */

	/* Création d'un nouveau processus */
	pid = fork();

	/* Vérification que fork a réussi */
	if (pid == -1)
	{
		perror("fork"); /* Affiche une erreur si fork échoue */
		return (-1);
	}

	/* Code exécuté par le processus fils */
	if (pid == 0)
	{
		/* Remplace le processus courant par la commande demandée */
		execve(command, args, envp);

		/* Si execve échoue, on quitte avec le code 127 */
		exit(127); /* code 127 = Commande non trouvée */
	}
	else
	{
		/* Le parent attend la fin du processus fils */
		wait(&status);
		/* Vérifie si le fils s’est terminé normalement (par exit) */
		if (WIFEXITED(status)) /* Vérifie si le fils s’est terminé normalement (via exit ou return) */
			return (WEXITSTATUS(status)); /* Récupère le code de sortie si le fils s’est terminé normalement */
		else
		/* Si le processus fils s’est terminé de manière anormale (signal, etc.) */
			return (-1); /* fin anormale */
	}
}
