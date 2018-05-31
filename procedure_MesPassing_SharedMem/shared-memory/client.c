#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>
#include <stdlib.h>

int main(){
    
    int shm_id;
    size_t size = sizeof(int);
    int shmflg = IPC_CREAT | 0444;

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

    int num = *numValue;
    if(num % 2 == 0){
        printf("The value %d is: even\n",num);
    }
    else{
        printf("The value %d is: odd\n",num);
    }

    *numValue = *numValue+1;
    
    if(shmdt(numValue) == -1){
        perror("ERROR: shmdt has failed \n");
    }

    shmctl(shm_id,IPC_RMID,NULL);

    return 0;
}