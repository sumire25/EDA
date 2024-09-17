#include <iostream>
#include <chrono>
using namespace std;

void bubbleSort(float* arr, int n){
    int i, j;
    for(i=n-1; i>0; i--){
        for(j=0; j<i; j++){
            if(arr[j] > arr[j+1]){
                swap(arr[j], arr[j+1]);
            }
        }
    }
}

void insertionSort(float* arr, int n){
    int i, j;
    float aux;
    for(i=1; i<n; i++){
        aux = arr[i];
        j = i - 1;
        while(aux < arr[j] && j >= 0){
            arr[j+1] = arr[j];
            j--;
        }
        arr[j+1] = aux;
    }
}

void selectionSort(float* arr, int n){
    int i, j, min;
    for(i=0; i<n-1; i++){
        min = i;
        for(j=i+1; j<n; j++){
            if(arr[j] < arr[min]){
                min = j;
            }
        }
        if(min != i){
            swap(arr[i], arr[min]);
        }
    }
}

void merge(float* arr, int sta, int mid, int end){
}

void mergeSort(float* arr, int sta, int end){
    if(sta >= end)
        return;
    int mid = (sta + end) / 2;
    mergeSort(arr, sta, mid);
    mergeSort(arr, mid+1, end);
    merge(arr, sta, mid, end);
}

int main(){
    int n=0;
    float* arr = new float[1'000'000];
    while(cin >> arr[n]){
        n++;
    }

    auto start = std::chrono::high_resolution_clock::now();
    selectionSort(arr, n);
    auto end = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double, std::milli> duration = end - start;
    std::cerr << "Execution time: " << duration.count() << " ms" << std::endl;

    for(int i=0; i<n; i++){
        cout << arr[i] << endl;
    }

	return 0;
}
