#include <iostream>
#include <string>
#include <thread>
#include <chrono>
#include <sstream>
#include <iomanip>
#include <zmqpp/zmqpp.hpp>


inline std::string to_iso_8601(std::chrono::time_point<std::chrono::system_clock> t) {
	auto epoch_seconds = std::chrono::system_clock::to_time_t(t);
	std::stringstream stream;
	stream << std::put_time(gmtime(&epoch_seconds), "%FT%T");
	auto truncated = std::chrono::system_clock::from_time_t(epoch_seconds);
	auto delta_us = std::chrono::duration_cast<std::chrono::milliseconds>(t - truncated).count();
	stream << "." << std::fixed << std::setw(3) << std::setfill('0') << delta_us << "Z";
	return stream.str();
}

int main() {

    // Create the context
    zmqpp::context zmqppContext;

    // Create a publish socket
    zmqpp::socket_type socketType = zmqpp::socket_type::publish;
    zmqpp::socket socket(zmqppContext, socketType);

    // Bind the publisher socket
    const std::string publisherEndPoint = "tcp://*:8000";
    socket.bind(publisherEndPoint);

    // Send message loop
    zmqpp::message message;
    int id{0};
    int velocity{100};
    std::string jsonMessage;
    while(true) {
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        // Hack to avoid use a external library
        jsonMessage = 
            "{\n   \"id\": " + std::to_string(id) + ",\n" +
            "   \"velocidade\": " + std::to_string(velocity) + ",\n" +
            "   \"timestamp\": \"" + to_iso_8601(std::chrono::system_clock::now()) + "\"\n}"; 
        std::cout << jsonMessage << std::endl;
        message << "music" << jsonMessage;
        socket.send(message);
        id++;
    }
}
