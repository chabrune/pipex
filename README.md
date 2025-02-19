# Pipex - Implémentation des Pipes UNIX

Un projet qui reproduit le comportement des pipes shell en C.

## 📝 Description

Pipex simule le comportement de la commande shell `< file1 cmd1 | cmd2 > file2` en implémentant les pipes UNIX.

## 🛠️ Fonctionnalités

### Usage
```bash
./pipex file1 cmd1 cmd2 file2
```

### Exemple d'utilisation
```bash
./pipex infile "ls -l" "wc -l" outfile
# Équivalent à : < infile ls -l | wc -l > outfile

./pipex infile "grep a1" "wc -w" outfile
# Équivalent à : < infile grep a1 | wc -w > outfile
```

## ⚙️ Fonctions Autorisées
- Manipulation de fichiers : `open`, `close`, `read`, `write`
- Gestion mémoire : `malloc`, `free`
- Gestion erreurs : `perror`, `strerror`
- Manipulation processus : `fork`, `pipe`, `execve`, `exit`
- Redirection : `dup`, `dup2`
- Autres : `access`, `unlink`, `wait`, `waitpid`
- Libft autorisée


## ⚠️ Exigences
- Gestion rigoureuse des erreurs
- Pas de fuites mémoire
- Makefile avec règles standard
- Conformité à la norme

---
*Projet réalisé dans le cadre du cursus de l'école 42*
