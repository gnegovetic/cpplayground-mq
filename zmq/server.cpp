// return packets that it receives
#include <zmq.hpp>
#include <string>
#include <iostream>
#include <unistd.h>
using namespace std;

int main () {
    //  Prepare our context and socket
    zmq::context_t context (1);
    zmq::socket_t socket (context, ZMQ_REP);
    socket.bind ("tcp://*:5555");
    socket.bind ("ipc://file1");

    while (true) {
        zmq::message_t request;

        //  Wait for next request from client
        socket.recv (&request);
        size_t msgSize = request.size();
        //cout << "Received " << msgSize << std::endl;

        //  Send the message back
        zmq::message_t reply(msgSize);
        memcpy(reply.data(), request.data(), msgSize);
        socket.send(reply);
    }
    return 0;
}
