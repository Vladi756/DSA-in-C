#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include "stopwatch.h"

/* New aggregate type which contains 3 variables:
      Array to contain list items
      Capacity - maximum number of items
      currentSize - actual number of items
*/

struct ArrayList{
    int *array;     // Even though no [], if used like an array, C will treat this variable like an array.
    int capacity;
    int currentSize;
};

// Function to insert item into the list
bool insertItem(struct ArrayList *list, int data, int index){
    if((index >= 0)&&(index <= list->currentSize) && (list->currentSize < list->capacity)) {
        int i = list->currentSize;
        while(i > index) {
            list->array[i] = list->array[i-1];
            i--;
        }
        list->array[index] = data;
        list->currentSize = list->currentSize + 1;
        return true;
    } else {
        return false;
    }
}

// Function to display the list.
void display(struct ArrayList *list){
    int i = 0;
    while(i < list->currentSize) {
        printf("Element %d: %d\n", i, list->array[i]);
        i++;
    }
}

//Function to remove item from the list.
int removeItem(struct ArrayList *list, int index){
    int removed = list->array[index];
    int i = index;
    while(i < list->currentSize - 1) {
        list->array[i] = list->array[i+1];
        i++;
    }
    list->currentSize = list->currentSize - 1;
    return removed;
}

//Function to get item from list
int getItem(struct ArrayList *list, int index){
    return list->array[index];
}

//Function to set item
int setItem(struct ArrayList *list, int data, int index){
    int old = list->array[index];
    list->array[index] = data;
    return old;
}

//Function to set size of list
void setSize(struct ArrayList *list, int s){
    list->currentSize = s;
}

//Functions using the stopwatch.h header file - to evaluate time complexity of functions
void randomAccessPerformanceDemo(struct ArrayList* list, int numberOfTests, int maxSize) {
    struct StopWatch* timer = malloc(sizeof(struct StopWatch));
    resetStopWatch(timer);

    int repetitions = 10000;

    printf("Random_access_demo (%d_random_accesses_for_each_list_size)\n", repetitions);
    printf("Size,Time Access\n");

    int stepSize = maxSize / numberOfTests;
    int i = 0;

    while (i < numberOfTests) {
        int listSize = maxSize - (i * stepSize);
        setSize(list,listSize);
        startStopWatch(timer);
        int r;

        for (r = 0; r < repetitions; r++) {
            getItem(list, (rand() / (double)(RAND_MAX + 1)) * list->currentSize);
        }
        stopStopWatch(timer);
        printf("%d ",list->currentSize);
        printStopWatchReport(timer);
        resetStopWatch(timer);
        i = i + 1;
    }
    free(timer);
}

void insertPerformanceDemo(struct ArrayList* list, int numberOfTests, int maxSize) {
    struct StopWatch* timer = malloc(sizeof(struct StopWatch));
    resetStopWatch(timer);
    int repetitions = 10000;

    printf("Insertion_demo (An_insert_at_position_zero_for_each_list_size,_repeated_%d_times_without_increasing_list_size)\n", repetitions);
    printf("Size,Time Insert\n");

    int stepSize = maxSize / numberOfTests;
    int i = 0;

    while (i < numberOfTests) {
        int listSize = (maxSize - (i * stepSize)) - 1;
        int r;
        for (r = 0; r < repetitions; r++) {
            setSize(list,listSize);
            startStopWatch(timer);
            insertItem(list, 999, 0);
            stopStopWatch(timer);
        }
        printf("%d ",list->currentSize);
        printStopWatchReport(timer);
        resetStopWatch(timer);
        i = i + 1;
    }
    free(timer);
}

void removePerformanceDemo(struct ArrayList* list, int numberOfTests, int maxSize) {
    struct StopWatch* timer = malloc(sizeof(struct StopWatch));
    resetStopWatch(timer);
    int repetitions = 10000;

    printf("Removal_demo (A_removal_from_position_zero_for_each_list_size,_repeated_%d_times_without_decreasing_list_size)\n", repetitions);
    printf("Size,Time Remove\n");

    int stepSize = maxSize / numberOfTests;
    int i = 0;

    while (i < numberOfTests) {
        int listSize = maxSize - (i * stepSize);
        int r;
        for (r = 0; r < repetitions; r++) {
            setSize(list,listSize);
            startStopWatch(timer);
            removeItem(list,0);
            stopStopWatch(timer);
        }
        printf("%d ",listSize);
        printStopWatchReport(timer);
        resetStopWatch(timer);
        i = i + 1;
    }
    free(timer);
}

// Main Function
int main(){

    srand(time(NULL));
    int capacity = 100000;
    int a[capacity];

    struct ArrayList list = {a, capacity, 0};

    int i = 0;
    while(i < 10){
        insertItem(&list, rand()%100, list.currentSize);    // Inserts a random number 0 - 99 into the beginning of list.
        i = i + 1;
    }
    display(&list); // Displays list.

    // Calling the function to make sure they work.
    printf("Item at index 2 = %d\n", getItem(&list, 2));
    printf("Item at index 200 (outside of array memory) = %d\n", getItem(&list, 200));

    printf("Inserting 999 at position 5\n");
    insertItem(&list, 999, 5);
    display(&list);

    printf("Deleting from position 3.\n");
    removeItem(&list, 3);
    display(&list);

    //Calling time complexity analysis functions.
    randomAccessPerformanceDemo(&list, 20, list.capacity);
    insertPerformanceDemo(&list, 20, list.capacity);
    removePerformanceDemo(&list, 20, list.capacity);

    return 0;
}
