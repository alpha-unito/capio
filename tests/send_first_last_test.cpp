#include <iostream>
#include <mpi.h>
#include "../capio_ordered/capio_ordered.hpp"

/*
 * test capio_send. To use with recv_simple_test.cpp
 *
 * each consumer sends an integer to a producer with the same rank
 *
 * send_simple_test and recv_simple_test must be lunched with an equals number of MPI processes
 *
 */

int main(int argc, char** argv) {
    int rank, recipient_rank;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    if (argc != 4) {
        std::cout << "input error: capio buffer size, number of consumers and config file needed" << std::endl;
        MPI_Finalize();
        return 1;
    }
    int buf_size = std::stoi(argv[1]);
    int num_consumers = std::stoi(argv[2]);
    std::string config_path = argv[3];
    capio_ordered capio(false, true, rank, buf_size, config_path);
    std::cout << "writer " << rank << "created capio object" << std::endl;
    if (rank == 0) {
        recipient_rank = num_consumers - 1;
        for (int i = 0; i < 100; ++i) {
            capio.capio_send(&i, 1, recipient_rank);
        }
    }
    std::cout << "writer " << rank << "ended " << std::endl;
    MPI_Finalize();
    return 0;
}
