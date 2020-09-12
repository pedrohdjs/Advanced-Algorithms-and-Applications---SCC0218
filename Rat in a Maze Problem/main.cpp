#include <iostream>
#include <vector>
#define CLEAR 0
#define WALL 1
#define VISITED 2

using namespace std;

class RatInAMazeProblem{
    public:
        RatInAMazeProblem(int mazeSize){
            this->mazeSize = mazeSize;
            this->numSolutions = 0;
            for(int i = 0; i<mazeSize; i++){
                vector<int> column;
                for(int j = 0; j<mazeSize; j++){
                    int cellValue;
                    cin >> cellValue;
                    column.push_back(cellValue);
                }
                this->maze.push_back(column);
            }
        }

        void solve(){
            tracePath(0,0);
        }

        void showResults(){
            cout << numSolutions;
        }

    private:
        void tracePath(int x, int y){
            if (isOutOfBounds(x,y)) 
                return;
            else if (isVisited(x,y) || isWall(x,y))
                return;
            if (hasReachedMazeEnd(x,y)){
                this->numSolutions++;
                return;
            }
            maze[x][y] = VISITED;//Add cell to answer
            //Repeat the procedure for all surrounding valid cells (up, down, left and right)
            tracePath(x,y-1);
            tracePath(x+1,y);
            tracePath(x,y+1);
            tracePath(x-1,y);
            maze[x][y] = CLEAR;//Remove cell from answer
            return;
        }

        bool isOutOfBounds(int x, int y){
            return (x<0 || y<0 || x>=mazeSize || y>=mazeSize);
        }

        /*If a cell is marked as visited, it shouldn't be processed again until marked as clear
        This prevents "loop" paths*/
        bool isVisited(int x, int y){
            return (maze[x][y] == VISITED);
        }

        bool isWall(int x, int y){
            return (maze[x][y] == WALL);
        }

        bool hasReachedMazeEnd(int x, int y){
            return (x == mazeSize-1 && y == mazeSize-1);
        }

        int mazeSize;
        int numSolutions;
        vector<vector<int>> maze;
};

int main(int argc, char* argv[]){
    int mazeSize;
    cin >> mazeSize;
    RatInAMazeProblem* p = new RatInAMazeProblem(mazeSize);
    p->solve();
    p->showResults();
    delete p;

    return 0;
}