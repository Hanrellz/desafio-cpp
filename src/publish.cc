#include <chrono>
#include <iostream>
#include <string>
#include <thread>

#include <Poco/DateTimeFormat.h>
#include <Poco/DateTimeFormatter.h>
#include <Poco/Random.h>
#include <Poco/Timestamp.h>
#include <Poco/Util/PropertyFileConfiguration.h>
#include <zmqpp/zmqpp.hpp>

#include "json.hpp"

using namespace std;
using Poco::AutoPtr;
using Poco::Util::PropertyFileConfiguration;
using Poco::DateTimeFormatter;
using Poco::DateTimeFormat;
using Poco::Random;
using json = nlohmann::json;

int main() {
  // Read properties file
  AutoPtr<PropertyFileConfiguration> pConf;
  pConf = new PropertyFileConfiguration("../MODULO/resources/config/MODULO.properties");
  std::string port = pConf->getString("port");
  std::string topic = pConf->getString("topic");

  const string endpoint = "tcp://127.0.0.1:" + port;

  Random rnd;
  rnd.seed();

  unsigned int id = 0;
  json text;

  // Create a publisher socket
  zmqpp::context context;
  zmqpp::socket_type type = zmqpp::socket_type::publish;
  zmqpp::socket socket (context, type);

  // Open the connection
  cout << "Binding to " << endpoint << "..." << endl;
  socket.bind(endpoint);

  while(true) {
    auto velocity = static_cast<unsigned char>(rnd.nextChar());
    Poco::Timestamp now;
    auto timestamp = DateTimeFormatter::format(now, DateTimeFormat::ISO8601_FRAC_FORMAT);

    text["id"] = id;
    text["velocidade"] = velocity;
    text["timestamp"] = timestamp;

    // Create a message and feed data into it
    zmqpp::message message;
    message << topic << text.dump();

    // Send it off to any subscribers
    socket.send(message);

    // Sleep for one second
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));

    id++;
  }

  // Unreachable, but for good measure
  socket.disconnect(endpoint);
  return 0;
}
