#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h> //for process communication
#include <sys/msg.h> //generating message queues

int true = 1;
struct message_queue
{
	long message_type;
	char message_text[100];
} message;

int main(){
	key_t  key;
	int message_id;

	//creating the key
	key = ftok("message passing",65);

	//create the message queues
	message_id = msgget(key,0666 | IPC_CREAT);
	while(true){
	//receive the message
	msgrcv(message_id,&message,sizeof(message),1,0);


	//display the message
	printf("data Received is:%s\n",message.message_text );
}
	//after using destroy message queues
	msgctl(message_id,IPC_RMID,NULL);

	return 0;
}