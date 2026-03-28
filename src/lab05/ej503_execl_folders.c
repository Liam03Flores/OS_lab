#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

int main() {
    pid_t pid_A, pid_B, pid_C, pid_D, pid_E, pid_F, pid_G, pid_H, pid_I, pid_J;

    pid_A = fork();
    if (pid_A == 0) {
        execl("/bin/echo", "echo", "ls", NULL);
        exit(1);
    }
    wait(NULL);

    pid_B = fork();
    if (pid_B == 0) {
        execl("/bin/ls", "ls", NULL);
        exit(1);
    }
    wait(NULL);

    pid_C = fork();
    if (pid_C == 0) {
        execl("/bin/echo", "echo", "rm new_folder", NULL);
        exit(1);
    }
    wait(NULL);

    pid_D = fork();
    if (pid_D == 0) {
        execl("/bin/rm", "rm", "-d", "-f", "new_folder", NULL);
        exit(1);
    }
    wait(NULL);

    pid_E = fork();
    if (pid_E == 0) {
        execl("/bin/echo", "echo", "ls", NULL);
        exit(1);
    }
    wait(NULL);

    pid_F = fork();
    if (pid_F == 0) {
        execl("/bin/ls", "ls", NULL);
        exit(1);
    }
    wait(NULL);

    pid_G = fork();
    if (pid_G == 0) {
        execl("/bin/echo", "echo", "mkdir new_folder", NULL);
        exit(1);
    }
    wait(NULL);

    pid_H = fork();
    if (pid_H == 0) {
        execl("/bin/mkdir", "mkdir", "new_folder", NULL);
        exit(1);
    }
    wait(NULL);

    pid_I = fork();
    if (pid_I == 0) {
        execl("/bin/echo", "echo", "ls", NULL);
        exit(1);
    }
    wait(NULL);

    pid_J = fork();
    if (pid_J == 0) {
        execl("/bin/ls", "ls", NULL);
        exit(1);
    }
    wait(NULL);

    return 0;
}