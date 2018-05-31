#include <stdio.h>
#include <stdlib.h>
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
	key_t key;//declare key of key type
	int message_id;

	//generate keys
	key = ftok("message passing",65);

	//creating message identifiers
	message_id = msgget(key,0666 |IPC_CREAT);
	message.message_type = 1; //return the identifier
	while(true){
	printf("Insert Text:\n");
	
	char mes = fgets(message.message_text,sizeof(message.message_text),stdin);//get text from standard input
	// if(mes =='s'){
	// 	printf("success\n");
	// }
	// else{
	// 	printf("Error\n");
	// 	exit(-1);
	// }

	//send the message
	msgsnd(message_id,&message,sizeof(message),0);

	//display the message
	printf("data sent is :  %s\n",message.message_text );
}
	return 0;
}