#include <benchmark/benchmark.h>
#include <zmq.hpp>
#include <iostream>
using namespace std;

class Setup : public benchmark::Fixture
{
protected:
    static const int kMsgLen = 4096;
    zmq::context_t* pContext;
    zmq::socket_t* pSocket;

public:
	void SetUp(const ::benchmark::State& state) {
        pContext = new zmq::context_t(1);
        pSocket = new zmq::socket_t(*pContext, ZMQ_REQ);
    }
    void TearDown(const ::benchmark::State& state) {
        delete pSocket;
        delete pContext;
    }

    bool send(zmq::socket_t& socket) {
        zmq::message_t msg (kMsgLen);
        auto res = socket.send(msg, zmq::send_flags::dontwait);

        if (res.has_value() && res.value() == kMsgLen) {
            //cout << "Message sent" << endl;
            return true;
        }

        cerr << "Error sending message" << endl;
        return false;

    }

    bool receive(zmq::socket_t& socket) {
        //cout << "Receiving..." << endl;
        zmq::message_t reply;
        bool suc = socket.recv (&reply);
        if (suc) {
            //cout << "Received " << reply.size() << endl;
        }
        else {
            cerr << "Error receiving message" << endl;
        }
        return suc;
    }
};

BENCHMARK_F(Setup, MsgTestTCP)(benchmark::State& state)
{
    pSocket->connect("tcp://localhost:5555");

	for (auto _ : state)
	{
		if ( send(*pSocket) ) {
            receive(*pSocket);
        }
	}
}

BENCHMARK_F(Setup, MsgTestICP)(benchmark::State& state)
{
    pSocket->connect("ipc://file1");

    for (auto _ : state)
	{
        if ( send(*pSocket) ) {
            receive(*pSocket);
        }
    }
}

BENCHMARK_MAIN();
