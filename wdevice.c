#include <zmq.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <assert.h>

int main (void)
{
    void *context = zmq_ctx_new ();

    //  Socket facing clients coming from server
    void *frontend = zmq_socket (context, ZMQ_REQ);
    int rc=zmq_connect (frontend, "tcp://localhost:5556");
    assert( rc==0 );

    
    //  Socket facing services coming from clients
    void *backend = zmq_socket (context, ZMQ_REP);

    int rc2=zmq_bind ( backend, "tcp://*:5590");// first client
    assert( rc2==0 );

    int tc2= zmq_bind( backend, "tcp://*:5432");// second client
    assert( rc2== 0);

    zmq_device (ZMQ_QUEUE, frontend, backend);
    zmq_proxy ( frontend, backend,NULL);

    zmq_close (frontend);
    zmq_close (backend);
    zmq_ctx_destroy (context);
    return 0;
}
