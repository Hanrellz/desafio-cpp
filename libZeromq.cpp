#include <zmq.hpp>
#include <fstream>
#include <string>
#include <ctime>
#include <vector>
#include <random>

#include "Poco/Timestamp.h"
#include "Poco/DateTimeFormat.h"
#include "Poco/DateTimeFormatter.h"

std::vector<std::string> getConfiguracoes(std::string caminho){
    std::vector<std::string> vetConfs;

    std::ifstream arqConf(caminho);
    std::string stringPorta;
    std::string stringTopico;
    zmq::message_t mensagem;

    std::getline(arqConf, stringPorta);
    std::getline(arqConf, stringTopico);

    vetConfs.push_back(stringPorta);
    vetConfs.push_back(stringTopico);

    return vetConfs;
}

void enviaTopico(zmq::socket_t &sock, const std::string &string){
    zmq::message_t mensagem(string.size());
    memcpy(mensagem.data(), string.data(), string.size());

    sock.send(mensagem, zmq::send_flags::sndmore);
}

void enviaOrdem(zmq::socket_t &sock, const int &ordem){

    zmq::message_t mensagem(sizeof(int));
    memcpy(mensagem.data(), std::to_string(ordem).c_str(), sizeof(int));

    sock.send(mensagem, zmq::send_flags::sndmore);
}

void enviaMensagem(zmq::socket_t &sock, const int &id){
    std::random_device rd;
    std::mt19937 gerador(rd());
    std::uniform_int_distribution<> distribuicao(0, 255);
 
    int velocidade = distribuicao(gerador);

    Poco::Timestamp ts;
    std::string timestamp = Poco::DateTimeFormatter::format(ts, Poco::DateTimeFormat::ISO8601_FORMAT);
    std::string textoMensagem = "{ \"id\" : std::to_string(id), \"velocidade\" : velocidade, \"timestamp\" : \"timestamp\" }";
    
    zmq::message_t mensagem(textoMensagem.size());
    memcpy(mensagem.data(), textoMensagem.data(), textoMensagem.size());

    sock.send(mensagem, zmq::send_flags::none);
}


std::string recebeMensagem(zmq::socket_t &sock){
    zmq::message_t mensagem;
    sock.recv(mensagem, zmq::recv_flags::none);
    // converte a mensagem para uma string
    return std::string(static_cast<char*>(mensagem.data()), mensagem.size());
}