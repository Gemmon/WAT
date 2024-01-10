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

    // Unlink existing semaphores (if any)
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

    pid_t pid, p1, p2 ,p3;
    sem_post(sem_print);

    if ((pid = fork()) == 0) {
        // Proces macierzysty (producent)
        while (1) {
            sem_wait(sem_print); // Wait for consumers to finish printing
            printf("Producent czeka na slowo: ");
            fgets(shared_memory, BUFFER_SIZE, stdin);

            // Zwolnij semafor dla jednego z konsumentów
            sem_post(sem_consumers);
        }
    }
    int i;
          while( i < 4){
            if ((p1 = fork()) == 0) {
                while (1) {
                    // Oczekuj na dane od producenta
                    sem_wait(sem_consumers);

                    printf("Klient 1 otrzymał: %s", shared_memory);

                    // Zwolnij semafor dla producenta
                    sem_post(sem_print);
                    printf("%d", i);
                    i++;
                }
            }
          }
          while
           if ((p2 = fork()) == 0) {
                while (1) {
                    // Oczekuj na dane od producenta
                    sem_wait(sem_consumers);

                    printf("Klient 2 otrzymał: %s", shared_memory);

                    // Zwolnij semafor dla producenta
                    sem_post(sem_print);
                }
            }

            if ((p3 = fork()) == 0) {
                while (1) {
                    // Oczekuj na dane od producenta
                    sem_wait(sem_consumers);

                    printf("Klient 3 otrzymał: %s", shared_memory);

                    // Zwolnij semafor dla producenta
                    sem_post(sem_print);
                }
            }


    // Czekaj na zakończenie wszystkich procesów potomnych
    for (int i = 0; i < 4; i++) {
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
