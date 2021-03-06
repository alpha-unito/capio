#include <iostream>
#include <mpi.h>
#include "../../../capio_ordered/capio_ordered.hpp"
#include "../../common/utils.hpp"

int const NUM_ELEM = 100;


int main(int argc, char** argv) {
    int data[NUM_ELEM];
    int expected_result[NUM_ELEM];
    int rank;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    if (argc != 4) {
        std::cout << "input error: capio buffer size, number of consumers and config file needed " << std::endl;
        MPI_Finalize();
        return 0;
    }
    int buf_size = std::stoi(argv[1]);
    int num_prods = std::stoi(argv[2]);
    std::string config_path = argv[3];
    std::cout << "reader " << rank << " before created capio object" << std::endl;
    capio_ordered capio(true, false, rank, buf_size, config_path);
    capio.capio_reduce(nullptr, data, NUM_ELEM, MPI_INT, nullptr, 0);
    if (rank == 0) {
        compute_expected_result_reduce(expected_result, NUM_ELEM, num_prods, 0);
        compare_expected_actual(data, expected_result, NUM_ELEM);
    }
    capio.capio_reduce(nullptr, data, NUM_ELEM, MPI_INT, nullptr, 0);
    if (rank == 0) {
        compute_expected_result_reduce(expected_result, NUM_ELEM, num_prods, 1);
        compare_expected_actual(data, expected_result, NUM_ELEM);
    }
    std::cout << "reader " << rank << " ended " << std::endl;
    MPI_Finalize();
}