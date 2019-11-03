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

int main() {
  Poco::AutoPtr<Poco::Util::PropertyFileConfiguration> pConf;
  pConf = new Poco::Util::PropertyFileConfiguration("resources/config/publish.properties");
  std::string port = pConf->getString("port");
  std::string topic = pConf->getString("topic");

  const std::string endpoint = "tcp://127.0.0.1:" + port;

  Poco::Random rnd;
  rnd.seed();

  unsigned int id = 0;
  nlohmann::json text;

  zmqpp::context context;
  zmqpp::socket_type type = zmqpp::socket_type::publish;
  zmqpp::socket socket (context, type);

  std::cout << "Binding to " << endpoint << "..." << std::endl;
  socket.bind(endpoint);

  while(true) {
    auto velocity = static_cast<unsigned char>(rnd.nextChar());
    Poco::Timestamp now;
    auto timestamp = Poco::DateTimeFormatter::format(now, Poco::DateTimeFormat::ISO8601_FRAC_FORMAT);

    text["id"] = id;
    text["velocidade"] = velocity;
    text["timestamp"] = timestamp;

    zmqpp::message message;
    message << topic << text.dump();

    socket.send(message);

    std::cout << "Sent at: " << timestamp << std::endl;

    std::this_thread::sleep_for(std::chrono::milliseconds(1000));

    id++;
  }

  socket.disconnect(endpoint);
  return 0;
}
