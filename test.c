#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>

int main(int argc, char *argv[], char *envp[]) {
    (void)argc;
    int fdin = open(argv[1], O_RDONLY);
    if (fdin == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }
    int fdout = open(argv[4], O_CREAT | O_WRONLY | O_TRUNC, 0644);
    if (fdout == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }
    int pipefd[2];
    if (pipe(pipefd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }
    pid_t pid1 = fork();
    if (pid1 == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    } else if (pid1 == 0) {
        // Child 1
        if (dup2(fdin, STDIN_FILENO) == -1) {
            perror("dup2");
            exit(EXIT_FAILURE);
        }
        if (dup2(pipefd[1], STDOUT_FILENO) == -1) {
            perror("dup2");
            exit(EXIT_FAILURE);
        }
        close(fdin);
        close(fdout);
        close(pipefd[0]);
        close(pipefd[1]);
        char *args[] = {"/bin/sh", "-c", argv[2], NULL};
        execve(args[0], args, envp);
        perror("execve");
        exit(EXIT_FAILURE);
    } else {
        pid_t pid2 = fork();
        if (pid2 == -1) {
            perror("fork");
            exit(EXIT_FAILURE);
        } else if (pid2 == 0) {
            // Child 2
            if (dup2(pipefd[0], STDIN_FILENO) == -1) {
                perror("dup2");
                exit(EXIT_FAILURE);
            }
            if (dup2(fdout, STDOUT_FILENO) == -1) {
                perror("dup2");
                exit(EXIT_FAILURE);
            }
            close(fdin);
            close(fdout);
            close(pipefd[0]);
            close(pipefd[1]);
            char *args[] = {"/bin/sh", "-c", argv[3], NULL};
            execve(args[0], args, envp);
            perror("execve");
            exit(EXIT_FAILURE);
        } else {
            // Parent
            close(fdin);
            close(fdout);
            close(pipefd[0]);
            close(pipefd[1]);
            waitpid(pid1, NULL, 0);
            waitpid(pid2, NULL, 0);
            printf("Commande terminée.\n");
        }
    }
    return 0;
}