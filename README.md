# Respostas de Perguntas

**3) Informações sobre quais bibliotecas e versões foram utilizadas;**

Não foi usada nenhuma biblioteca externa no test para facilitar a compreenção.

**4) Qual o tempo aproximado gasto no desenvolvimento do software;**

Menos de 8 horas, a maior parte foi gasta tentando achar alguma documentação atual.

**5) E por último, não menos importante, quais a dificuldades que você enfrentou
no desafio.**

A biblioteca "zmqpp" não possui documentação, exemplos e não é atualizada a mais de ano.

# Desafio C++

Esse desafio é a parte prática, onde podemos analisar seu nível técnico, organização de código e arquitetura da solução.

O Desafio consiste em escrever um cliente e um servidor na linguagem C++ para ambientes linux utilizando as premissas solicitadas.

O Intuito do software servidor é enviar a publicação de mensagens (padrão Publish/Subscribe do ZeroMQ), e o cliente 
deverá se escrever no tópico de qual o servidor disponibilizar. 

Ao receber os dados, o software deverá salvar em arquivos localmente
a mensagem recebida, com o nome do arquivo TIMESTAMP_DA_MENSAGEM.json.

# Orientações

- Efetuar um Fork desse Repositório para sua conta do GitHub;
- Fazer um Clone do seu Repositório;
- Realizar o Teste;
- Efetuar o Commit e o Push;
- Solicitar um Pull Request.

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

# O que você deve nos entregar após a conclusão do desafio

1) Código-fonte de tudo que foi desenvolvido, esteja o software funcionando ou
não;
2) Makefile, CMakeLists ou linha de compilação;
3) Informações sobre quais bibliotecas e versões foram utilizadas;
4) Qual o tempo aproximado gasto no desenvolvimento do software;
5) E por último, não menos importante, quais a dificuldades que você enfrentou
no desafio.

# Ponto Extra

- Build sem Alertas de compilação;
- Google Code Style.
