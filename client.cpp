// creates a packet, sends it and expect to receive it back
#include <zmq.hpp>
#include <iostream>
using namespace std;

static const int kMsgLen = 4096;

static bool send(zmq::socket_t& socket) {
    zmq::message_t msg (kMsgLen);
    auto res = socket.send(msg, zmq::send_flags::dontwait);

    if (res.has_value() && res.value() == kMsgLen) {
        cout << "Message sent" << endl;
        return true;
    }

    cerr << "Error sending message" << endl;
    return false;

}

static bool receive(zmq::socket_t& socket) {
    cout << "Receiving..." << endl;
    zmq::message_t reply;
    bool suc = socket.recv (&reply);
    if (suc) {
        cout << "Received " << reply.size() << endl;
    }
    else {
        cerr << "Error receiving message" << endl;
    }
    return suc;
}

int main()
{
    zmq::context_t context(1);
    zmq::socket_t socket(context, ZMQ_REQ);

    cout << "--- Test TCP" << endl;
    socket.connect("tcp://localhost:5555");

    if ( send(socket) ) {
        receive(socket);
    }

    cout << "--- Test ICP" << endl;
    socket.connect("ipc://file1");

    if ( send(socket) ) {
        receive(socket);
    }

    return 0;
}