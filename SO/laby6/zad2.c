#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <string.h>
#include <semaphore.h>
#include <fcntl.h>

#define SHM_KEY 1234

#define BUFFER_SIZE 50

int main() {
    int shmid;

    sem_unlink("/sem_producer");
    sem_unlink("/sem_consumers");
    sem_unlink("/sem_mutex");
    sem_unlink("/sem_print");

    // Utwórz pamięć dzieloną
    if ((shmid = shmget(SHM_KEY, BUFFER_SIZE, IPC_CREAT | 0666)) < 0) {
        perror("shmget");
        exit(1);
    }

    // Przydziel pamięć dzieloną do wskaźnika
    char *shared_memory = shmat(shmid, NULL, 0);

    // Utwórz semafory
    sem_t *sem_producer, *sem_consumers, *sem_mutex, *sem_print;

    // Inicjalizuj semafory
    sem_producer = sem_open("/sem_producer", O_CREAT | O_EXCL, 0666, 1);
    sem_consumers = sem_open("/sem_consumers", O_CREAT | O_EXCL, 0666, 0);
    sem_mutex = sem_open("/sem_mutex", O_CREAT | O_EXCL, 0666, 1);
    sem_print = sem_open("/sem_print", O_CREAT | O_EXCL, 0666, 0);

    if (sem_producer == SEM_FAILED || sem_consumers == SEM_FAILED || sem_mutex == SEM_FAILED || sem_print == SEM_FAILED) {
        perror("sem_open");
        exit(1);
    }

    pid_t pid;

    sem_post(sem_print);

    if ((pid = fork()) == 0) {
        // Proces macierzysty (producent)
        while (1) {
            sem_wait(sem_print); // Wait for consumers to finish printing
            printf("Producent czeka na slowo: ");
            fgets(shared_memory, BUFFER_SIZE, stdin);

            // Zwolnij semafor dla pierwszego konsumenta
            sem_post(sem_consumers);
        }
    } else if (pid > 0) {
        // Proces potomny (konsumenci)
        for (int i = 1; i <= 3; i++) {
            if ((pid = fork()) == 0) {
                while (1) {
                    // Oczekuj na dane od producenta
                    sem_wait(sem_consumers);

                    printf("Klient %d otrzymał: %s", i, shared_memory);

                    // Zwolnij semafor dla producenta
                    sem_post(sem_print);
                    sem_post(sem_producer);
                }
            }
        }
    } else {
        perror("fork");
        exit(1);
    }

    // Czekaj na zakończenie wszystkich procesów potomnych
    for (int i = 0; i < 3; i++) {
        wait(NULL);
    }

    // Zamknij i usuń semafory
    sem_close(sem_producer);
    sem_close(sem_consumers);
    sem_close(sem_mutex);
    sem_close(sem_print);

    sem_unlink("/sem_producer");
    sem_unlink("/sem_consumers");
    sem_unlink("/sem_mutex");
    sem_unlink("/sem_print");

    // Zwolnij zasoby
    shmdt(shared_memory);
    shmctl(shmid, IPC_RMID, NULL);

    return 0;
}
