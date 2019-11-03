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

#include "../shared/json.hpp"

using namespace std;
using Poco::AutoPtr;
using Poco::Util::PropertyFileConfiguration;
using Poco::DateTimeFormatter;
using Poco::DateTimeFormat;
using Poco::Random;
using json = nlohmann::json;

int main() {
  AutoPtr<PropertyFileConfiguration> pConf;
  pConf = new PropertyFileConfiguration("resources/config/publish.properties");
  std::string port = pConf->getString("port");
  std::string topic = pConf->getString("topic");

  const string endpoint = "tcp://127.0.0.1:" + port;

  Random rnd;
  rnd.seed();

  unsigned int id = 0;
  json text;

  zmqpp::context context;
  zmqpp::socket_type type = zmqpp::socket_type::publish;
  zmqpp::socket socket (context, type);

  cout << "Binding to " << endpoint << "..." << endl;
  socket.bind(endpoint);

  while(true) {
    auto velocity = static_cast<unsigned char>(rnd.nextChar());
    Poco::Timestamp now;
    auto timestamp = DateTimeFormatter::format(now, DateTimeFormat::ISO8601_FRAC_FORMAT);

    text["id"] = id;
    text["velocidade"] = velocity;
    text["timestamp"] = timestamp;

    zmqpp::message message;
    message << topic << text.dump();

    socket.send(message);

    std::this_thread::sleep_for(std::chrono::milliseconds(1000));

    id++;
  }

  socket.disconnect(endpoint);
  return 0;
}
