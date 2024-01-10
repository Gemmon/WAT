#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>

#define SHM_SIZE 1024

struct sembuf sem_op;

//funkcja do czekania 
void wait_semaphore(int sem_id, int sem_num) {
    sem_op.sem_num = sem_num;
    sem_op.sem_op = -1;
    sem_op.sem_flg = 0;
    semop(sem_id, &sem_op, 1);
}

//oblsuga syngalow
void signal_semaphore(int sem_id, int sem_num) {
    sem_op.sem_num = sem_num;
    sem_op.sem_op = 1;
    sem_op.sem_flg = 0;
    semop(sem_id, &sem_op, 1);
}

int main() {

    //tworzenie pamieci dzielonej

    key_t key = ftok("keyfile", 'R');
    int shmid = shmget(key, SHM_SIZE, IPC_CREAT | 0666);
    char *shmaddr = shmat(shmid, NULL, 0);

    //tworzenie semeforow

    int sem_id = semget(key, 1, IPC_CREAT | 0666);
    sem_op.sem_num = 0;
    sem_op.sem_op = 1;
    sem_op.sem_flg = 0;
    semop(sem_id, &sem_op, 1);

    pid_t pid;


//przechodzenie po klientach
    for (int i = 0; i < 3; ++i) {
        pid = fork();
        if (pid == 0) {
            // Klient
            while (1) {
                wait_semaphore(sem_id, 0);
                printf("Klient %d otrzymał: %s\n", i + 1, shmaddr);
                signal_semaphore(sem_id, 0);
            }
        } else if (pid < 0) {
            perror("Błąd fork");
            exit(EXIT_FAILURE);
        }
    }

    // Producent, odbieranie stdin
    while (1) {
        wait_semaphore(sem_id, 0);
        printf("Podaj słowo: ");
        fgets(shmaddr, SHM_SIZE, stdin);
        signal_semaphore(sem_id, 0);
    }

    //usuwanie pamieci
    shmdt(shmaddr);
    shmctl(shmid, IPC_RMID, NULL);

    return 0;
}
