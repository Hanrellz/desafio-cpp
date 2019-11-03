# Desafio C++
Solução do desafio: [Hanrellz/desafio-cpp](https://github.com/Hanrellz/desafio-cpp).

## Uso
```
cd desafio-cpp
make
```

### Subscribe
```
cd desafio-cpp/subscribe
./subscribe
```

### Publish
```
cd desafio-cpp/publish
./publish
```

## Configuração
Os arquivos de configuração se encontram em `desafio-cpp/MODULE/resources/config/MODULE.properties`.

As chaves disponíveis são:
- port
- topic


## Bibliotecas
- [Poco C++](https://pocoproject.org/) _1.9.4_
- [ZeroMQ](http://zeromq.org/) _4.3.2_
- [zmqpp](https://github.com/zeromq/zmqpp) _Branch master_
- [nlohmann/json](https://github.com/nlohmann/json) _3.7.0_
    
## Tempo gasto
Sem contar o tempo de instalação das bibliotecas, o tempo gasto foi de aproximadamente 6 horas.

## Dificuldades
As principais dificuldades estão relacionadas às documentações do **Poco**, do **ZeroMQ** e do **zmqpp**.
