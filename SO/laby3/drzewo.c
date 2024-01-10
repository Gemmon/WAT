#include<sys/types.h>
#include<sys/wait.h>
#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>


void potomni(int dzieci) {
    switch (fork()) {
        case 0:
            //potomny
            printf("PP: Pid potomka: %d, ppid: %d \n", getpid(), getppid());
            exit(0);
        case -1:
            // blad
            perror("blad");
            exit(1);
        default:
            // macierzysty
            printf("PM pid przodka: %d, ppid: %d \n", getpid(), getppid());
            wait(NULL);
            exit(0);
    }
}

int main(){


   printf("P1 (PID=%d)\n", getpid());

    for (int i = 2; i <= 7; ++i) {
        potomni(i);
    }

    printf("P1 (PID=%d) - Koniec\n", getpid());

    return 0;
}