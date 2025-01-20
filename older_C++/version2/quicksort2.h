#ifndef QUICKSORT_H
#define QUICKSORT_H

// QuickSortHelper class to sort event IDs using QuickSort algorithm
class QuickSortHelper {
public:
    static void sort(int ids[], int low, int high);

private:
    static int partition(int ids[], int low, int high);
};

#endif // QUICKSORT_H
