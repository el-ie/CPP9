#include <stdio.h>

int SIZE = 6;

void CopyArray(int A[SIZE], int iBegin, int iEnd, int B[SIZE])
{
    for (int k = iBegin; k < iEnd; k++)
        B[k] = A[k];
}

//  Left source half is A[ iBegin:iMiddle-1].
// Right source half is A[iMiddle:iEnd-1   ].
// Result is            B[ iBegin:iEnd-1   ].
void TopDownMerge(int B[SIZE], int iBegin, int iMiddle, int iEnd, int A[SIZE])
{
    int i = iBegin;
    int j = iMiddle;
 
    // While there are elements in the left or right runs...
    for (int k = iBegin; k < iEnd; k++) {
        // If left run head exists and is <= existing right run head.
        if (i < iMiddle && (j >= iEnd || A[i] <= A[j])) {
            B[k] = A[i];
            i++;
        } else {
            B[k] = A[j];
            j++;
        }
    }
}

// Split A[SIZE] into 2 runs, sort both runs into B[SIZE], merge both runs from B[SIZE] to A[SIZE]
// iBegin is inclusive; iEnd is exclusive (A[iEnd] is not in the set).
void TopDownSplitMerge(int B[SIZE], int iBegin, int iEnd, int A[SIZE])
{
    if (iEnd - iBegin <= 1)                     // if run size == 1
        return;                                 //   consider it sorted
    		// split the run longer than 1 item into halves
    int iMiddle = (iEnd + iBegin) / 2;              // iMiddle = mid point
    		// recursively sort both runs from array A[SIZE] into B[SIZE]
    TopDownSplitMerge(A, iBegin,  iMiddle, B);  // sort the left  run
    TopDownSplitMerge(A, iMiddle,    iEnd, B);  // sort the right run
    		// merge the resulting runs from array B[SIZE] into A[SIZE]
    TopDownMerge(B, iBegin, iMiddle, iEnd, A);
}

int	main(void)
{
	int	A[] = {2,8,9,6,5,7};
	int	B[SIZE];

    	CopyArray(A, 0, SIZE, B);           // one time copy of A[SIZE] to B[SIZE]

    	TopDownSplitMerge(A, 0, SIZE, B);   // sort data from B[SIZE] into A[SIZE]

	for (int i = 0; i < SIZE; i++)
		printf("%d - ", A[i]);

	return 0;
}
