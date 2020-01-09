#include "zhelpers.h"
#include <unistd.h>
#include <stdlib.h>

int main(void)
{
  /* cria um novo contexto **/
  void *context = zmq_ctx_new();

  /* cria um novo socket, para enviar as mensagens **/
  void *publisher = zmq_socket(context, ZMQ_PUB);

  /* coloca a porta específica no socket criado **/
  zmq_bind(publisher, "tcp://*:5563");
  
  /* definição do tópico, id e valor aleatório para velocidade **/
  char topico[] = "VEICULO";
  unsigned long int id = 0;
  int velocidade = rand() % 255;

  /* fica mandando mensagens indefinidamente **/
  while (1)
  {
    /* altera o valor de id**/
    ++id;
    int length = snprintf(NULL, 0, "%ld", id);
    char *str_id = malloc(length + 1);
    snprintf(str_id, length + 1, "%ld", id);

    /* escreve a mensagem com 3 parâmetros **/
    s_sendmore(publisher, topico);
    s_send(publisher, topico);
    s_sendmore(publisher, topico);
    s_send(publisher, str_id);

    /* @TODO criar json com os valores da mensagem**/
    s_sendmore(publisher, topico);
    s_send(publisher, "mensagem - id, velocidade, timestamp");

    /* libera memória **/
    free(str_id);
    /* fica mais fácil de acompanhar **/
    sleep(1);
  }
  zmq_close(publisher);
  zmq_ctx_destroy(context);
  return 0;
}
