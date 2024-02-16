#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <sys/time.h>  

#define BILLION  1000000000.0



void Trocar(int* a, int* b)
{
    int t = *a;
    *a = *b;
    *b = t;
}
 
// Partition the array using the last element as the pivot
int Particionar(int arr[], int low, int high)
{
    // Choosing the pivot
    int pivot = arr[high];
 
    // Index of smaller element and indicates
    // the right position of pivot found so far
    int i = (low - 1);
 
    for (int j = low; j <= high - 1; j++) {
 
        // If current element is smaller than the pivot
        if (arr[j] < pivot) {
 
            // Increment index of smaller element
            i++;
            Trocar(&arr[i], &arr[j]);
        }
    }
    Trocar(&arr[i + 1], &arr[high]);
    return (i + 1);
}
 
// The main function that implements QuickSort
// arr[] --> Array to be sorted,
// low --> Starting index,
// high --> Ending index
void QuickSort(int arr[], int low, int high)
{
    if (low < high) {
 
        // pi is partitioning index, arr[p]
        // is now at right place
        int pi = Particionar(arr, low, high);
 
        // Separately sort elements before
        // partition and after partition
        QuickSort(arr, low, pi - 1);
        QuickSort(arr, pi + 1, high);
    }
}

void Juntar(int arr[], int l, int m, int r)
{
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;
 
    // Create temp arrays
    int L[n1], R[n2];
 
    // Copy data to temp arrays L[] and R[]
    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];
 
    // Merge the temp arrays back into arr[l..r
    i = 0;
    j = 0;
    k = l;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        }
        else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }
 
    // Copy the remaining elements of L[],
    // if there are any
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }
 
    // Copy the remaining elements of R[],
    // if there are any
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}
 
// l is for left index and r is right index of the
// sub-array of arr to be sorted
void MergeSort(int arr[], int l, int r)
{
    if (l < r) {
        int m = l + (r - l) / 2;
 
        // Sort first and second halves
        MergeSort(arr, l, m);
        MergeSort(arr, m + 1, r);
 
        Juntar(arr, l, m, r);
    }
}
// To heapify a subtree rooted with node i
// which is an index in arr[].
// n is size of heap
void Heapificar(int arr[], int N, int i)
{
    // Find largest among root,
    // left child and right child

    // Initialize largest as root
    int largest = i;

    // left = 2*i + 1
    int left = 2 * i + 1;

    // right = 2*i + 2
    int right = 2 * i + 2;

    // If left child is larger than root
    if (left < N && arr[left] > arr[largest])

        largest = left;

    // If right child is larger than largest
    // so far
    if (right < N && arr[right] > arr[largest])

        largest = right;

    // Swap and continue heapifying
    // if root is not largest
    // If largest is not root
    if (largest != i) {

        Trocar(&arr[i], &arr[largest]);

        // Recursively heapify the affected
        // sub-tree
        Heapificar(arr, N, largest);
    }
}

// Main function to do heap sort
void HeapSort(int arr[], int N)
{

    // Build max heap
    for (int i = N / 2 - 1; i >= 0; i--)

        Heapificar(arr, N, i);

    // Heap sort
    for (int i = N - 1; i >= 0; i--) {

        Trocar(&arr[0], &arr[i]);

        // Heapify root element
        // to get highest element at
        // root again
        Heapificar(arr, i, 0);
    }
}

// An optimized version of Bubble Sort
void BubbleSort(int arr[], int n)
{
    int i, j;
    bool swapped;
    for (i = 0; i < n - 1; i++) {
        swapped = false;
        for (j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                Trocar(&arr[j], &arr[j + 1]);
                swapped = true;
            }
        }
 
        // If no two elements were swapped by inner loop,
        // then break
        if (swapped == false)
            break;
    }
}


void SelectionSort(int arr[], int n)
{
    int i, j, min_idx;
 
    // One by one move boundary of unsorted subarray
    for (i = 0; i < n-1; i++)
    {
        // Find the minimum element in unsorted array
        min_idx = i;
        for (j = i+1; j < n; j++)
          if (arr[j] < arr[min_idx])
            min_idx = j;
 
        // Swap the found minimum element with the first element
           if(min_idx != i)
            Trocar(&arr[min_idx], &arr[i]);
    }
}

void ImprimeVetor (int* vet, int n)
{
    int i; 
    for (i=0; i<n; i++)
    {
        printf ("%d ", vet[i]);
    }
}

int* GeraVetorRandom (int n)
{
    int* vetRandom;
    int i;
    vetRandom = (int*)malloc(n * sizeof(int));
    if (vetRandom == NULL) {
        printf("Memoria nao alocada.\n");
        exit(0);
    }
    else {
        for (i = 0; i < n; ++i) {
            vetRandom[i] = rand()%10000;
        }
    return vetRandom;
    }
}

void Inverter(int arr[], int start, int end)
{
    int temp;
    while (start < end)
    {
        temp = arr[start];   
        arr[start] = arr[end];
        arr[end] = temp;
        start++;
        end--;
    }   
}     

