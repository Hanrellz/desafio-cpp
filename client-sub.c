#include "zhelpers.h"

int main(void)
{
  /* cria um novo contexto **/
  void *context = zmq_ctx_new();
  /* cria um novo socket, para receber as mensagens **/
  void *subscriber = zmq_socket(context, ZMQ_SUB);
  /* conecta na porta específica para ficar monitorando
    * @TODO valor da porta variável
    **/
  zmq_connect(subscriber, "tcp://localhost:5563");
  /* inscreve no tópico VEICULO **/
  zmq_setsockopt(subscriber, ZMQ_SUBSCRIBE, "VEICULO", 1);

  while (1)
  {
    /* recebe a mensagem **/
    char *address = s_recv(subscriber);
    /* recebe o conteúdo e imprime eles na tela **/
    char *contents = s_recv(subscriber);
    printf("[%s] %s\n", address, contents);
    /* libera a memória utilizada para não dar overflow**/
    free(address);
    free(contents);
  }
  zmq_close(subscriber);
  zmq_ctx_destroy(context);
  return 0;
}