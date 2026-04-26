#include <stdio.h>
#include <unistd.h>
#include <signal.h>

void handlerSIGINT(int s)
{
    printf("Se detectó CTRL+C por parte del usuario\n");
    sleep(3);
}

int main() {
    signal(SIGINT, handlerSIGINT);

    while (1)
    {
        printf("PID actual: %d\n", getpid());
        sleep(1);
    }

    return 0;
}