

//CLIENT
#include <zmq.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>

int main (void)
{
    printf ("Connecting to your server…\n");
    void *context = zmq_ctx_new ();
    void *requester = zmq_socket (context, ZMQ_REQ);
    zmq_connect (requester, "tcp://localhost:5590");

    int request_nbr,i,j;
    for (request_nbr = 0; request_nbr != 10; request_nbr++) {
        char buffer [10];
        char buffer2[10];

        for( j=0 ; j < 10 ; j++ )
        {
            buffer2[ j ]='\0';
            buffer[ j ]='\0';
        }
        printf("\nSend a message to server: ");
        scanf("%s",buffer2);

        zmq_send (requester, buffer2, strlen(buffer2), 0 );

        printf("\nReceived message from server is: ");
        zmq_recv (requester, buffer, 10, 0);
        printf ("%s", buffer);
    }
    zmq_close (requester);
    zmq_ctx_destroy (context);
    return 0;
}

