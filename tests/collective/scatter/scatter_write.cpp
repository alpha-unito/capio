#include <iostream>
#include <mpi.h>
#include "../../../capio_ordered/capio_ordered.hpp"
#include "../../common/utils.hpp"

int const NUM_ELEM = 100;

int main(int argc, char** argv) {
    int data[NUM_ELEM];
    int rank;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    if (argc != 4) {
        std::cout << "input error: capio buffer size, number of consumers and config file needed " << std::endl;
        MPI_Finalize();
        return 0;
    }
    int buf_size = std::stoi(argv[1]);
    int num_cons = std::stoi(argv[2]);
    std::string config_path = argv[3];
    capio_ordered capio(false, true, rank, buf_size, config_path);
    std::cout << "writer " << rank << "created capio object" << std::endl;

    if (rank == 0) {
        initialize(data, NUM_ELEM, 0);
        capio.capio_scatter(data, nullptr, NUM_ELEM / num_cons);
        initialize(data, NUM_ELEM, 1);
        capio.capio_scatter(data, nullptr, NUM_ELEM / num_cons);
    }
    std::cout << "writer " << rank << "ended " << std::endl;
    MPI_Finalize();
    return 0;
}