#include "knn.h"

/* 
 * Reads MNIST image and corresponding label file. This function is used
 * for both training and testing files.
 */
void
read_mnist (char *img_file, char *lbl_file, image_t *f_data, int do_print)
{
    unsigned char ubyte_m;
    unsigned char ubyte0;
    unsigned char ubyte1;
    unsigned char ubyte2;
    unsigned char ubyte3;
    int k, tmp_n;

    /* Opening image file */
    FILE *fd = fopen (img_file, "rb");

    if (do_print)
        printf ("Reading file: %s\n", img_file);

    /*
     * Reading image file header...
     */

    /* Reading/verifying the image file's magic number */
    ubyte_m = fgetc (fd); // expected 0
    ubyte_m = fgetc (fd); // expected 0

    if ((ubyte_m = fgetc (fd)) != 8) // expected 8 = unsigned char
    {
        printf ("Read magic number, data type %d. Expected 8.\n", ubyte_m); 
        exit;
    }
    if ((ubyte_m = fgetc (fd)) <= 2 || ubyte_m > 3) // expected 3 = image
    {
        printf ("Read magic number, number of dimensions %d. \
                 Expected 3 for image file.\n", ubyte_m); 
        exit;
    }

    /* Reading the number of examples from image file */
    ubyte0 = fgetc (fd);
    ubyte1 = fgetc (fd);
    ubyte2 = fgetc (fd);
    ubyte3 = fgetc (fd);
    f_data->n = (ubyte0 << 24) | (ubyte1 << 16) | (ubyte2 << 8) | ubyte3;
    if (do_print)
        printf ("Number of examples: %d\n", f_data->n);

    /* Reading the number of rows per example from image file */
    ubyte0 = fgetc (fd);
    ubyte1 = fgetc (fd);
    ubyte2 = fgetc (fd);
    ubyte3 = fgetc (fd);
    f_data->rows = (ubyte0 << 24) | (ubyte1 << 16) | (ubyte2 << 8) | ubyte3;
    if (do_print)
        printf ("Number of rows per example: %d\n", f_data->rows);

    /* Reading the number of columns per example from image file */
    ubyte0 = fgetc (fd);
    ubyte1 = fgetc (fd);
    ubyte2 = fgetc (fd);
    ubyte3 = fgetc (fd);
    f_data->cols = (ubyte0 << 24) | (ubyte1 << 16) | (ubyte2 << 8) | ubyte3;
    if (do_print)
        printf ("Number of columns per example: %d\n", f_data->cols);

    /* Allocating memory for image data */
    f_data->img = malloc (sizeof(unsigned char)*f_data->n*f_data->rows*f_data->cols);

    /* Calculating the total number of pixels/bytes to be read */
    f_data->total = f_data->n*f_data->rows*f_data->cols;

    /* Reading image data */
    for (k = 0; k < f_data->total; k++)
    {
        f_data->img[k] = fgetc (fd);

        if (do_print)
            printf ("%d:%d ", k, f_data->img[k]);
    }

    if (do_print)
        printf ("\n%d pixels (unsigned chars) read.\n", k);

    /* Closing image file */
    fclose (fd);


    /* Opening label file */
    fd = fopen (lbl_file, "rb");

    if (do_print)
        printf ("Reading file: %s\n", lbl_file);

    /*
     * Reading label file header...
     */

    /* Reading/verifying the label file's magic number */
    ubyte_m = fgetc (fd); // expected 0
    ubyte_m = fgetc (fd); // expected 0
    if ((ubyte_m = fgetc (fd)) != 8) // expected 8 = unsigned char
    {
        printf ("Read magic number, data type %d. Expected 8.\n", ubyte_m); 
        exit;
    }
    if ((ubyte_m = fgetc (fd)) < 1 || ubyte_m > 1) // expected 1 = label
    {
        printf ("Read magic number, number of dimensions %d. \
                 Expected 1 for label file.\n", ubyte_m); 
        exit;
    }

    /* Reading the number of example labels from label file */
    ubyte0 = fgetc (fd);
    ubyte1 = fgetc (fd);
    ubyte2 = fgetc (fd);
    ubyte3 = fgetc (fd);
    tmp_n = (ubyte0 << 24) | (ubyte1 << 16) | (ubyte2 << 8) | ubyte3;
    if (do_print)
        printf ("Number of labels: %d\n", tmp_n);

    if (f_data->n != tmp_n)
    {
        printf ("Total number of label entries don't match the total \
                 number of images read.\n");

        printf ("Stopping run.\n");
	exit;
    }

    /* Allocating memory for image data */
    f_data->lbl = malloc (sizeof(unsigned char)*f_data->n);

    /* Reading label data */
    for (k = 0; k < f_data->n; k++)
    {
        f_data->lbl[k] = fgetc (fd);

        if (do_print)
            printf ("%d:%d ", k, f_data->lbl[k]);
    }

    if (do_print)
        printf ("\n%d labels (unsigned chars) read.\n", k);

    /* Closing label file */
    fclose (fd);
}

