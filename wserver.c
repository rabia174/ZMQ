

//SERVER

#include <zmq.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <assert.h>

int main (void)
{
    int i,j;
    //  Socket to talk to clients
    void *context = zmq_ctx_new ();
    void *responder = zmq_socket (context, ZMQ_REP);
    int rc = zmq_bind (responder, "tcp://*:5556");    
    assert( rc == 0);
    
    printf("Waiting for clients...\n");

    while (1) {

        char buffer [10];
        char buffer2[10];

         for( j=0 ; j < 10 ; j++ )
         {
            buffer[ j ]='\0';
            buffer2[ j ]='\0';
         }

        zmq_recv (responder, buffer, 10, 0);
    
        printf("\nReceived message from client is: ");

        for( i=0 ; buffer[ i ] !='\0'; i++ )
            printf("%c",buffer[ i ]);      

        printf("\nSend your message to client: ");

        scanf("%s",buffer2);

        sleep (1);          //  Do some 'work'
        zmq_send (responder, buffer2,strlen(buffer2), 0);
    }
    return 0;
}

