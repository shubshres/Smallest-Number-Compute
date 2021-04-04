//Goals:
//1.Understanding of radix and counting sorts.
//2.Understanding of selection.
//Description:
/*Write a C program to compute the kth smallest 
        number in a sequence of nintegers in the range
         0...999,999,999.  The input will consist of:
            a. n and k.  1 ≤ k ≤ n ≤10,000,000
            b. n integers in the indicated range, one per line.  
               Duplicate inputs are possible.
        */

//Includes
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <stdbool.h>

void readInput(int *n, int *k, int *kInitial, int **inputTable, int **digitTable)
{
    //reading in the initial values
    scanf("%d %d", n, k);

    //variable that holds the initial k value
    *kInitial = *k;

    //dynamically allocated arrays
    *inputTable = (int *)malloc((*n) * sizeof(int));
    *digitTable = (int *)malloc((*n) * sizeof(int));

    //filling up input array.
    int i;
    for (i = 0; i < *n; i++)
    {
        scanf("%d", *inputTable + i);
    }
}

int isolateDigit(int passNum, int position)
{
    //performing mathematical operations to prepare for sort
    int newNum = passNum;
    int factor = (1000000000) / (pow(10, position));
    newNum = (newNum % factor);

    //checking if dividing by 0
    if ((factor / 10) != 0)
    {
        newNum = (newNum) / (factor / 10);
    }

    //returns new calculated num
    return newNum;
}

void countingSort(int *inputTable, int *countTable, int *slot, int *n, int *k, int *digitTable, int *position)
{
    //phase 1: clear countTable
    int i;
    for (i = 0; i < 10; i++)
    {
        countTable[i] = 0;
    }

    //phase 2: pass in input table
    for (i = 0; i < *n; i++)
    {
        countTable[isolateDigit(inputTable[i], *position)] += 1;
    }

    //phase 3: finding first slot
    //initial starting value set to 0
    slot[0] = 0;

    //loops through the slot table and adds teh new values
    for (i = 1; i < 10; i++)
    {
        slot[i] = slot[i - 1] + countTable[i - 1];
    }

    //printing out position and n
    printf("position %d n %d \n", (9 - *position), *n);

    //processing
    int keep = 0;
    int nInitial = 0;
    for (i = 0; i < 10; i++)
    {
        if ((slot[i] < *k) && (*k <= slot[i + 1]))
        {
            nInitial = *n;
            keep = i;
            *k = *k - slot[i];
            *n = slot[i + 1] - slot[i];
        }
    }

    //Phase 4: copy to output array
    int l = 0;
    for (i = 0; i < nInitial; i++)
    {
        if (isolateDigit(inputTable[i], *position) == keep)
        {
            digitTable[l++] = inputTable[i];
        }
    }

    //overwriting the input array
    for (i = 0; i < *n; i++)
    {
        inputTable[i] = digitTable[i];
    }

    //increasing digit position
    *position = (*position + 1);
}

int main(void)
{
    //initialize variables
    int n;        //size of input set
    int k;        //target value
    int kInitial; //holds initial k value
    int position = 0;
    int countTable[10];
    int slot[10];
    int *inputTable; //input set
    int *digitTable; //table with the digits from columns

    //calling readinput function
    readInput(&n, &k, &kInitial, &inputTable, &digitTable);

    //counting sort
    while ((position < 9) && (n > 1))
    {
        countingSort(inputTable, countTable, slot, &n, &k, digitTable, &position);
    }

    //printing out final position and the final bits of output
    printf("position %d n %d \n", (9 - position), n);
    printf("MSD 10 radix: The value with rank %d is %d \n", kInitial, digitTable[k]);

    //freeing memory
    free(digitTable);
    free(inputTable);

    return 0;
}
