#include <iomanip>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#include <Poco/Util/PropertyFileConfiguration.h>
#include <zmqpp/zmqpp.hpp>

#include "../shared/json.hpp"

int main() {
  Poco::AutoPtr<Poco::Util::PropertyFileConfiguration> pConf;
  pConf = new Poco::Util::PropertyFileConfiguration("resources/config/subscribe.properties");
  std::string port = pConf->getString("port");
  std::string topic = pConf->getString("topic");

  const std::string endpoint = "tcp://127.0.0.1:" + port;

  std::string content;

  std::ofstream myfile;

  zmqpp::context context;
  zmqpp::socket_type type = zmqpp::socket_type::subscribe;
  zmqpp::socket socket(context, type);

  socket.subscribe(topic);

  std::cout << "Connecting to " << endpoint << "..." << std::endl;
  socket.connect(endpoint);


  while(true) {
    zmqpp::message message;
    socket.receive(message);

    message >> topic >> content;

    auto content_json = nlohmann::json::parse(content);

    auto timestamp = content_json["timestamp"].dump();
    timestamp = timestamp.substr(1, timestamp.size() - 2);

    std::cout << "Received at: " << timestamp << std::endl;

    std::ostringstream filename;
    filename << timestamp << ".json";

    myfile.open(filename.str());
    myfile << std::setw(4) << content_json;
    myfile.close();
  }

  socket.disconnect(endpoint);
  return 0;
}
