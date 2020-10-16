## Install libraries

# Install ZMQ
```
git clone https://github.com/zeromq/libzmq.git
cd libzmq
mkdir build && cd build
cmake -DCMAKE_BUILD_TYPE=Release ..
make
sudo make install
```

# Install cppzmq
```
git clone https://github.com/zeromq/cppzmq.git
Repeate above steps to install
```

# Install Google Benchmark
```
git clone https://github.com/google/benchmark.git
git clone https://github.com/google/googletest.git benchmark/googletest
Repeate above steps to install
```

## Build test code
```
mkdir build && cd build
cmake ..
make
```
