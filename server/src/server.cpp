#include <zmq.hpp>
#include <string>
#include <iostream>
#include <unistd.h>
#include <stdint.h>
#include <sys/time.h>
#include <fstream>

#include <Poco/JSON/JSON.h>
#include <Poco/JSON/Parser.h>
#include <Poco/Dynamic/Var.h>


std::string timestamp = "2017-01-03T13:35:22.103Z";
std::string topico = "topico_default";
std::string porta_servidor = "5555";

int32_t ordem = 1;
uint8_t velocidade = 0;

void updateTimestamp(void){
	timeval now;
	gettimeofday(&now, NULL);
	int milli = now.tv_usec / 1000;
	char tmp[sizeof ("2017-01-03T13:35:22.103Z")];
	char buf[sizeof ("2017-01-03T13:35:22.103Z")];
	strftime(tmp, sizeof(tmp),"%Y-%m-%dT%H:%M:%S", localtime(&now.tv_sec));
	snprintf(buf, sizeof(buf),"%s.%dZ",tmp,milli);

	std::stringstream ss;
	ss << buf;
	ss >> timestamp;
}

void updateVelocidade(void){
	velocidade = rand() % 255;
}


void readConfig(void){
	std::string s_file;
	std::ifstream ifs;
	ifs.open ("./resources/config/server.properties");
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

void saveConfig(void){
	Poco::JSON::Object jsonProp;
	jsonProp.set("topico",topico);
	jsonProp.set("porta_servidor",porta_servidor);
	std::stringstream ss_file;
	Poco::JSON::Stringifier::stringify(jsonProp, ss_file);

	std::ofstream ofs;
	ofs.open ("./resources/config/server.properties");
	ofs << ss_file.str();
	ofs.close();
}


int main (){
	
	std::string mensagem;

	//saveConfig();
	readConfig();

	zmq::context_t ctx;
	zmq::socket_t pub (ctx, ZMQ_PUB);
	std::string server_add = "tcp://*:"+porta_servidor;
	pub.bind(server_add.c_str());

	while(1){

		sleep(1);

		updateTimestamp();
		updateVelocidade();


		Poco::JSON::Object jsonMsg;
		jsonMsg.set("id",1);
		jsonMsg.set("velocidade",velocidade);
		jsonMsg.set("timestamp",timestamp);

		std::ostringstream oss;
		Poco::JSON::Stringifier::stringify(jsonMsg, oss);
		

		std::string smsg = topico +" "+ std::to_string(ordem)+" " +oss.str();
		zmq::message_t msg(smsg.size());
		std::memcpy(msg.data(), (smsg.c_str()), smsg.length());

		std::string str = std::string(static_cast<char*>(msg.data()), msg.size());
		std::cout << str << std::endl;
		pub.send(msg);

		ordem += 1;
		if(ordem < 0) ordem = 0;
		
	}


	pub.close();
	ctx.close();

	return 0;
}
