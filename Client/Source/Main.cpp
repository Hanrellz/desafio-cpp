#include <iostream>
#include <fstream>
#include <string>
#include <zmqpp/zmqpp.hpp>


void SaveFile(std::string& jsonMessage) {
    // // Hack to avoid use a external library to pasr the josno
    std::size_t found = jsonMessage.find("timestamp");
    if (found != std::string::npos) {
        std::string filename =  jsonMessage.substr(found+13, 24) + ".json";
        std::cout << "filename: " << filename << '\n';
        std::ofstream myfile;
        myfile.open(filename);
        myfile << jsonMessage;
        myfile.close();
    }
}

int main() {

    // Create the context
    zmqpp::context zmqppContext;

    // Create a subscriber socket
    zmqpp::socket_type socketType = zmqpp::socket_type::subscribe;
    zmqpp::socket socket(zmqppContext, socketType);

    // Set the topic
    std::string topic = "music";
    socket.subscribe(topic);

    // Connect to the publisher
    const std::string publisherEndPoint = "tcp://localhost:8000";
    socket.connect(publisherEndPoint);

    // Receive message loop
    zmqpp::message message;
    std::string jsonMessage;
    while(true) {
        std::cout << "Waiting for messages..." << std::endl;
        if (socket.receive(message) ) {
            message >> topic >> jsonMessage;
            std::cout << "Topic: " << topic << std::endl;
            std::cout << jsonMessage << std::endl;
            SaveFile(jsonMessage);
        }
    }

    return EXIT_SUCCESS;
}
