#!/bin/bash


mpiexec -n 2 ../../build/capio_process/capio 10010 ../../one_node_4_4.yaml > exp_capio_read_one_to_one_4_4_capio.txt &

mpiexec -n 4 ../../build/experiments/capio_comm/capio_write_one_matrix 100 100 ../../one_node_4_4.yaml > exp_capio_read_one_to_one_4_4_prods.txt &

mpiexec -n 4 ../../build/experiments/capio_comm/capio_read_one_matrix 100 100 ../../one_node_4_4.yaml > exp_capio_read_one_to_one_4_4_cons.txt

