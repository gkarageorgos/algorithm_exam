#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

#define k 10
#define n 100
#define MAX_VALUE 1000

/*Answer to question b: Sorting the k elements into array B.
 * Insertion of the sorted B into the sorted array A. O(klogk+n)*/

// Function to generate random arrays
void generateRandomArray(int size, int* array){
    for (int i = 0; i < size; i++) {
        // Generate a random integer in the range [-MAX_VALUE, MAX_VALUE]
        array[i] = rand() % (2 * MAX_VALUE + 1) - MAX_VALUE;
    }
}

// Function to print arrays
void printArray(int size, int* array) {
    for (int i = 0; i < size; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");
}

void merge(int* array, int l, int m, int r) {
    int leftSize = m - l + 1;
    int rightSize = r - m;

    int leftArray[leftSize];
    int rightArray[rightSize];

    // Copy data to temporary arrays leftArray and rightArray
    for (int i = 0; i < leftSize; i++) {
        leftArray[i] = array[l + i];
    }
    for (int i = 0; i < rightSize; i++) {
        rightArray[i] = array[m + 1 + i];
    }

    int i = 0, j = 0, index = l;

    // Merge the two arrays leftArray and rightArray into array
    while (i < leftSize && j < rightSize) {
        if (leftArray[i] < rightArray[j]) {
            array[index] = leftArray[i];
            i++;
        } else {
            array[index] = rightArray[j];
            j++;
        }
        index++;
    }

    // Copy any remaining elements from leftArray and rightArray to the array
    while (i < leftSize) {
        array[index] = leftArray[i];
        i++;
        index++;
    }

    while (j < rightSize) {
        array[index] = rightArray[j];
        j++;
        index++;
    }
}


void mergeSort(int *arr, int l, int r) {
    if (l < r) {
        int m = (l + r) / 2;
        // Sort first and second halves
        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);

        merge(arr, l, m, r);
    }
}

void insertion_k_elements_into_sorted_array(){
    int B[k], A[n];

    // Initialize the random number generator
    srand(time(0));

    // Create the random arrays
    generateRandomArray(k, B);
    generateRandomArray(n, A);

    // Print the new elements
    printf("The 10 new elements to be inserted into the array with 100 elements:\n");
    printArray(k, B);

    // Sorting the arrays
    mergeSort(B, 0, k - 1);
    mergeSort(A, 0, n - 1);

    // Print the sorted array
    printf("\nArray with 100 elements:\n");
    printArray(n, A);

    int C[k+n];
    int i;
    for (i = 0; i < k; i++){
        C[i] = B[i];
    }
    for (int j = i; j < k + n; j++){
        C[j] = A[j - i];
    }

    // After sorting the k elements in O(klogk) time, I merge the two arrays in O(n) time.
    merge(C, 0, k-1, k+n-1);

    printf("\nInserting the elements into the sorted array while maintaining the sorted order.\n");
    printArray(k+n, C);
}

/*Answer to question c: Checking if there are two elements in a sorted array
 * with a sum equal to an integer, in O(n) time. We have two pointers,
 * one pointing to the beginning of the array, named left, and one pointing to
 * the end of the array, named right. Adding the values of the array at positions left and right.
 * If the sum is smaller, the left pointer points to the next position,
 * and if it is larger, the right pointer points to the previous one.*/

void binarySearch(int* array, int* indexes, int target){
    int left = indexes[0];
    int right = indexes[1];
    int sum = array[left] + array[right];
    while (left < right){
        if (sum == target) {
            break;
        }else if (sum < target){
            left += 1;
        } else{
            right -= 1;
        }
        sum = array[left] + array[right];
    }
    indexes[0] = left;
    indexes[1] = right;
}

