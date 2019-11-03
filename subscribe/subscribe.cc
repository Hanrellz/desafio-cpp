#include <iomanip>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#include <Poco/Util/PropertyFileConfiguration.h>
#include <zmqpp/zmqpp.hpp>

#include "../shared/json.hpp"

using namespace std;
using Poco::AutoPtr;
using Poco::Util::PropertyFileConfiguration;
using json = nlohmann::json;

int main() {
  AutoPtr<PropertyFileConfiguration> pConf;
  pConf = new PropertyFileConfiguration("resources/config/subscribe.properties");
  string port = pConf->getString("port");
  string topic = pConf->getString("topic");

  const string endpoint = "tcp://127.0.0.1:" + port;

  string content;

  ofstream myfile;

  zmqpp::context context;
  zmqpp::socket_type type = zmqpp::socket_type::subscribe;
  zmqpp::socket socket(context, type);

  socket.subscribe(topic);

  cout << "Connecting to " << endpoint << "..." << endl;
  socket.connect(endpoint);


  while(true) {
    zmqpp::message message;
    socket.receive(message);

    message >> topic >> content;

    auto content_json = json::parse(content);

    auto timestamp = content_json["timestamp"].dump();
    timestamp = timestamp.substr(1, timestamp.size() - 2);

    cout << "Received at: " << timestamp << endl;

    std::ostringstream filename;
    filename << timestamp << ".json";

    myfile.open(filename.str());
    myfile << std::setw(4) << content_json;
    myfile.close();
  }

  socket.disconnect(endpoint);
  return 0;
}
