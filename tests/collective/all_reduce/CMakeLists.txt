add_executable(all_reduce_write all_reduce_write.cpp ../../../capio_ordered/capio_ordered.hpp)
add_executable(all_reduce_read all_reduce_read.cpp ../../../capio_ordered/capio_ordered.hpp)

target_link_libraries(all_reduce_write ${MPI_LIBRARIES} rt Threads::Threads)
target_link_libraries(all_reduce_read ${MPI_LIBRARIES} rt Threads::Threads)

# includes MPI
include_directories(${MPI_INCLUDE_PATH})
if(MPI_COMPILE_FLAGS)
    set_target_properties(all_reduce_write PROPERTIES
            COMPILE_FLAGS "${MPI_COMPILE_FLAGS}")
    set_target_properties(all_reduce_read PROPERTIES
            COMPILE_FLAGS "${MPI_COMPILE_FLAGS}")
endif()

if(MPI_LINK_FLAGS)
    set_target_properties(all_reduce_write PROPERTIES
            LINK_FLAGS "${MPI_LINK_FLAGS}")
    set_target_properties(all_reduce_read PROPERTIES
            LINK_FLAGS "${MPI_LINK_FLAGS}")
endif()
