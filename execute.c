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
	int status;
	pid_t pid;

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
		wait(&status);
		if (WIFEXITED(status))
			return (WEXITSTATUS(status));
		else
			return (-1);  /* fin anormale */
	}
}
