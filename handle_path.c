#include "main.h"

/**
 * find_full_path - Cherche le chemin complet d'une commande via PATH
 * @command: nom de la commande saisie (ex: "ls")
 * @envp: tableau des variables d'environnement
 *
 * Description :
 * Si la commande contient un '/', on considère qu'elle est déjà un chemin.
 * Sinon, on récupère la variable PATH, on la découpe et on teste chaque
 * dossier pour voir si la commande y est exécutable.
 *
 * Return: chemin complet (chaîne à libérer) si trouvé, sinon NULL
 */
char *find_full_path(char *command, char **envp)
{
	char *path, *path_copy, *token, *full_path;
	int len;

	if (strchr(command, '/')) /* Si la commande contient un '/' */
		return (strdup(command)); /* On suppose qu'elle est déjà un chemin */

	path = get_path_from_env(envp); /* Cherche la valeur de PATH dans envp */
	if (!path)
		return (NULL); /* Si PATH est introuvable, abandon */

	path_copy = strdup(path); /* Copie car strtok modifie la chaîne */
	if (!path_copy)
		return (NULL); /* Erreur d'allocation */

	token = strtok(path_copy, ":"); /* Découpe PATH sur les ':' */
	while (token)
	{
		/* Calcule la taille pour "répertoire/commande\0" */
		len = strlen(token) + strlen(command) + 2;
		full_path = malloc(len); /* Alloue la mémoire pour le chemin complet */
		if (!full_path)
		{
			free(path_copy);
			return (NULL); /* Erreur d'allocation mémoire */
		}
		sprintf(full_path, "%s/%s", token, command); /* Build le chemin complet */

		if (access(full_path, X_OK) == 0) /* Teste si le fichier est exécutable */
		{
			free(path_copy); /* Libère la copie de PATH */
			return (full_path); /* Retourne le chemin valide */
		}

		free(full_path); /* Sinon, libère et teste le dossier suivant */
		token = strtok(NULL, ":");
	}

	free(path_copy); /* Aucun chemin trouvé → libère et retourne NULL */
	return (NULL);
}
