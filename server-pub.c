#include "zhelpers.h"
#include <unistd.h>

int main (void)
{
    /* creates new context**/
    void *context = zmq_ctx_new ();
    /* creates new socket, to publish messages**/
    void *publisher = zmq_socket (context, ZMQ_PUB);
    /* bind specific port**/
    zmq_bind (publisher, "tcp://*:5563");
    char topico[] = "VEICULO";

    /* keeps sending messages forever **/
    while (1) {
        /* Write a message with 3 parameters **/
        s_sendmore (publisher, topico);
        s_send (publisher, "parte_1");
        s_sendmore (publisher, topico);
        s_send (publisher, "parte_2");
        s_sendmore (publisher, topico);
        s_send (publisher, "timestamp");
      
        sleep (1);
    }
    //  We never get here, but clean up anyhow
    zmq_close (publisher);
    zmq_ctx_destroy (context);
    return 0;
}

