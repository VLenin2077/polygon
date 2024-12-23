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


vector<int> Cocktail(vector<int> &nums){
    int right = nums.size() -1; //+4 bytes
    int left = 0; //+4 bytes
    while (right >= left){ //O(2*n) == O(n)
        for (int i = left; i < right; i++){ //O(n) проход слева направо
            if (nums[i] > nums[i+1]){
                swap(nums[i], nums[i+1]);
            }
        }
        right--; //обновляем границу прохода
        for (int j = right; j > left; j--){ //O(n) проход справо налево
            if (nums[j] < nums[j-1]){
                swap(nums[j], nums[j-1]);
            }
        }
        left++; //обновляем границу прохода
    }
    return nums;
}
// O(n), n*8 + 12 bytes

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
        vector<int> nums = open_for_lines("numbers.tsv", i);
        std::chrono::high_resolution_clock::time_point start = std::chrono::high_resolution_clock::now();
        vector<int> res = Cocktail(nums);
        std::chrono::high_resolution_clock::time_point end = std::chrono::high_resolution_clock::now(); //конец подсчета времени
        std::chrono::duration<double> duration = end - start;
        cout << i << ' ' << duration.count() << '\n';
    }
}


void box(){
    vector<int> nums = open_file("box1e5.tsv");
    for (int i = 1; i <= 50; i++){
        std::chrono::high_resolution_clock::time_point start = std::chrono::high_resolution_clock::now();
        Cocktail(nums);
        std::chrono::high_resolution_clock::time_point end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> duration = end - start;
        cout << duration.count() << '\n';
    }
}

int main(){
    // vector<int> sorted = open_file("sorted_test.txt");
    // vector<int> middle = open_file("middle_test.txt");
    // vector<int> unsorted = open_file("unsorted_test.txt");
    // assert(sorted == Cocktail(sorted));
    // cout << "Test best done\n";
    // assert(sorted == Cocktail(middle));
    // cout << "Test middle done\n";
    // assert(sorted == Cocktail(unsorted));
    // cout << "Test worse done\n";
    // lin_graph();
    box();
}