#include "knn.h"
#include <omp.h>

/* Adjust these parameters (macros) to alter no. threads used.
 * If run using a batch system, adjust corresponding batch
 * file as needed */
#define ADJUST_NUM_THREADS false 
#define ADJUSTED_MAX_THREADS 16 

int
main (void)
{
  int test_j, test_counter = 0;
  int image_size;
  image_t train_data;
  image_t test_data;
  int num_threads;
  int thread_id;
  int count_right = 0;
  int count_wrong = 0;
  clock_t t_start, t_end, t_file_end, t_comp_start;
  double ttotal;

  /*** Capturing start time before file reading, content saving  */
  t_start = clock ();

  /* Reading both image, label training and testing files */
  read_mnist (train_img_file, train_lbl_file, &train_data, false);
  read_mnist (test_img_file, test_lbl_file, &test_data, false);

  /*** Capturing end time of file reading, content saving  */
  t_file_end = clock();

  /* Calculating the number of bytes containing each image */
  image_size = train_data.rows * train_data.cols;

  /* Getting the total number of threads available */
  num_threads = omp_get_max_threads ();

  /* As part of the project requirements, using ADJUSTED_MAX_THREADS
   * to adjust the number of threads used. Otherwise, defaults to
   * the number of threads read by omp_get_max_threads() */
  if (ADJUST_NUM_THREADS)
  { 
    num_threads = ADJUSTED_MAX_THREADS;
  }

  /* Declaring shared kk_shared array for recording and keeping
   * track of the K lists from each thread */
  int kk_shared_max = KV * num_threads;
  k_t kk_shared[kk_shared_max];

  /* Iterating through the test entries */
  for (test_counter = 0; test_counter < test_data.n; test_counter++)
  {
    /* Updating test image counter */
    test_j = test_counter * image_size;

    /* Initializing the shared kk_shared array */
    init (kk_shared, kk_shared_max);

    #pragma omp parallel shared(count_right,count_wrong)
    {
      /* Private/local (thread) variables */
      int z, px, px_sum;
      int train_j, train_counter;
      k_t kk[KV];
      int thread_id = omp_get_thread_num ();
      int l_count_right = 0;
      int l_count_wrong = 0;

      /* Initializing k_t arrays (containing the K closest images + labels */
      init (kk, KV);

      /* Iterating through the training entries */
      #pragma omp for private(train_counter, train_j)
      for (train_counter = 0; train_counter < train_data.n; train_counter++)
      {
        /* Updating training image counter */
        train_j = train_counter * image_size;

        /* Resetting variables before iterating though image's bytes */
        z = px = px_sum = 0;

        /* Iterating through each test, train images' bytes */
        while (z < image_size)
        {
          /* Calculating difference between pixels/bytes */
          px = test_data.img[test_j + z] - train_data.img[train_j + z];

          /* Adding all differences between test, train images */
          px_sum += (px * px);

          /* Increasing byte counter */
          ++z;

        } /*** CLOSING PIXEL/BYTE COMPARISON WHILE-LOOP ***/

        /* Verifying if comparison lies within the K smallest distances */
        if (px_sum < kk[KV - 1].dst)
        {
          /* Replacing last kk entry with current train image */
          kk[KV - 1].dst = px_sum;
          kk[KV - 1].lbl = train_data.lbl[train_counter];

          /* Sorting kk array by distance to keep them in increasing order */
          qsortk (kk, 0, KV - 1);
        }

      } /*** CLOSING (inner) TRAINING FOR-LOOP ***/

      /* Comparing actual value vs projected/expected value.
       *
       * Here we are using an OMP CRITICAL constructor/block allowing only
       * one thread at a time to update the coresponding portion of the
       * shared kk_shared array */
      #pragma omp critical
      {
        for (z = 0; z < KV; z++)
        {
          /* Saving K list/array from each thread */
          kk_shared[(KV * thread_id) + z] = kk[z];
        }
      }

      /* Using OMP BARRIER to make sure we sync all threads before
       * we go ahead with the sorting of the shared kk_shared array */
      #pragma omp barrier

      /* Using the OMP SINGLE construct/block to allow one thread
       * (the first one available, not necessarily the master) to
       * complete the sorting of kk_shared and updating counts.
       * This construct has the added feature of an ending barrier */
      #pragma omp single
      {
        qsortk (kk_shared, 0, (kk_shared_max) - 1);

        if (evaluate (kk_shared) == test_data.lbl[test_counter])
        {
          // Identifying another correctly classified digit
          ++count_right;
        }
        else
        {
          // Identifying another incorrectly classified digit
          ++count_wrong;
        }
      }

    } /*** CLOSING PARALLEL OMP ***/

  } /*** CLOSING (outer) TESTING FOR-LOOP ***/

  /*** Capturing time completed after all computations */
  t_end = clock();

  printf ("Number of training samples: %d\n", train_data.n);
  printf ("Number of test samples: %d\n", test_data.n);

  printf ("Number of threads used: %d\n", num_threads);

  float count_per = ((float)count_right/(float)test_data.n) * 100.0f;
  printf ("Number (percentage) of correctly identified test samples: %d (%.2f%)\n",
          count_right, count_per);
  count_per = count_wrong/test_data.n;
  count_per = ((float)count_wrong/(float)test_data.n) * 100.0f;
  printf ("Number of incorrectly identified test samples: %d (%.2f%)\n",
          count_wrong, count_per);

  /* Writing to terminal captured times - Note that these aren't real times,
   * but the "user" unix times. Still, it's a common way of comparison */
  ttotal = ((double) (t_file_end - t_start)) / ((double) CLOCKS_PER_SEC);
  printf ("File reading and capturing (user) time (seconds): %f\n", ttotal);

  ttotal = ((double) (t_end - t_file_end)) / ((double) CLOCKS_PER_SEC);
  printf ("Computation only (user) time (seconds): %f\n", ttotal);

  ttotal = ((double) (t_end - t_start)) / ((double) CLOCKS_PER_SEC);
  printf ("Overall approx. (real) time (seconds): %f (No load, print, exit times)\n", ttotal/num_threads);

  return 0;
}
