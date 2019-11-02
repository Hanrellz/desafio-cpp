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

  const string endpoint = "tcp://localhost:" + port;

  // initialize the 0MQ context
  zmqpp::context context;

  // generate a push socket
  zmqpp::socket_type type = zmqpp::socket_type::push;
  zmqpp::socket socket (context, type);

  // open the connection
  cout << "Opening connection to " << endpoint << "..." << endl;
  socket.connect(endpoint);

  // send a message
  cout << "Sending text and a number..." << endl;
  zmqpp::message message;
  // compose a message from a string and a number
  message << "Hello World!" << 42;
  socket.send(message);
  
  cout << "Sent message." << endl;
  cout << "Finished." << endl;
}
