**knn_openmp_mnist

This is a very fast implementation of the k Nearest Neighbors (kNN) classification algorithm using C with OpenMP targeting the MNIST dataset (See http://yann.lecun.com/exdb/mnist/). The MNIST dataset includes four files that are expected to be available:


- train-images-idx3-ubyte
- train-labels-idx1-ubyte
- t10k-images-idx3-ubyte
- t10k-labels-idx1-ubyte 


It includes both serial and multithreaded (via OpenMP) implementations. In comparison, the OpenMP code is pretty fast when using a machine with a large number of CPU cores!  And it was successfully tested for scalability (up to 16 cores) using a node from the Stampede Supercomputer system thanks to XSEDE (https://www.xsede.org/) + TACC (https://www.tacc.utexas.edu/)! (Stampede was superceded by Stampede2 in 2018). The code was implemented and tested using GCC. Any modern, stable version of GCC should work fine. The included Makefile will generate by default both serial (knn-serial) and a multithreaded (knn-openmp) binaries. The code expects the MNIST data files to be on the same directory as the binary.
