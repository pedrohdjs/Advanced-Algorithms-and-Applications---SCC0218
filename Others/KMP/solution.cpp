#include <iostream>
#include <string>
#include <vector>
#include <fstream>


using namespace std;

class Problem{

    public:

        Problem(string s1, string s2){
            this->s1 = s1;
            this->s2 = s2;

            prefixTable.push_back(0);
            int length = 0;
            int i = 1;
            prefixTable = vector<int>(s2.length());
            prefixTable[0]=0;
            while(i<(int)s2.length()){
                if(s2[i]==s2[length]){
                    length++;
                    prefixTable[i] = length;
                    i++;
                }
                else{
                    if(length != 0){
                        length = prefixTable[length-1];
                    }
                    else{
                        prefixTable[i] = 0;
                        i++;
                    }
                }
            }            
        }

        void solve(){
            int i=0, j=0;
            for(i = 0; i<(int)s1.size(); i=i){
                bool currentCharIsValid = (s1[i] == s2[j]);
                if(currentCharIsValid){
                    i++;
                    j++;
                }
                
                if (j == (int)s2.size()){
                    cout << "O padrao foi encontrado na posicao " << i-j << endl;
                    j = prefixTable[j-1];
                }

                else if (!currentCharIsValid){
                    if(j != 0){
                        j = prefixTable[j-1];
                    }
                    else{
                        i++;
                    }
                }
            }
        }

    private:

        string s1,s2;
        vector<int> prefixTable;


};

int main(int argc, char* argv[]){
    string s1, s2;
    cin >> s1;
    cin >> s2;
    Problem p = Problem(s1,s2);
    p.solve();
    return 0;
}