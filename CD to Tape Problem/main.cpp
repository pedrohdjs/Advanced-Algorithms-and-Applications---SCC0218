#include <iostream>
#include <vector>

using namespace std;

class CDToTapeProblem{
    public:
        CDToTapeProblem(int maxDuration, int numTracks, vector<int> tracksDuration){
            this->maxDuration = maxDuration;
            this->numTracks = numTracks;
            this->tracksDuration = tracksDuration;
            for(int i = 0; i<numTracks;i++){
                isTrackOnSolution.push_back(false);
            }
            this->solutionDuration = 0;
            this->bestSolutionDuration = 0;
        }

        ~CDToTapeProblem(){
            delete isTrackOnBestSolution;
        }

        void showAnswer(){
            for(int i = 0;i<numTracks;i++){
                if(isTrackOnBestSolution->at(i))
                    cout << tracksDuration[i] << " ";
            }
            cout << "sum:" << bestSolutionDuration << endl;
        }

        void solve(int currentTrack){
            if (currentTrack == numTracks) return;

            /*Basic backtracking: add the current processed track to the answer (if it is possible), test all 
            possible outcomes with this track on the answer*/
            if(!(solutionDuration + tracksDuration[currentTrack] > maxDuration)){ 
                addTrackToSolution(currentTrack);
                if (solutionDuration > bestSolutionDuration){
                    setCurrentSolutionAsBest();
                }
                if (solutionDuration == maxDuration){
                    return;//Best possible answer found
                }
                solve(currentTrack+1);
                removeTrackFromSolution(currentTrack);
                
            }
            //Test the possible outcomes without this track on the answer
            solve(currentTrack+1);
        }


    private:
        void addTrackToSolution(int track){
            isTrackOnSolution[track] = true;
            solutionDuration += tracksDuration[track];
        }

        void removeTrackFromSolution(int track){
            isTrackOnSolution[track] = false;
            solutionDuration -= tracksDuration[track];
        }

        void setCurrentSolutionAsBest(){
            bestSolutionDuration = solutionDuration;
            isTrackOnBestSolution = new vector<bool>(isTrackOnSolution);
        }

        int maxDuration;
        int numTracks;
        vector<int> tracksDuration;
        int solutionDuration;
        vector<bool> isTrackOnSolution;
        int bestSolutionDuration;
        vector<bool> *isTrackOnBestSolution;

};

int main(int argc, char* argv[]){
    int maxDuration;
    int numTracks;
    while (cin >> maxDuration >> numTracks){
        vector<int> tracksDuration;
        for (int i = 0; i<numTracks;i++){
            int newTrack;
            cin >> newTrack;
            tracksDuration.push_back(newTrack);
        }
        CDToTapeProblem *p = new CDToTapeProblem(maxDuration,numTracks,tracksDuration);
        p->solve(0);
        p->showAnswer();
        delete p;
    }
    
    return 0;
}