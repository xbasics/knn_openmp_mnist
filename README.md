knn_openmp_mnist

This is a very fast implementation of the k Nearest Neighbor (kNN) classification XXX using C with OpenMP targeting the MNIST dataset (See http://yann.lecun.com/exdb/mnist/). It includes both a serial and multithreaded (via OpenMP) implementations.  In comparison, the OpenMP code is ridiculously fast!  And it was successfully tested for scalability (up to 16 cores) using a node from the Stampede Supercomputer (Stampede was superceded by Stampede2 in 2018). Go XSEDE (https://www.xsede.org/) + TACC (https://www.tacc.utexas.edu/)! The code was implemented and tested with the GCC. A modern verion of GCC should work fine. The included Makefile will generate by default both serial (knn-serial) and a multithreaded (knn-openmp) binaries. The code expects the MNIST dataset to be on the same directory as the binary.