int main (){


    srand (time(NULL));
    int n = 1000; //500000+rand()%900;
    double time_spent = 0.0;
    long seconds, micros;

    struct timeval start, end;
 	
	 
    gettimeofday(&start, NULL);//começa a contagem do tempo
    

    int* vetRandom = GeraVetorRandom(n); // gera um vetor randomico
	gettimeofday(&end, NULL);//termina a contagem do tempo

	
	seconds = (end.tv_sec - start.tv_sec);
    micros = ((seconds * 1000000) + end.tv_usec) - (start.tv_usec);
 	
    printf("Tempo gasto para gerar o vetor: %d segundos and %d micros\n", seconds, micros);

    
    printf("\n\nMerge Sort\n\n");
	gettimeofday(&start, NULL);
	
    vetRandom = GeraVetorRandom(n);
    MergeSort(vetRandom, 0, n-1);
   
	gettimeofday(&end, NULL);
	seconds = (end.tv_sec - start.tv_sec);
	micros = ((seconds * 1000000) + end.tv_usec) - (start.tv_usec);
	printf("Tempo gasto %d segundos and %d micros\n", seconds, micros);
	
	gettimeofday(&start, NULL);
    vetRandom = GeraVetorRandom(n);
  	
    MergeSort(vetRandom, 0, n-1);
    Inverter(vetRandom, 0, n-1);
   
	gettimeofday(&end, NULL);
	seconds = (end.tv_sec - start.tv_sec);
	micros = ((seconds * 1000000) + end.tv_usec) - (start.tv_usec);
	printf("Tempo gasto %d segundos and %d micros\n", seconds, micros);
	
    printf("\n\nBubble Sort\n\n");
    
    vetRandom = GeraVetorRandom(n);
    gettimeofday(&start, NULL);
    
    BubbleSort(vetRandom, n);
    
    gettimeofday(&end, NULL);
    seconds = (end.tv_sec - start.tv_sec);
	micros = ((seconds * 1000000) + end.tv_usec) - (start.tv_usec);
	printf("Tempo gasto %d segundos and %d micros\n", seconds, micros);
	vetRandom = GeraVetorRandom(n);
	gettimeofday(&start, NULL);
    
    BubbleSort(vetRandom, n);
    Inverter(vetRandom, 0, n-1);
    
    gettimeofday(&end, NULL);
    seconds = (end.tv_sec - start.tv_sec);
	micros = ((seconds * 1000000) + end.tv_usec) - (start.tv_usec);
	printf("Tempo gasto %d segundos and %d micros\n", seconds, micros);
	
	printf("\n\nSelection Sort\n\n");
    
    int* vetRandomSelection = GeraVetorRandom(n);
    gettimeofday(&start, NULL);
    
    SelectionSort(vetRandomSelection, n);
    
    gettimeofday(&end, NULL);
    seconds = (end.tv_sec - start.tv_sec);
	micros = ((seconds * 1000000) + end.tv_usec) - (start.tv_usec);
	printf("Tempo gasto %d segundos and %d micros\n", seconds, micros);
	
	vetRandomSelection = GeraVetorRandom(n);
	
	gettimeofday(&start, NULL);
    
    SelectionSort(vetRandomSelection, n);
    Inverter(vetRandomSelection, 0, n-1);
    
    gettimeofday(&end, NULL);
    seconds = (end.tv_sec - start.tv_sec);
	micros = ((seconds * 1000000) + end.tv_usec) - (start.tv_usec);
	printf("Tempo gasto %d segundos and %d micros\n", seconds, micros);
	
	
	printf("\n\nQuickSort\n\n");


int* vetRandomQuick = GeraVetorRandom(n);
    gettimeofday(&start, NULL);
    
    QuickSort(vetRandomQuick, 0, n);
    
    gettimeofday(&end, NULL); 
    seconds = (end.tv_sec - start.tv_sec);
	micros = ((seconds * 1000000) + end.tv_usec) - (start.tv_usec);
	printf("Tempo gasto %d segundos and %d micros\n", seconds, micros);
	
	vetRandomQuick = GeraVetorRandom(n);
	
	gettimeofday(&start, NULL);
    
    QuickSort(vetRandomQuick, 0, n);
    Inverter(vetRandomQuick, 0, n-1);
    
    gettimeofday(&end, NULL);
    seconds = (end.tv_sec - start.tv_sec);
	micros = ((seconds * 1000000) + end.tv_usec) - (start.tv_usec);
	printf("Tempo gasto %d segundos and %d micros\n", seconds, micros);
	
	
	
	
	printf("\n\nHeapSort\n\n");


int* vetRandomHeap = GeraVetorRandom(n);
    gettimeofday(&start, NULL);
    
    HeapSort(vetRandomHeap, n);
    
    gettimeofday(&end, NULL);
    seconds = (end.tv_sec - start.tv_sec);
	micros = ((seconds * 1000000) + end.tv_usec) - (start.tv_usec);
	printf("Tempo gasto %d segundos and %d micros\n", seconds, micros);
	
	vetRandomHeap = GeraVetorRandom(n);
	
	gettimeofday(&start, NULL);
    
    HeapSort(vetRandomHeap, n);
    Inverter(vetRandomHeap, 0, n-1);
    
    gettimeofday(&end, NULL);
    seconds = (end.tv_sec - start.tv_sec);
	micros = ((seconds * 1000000) + end.tv_usec) - (start.tv_usec);
	printf("Tempo gasto %d segundos and %d micros\n", seconds, micros);
	
    

}
