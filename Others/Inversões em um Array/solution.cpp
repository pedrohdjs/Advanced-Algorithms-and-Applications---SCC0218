#include <iostream>
#include <sstream>
#include <iterator>
#include <vector>

using namespace std;

class InversionNumberProblem{
    public:
        InversionNumberProblem(vector<int> numbers){
            this->numbers = numbers;
            this->temp = vector<int>(numbers.size());
        }

        void solve(){
            int res = numInversions(0,this->numbers.size()-1);
            cout << res << endl;
        }

    private:

        int numInversions(int min, int max){
            int inversions = 0;
            if (max > min){
                int mid = (min+max)/2;
                inversions += numInversions(min,mid);
                inversions += numInversions(mid+1,max);
                inversions += merge(min,mid+1,max);
            }
            return inversions;
        }

        int merge(int min, int mid, int max){
            int inversions = 0, 
                i = min, 
                j = mid,
                k = min;

            while((i<=mid-1) && (j<=max)){

                if(numbers[i] > numbers[j]){
                    temp[k++] = numbers[j++];
                    inversions = inversions + (mid - i);
                }

                else{       
                    temp[k++] = numbers[i++];
                }
            }

            while (i <= mid-1){
                temp[k++] = numbers[i++];
            }

            while (j <= max){
                temp[k++] = numbers[j++];
            }

            for(int i = min; i<=max;i++){
                numbers[i] = temp[i];
            }
            
            return inversions;
        }

        vector<int> numbers;
        vector<int> temp;
};

int main (){
    int numTestCases;
    cin >> numTestCases;

    for (int i = 0; i<numTestCases; i++){
        vector<int> numbers;
        int size;
        cin >> size;
        for (int i = 0; i<size; i++){
            int num;
            cin >> num;
            numbers.push_back(num);
        }
        InversionNumberProblem p = InversionNumberProblem(numbers);
        p.solve();
    }
    return 0;
}