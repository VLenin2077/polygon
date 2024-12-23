#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <cassert>
#include <chrono>
using namespace std;

vector<int> open_file(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Ошибка открытия файла!" << endl;
        return {};
    }

    vector<int> v{}; //n * 4 байт
    int num; // + 4 байт
    while (file >> num) { //O(n)
        v.push_back(num);
    }
    file.close();
    return v;
}

void insertionSort(vector<int>& arr, int left, int right) { //сортировка вставками фрагментов списка
    for (int i = left + 1; i <= right; i++) { //O(n)
        int temp = arr[i]; // + 4 байт
        int j = i - 1; // + 4 байт
        while (j >= left && arr[j] > temp) { //O(n)
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = temp;
    }
}
//O(n^2)
void merge(vector<int>& arr, int l, int m, int r) { //сортировка слиянием
    int len1 = m - l + 1, len2 = r - m; // + 8 байт
    vector<int> left(len1); //n * 4 байт
    vector<int> right(len2); //n * 4 байт
    for (int i = 0; i < len1; i++) //O(n)
        left[i] = arr[l + i];
    for (int i = 0; i < len2; i++) //O(n)
        right[i] = arr[m + 1 + i];

    int i = 0; // + 4 байт
    int j = 0; // + 4 байт
    int k = l; // + 4 байт

    while (i < len1 && j < len2) { //O(n)
        if (left[i] <= right[j]) {
            arr[k] = left[i];
            i++;
        }
        else {
            arr[k] = right[j];
            j++;
        }
        k++;
    }
    while (i < len1) { //O(n)
        arr[k] = left[i];
        k++;
        i++;
    }
    while (j < len2) { //O(n)
        arr[k] = right[j];
        k++;
        j++;
    }
}
//O(5n) = O(n)
vector<int> timSort(vector<int> &arr) {
    const int RUN = 32; // + 4 байт
    int n = arr.size(); // + 4 байт
    for (int i = 0; i < n; i += RUN) //O(n)
        insertionSort(arr, i, min((i + RUN - 1), (n - 1))); 
    for (int size = RUN; size < n; size = 2 * size) { //O(n)
        for (int left = 0; left < n; left += 2 * size) { //O(n)
            int mid = left + size - 1; // + 4 байт
            int right = min((left + 2 * size - 1), (n - 1)); // + 4 байт
            if (mid < right)
                merge(arr, left, mid, right);
        }
    }
    return arr;
}
//O(nlogn)   n*12 + 44 байт

vector<int> open_for_lines(string filename, int lim){
    fstream file;
    file.open(filename); 
    vector<int> v{}; 
    int num;
    int ct = 0; 
    while (file >> num && ct < lim){  
            v.push_back(num);
            ct++; 
    }
    file.close();
    return v;
}

void lin_graph(){
    for (int i = 1000; i < 1000000; i+=1000){
        vector<int> arr = open_for_lines("numbers.tsv", i);
        std::chrono::high_resolution_clock::time_point start = std::chrono::high_resolution_clock::now();
        vector<int> res = timSort(arr);
        std::chrono::high_resolution_clock::time_point end = std::chrono::high_resolution_clock::now(); //конец подсчета времени
        std::chrono::duration<double> duration = end - start;
        cout << i << ' ' << duration.count() << '\n';
    }
}


void box(){
    vector<int> nums = open_file("box1e4.tsv");
    for (int i = 1; i <= 50; i++){
        std::chrono::high_resolution_clock::time_point start = std::chrono::high_resolution_clock::now();
        timSort(nums);
        std::chrono::high_resolution_clock::time_point end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> duration = end - start;
        cout << duration.count() << '\n';
    }
}


int main() {

    vector<int> sorted = open_file("sorted_test.txt");
    vector<int> middle = open_file("middle_test.txt");
    vector<int> unsorted = open_file("tim_worst_test.txt");
    assert(sorted == timSort(sorted));
    cout << "Test best done\n";
    assert(sorted == timSort(middle));
    cout << "Test middle done\n";
    assert(sorted == timSort(unsorted));
    cout << "Test worse done\n";
    lin_graph();
    box();
}
