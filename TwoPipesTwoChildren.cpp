#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>

int main(int argc, char **argv){
    int pipes1[2];
    int pipes2[2];
    pid_t pid1, pid2;

    char *ls_args[] = {"ls", "-ltr", NULL};
    char *grep_args[] = {"grep", "3376", NULL};
    char *wc_args[] = {"wc", "-l", NULL};

    if (pipe(pipes1) == -1) {
        perror("Failed to create pipe 1");
        exit(1);
    }
    if (pipe(pipes2) == -1) {
        perror("Failed to create pipe 2");
        exit(1);
    }

    // First child
    pid1 = fork();
    if (pid1 == -1) {
        perror("Failed to fork");
        exit(1);
    }

    if (pid1 == 0) {
        // Redirect stdout to pipes1 write end
        dup2(pipes1[1], STDOUT_FILENO);
        close(pipes1[0]);
        close(pipes1[1]);

        // Execute ls -ltr
        execvp(ls_args[0], ls_args);
        perror("Failed to exec ls");
        exit(1);
    } else {
        // Second child
        pid2 = fork();
        if (pid2 == -1) {
            perror("Failed to fork");
            exit(1);
        }

        if (pid2 == 0) {
            // Redirect stdin from pipes1 read end
            dup2(pipes1[0], STDIN_FILENO);
            close(pipes1[0]);
            close(pipes1[1]);

            // Redirect stdout to pipes2 write end
            dup2(pipes2[1], STDOUT_FILENO);
            close(pipes2[0]);
            close(pipes2[1]);

            // Execute grep 3376
            execvp(grep_args[0], grep_args);
            perror("Failed to exec grep");
            exit(1);
        } else {
            // Parent handling wc -l
            close(pipes1[0]);
            close(pipes1[1]);

            dup2(pipes2[0], STDIN_FILENO);
            close(pipes2[0]);
            close(pipes2[1]);

            // Execute wc -l
            execvp(wc_args[0], wc_args);
            perror("Failed to exec wc");
            exit(1);
        }
    }

    return 0;
}
