#include "knn.h"

/* 
 * Initializes k_t (struct) array entries. This is needed to have a
 * point of comparison when adding the first K values to the list
 */
void
init (k_t *kk, int len)
{
    int z;

    for (z = 0; z < len; z++)
    {
        /* 
	 * Initializing the distance to a large value making sure
	 * the first K first image comparisons get added to kk
	 */
        kk[z].dst = 999999999;
	kk[z].lbl = 0;
	kk[z].c = 0; 
    }
}


/*
 * Evaluates the provided K list of (training) points to identify
 * the expected value of the test numerical digit.
 *
 * Note that this functions reuses the k_t (struct) type for
 * this work, particularly the added "c" component
 */
int
evaluate (k_t *kk)
{
    int z, tmp = 0;
    k_t x[10];

    /* Initializes all values of the local k_t array; one
     * for each numerical digit */
    x[0].lbl = 0; x[0].c = x[0].dst = 0;
    x[1].lbl = 1; x[1].c = x[1].dst = 0;
    x[2].lbl = 2; x[2].c = x[2].dst = 0;
    x[3].lbl = 3; x[3].c = x[3].dst = 0;
    x[4].lbl = 4; x[4].c = x[4].dst = 0;
    x[5].lbl = 5; x[5].c = x[5].dst = 0;
    x[6].lbl = 6; x[6].c = x[6].dst = 0;
    x[7].lbl = 7; x[7].c = x[7].dst = 0;
    x[8].lbl = 8; x[8].c = x[8].dst = 0;
    x[9].lbl = 9; x[9].c = x[9].dst = 0;

    /* Iterating through the captured K closest values */
    for (z = 0; z < KV; z++)
    {
        /* Based on each label/digit, increase count, add distances */
        switch (kk[z].lbl)
        { 
            case 0: ++x[0].c; x[0].dst += kk[z].dst; break;
            case 1: ++x[1].c; x[1].dst += kk[z].dst; break;
            case 2: ++x[2].c; x[2].dst += kk[z].dst; break;
            case 3: ++x[3].c; x[3].dst += kk[z].dst; break;
            case 4: ++x[4].c; x[4].dst += kk[z].dst; break;
            case 5: ++x[5].c; x[5].dst += kk[z].dst; break;
            case 6: ++x[6].c; x[6].dst += kk[z].dst; break;
            case 7: ++x[7].c; x[7].dst += kk[z].dst; break;
            case 8: ++x[8].c; x[8].dst += kk[z].dst; break;
            case 9: ++x[9].c; x[9].dst += kk[z].dst; break;
        }
    }

    /*
     * We are going to make use of two mechanisms to evaluate/identify
     * the value of the test entry. The first one (right below) is the
     * quickest and assumes there is a majority count of labels for a
     * single/expected value. This should work in most cases and if a
     * value is found no further work is required allowing to stay
     * away from loops... and approaching O(1)
     */
    if (x[0].c > x[1].c && x[0].c > x[2].c && x[0].c > x[3].c &&
        x[0].c > x[4].c && x[0].c > x[5].c && x[0].c > x[6].c &&
        x[0].c > x[7].c && x[0].c > x[8].c && x[0].c > x[9].c)
    {
        return 0;
    }
    else if (x[1].c > x[2].c && x[1].c > x[3].c && x[1].c > x[4].c &&
             x[1].c > x[5].c && x[1].c > x[6].c && x[1].c > x[7].c &&
             x[1].c > x[8].c && x[1].c > x[9].c && x[1].c > x[0].c)
    {
        return 1;
    }
    else if (x[2].c > x[3].c && x[2].c > x[4].c && x[2].c > x[5].c &&
             x[2].c > x[6].c && x[2].c > x[7].c && x[2].c > x[8].c &&
             x[2].c > x[9].c && x[2].c > x[0].c && x[2].c > x[1].c)
    {
        return 2;
    }
    else if (x[3].c > x[4].c && x[3].c > x[5].c && x[3].c > x[6].c &&
             x[3].c > x[7].c && x[3].c > x[8].c && x[3].c > x[9].c &&
             x[3].c > x[0].c && x[3].c > x[1].c && x[3].c > x[2].c)
    {
        return 3;
    }
    else if (x[4].c > x[5].c && x[4].c > x[6].c && x[4].c > x[7].c &&
             x[4].c > x[8].c && x[4].c > x[9].c && x[4].c > x[0].c &&
             x[4].c > x[1].c && x[4].c > x[2].c && x[4].c > x[3].c)
    {
        return 4;
    }
    else if (x[5].c > x[6].c && x[5].c > x[7].c && x[5].c > x[8].c &&
             x[5].c > x[9].c && x[5].c > x[0].c && x[5].c > x[1].c &&
             x[5].c > x[2].c && x[5].c > x[3].c && x[5].c > x[4].c)
    {
        return 5;
    }
    else if (x[6].c > x[7].c && x[6].c > x[8].c && x[6].c > x[9].c &&
             x[6].c > x[0].c && x[6].c > x[1].c && x[6].c > x[2].c &&
             x[6].c > x[3].c && x[6].c > x[4].c && x[6].c > x[5].c)
    {
        return 6;
    }
    else if (x[7].c > x[8].c && x[7].c > x[9].c && x[7].c > x[0].c &&
             x[7].c > x[1].c && x[7].c > x[2].c && x[7].c > x[3].c &&
             x[7].c > x[4].c && x[7].c > x[5].c && x[7].c > x[6].c)
    {
        return 7;
    }
    else if (x[8].c > x[9].c && x[8].c > x[0].c && x[8].c > x[1].c &&
             x[8].c > x[2].c && x[8].c > x[3].c && x[8].c > x[4].c &&
             x[8].c > x[5].c && x[8].c > x[6].c && x[8].c > x[7].c)
    {
        return 8;
    }
    else if (x[9].c > x[0].c && x[9].c > x[1].c && x[9].c > x[2].c &&
             x[9].c > x[3].c && x[9].c > x[4].c && x[9].c > x[5].c &&
             x[9].c > x[6].c && x[9].c > x[7].c && x[9].c > x[8].c)
    {
        return 9;
    }

    /*
     * Otherwise, if we need to continue, it might mean we got two or more
     * equal total number of possible solutions and therefore we need
     * to consider distances. We start this phase by sorting the added
     * distances in order to find the closest and the far appart ones.
     * Note that we are again utilizing our quick sorting function.
     * This is the reason why I decided to add the "c" variable to k_t.
     * So, I could make use qsortk() without any more changes.
     */
    qsortk (x, 0, 9); 

    /* Setting up tmp to a known value */
    tmp = -1;

    /* Now, we have the k_t array in increasing order with the
     * largest distance difference at the end. */
    for (z = 9; z > 0; z--)
    {
        /* Disregard zero entries */
        if (x[z].c == 0)
            continue;

	/* After sorting, we're assuming that digits with the same
	 * count will have also about the same distance from the
	 * target digit */
        if (x[z].c == x[z-1].c)
        {
            if (x[z].dst < x[z+1].dst)
            {
                tmp = x[z].lbl;
            }
            else
            {
                tmp = x[z+1].lbl;
            }
        }
    }

    /* If this last search didn't produce a prediction, pick
     * the closets training value */
    if (tmp == -1)
    {
       tmp = kk[0].lbl;
    }

    return tmp;
}
