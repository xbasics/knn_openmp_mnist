#include "knn.h"


int
main (void)
{
    int test_j, test_counter = 0;
    int train_j, train_counter = 0;
    int image_size;
    int z, tmp, tmp_sum;
    int count_right = 0;
    int count_wrong = 0;
    image_t train_data;
    image_t test_data;
    k_t kk[KV];
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

    /* Iterating through the test entries */
    for (test_j = 0; test_j < test_data.total; test_j += image_size)
    {
        /* Initializing k_t arrays (containing the K closest images + labels */
        init (kk, KV);

        /* Iterating through the training entries */
        for (train_j = 0; train_j < train_data.total; train_j += image_size)
	{
            /* Resetting variables before iterating though image's bytes */
            z = tmp = tmp_sum = 0;

            /* Iterating through each test, train images' bytes */
            while (z < image_size)
	    {
                /* Calculating difference between pixels/bytes */
                tmp = test_data.img[test_j + z] - train_data.img[train_j + z];

		/* Adding all differences between test, train images */
		tmp_sum += (tmp * tmp);

                /* Increasing byte counter */
                ++z;
	    }

	    /* Verifying if comparison lies within the K smallest distances */ 
	    if (tmp_sum < kk[KV-1].dst)
	    {
                /* Replacing last kk entry with current train image */
                kk[KV-1].dst = tmp_sum;
		kk[KV-1].lbl = train_data.lbl[train_counter];

		/* Sorting kk array by distance to keep them in increasing order */
		qsortk (kk, 0, KV-1);
	    } 

	    /* Increasing train (whole) image counter */
	    ++train_counter;
	}

	/* Comparing actual with projected value */
        if (evaluate (kk) == test_data.lbl[test_counter])
        {
            ++count_right;
        }
	else
        {
            ++count_wrong;
        }

        /*	
        for (z = 0; z < KV; z++)
        {
            printf ("%d:%d ", kk[z].dst, kk[z].lbl);
        }
        printf ("\t\t>> %d\t>> %d", test_data.lbl[test_counter], evaluate(kk));
        printf ("\n");
	if (test_counter > 0 && test_counter % 100 == 0)
	{
            printf ("Testing test entry %d\n", test_counter);
	    return 0;
	}
        */

	/* Restarting comparisons with next test image */
	train_counter = 0;
	++test_counter;
    }


  /*** Capturing time completed after all computations */
  t_end = clock();

  printf ("Number of training samples: %d\n", train_data.n);
  printf ("Number of test samples: %d\n", test_data.n);

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
  printf ("Overall approx. (real) time (seconds): %f (No load, print, exit times)\n", ttotal);

  return 0;
}
