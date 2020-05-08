/* Making sure we are only using one single copy of this code */
#ifndef __KNN__
#define __KNN__

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <sys/times.h>

/* Defining the K value for our nearest neighbor implementation */
#define KV 5

/* Definitions for name of training image and label files */
#define train_img_file "train-images-idx3-ubyte"
#define train_lbl_file "train-labels-idx1-ubyte"

/* Definitions for name of testing image and label files */
#define test_img_file "t10k-images-idx3-ubyte"
#define test_lbl_file "t10k-labels-idx1-ubyte"

/* Convenience definitions for true, false boolean values */
#define true 1
#define false 0

/* Type definition for the structure containing both images, labels */
typedef struct 
{
    unsigned char *img; /* pixels/bytes for all images */
    unsigned char *lbl; /* labels for all images */
    int n; /* number of image, label entries */
    int rows; /* number of image rows */
    int cols; /* number of image columns */
    int total; /* total number of image pixels/bytes */
} image_t;

/* Type definition for the structure containing distance, label for k vectors */
typedef struct
{
    int dst; /* distance */
    unsigned char lbl; /* label */
    int c; /* count; used only during digit identification */
} k_t;

/* Reads content of both image and label files into the image_t structure */
void read_mnist (char *, char *, image_t *, int);

/* Initializing kk array */
void init (k_t *, int);

/* Quick sort implementation for sorting the kk array values */
void qsortk (k_t *, int, int);

/* Identify digit value based on the K closest distances */
int evaluate (k_t *);

#endif
