#include <stdio.h>

int search(int arr[], int n, int x)         // Sequential Seach Algorithm.
{
    int i;
    for (i = 0; i < n; i++)                 // for loop checks every array element.
        if (arr[i] == x)                    // if statement determines whether the target is found or not
            return i;                       // returns position of target.
    return -1;
}

int main(void)                              // Main Function
{
    int arr[] = {4, 6, 8, 10, 50};
    int n = sizeof(arr);                    // Initalizing all the variables.
    int x;

    printf("Please input a number: ");      // Prompting user for Target.
    scanf("%d", &x);

    int result = search(arr, n, x);
    (result == -1)
        ? printf("Element is not present in array")              // In case the target cannot be found.
        : printf("Element is present at index %d.", result);     // If case target is found.
    return 0;
}
