#include <zmq.hpp>
#include <string>
#include <iostream>
#include <unistd.h>
#include <sstream>
#include <fstream>

#include <Poco/JSON/JSON.h>
#include <Poco/JSON/Parser.h>
#include <Poco/Dynamic/Var.h>

std::string timestamp = "2017-01-03T13:35:22.103Z";
std::string topico = "topico_default";
int32_t ordem = 0;
std::string porta_servidor = "5555";
std::string s_msg_received = "{\"id\":1,\"timestamp\":\"2019-11-26T16:21:34.248Z\",\"velocidade\":163}";

void readConfig(void){
	std::string s_file;
	std::ifstream ifs;
	ifs.open ("./resources/config/client.properties");
	getline(ifs,s_file);
	ifs.close();

	Poco::JSON::Parser parser;
	Poco::Dynamic::Var result = parser.parse(s_file);
	Poco::JSON::Object::Ptr jsonProp = result.extract<Poco::JSON::Object::Ptr>();

	topico = jsonProp->get("topico").toString();
	porta_servidor = jsonProp->get("porta_servidor").toString();

	std::cout << "Topico :" << topico << std::endl;
	std::cout << "Porta :" << porta_servidor << std::endl;
}


void savePackage(std::string pMsg){
	std::istringstream iss(pMsg);
	std::string jsonStr = s_msg_received;
	int i=0;
	for(std::string value; iss >> value; i++){
		if(i==2) jsonStr = value;
	}

	Poco::JSON::Parser parser;
	Poco::Dynamic::Var result = parser.parse(jsonStr);
	Poco::JSON::Object::Ptr jsonMsg = result.extract<Poco::JSON::Object::Ptr>();

	timestamp = jsonMsg->get("timestamp").toString();

	std::ofstream ofs;
	std::string file_name = "./receives/"+timestamp+".json";
	ofs.open (file_name);
	ofs << pMsg;
	ofs.close();
	std::cout << pMsg << std::endl;
	//std::cout << "Package Saved :" << file_name << std::endl;
}

int main(){


	readConfig();

	//savePackage(s_msg_received); 	//APENAS PARA TESTE

	zmq::context_t ctx(1);
	zmq::socket_t sub(ctx, ZMQ_SUB);
	
	std::string server_add = "tcp://localhost:"+porta_servidor;
	sub.connect(server_add.c_str());

	std::stringstream ss;
	ss << topico;

	sub.setsockopt(ZMQ_SUBSCRIBE, ss.str().c_str(), ss.str().size());

	while(1){

		zmq::message_t msg;
		std::cout << "Aguardando resposta do server" << std::endl;

		sub.recv(&msg);

		std::string str = std::string(static_cast<char*>(msg.data()), msg.size());
		savePackage(str);

		//std::cout << str << std::endl;		

	}
	return 0;
}
