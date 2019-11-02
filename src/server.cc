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

  const string endpoint = "tcp://127.0.0.1:" + port;

  // Create a subscriber socket
  zmqpp::context context;
  zmqpp::socket_type type = zmqpp::socket_type::subscribe;
  zmqpp::socket socket(context, type);

  // Subscribe to the default channel
  socket.subscribe("");

  // Connect to the publisher
  cout << "Connecting to " << endpoint << "..." << endl;
  socket.connect(endpoint);

  while(true) {

    // Receive (blocking call)
    zmqpp::message message;
    socket.receive(message);

    // Read as a string
    string text;
    message >> text;

    cout << "[RECV]: \"" << text << "\"" << endl;
  }

  // Unreachable, but for good measure
  socket.disconnect(endpoint);
  return 0;
}
