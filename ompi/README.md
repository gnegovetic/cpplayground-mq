## Instalation
sudo apt install mpi

## Build from source code
Follow steps: https://www.open-mpi.org/faq/?category=building#easy-build

## Build test code and run
mkdir build && cd build
cmake ..
make

mpirun --hostfile ../hostfile -np 2 ./mpicomm -v
mpirun --hostfile ../hostfile -np 2 ./mpicomm

