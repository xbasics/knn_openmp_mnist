#include "knn.h"

/*
 * There are lots of implementations for Quick Sort in books
 * and throughout the Internet.  My original implementation,
 * although it worked fine, made use of a couple of function.
 * Searching around a simpler (one function) implementation,
 * found a simpler one as provided by Piyush Chugh at
 * https://www.codingbot.net/2013/01/quick-sort-algorithm-and-c-code.html
 *
 * This quick sort implementation was cleaned, verified,
 * and modified to make use of structs for this project.
 */

void qsortk (k_t *kk, int left, int right)
{
    int i, j, pivot;
    k_t tmp;

    if (left < right)
    {
        /* Selecting pivot value (left entry) */
        pivot = left;
        i = left;
        j = right;

	/* Iterating through k_t.dst array within i,j block limits */
        while (i < j)
        {
            /* Identifying left position > pivot */
            while ((kk[i].dst <= kk[pivot].dst) && (i < right))
                i++;

            /* Identifying right position < pivot */
            while (kk[j].dst > kk[pivot].dst)
                j--;

            /* Switch left, right values if it's not same position, i ngt j */
            if (i < j)
            { 
                tmp = kk[i];
                kk[i] = kk[j];
                kk[j] = tmp;
            }
        }

	/* Moving original pivot value to found position j */
        tmp = kk[pivot];
        kk[pivot] = kk[j];
        kk[j] = tmp;

	/* Repeat same process for left, right sides from pivot */
        qsortk (kk, left, j-1);
        qsortk (kk, j+1, right);
    }
}

