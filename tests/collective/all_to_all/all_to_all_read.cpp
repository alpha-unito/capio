#include <iostream>
#include <mpi.h>
#include "../../../capio_ordered/capio_ordered.hpp"
#include "../../common/utils.hpp"

int const NUM_ELEM = 100;

void compute_expected_result(int* expected_result, int array_length, int size, int rank) {
    int start = NUM_ELEM / size * rank;
    for (int i = 0, num = start; i < array_length; ++i) {
        expected_result[i] = num;
        ++num;
        if ((i + 1) % (NUM_ELEM / size) == 0) {
            ++start;
            num = start;
        }
    }
}

int main(int argc, char** argv) {
    int* data, *expected_result;
    int rank, size;
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    if (argc != 4) {
        std::cout << "input error: capio buffer size, number of producers and config file needed " << std::endl;
        MPI_Finalize();
        return 0;
    }
    int buf_size = std::stoi(argv[1]);
    int num_prods= std::stoi(argv[2]);
    std::string config_path = argv[3];
    int array_length = NUM_ELEM / size * num_prods;
    capio_ordered capio(true, false, rank, buf_size, config_path);
    std::cout << "reader " << rank << " before created capio object" << std::endl;
    data = new int[array_length];
    expected_result = new int[array_length];
    capio.capio_all_to_all(nullptr, NUM_ELEM / size, data);
    compute_expected_result(expected_result, array_length, size, rank);
    compare_expected_actual(data, expected_result, array_length);
    capio.capio_all_to_all(nullptr, NUM_ELEM / size, data);
    compare_expected_actual(data, expected_result, array_length);
    free(data);
    free(expected_result);
    std::cout << "reader " << rank << " ended " << std::endl;
    MPI_Finalize();
}