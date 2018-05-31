#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

int main(){
    
    int shm_id;
    size_t size = sizeof(int);
    int shmflg = IPC_CREAT | 0666;

    key_t key = 12345;
    int *numValue;

    shm_id = shmget(key, size, shmflg);
    if(shm_id == -1){
        perror("ERROR: shmget has failed\n");
        exit(0);
    }
    numValue = shmat(shm_id, NULL, 0);
    if(numValue == (void *)-1){
        perror("ERROR: shmat has failed\n");
        exit(0);
    }

    int randomNum = rand()%20;
    printf("randomNum = %d\n",randomNum);

    if(randomNum < 10){
        *numValue = randomNum;
    }

    if(shmdt(numValue) == -1){
        perror("ERROR: shmdt has failed \n");
    }

    //shmctl(shm_id,IPC_RMID,NULL);

    return 0;
}