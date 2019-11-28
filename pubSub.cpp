#include <iostream>
#include "libZeromq.hpp"
#include <thread>

void publisher(){
    zmq::context_t contextoPublisher(1);
    zmq::socket_t socketPusblisher(contextoPublisher, ZMQ_PUB);

    bool status;
    int ordem = 0;
    int id;

    std::vector<std::string> vetConfs = getConfiguracoes("resources/config/publisher.properties");
    std::string stringPorta = vetConfs.at(0);
    std::string stringTopico = vetConfs.at(1);

    socketPusblisher.bind("tcp://localhost:" + stringPorta);
    
    while(1){
        try{
        enviaTopico(socketPusblisher, stringTopico);
        enviaOrdem(socketPusblisher, ordem);
        enviaMensagem(socketPusblisher, id);
        } catch(zmq::error_t &excecao) {
            std::cout << excecao.what() << std::endl;
        }
    }
}

void subscriber(){
    zmq::context_t contextoSubscriber(1);
    zmq::socket_t socketSubscriber(contextoSubscriber, ZMQ_PUB);

    bool status;
    int ordem = 0;
    int id;
    std::string mensagem;

    std::vector<std::string> vetConfs = getConfiguracoes("resources/config/subscriber.properties");
    std::string stringPorta = vetConfs.at(0);
    std::string stringTopico = vetConfs.at(1);

    socketSubscriber.connect("tcp://localhost:" + stringPorta);

    socketSubscriber.setsockopt( ZMQ_SUBSCRIBE, stringTopico.c_str(), 1);

    while(1){
        mensagem = recebeMensagem(socketSubscriber);
        std::cout << mensagem << std::endl;
    }

}

int main(int argc, char **argv){
    
    std::thread threadPublisher(publisher);
    
    std::thread threadSubscriber(subscriber);

    return 0;
}