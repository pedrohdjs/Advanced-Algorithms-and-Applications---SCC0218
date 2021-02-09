#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <map>

using namespace std;

const char FINAL_STATE_POSITIONS[9] = {'1','2','3','4','5','6','7','8','x'};
const char POSSIBLE_MOVES[4] = {'d','l','u','r' };
map<char,pair<int,int>> FINAL_STATE_POSITIONS_MANHATTAN_COORDINATES = { {'1',pair<int,int>(0,0)},
                                                                        {'2',pair<int,int>(0,1)},
                                                                        {'3',pair<int,int>(0,2)},
                                                                        {'4',pair<int,int>(1,0)},
                                                                        {'5',pair<int,int>(1,1)},
                                                                        {'6',pair<int,int>(1,2)},
                                                                        {'7',pair<int,int>(2,0)},
                                                                        {'8',pair<int,int>(2,1)},
                                                                        {'x',pair<int,int>(2,2)} };


class State {
    public:
        State(vector<char> positions,int xPosition, char movementBefore, int depth){
            this->positions = positions;
            this->xPosition = xPosition;
            this->movementBefore = movementBefore;
            this->depth = depth;
        }

        State(){
            this->xPosition = -1;
        }

        int getDepth(){
            return this->depth;
        }

        char getMovementBefore(){
            return this->movementBefore;
        }

        bool isValidState(){
            return (this->xPosition != -1);
        }

        bool isFinalState(){
            for(int i = 0; i<9; i++){
                if (this->positions[i] != FINAL_STATE_POSITIONS[i])
                    return false;
            }
            return true;
        }

        State getNextState(char move){
            vector<char> newPositions = vector<char>(this->positions);
            int newXPosition = this->xPosition;

            switch (move){
                case ('r'):
                    if (this->xPosition == 2 || this->xPosition == 5 || this->xPosition == 8)
                        return State();//Invalid state returned
                    newXPosition = this->xPosition + 1;            
                    break;

                case ('l'):
                    if (this->xPosition == 0 || this->xPosition == 3 || this->xPosition == 6)
                        return State();//Invalid state returned
                    newXPosition = this->xPosition - 1;
              
                    break;

                case ('u'):
                    if (this->xPosition == 0 || this->xPosition == 1 || this->xPosition == 2)
                        return State();//Invalid state returned
                    newXPosition = this->xPosition - 3;              
                    break;

                case ('d'):
                    if (this->xPosition == 6 || this->xPosition == 7 || this->xPosition == 8)
                        return State();//Invalid state returned
                    newXPosition = this->xPosition + 3;
              
                    break;

                default:
                    return State();//Invalid state returned
                    break;
            
            
            }
            //Swap the old and new X positions;
            newPositions[xPosition] = newPositions[newXPosition];
            newPositions[newXPosition] = 'x';  
            return State(newPositions,newXPosition,move,this->depth+1);
            
        }

        vector<State> getAllNextStates(){
            vector<State> nextStates;
            for (char move : POSSIBLE_MOVES){
                State nextState = this->getNextState(move);
                if (nextState.isValidState()){
                    nextStates.push_back(nextState);
                }
            }
            return nextStates;
        }

        string toString(){
            string s = "";
            for(int i = 0; i<9; i++)
                s += this->positions[i];
            return s;
        }

        //Heuristic function using manhattan distance between the current position and the goal position
        int distanceToFinalState(){
            int distance = 0;
            for(int i = 0; i<9; i++){
                if (this->positions[i] != 'x'){
                    distance += abs(FINAL_STATE_POSITIONS_MANHATTAN_COORDINATES[this->positions[i]].first  - i/3) 
                              + abs(FINAL_STATE_POSITIONS_MANHATTAN_COORDINATES[this->positions[i]].second - i%3);
                }
            }
            return distance;
        }

        bool isSolvable(){
            return (this->numInversions()%2 == 0);
        }

        int numInversions(){
            int inversions = 0;
            for(int i = 0; i<9;i++){
                if (positions[i] == 'x') continue;
                for(int j = i+1; j<9; j++){

                    if(positions[j] < positions[i])
                        inversions++;
                }
            }
            return inversions;
        }

    private:
        vector<char> positions;
        int xPosition;
        char movementBefore;
        int depth;
};

class CompareState {
    public:
        CompareState(){

        }

        bool operator()(State & s1, State & s2) {       
            return s1.distanceToFinalState() + s1.getDepth() > s2.distanceToFinalState() + s2.getDepth();
        }
};


class EightPuzzleProblem{
    public:
        EightPuzzleProblem(State initialState){
            this->initialState = initialState;
            this->finalState = State();
            this->previousState[initialState.toString()] = State();
        }

        void solve(){
            if (!this->isSolvable()) return;
            priority_queue<State,vector<State>,CompareState> states{CompareState()};
            states.push(this->initialState);

            while(!states.empty()){
                State currentState = states.top();
                states.pop();

                if (currentState.isFinalState()){
                    this->finalState = currentState;
                    return;
                }

                if (visited[currentState.toString()]) 
                    continue;//Skip the current iteration since this state was already processed

                visited[currentState.toString()] = true;

                vector<State> nextStates = currentState.getAllNextStates();
                for (State s : nextStates){
                    if(!found[s.toString()]){
                        states.push(s);
                        previousState[s.toString()] = currentState;
                        found[s.toString()] = true;
                    }             
                }

            }
        }

        void showAnswer(){
            if (!this->finalState.isValidState()){
                cout << "unsolvable" << endl;//No solution found
            }
            else{
                string s = "";
                State currentState = this->finalState;
                while (currentState.getMovementBefore() != 'x'){
                    s = currentState.getMovementBefore() + s;
                    currentState = previousState[currentState.toString()];
                }
                
                cout << s << endl;
            }
        }

    private:
        bool isSolvable(){
            return this->initialState.isSolvable();
        }
        
    
        State initialState;
        State finalState;
        map<string,bool> visited;
        map<string,bool> found;
        map<string,State> previousState;

};

int main(int argc, char* argv[]){
    int numTests;
    cin >> numTests;
    for (int i = 0; i<numTests;i++){
        int xPosition;
        vector<char> positions;
        for (int j = 0; j<9;j++){
            char value;
            cin >> value;
            if (value == '0') 
                value = 'x';
            positions.push_back(value);
            if(value == 'x'){
                xPosition = j;
            }
        }
        State initialState = State(positions,xPosition,'x',0);

        EightPuzzleProblem p = EightPuzzleProblem(initialState);
        p.solve();
        p.showAnswer();
        if(i != numTests -1 )
            cout << endl;
        
    }
    return 0;
}