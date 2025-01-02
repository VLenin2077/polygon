#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int maxSatisfaction(vector<int>& satisfaction) { // 4*n byte
        int n = satisfaction.size(); //+4 byte 
        int sum = 0;// +4 byte
        int coef = 0; // + 4 byte
        sort(begin(satisfaction), end(satisfaction)); //O(nlogn)
        for (int i = 1; i <= n; i++){ //O(n)
            coef += i*satisfaction[i-1];
            sum += satisfaction[i-1];
        }
        int sumer_ans = coef;
        for (int i = 0; i < n; i++){//O(n)
            coef -= sum;
            sum -= satisfaction[i];
            sumer_ans = max(sumer_ans, coef);
        }
    return sumer_ans;
    }  
//O(n) + O(n) + O(nlogn) = O(nlogn)  4*n + 12 byte
int main(){
    vector<int> f = {-1,-8,0,5,-9};
    int j = maxSatisfaction(f);
    cout << j;
}