void findPairWithSum(){
    srand(time(0));
    int z = rand() % (2 * MAX_VALUE + 1) - MAX_VALUE;
    int arr[n];
    // Generate a random array of size 'n'
    generateRandomArray(n, arr);
    // Sort the random array 'arr' using merge sort algorithm
    mergeSort(arr, 0, n-1);
    printf("We are searching for two elements of a sorted array with a sum equal to z=%d:\n", z);
    printf("\nThe sorted array:\n");
    printArray(n, arr);
    int indexes[2] = {0, n - 1};
    binarySearch(arr, indexes, z);
    int left = indexes[0] + 1;
    int right = indexes[1] + 1;
    if (left == right){
        printf("\nThere are no two elements in the array with a sum equal to %d.\n", z);
    } else{
        printf("\nThe value at positions %d and %d are equal to the %d and %d respectively, "
               "and their sum is equal to %d.\n", left, right, arr[left-1], arr[right-1], z);
    }
}

/*Answer to question d: We sort the array in O(nlogn) time. We have two pointers,
 * one pointing to the non-negatives, and one to the positives. Let's assume we have k negative numbers.
 * With the help of question c. For each negative number,
 * checking if there are two elements in the sorted array of non-negative numbers
 * with a sum equal to that negative number, in O(kn) time. Also, for each positive number,
 * checking if there are two elements in the sorted array of non-positive numbers
 * with a sum equal to that positive number, in O((n-k)n) time. The total time is indeed
 * nlogn + kn + (n-k)n = nlogn +(k + n - k)n = nlogn +n^2,  nlogn < n^2 for each n.
 * Therefore O(n^2)*/

void findIndexes(int *array, int size, int* indexes){
    int i;
    for (i = 0; i < size; i++){
        if (array[i] >= 0){
            // first non-negative
            break;
        }
    }
    indexes[0] = i;
    int j;
    for (j = i; j < size; j++){
        if (array[j] > 0){
            // first positive
            break;
        }
    }
    indexes[1] = j;
}

void find_triplets_with_zero_sum(){
    srand(time(0));
    int arr[n];
    // Generate a random array of size 'n'
    generateRandomArray(n, arr);
    // Sort the random array 'arr' using merge sort algorithm
    mergeSort(arr, 0, n-1);
    printf("\nThe sorted array:\n");
    printArray(n, arr);

    int indexes[2];
    findIndexes(arr, n, indexes);

    int firstNonNegative = indexes[0];
    int firstPositive = indexes[1];

    if (firstPositive - firstNonNegative >= 3){
        printf("\nThere are three zeros in the array\n");
        return;
    }

    if (firstPositive == n || firstNonNegative == 0){
        printf("\nThere are no three elements in the array with a sum equal to 0.\n");
        return;
    }

    int nonNegativeBorders[2] = {firstNonNegative, n - 1};
    for (int i = 0; i < firstNonNegative; i++){
        int target = -arr[i];
        binarySearch(arr, nonNegativeBorders, target);
        if (nonNegativeBorders[0] == nonNegativeBorders[1]){
            nonNegativeBorders[0] = firstNonNegative;
            nonNegativeBorders[1] = n - 1;
        } else{
            printf("\nThe values %d, %d and %d into array with sum equal to 0",
                   arr[i], arr[nonNegativeBorders[0]], arr[nonNegativeBorders[1]]);
            return;
        }
    }

    int nonPositiveBorders[2] = {0, firstPositive - 1};
    for (int i = firstPositive; i < n; i++){
        int target = -arr[i];
        binarySearch(arr, nonPositiveBorders, target);
        if (nonPositiveBorders[0] == nonPositiveBorders[1]){
            nonPositiveBorders[0] = 0;
            nonPositiveBorders[1] = firstPositive - 1;
        } else{
            printf("\nThe values %d, %d and %d into array with sum equal to 0",
                   arr[i], arr[nonPositiveBorders[0]], arr[nonPositiveBorders[1]]);
            return;
        }
    }

    printf("\nThere are no three elements in the array with a sum equal to 0.\n");

}

int main( )
{
    // Answer to question b
    //insertion_k_elements_into_sorted_array();

    // Answer to question c
    //findPairWithSum();

    // Answer to question d
    find_triplets_with_zero_sum();

    return 0;
}
