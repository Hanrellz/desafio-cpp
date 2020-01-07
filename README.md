
# Desafio C++

Este projeto consiste em escrever um cliente e um servidor na linguagem C++ para ambientes linux utilizando as premissas solicitadas.

O Intuito do software servidor é enviar a publicação de mensagens (padrão Publish/Subscribe do ZeroMQ), e o cliente 
deverá se escrever no tópico de qual o servidor disponibilizar. 

Ao receber os dados, o software deverá salvar em arquivos localmente
a mensagem recebida, com o nome do arquivo TIMESTAMP_DA_MENSAGEM.json.


# Instruções

Rode o arquivo _install_dependencies.sh_ para instalar as dependencias necessárias para rodar o projeto.

    $ sudo ./install_dependencies.sh

Este irá instalar as seguintes dependências:

 - libtool
 - build-essential
 - g++
 - pkg-config
 - libssl-dev
 - libzmq3-dev
 - libpoco-dev

Estrutura de pastas:
```
desafio-cpp
├── client
|   ├── src
|   ├── resources
|   ├── receives
|   └── build
└── server
    ├── src
    ├── resources
    └── build
```

 - ***_client_*** : arquivos necessários para rodar a aplicação _client_;
	 - ***_src_*** : arquivos fonte da aplicação _client_;
	 - ***_resources_*** : arquivos de apoio para a aplicação;
	 - ***_receives_*** : arquivos contendo o package recebido;
	 - ***_build_*** : arquivos gerados pela compilação.
- ***_server_*** : arquivos necessários para rodar a aplicação _server_;
	 - ***_src_*** : arquivos fonte da aplicação _server_;
	 - ***_resources_*** : arquivos de apoio para a aplicação;
 	 - ***_build_*** : arquivos gerados pela compilação.


Para rodar, acesse a pasta da aplicação desejada (_client_ ou _server_):

    $ cd ./client

E rode os seguintes comandos : 

    $ ./clean_build
    $ ./build_client.sh
    $ ./run_client.sh


# Premissas

 - A porta do servidor e do cliente deverá ser configurável pelo arquivo MODULO/resources/config/MODULO.properties;
 - O Tópico do Pub/Sub do servidor e cliente também deverá ser configurada pelo arquivo de configuração de ambos os módulos;
 - Comunicação TCP.

# Observações

- Sistema Operacional
    - [Debian](https://www.debian.org) _9_
- Bibliotecas
    - [Poco C++](https://pocoproject.org/) _1.9.0_
    - [ZeroMQ](http://zeromq.org/) _4.x.x_
    - [zmqpp](https://github.com/zeromq/zmqpp) _Branch master_
- Plataforma
    - [CMake](https://cmake.org/) _3.13.4_
    - [Make](https://www.gnu.org/software/make/) _last_
    
## Mecanismo de Emissão

As mensagem são transmitidas em uma LAN usando o protocolo TCP/IP e padrão Publish/Subscribe implementado pela biblioteca ZeroMQ.

### Estruturação de Envelope Mensagens ZeroMQ

Cada envelope de mensagem é transmitidas possuindo múltiplas partes, na seguinte ordem:

1. **Tópico**: String - Nome do Tópico.
2. **Ordem**: Integer - 0 até (2,147,483,647 - 1). Overflow pra 0.
3. **Mensagem**: String.

A mensagem usa a notação *JSON* e possui os seguintes dados:

```json
{
    "id": 1, 
    "velocidade": 100,
    "timestamp": "2017-01-03T13:35:22.103Z"
}
  ```
Onde:
* **id**: Inteiro - Identificador único Sequencial.
* **velocidade**: Inteiro - Numero randômico entre 0 - 255 para simular uma marcação de uma ***Velocidade em km/h***.
* **timestamp**: String  - Marca temporal UTC após a geração do numero randômico. ISO 8601 incluindo milissegundos.
