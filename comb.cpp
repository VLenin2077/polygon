#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <cassert>
#include <chrono>
using namespace std;


vector<int> open_file(string filename){ //функция для перевода чисел из файла в вектор
    fstream file;
    file.open(filename); 
    vector<int> v{}; //n * 4 байт
    int num; // + 4 байт
    while (file >> num){  //O(n)
            v.push_back(num); //O(1)
    }
    file.close();
    return v;
}


vector<int> combSort(vector<int> &arr) {
    int n = arr.size(); //n * 4 байт
    int step = n; // + 4 байт
    bool flag = false; // + 2 байт
    while (step > 1 || flag) { //O(n)
        if (step > 1) {
            step = step * 4 / 5;
        }
        flag = false;
        int i = 0;
        while (i + step < n) { //O(n)
            if (arr[i] > arr[i + step]){
                flag = true;
                swap(arr[i], arr[i + step]);
            }
            i += step;
        }
    }
    return arr;
}
// O(n), n*8 + 10 байт

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
        vector<int> res = combSort(arr);
        std::chrono::high_resolution_clock::time_point end = std::chrono::high_resolution_clock::now(); //конец подсчета времени
        std::chrono::duration<double> duration = end - start;
        cout << i << ' ' << duration.count() << '\n';
    }
}


void box(){
    vector<int> nums = open_file("box.txt");
    for (int i = 1; i <= 50; i++){
        std::chrono::high_resolution_clock::time_point start = std::chrono::high_resolution_clock::now();
        combSort(nums);
        std::chrono::high_resolution_clock::time_point end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> duration = end - start;
        cout << duration.count() << '\n';
    }
}


int main(){
    // vector<int> sorted = open_file("sorted_test.txt");
    // vector<int> middle = open_file("middle_test.txt");
    // vector<int> unsorted = open_file("unsorted_test.txt");
    // assert(sorted == combSort(sorted));
    // cout << "Test best done\n";
    // assert(sorted == combSort(middle));
    // cout << "Test middle done\n";
    // assert(sorted == combSort(unsorted));
    // cout << "Test worse done\n";
    // lin_graph();
    box();
}