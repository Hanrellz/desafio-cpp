#include <zmq.hpp>
#include <fstream>
#include <string>
#include <ctime>
#include <vector>
#include <random>

#include "Poco/Timestamp.h"
#include "Poco/DateTimeFormat.h"
#include "Poco/DateTimeFormatter.h"

std::vector<std::string> getConfiguracoes(std::string caminho);

void enviaTopico(zmq::socket_t &sock, const std::string &string);

void enviaOrdem(zmq::socket_t &sock, const int &ordem);

void enviaMensagem(zmq::socket_t &sock, const int &id);

std::string recebeMensagem(zmq::socket_t &sock);