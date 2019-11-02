#include <string>
#include <iostream>

#include <zmqpp/zmqpp.hpp>
#include <Poco/Util/PropertyFileConfiguration.h>

using namespace std;
using Poco::AutoPtr;
using Poco::Util::PropertyFileConfiguration;

int main() {
  AutoPtr<PropertyFileConfiguration> pConf;
  pConf = new PropertyFileConfiguration("../MODULO/resources/config/MODULO.properties");
  std::string port = pConf->getString("port");
  std::string topic = pConf->getString("topic");

  const string endpoint = "tcp://127.0.0.1:" + port;

  // Create a publisher socket
  zmqpp::context context;
  zmqpp::socket_type type = zmqpp::socket_type::publish;
  zmqpp::socket socket (context, type);

  // Open the connection
  cout << "Binding to " << endpoint << "..." << endl;
  socket.bind(endpoint);

  while(true) {
    string text = "Hello at ";

    // Create a message and feed data into it
    zmqpp::message message;
    message << topic << text;

    // Send it off to any subscribers
    socket.send(message);
  }

  // Unreachable, but for good measure
  socket.disconnect(endpoint);
  return 0;
}
