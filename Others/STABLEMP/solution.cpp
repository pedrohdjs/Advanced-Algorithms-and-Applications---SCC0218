/*Important: since men/women are labeled from 1 to N, 0 indexes are not considered in this solution
Also, i tried to use OOP to write code which is simpler to understand.*/
/*
2
4
1 4 3 1 2
2 2 1 3 4
3 1 3 4 2
4 4 3 1 2
1 3 2 4 1
2 2 3 1 4
3 3 1 2 4
4 3 2 4 1
7
1 3 4 2 1 6 7 5
2 6 4 2 3 5 1 7
3 6 3 5 7 2 4 1
4 1 6 3 2 4 7 5
5 1 6 5 3 4 7 2
6 1 7 3 4 5 6 2
7 5 6 2 4 3 7 1
1 4 5 3 7 2 6 1
2 5 6 4 7 3 2 1
3 1 6 5 4 3 7 2
4 3 5 6 7 2 4 1
5 1 7 6 4 3 5 2
6 6 3 7 5 2 4 1
7 1 7 4 2 6 5 3

*/
#include <iostream>
#include <cstring>

using namespace std;


class StableMarriageProblem {
    public:

        StableMarriageProblem(){
            cin >> numMarriages;
            unformedMarriages = numMarriages;
            menMarriages = new int[numMarriages+1]();
            womenMarriages = new int[numMarriages+1]();
            readWomenPreferences();
            readMenPreferences();
            initProposals();
        }

        ~StableMarriageProblem(){
            delete [] menMarriages;
            delete [] womenMarriages;
            for (int i=0;i<numMarriages+1;i++){
                delete [] menPreferences[i];
                delete [] womenPreferences[i];
            }
            delete [] menPreferences;
            delete [] womenPreferences;
        }

        void solve(){
            int currentMan = getNextMan();
            while(currentMan != -1){
                currentMan = getNextMan();
                int currentWoman = getNextWoman(currentMan);

                hasProposed[currentMan][currentWoman] = true;

                if(!isWomanMarried(currentWoman)){
                    engage(currentMan,currentWoman);
                }
                else if (womanPrefersManToCurrentHusband(currentWoman,currentMan)){
                    makeManSingle(womenMarriages[currentWoman]);
                    engage(currentMan,currentWoman);
                    
                }

                currentMan = getNextMan();
                //printProposals();

            }
        }

        void printResults(){
            for(int i=1;i<numMarriages+1;i++){
                cout << i << " " << menMarriages[i] << endl;
            }
        }

    private:
        
        int numMarriages, unformedMarriages;
        int* menMarriages;
        int* womenMarriages;
        bool** hasProposed;
        int** menPreferences;
        int** womenPreferences;
        static const int NOT_MARRIED = 0;

        /**
         * Read the man to woman prefference list from the console and allocate necessary memory. 
         * Called on constructor.
         */
        void readMenPreferences(){
            menPreferences = new int*[numMarriages+1];
            for(int i=0;i<numMarriages+1;i++){
                menPreferences[i] = new int[numMarriages+1];
            }
            for(int i=1;i<numMarriages+1;i++){
                int currentMan;
                cin >> currentMan;
                for (int j=1;j<numMarriages+1;j++){
                    cin >> menPreferences[currentMan][j];
                }
            }
        }

        /**
         * Read the man to woman prefference list from the console and allocate necessary memory. 
         * Called on constructor.
         */
        void readWomenPreferences(){
            womenPreferences = new int*[numMarriages+1];
            for(int i=0;i<numMarriages+1;i++){
                womenPreferences[i] = new int[numMarriages+1];
            }
            for(int i=1;i<numMarriages+1;i++){
                int currentWoman;
                cin >> currentWoman;
                for (int j=1;j<numMarriages+1;j++){
                    cin >> womenPreferences[currentWoman][j];
                }
            }
        }

        void initProposals(){
            hasProposed = new bool*[numMarriages+1];
            for(int i=0;i<numMarriages+1;i++){
                hasProposed[i] = new bool[numMarriages+1];
                memset(hasProposed[i],false,numMarriages+1);
            }

        }

        int getNextMan(){
            for(int i = 1;i<numMarriages+1;i++){
                if (!isManMarried(i) && !hasManProposedToEveryone(i)){
                    return i;
                }
            }
            return -1;
        }

        bool hasManProposedToEveryone(int currentMan){
            int mansLastOption = menPreferences[currentMan][numMarriages];
            return hasProposed[currentMan][mansLastOption];
        }

        int getNextWoman(int currentMan){
            for(int i = 1;i<numMarriages+1;i++){
                int currentWoman = menPreferences[currentMan][i];
                if (!hasProposed[currentMan][currentWoman]) return currentWoman;
            }
            return -1;
        }

        bool isManMarried(int currentMan){
            return menMarriages[currentMan] != 0;
        }

        bool isWomanMarried(int currentWoman){
            return womenMarriages[currentWoman] != 0;
        }

        void engage(int currentMan, int currentWoman){
            menMarriages[currentMan] = currentWoman;
            womenMarriages[currentWoman] = currentMan;
        }

        void makeManSingle(int currentMan){
            menMarriages[currentMan] = NOT_MARRIED;
        }

        bool womanPrefersManToCurrentHusband(int currentWoman, int currentMan){
            int currentHusband = womenMarriages[currentWoman];
            for(int i = 1;i<numMarriages+1;i++){
                int currentManOption = womenPreferences[currentWoman][i];
                //Whichever value is found first
                if (currentManOption == currentHusband){ 
                    return false;
                }
                else if (currentManOption == currentMan){
                     return true;
                }
            }
            return false;
        }

        void printProposals(){
            cout << "x ";
            for (int i = 1;i<numMarriages+1;i++) cout << i << " ";
            cout << endl;
            for (int i = 1;i<numMarriages+1;i++){
                cout << i << " ";
                for(int j =1;j<numMarriages+1;j++){
                    cout << hasProposed[i][j] << " ";
                }
            cout << endl;
            }
        }


        void printManPreferenceList(){
            for (int i = 1;i<numMarriages+1;i++){
                cout << i << " ";
                for(int j =1;j<numMarriages+1;j++){
                    cout << menPreferences[i][j] << " ";
                }
            cout << endl;
            }
        }

        void printWomanPreferenceList(){
            for (int i = 1;i<numMarriages+1;i++){
                cout << i << " ";
                for(int j =1;j<numMarriages+1;j++){
                    cout << womenPreferences[i][j] << " ";
                }
            cout << endl;
            }
        }
};    


int main(int argc, char* argv[]){
    int numTestCases;
    cin >> numTestCases;
    for (int i = 0; i < numTestCases; i++) {
        StableMarriageProblem* p = new StableMarriageProblem();
        p->solve();
        p->printResults();
        delete p;
    }
    return 0;
}
