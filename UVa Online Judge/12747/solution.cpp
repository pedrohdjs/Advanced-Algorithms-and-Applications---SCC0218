#include <iostream>
#include <vector>
#include <cstring>
#define NOT_SOLVED -1

using namespace std;

int min(int i1, int i2){
    return (i1 < i2) ? i1 : i2;
}

class Problem {
    public:

        Problem(vector<int> v1, vector<int> v2){
            this->v1 = v1;
            this->v2 = v2;
            memset(this->mem,NOT_SOLVED,sizeof(this->mem));
        }

        int solve(){
            return solveFor(v1.size(),v2.size());
            // for(int i = 0; i<v1.size();i++){
            //     for(int j = 0; j<v2.size(); j++){
            //         cout << mem[i][j] << " ";
            //     }
            //     cout << endl;
            // }

        }

    private:

        int solveFor(int m, int n){
            if (m == 0){//Caso base 1
                return n;
            }
            else if (n == 0){//Caso base 2
                return m;
            }
            else if (mem[m-1][n-1] != NOT_SOLVED){//Resposta memoizada
                return mem[m-1][n-1];
            }
            else if (v1[m-1] == v2[n-1]){
                mem[m-1][n-1] = solveFor(m-1,n-1);
                return mem[m-1][n-1];
            }
            else {
                mem[m-1][n-1] = 1 + min(
                                        solveFor(m-1,n),//Remove
                                        solveFor(m,n-1) //Insere
                                    );
                return mem[m-1][n-1];
            }
            
        }

        vector<int> v1, v2;
        int mem[500][500];

};

int main(int argc, char* argv[]){
    int numTestCases;
    cin >> numTestCases;
    for (int i = 1; i<=numTestCases;i++){
        int vectorSize;
        cin >> vectorSize;

        vector<int> v1, v2;
        for (int j = 0;j<vectorSize;j++){
            int number;
            cin >> number;
            v1.push_back(number);
        }
        for (int j = 0;j<vectorSize;j++){
            int number;
            cin >> number;
            v2.push_back(number);
        }

        Problem p = Problem(v1,v2);
        cout << "Case " << i << ": " << p.solve() << endl;
    }
    return 0;
}