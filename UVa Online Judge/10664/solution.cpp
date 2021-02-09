#include <iostream>
#include <sstream>
#include <iterator>
#include <vector>
#include <map>

#define STATES_UNSOLVABLE -1
#define STATES_NOT_TESTED 0
#define STATES_SOLVABLE 1

using namespace std;

class Problem {
    public:
        Problem(vector<int> weights){
            this->weights = weights;            
        }

        void solve(){
            if (!initGoalValue()){ //O problema não tem solução pois a soma dos pesos é ímpar.
                return;
            }
            /*Nesse ponto, o problema vira literalmente o subset sum problem! 
            Basta tentar achar um subconjunto cuja soma é igual a goalValue.*/
            if (solveSSP(weights.size()-1,goalValue)){
                solvable = true;
            }
            else{
                solvable = false;
            }
        }

        void showAnswer(){
            cout << ((solvable) ? "YES" : "NO") << endl;
        }

    private:

        bool solveSSP(int lastVectorIndex,int value){
            pair<int,int> statePair = pair<int,int>(lastVectorIndex,value);
            if(value == 0){
                return true;
            }
            else if(lastVectorIndex < 0){
                return false;
            }
            else if(mem[statePair] != STATES_NOT_TESTED){//State was memoized
                switch (mem[statePair]){
                    case STATES_SOLVABLE:
                        return true;
                        break;
                    
                    case STATES_UNSOLVABLE:
                        return false;
                        break;
                }
            }
            else{
                bool stateIsSolvable = (solveSSP(lastVectorIndex-1,value) || solveSSP(lastVectorIndex-1,value-weights[lastVectorIndex]));
                if (stateIsSolvable) mem[statePair] = STATES_SOLVABLE;
                else mem[statePair] = STATES_UNSOLVABLE;
                return stateIsSolvable;
            }
            return false;//Remover warning do runcodes
        }

        bool initGoalValue(){
            int weightsSum = 0;
            for(int i = 0;i<(int)weights.size();i++){
                weightsSum += weights[i];
            }
            if ((weightsSum%2) != 0){
                solvable = false; //A soma dos pesos é ímpar: O número não pode ser dividido igualmente em dois.
                return false;
            }
            /*Devemos encontrar um subconjunto de itens com soma dos pesos igual à metade da soma dos pesos.
            Com isso, podemos concluir que existe outro subconjunto com a mesma soma de pesos, e, os pesos
            podem ser divididos igualmente em dois.*/
            goalValue = weightsSum/2;
            return true;
        }

        map<pair<int,int>,int> mem;
        vector<int> weights;
        int goalValue;
        bool solvable;

};

int main(int argc, char* argv[]){
    int numTestCases;
    cin >> numTestCases;
    cin.ignore();

    for (int i = 0; i<numTestCases;i++){
        string line;
        getline(cin,line);
        
        istringstream iss = istringstream(line);
        vector<int> weights;
        int weight;
        while (iss >> weight){
            weights.push_back(weight);
        }

        Problem p = Problem(weights);
        p.solve();
        p.showAnswer();
    }
    return 0;
}