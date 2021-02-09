#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <map>

using namespace std;

const int STATE_MOVES[8][4] = { { 1, 0, 0, 0},
                                {-1, 0, 0, 0},
                                { 0, 1, 0, 0},
                                { 0,-1, 0, 0},
                                { 0, 0, 1, 0},
                                { 0, 0,-1, 0},
                                { 0, 0, 0, 1},
                                { 0, 0, 0,-1} };

/*DISTANCE_BETWEEN[i][j] gives the minimal distance between two numbers on the problem, suposing
number i can be reached by number j. It's important in our heuristic which will be used to sort the priority queue
of all possible outcomes.*/
const int DISTANCE_BETWEEN[10][10]={{0,1,2,3,4,5,4,3,2,1},
                                    {1,0,1,2,3,4,5,4,3,2},
                                    {2,1,0,1,2,3,4,5,4,3},
                                    {3,2,1,0,1,2,3,4,5,4},
                                    {4,3,2,1,0,1,2,3,4,5},
                                    {5,4,3,2,1,0,1,2,3,4},
                                    {4,5,4,3,2,1,0,1,2,3},
                                    {3,4,5,4,3,2,1,0,1,2},
                                    {2,3,4,5,4,3,2,1,0,1},
                                    {1,2,3,4,5,4,3,2,1,0}};

class State{
    public:
        State(int digits[4], int depth){
            this->digits[0] = digits[0];
            this->digits[1] = digits[1];
            this->digits[2] = digits[2];
            this->digits[3] = digits[3];
            this->depth = depth;
        }

        State(const State *state){
            this->digits[0] = state->digits[0];
            this->digits[1] = state->digits[1];
            this->digits[2] = state->digits[2];
            this->digits[3] = state->digits[3];
            this->depth = state->depth;
        }

        State(){
            this->digits[0] = 0;
            this->digits[1] = 0;
            this->digits[2] = 0;
            this->digits[3] = 0;
            this->depth = 0;
        }

        vector<State> nextStates(){
            vector<State> nextStates;
            for (int i = 0; i<8;i++){
                State newState(this);
                for(int j = 0;j<4;j++){
                    newState.digits[j] += STATE_MOVES[i][j];
                    if (newState.digits[j] > 9 ) newState.digits[j] = 0;
                    else if (newState.digits[j] < 0 ) newState.digits[j] = 9;
                }
                newState.depth = this->depth+1;
                nextStates.push_back(newState);
            }
            return nextStates;
        }

        string toString(){
            string str = "";
            for(int i = 0; i<4;i++){
                str.append(std::to_string(digits[i]));
            }
            return str;
        }

        bool equals(State other){
            for (int i = 0; i<4; i++){
                if (this->digits[i] != other.digits[i]) return false;
            }
            return true;
        }

        /*Heuristic function (This is an optimistic heuristic because s1.distanceTo(s2) returns
        the minimal possible number of moves to get to s2 from s1, which is smaller or equal to
        the actual number of moves required*/
        int distanceTo(State other){
            int distance = 0;
            for (int i = 0; i<4; i++){
                distance += DISTANCE_BETWEEN[this->digits[i]][other.digits[i]];
            }
            return distance;
        }

        int getDepth(){
            return this->depth;
        }

        int* getDigits(){
            return this->digits;
        }

    private:
        int digits[4];
        int depth;
        friend class CompareState;
};

/*Used to sort the possible states in the priority queue in ascending order of distance towards the
final state*/
class CompareState { 
    State finalState;
    public:
    CompareState(State finalState){
        this->finalState = finalState;
    }
    bool operator()(State & s1, State & s2) 
    {       
        //A* algorithm: heuristic(state) + depth(state)
        return (s1.distanceTo(finalState) + s1.depth >  s2.distanceTo(finalState) + s2.depth);
    }         
}; 


class PlayingWithWheelsProblem{
    public:
        PlayingWithWheelsProblem(State startingState, State finalState, vector<State> forbiddenStates){
            this->startingState = startingState;
            this->finalState = finalState;

            for (State s : forbiddenStates){
                this->visited[s.toString()] = true;
            }
            this->answer = -1;
        }

        void solve(){
            priority_queue<State,vector<State>,CompareState> q{CompareState(finalState)};
            //Invalid state
            if (visited[startingState.toString()]) 
                return;
            q.push(startingState);

            while (!q.empty()){
                State current = q.top();
                q.pop();

                if(visited[current.toString()]) 
                    continue;
                    
                visited[current.toString()] = true;

                if (current.equals(finalState)){
                    this->answer = current.getDepth();
                    return;
                }

                vector<State> nextStates = current.nextStates();
                for (State s : nextStates){
                    q.push(s);
                }
            } 
        }

        void showAnser(){
            cout << answer << endl;
        }

    private:
        State startingState;
        State finalState;
        map<string,bool> visited;
        int answer;
};

int main(int argc, char* argv[]){
    int numCases;
    cin >> numCases;
    for (int i = 0; i<numCases; i++){
        int digits[4];
        for (int j = 0; j<4; j++){
            cin >> digits[j];
        }
        State startingState = State(digits,0);
        for (int j = 0; j<4; j++){
            cin >> digits[j];
        }
        State finalState = State(digits,0);
        int numForbidden;
        vector<State> forbiddenStates;
        cin >> numForbidden;
        for (int j = 0; j<numForbidden;j++){
            for (int k = 0; k<4; k++){
                cin >> digits[k];
            }
            forbiddenStates.push_back(State(digits,0));
        }
        PlayingWithWheelsProblem p = PlayingWithWheelsProblem(startingState,finalState,forbiddenStates);
        p.solve();
        p.showAnser();
    }
    return 0;
}
