#include "../../capio_ordered/capio_ordered.hpp"
#include "../commons/utils_exp.hpp"
#include <mpi.h>


int main(int argc, char** argv) {
    int rank, num_rows, num_cols, buf_size, **matrix;
    MPI_Init(&argc, &argv);
    if (argc != 5) {
        std::cout << "input error: capio buffer size, num of rows, num of columns and config file needed" << std::endl;
        MPI_Finalize();
        return 1;
    }
    buf_size = std::stoi(argv[1]);
    num_rows = std::stoi(argv[2]);
    num_cols = std::stoi(argv[3]);
    std::string config_path(argv[4]);
    matrix = alloc_2d_int(num_rows, num_cols);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    capio_ordered capio(false, true, rank, buf_size, config_path);
    for (int i = 0; i < num_rows; ++i) {
        for (int j = 0; j < num_cols; ++j) {
            matrix[i][j] = i + j + rank;
        }
    }
    capio.capio_send(matrix[0], num_rows * num_cols, 0);
    free(matrix[0]);
    free(matrix);
    MPI_Finalize();
}