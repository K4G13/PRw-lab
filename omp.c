#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <omp.h>
 
bool checkSum(int sumLeft[], int k)
{
    bool r = true;
    for (int i = 0; i < k; i++)
    {
        if (sumLeft[i] != 0) {
            r = false;
        }
    }
 
    return r;
}
 
bool subsetSum(int S[], int n, int sumLeft[], int A[], int k)
{
    if (checkSum(sumLeft, k)) {
        return true;
    }
 
    if (n < 0) {
        return false;
    }
 
    bool result = false;
 
    int a;
    #pragma omp parallel for private(a)
    for (int i = 0; i < k; i++)
    {
        if (!result && (sumLeft[i] - S[n]) >= 0)
        {
            a = i + 1;
            sumLeft[i] = sumLeft[i] - S[n];
            result = subsetSum(S, n - 1, sumLeft, A, k);
            sumLeft[i] = sumLeft[i] + S[n];
            A[n] = a;
        }
    }
 
    return result;
}
 
void partition(int S[], int n, int k)
{
    if (n < k)
    {
        printf("k-partition of set S is not possible");
        return;
    }
 
    int sum = 0;
    for (int i = 0; i < n; i++) {
        sum += S[i];
    }
 
    int A[n], sumLeft[k];
 
    for (int i = 0; i < k; i++) {
        sumLeft[i] = sum / k;
    }
 
    bool result = !(sum % k) && subsetSum(S, n - 1, sumLeft, A, k);
 
    // if (!result)
    // {
    //     printf("k-partition of set S is not possible");
    //     return;
    // }
 
    // for (int i = 0; i < k; i++)
    // {
    //     printf("Partition %d is ", i);
    //     for (int j = 0; j < n; j++)
    //     {
    //         if (A[j] == i + 1) {
    //             printf("%d ", S[j]);
    //         }
    //     }
    //     printf("\n");
    // }
}
 
int main(int argc, char* argv[])
{
    //int S[] = { 7, 3, 5, 12, 2, 1, 5, 3, 8, 4, 6, 4 };
    // int n = sizeof(S) / sizeof(S[0]);
    // int k = 2;
 
    /*         k S[        . . .        ]
        Input: 3 7 3 5 12 2 1 5 3 8 4 6 4
 
        Output: Partition 0 is 2 1 3 4 6 4 
                Partition 1 is 7 5 8
                Partition 2 is 3 5 12
    */
 
    int S[argc];
    for (int i = 2; i < argc; i++)
    {
        S[i-2] = atoi(argv[i]);
    }
    int n = argc - 2;
    int k = atoi(argv[1]);
 
    omp_set_num_threads(k); // Liczba wątków = k
 
    partition(S, n, k);
 
    return 0;
}