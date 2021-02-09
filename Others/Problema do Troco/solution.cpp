#include <iostream>
#include <climits>
#include <vector>
#include <map>

#define NOT_SOLVABLE -1

using namespace std;

class ChangeProblem{
    public:
        ChangeProblem(int initialValue, vector<int> coins){
            this->initialValue = initialValue;
            this->coins = coins;
            for(int coinValue : coins){
                //The minimal coins in the change for the exact value of a coin is 1 coin
                this->minimalChange[coinValue] = 1;
            }
        }
        
        void solve(){
            int solution = solveFor(initialValue);
            if (solution != NOT_SOLVABLE)
                cout << solveFor(initialValue) << endl;
            else 
                cout << "sem solucao" << endl;
        }

    private:

        int solveFor(int value){
            if (value == 0){
                //A defined value, but "minimalChange[value]" would evaluate to false.
                return 0;
            }
            else if (minimalChange[value]){
                //This value was already calculated
                return minimalChange[value];
            }

            else{
                //Djikstra-like logic
                int currentBestAnswer = INT_MAX;
                for(int coinValue : coins){ //For each possible coin
                    if (coinValue > value) //Not possible
                        continue;
                    int currentAnswer = solveFor(value-coinValue) + 1;
                    //If the current answer is better than the current "best" one and valid
                    if ((currentAnswer < currentBestAnswer) && (currentAnswer != NOT_SOLVABLE + 1))
                        currentBestAnswer = currentAnswer;
                }
                if(currentBestAnswer != INT_MAX){ //An answer was in fact found!
                    minimalChange[value] = currentBestAnswer; //Memorize it
                    return currentBestAnswer;
                }
                else{ //No answer
                    minimalChange[value] = NOT_SOLVABLE;
                    return NOT_SOLVABLE;
                }
                
            }

            return 1;
        }

        vector<int> coins;
        map<int,int> minimalChange;
        int initialValue;
};

int main(int argc, char* argv[]){
    int numTestCases;
    cin >> numTestCases;

    for(int i = 0; i<numTestCases; i++){
        int value, numCoins;
        vector<int> coins;
        cin >> value >> numCoins;
        for (int j = 0; j<numCoins; j++){
            int currentCoin;
            cin >> currentCoin;
            coins.push_back(currentCoin);
        }
        ChangeProblem p = ChangeProblem(value,coins);
        p.solve();
    }
    
    return 0;
}