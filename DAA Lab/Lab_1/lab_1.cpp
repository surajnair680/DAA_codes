#include <iostream>
#include <chrono>
using namespace std;

// Merge sort
void merge(int input[], int si, int mid, int ei)
{
    int i = si;
    int j = mid + 1;
    int k = si;
    int arr[ei + 1];

    while (i <= mid && j <= ei)
    {
        if (input[i] <= input[j])
        {
            arr[k] = input[i];
            i++;
        }
        else
        {
            arr[k] = input[j];
            j++;
        }

        k++;
    }

    if (i > mid) // if first half is exhausted
    {
        while (j <= ei) // transfer leftover elements of second half
        {
            arr[k] = input[j];
            j++;
            k++;
        }
    }
    else // if second half is exhausted
    {
        while (i <= mid) // transfer leftover elements of first half
        {
            arr[k] = input[i];
            i++;
            k++;
        }
    }

    for (int i = si; i <= ei; i++)
    {
        input[i] = arr[i];
    }
}

void Msort(int *input, int si, int ei)
{
    if (si >= ei)
        return; // if 0 or 1 elements
    int mid = (si + ei) / 2;
    Msort(input, si, mid);
    Msort(input, mid + 1, ei);
    merge(input, si, mid, ei); // function to merge two sorted arrays
}

void mergeSort(int input[], int size)
{

    Msort(input, 0, size - 1);
}

// Quick sort
int partition(int input[], int si, int ei)
{
    int c = 0;
    for (int i = si + 1; i <= ei; i++)
    {
        if (input[si] >= input[i])
        {
            c++;
        }
    }

    swap(input[si], input[si + c]);

    int i = si;
    int j = ei;
    while (i < si + c && j > si + c)
    {
        while (input[i] <= input[si + c])
        {
            i++;
        }

        while (input[j] > input[si + c])
        {
            j--;
        }

        if (i < si + c && j > si + c)
        {
            swap(input[i], input[j]);
            i++;
            j--;
        }
    }

    return si + c;
}

void qs(int input[], int si, int ei)
{
    if (si >= ei)
        return;
    int c = partition(input, si, ei);
    qs(input, si, c - 1);
    qs(input, c + 1, ei);
}

void quickSort(int input[], int size)
{

    qs(input, 0, size - 1);
}

// heap sort
void heapify(int arr[], int N, int i)
{

    // Initialize largest as root
    int largest = i;

    // left = 2*i + 1
    int l = 2 * i + 1;

    // right = 2*i + 2
    int r = 2 * i + 2;

    // If left child is larger than root
    if (l < N && arr[l] > arr[largest])
        largest = l;

    // If right child is larger than largest
    // so far
    if (r < N && arr[r] > arr[largest])
        largest = r;

    // If largest is not root
    if (largest != i)
    {
        swap(arr[i], arr[largest]);

        // Recursively heapify the affected
        // sub-tree
        heapify(arr, N, largest);
    }
}

// Main function to do heap sort
void heapSort(int arr[], int N)
{

    // Build heap (rearrange array)
    for (int i = N / 2 - 1; i >= 0; i--)
        heapify(arr, N, i);

    // One by one extract an element
    // from heap
    for (int i = N - 1; i > 0; i--)
    {

        // Move current root to end
        swap(arr[0], arr[i]);

        // call max heapify on the reduced heap
        heapify(arr, i, 0);
    }
}

void print(int *arr, int size)
{
    for (int i = 0; i < size; i++)
    {
        cout << arr[i] << endl;
    }

    cout << endl;
}

int main()
{
    // srand(time(NULL));
    // srand(0);

    int input[10000];

    for (int i = 0; i < 10000; i++)
    {
        input[i] = rand();
    }

    cout << "size "
         << "Time consumed (in milliseconds)" << endl
         << endl;

    int size = 50;
    while (size <= 10000)
    {
        int arrMerge[size];
        int arrQuick[size];
        int arrHeap[size];
        for (int i = 0; i < size; i++)
        {
            arrMerge[i] = input[i];
            arrQuick[i] = input[i];
            arrHeap[i] = input[i];
        }

        auto begin = chrono::high_resolution_clock::now();
        mergeSort(arrMerge, size);

        auto end = chrono::high_resolution_clock::now();
        auto elapsed = chrono::duration_cast<chrono::nanoseconds>(end - begin);
        cout << size << " ";
        printf("%.10f", elapsed.count() * 1e-3);

        cout << " ";

        begin = chrono::high_resolution_clock::now();
        quickSort(arrQuick, size);
        end = chrono::high_resolution_clock::now();
        elapsed = chrono::duration_cast<chrono::nanoseconds>(end - begin);
        printf("%.10f", elapsed.count() * 1e-3);

        cout << " ";

        begin = chrono::high_resolution_clock::now();
        heapSort(arrHeap, size);
        end = chrono::high_resolution_clock::now();
        elapsed = chrono::duration_cast<chrono::nanoseconds>(end - begin);
        printf("%.10f", elapsed.count() * 1e-3);
        cout << endl;

        size = size + 50;
    }

    return 0;
}
